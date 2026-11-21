/*
    This example code is in the Public Domain (or CC0 licensed, at your option.)

    Unless required by applicable law or agreed to in writing, this
    software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
    CONDITIONS OF ANY KIND, either express or implied.
*/

#include "../core/options.h"
#if(SPDIF_OUT != 255)
#include "spdif.h"
#define CONFIG_I2S_SUPPRESS_DEPRECATE_WARN true
#define CONFIG_ADC_SUPPRESS_DEPRECATE_WARN true
#include <driver/i2s.h>
#include <esp_heap_caps.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
using namespace std;

#define I2S_NUM			        I2S_NUM_0
#define SPDIF_BLOCK_SIZE	    192*8*2 //(SPDIF_BLOCK_SAMPLES * (BMC_BITS_PER_SAMPLE/8) * I2S_CHANNELS)
#define SPDIF_BUF_ARRAY_SIZE	(SPDIF_BLOCK_SIZE / sizeof(uint32_t))

static uint32_t spdif_buf[SPDIF_BUF_ARRAY_SIZE];
static uint32_t *spdif_ptr;

// PCM queue separates the decoder from the real-time SPDIF/I2S output task.
#define SPDIF_QUEUE_SAMPLES 2048
static int16_t (*spdif_samples)[2] = nullptr;
static volatile uint16_t spdif_write_index = 0;
static volatile uint16_t spdif_read_index = 0;
static portMUX_TYPE spdif_queue_mux = portMUX_INITIALIZER_UNLOCKED;
static TaskHandle_t spdif_task_handle = nullptr;
static volatile uint32_t spdif_pending_rate = 0;
static volatile bool spdif_ftp_paused = false;

static void spdif_output_task(void *parameter);
static void spdif_encode_sample(const int16_t smp[2]);

// BMC (Biphase Mark Coded) values (bit order reversed, i.e. LSB first)
static const uint16_t spdif_bmclookup[256] = {
    0xcccc, 0x4ccc, 0x2ccc, 0xaccc, 0x34cc, 0xb4cc, 0xd4cc, 0x54cc,
    0x32cc, 0xb2cc, 0xd2cc, 0x52cc, 0xcacc, 0x4acc, 0x2acc, 0xaacc,
    0x334c, 0xb34c, 0xd34c, 0x534c, 0xcb4c, 0x4b4c, 0x2b4c, 0xab4c,
    0xcd4c, 0x4d4c, 0x2d4c, 0xad4c, 0x354c, 0xb54c, 0xd54c, 0x554c,
    0x332c, 0xb32c, 0xd32c, 0x532c, 0xcb2c, 0x4b2c, 0x2b2c, 0xab2c,
    0xcd2c, 0x4d2c, 0x2d2c, 0xad2c, 0x352c, 0xb52c, 0xd52c, 0x552c,
    0xccac, 0x4cac, 0x2cac, 0xacac, 0x34ac, 0xb4ac, 0xd4ac, 0x54ac,
    0x32ac, 0xb2ac, 0xd2ac, 0x52ac, 0xcaac, 0x4aac, 0x2aac, 0xaaac,
    0x3334, 0xb334, 0xd334, 0x5334, 0xcb34, 0x4b34, 0x2b34, 0xab34,
    0xcd34, 0x4d34, 0x2d34, 0xad34, 0x3534, 0xb534, 0xd534, 0x5534,
    0xccb4, 0x4cb4, 0x2cb4, 0xacb4, 0x34b4, 0xb4b4, 0xd4b4, 0x54b4,
    0x32b4, 0xb2b4, 0xd2b4, 0x52b4, 0xcab4, 0x4ab4, 0x2ab4, 0xaab4,
    0xccd4, 0x4cd4, 0x2cd4, 0xacd4, 0x34d4, 0xb4d4, 0xd4d4, 0x54d4,
    0x32d4, 0xb2d4, 0xd2d4, 0x52d4, 0xcad4, 0x4ad4, 0x2ad4, 0xaad4,
    0x3354, 0xb354, 0xd354, 0x5354, 0xcb54, 0x4b54, 0x2b54, 0xab54,
    0xcd54, 0x4d54, 0x2d54, 0xad54, 0x3554, 0xb554, 0xd554, 0x5554,
    0x3332, 0xb332, 0xd332, 0x5332, 0xcb32, 0x4b32, 0x2b32, 0xab32,
    0xcd32, 0x4d32, 0x2d32, 0xad32, 0x3532, 0xb532, 0xd532, 0x5532,
    0xccb2, 0x4cb2, 0x2cb2, 0xacb2, 0x34b2, 0xb4b2, 0xd4b2, 0x54b2,
    0x32b2, 0xb2b2, 0xd2b2, 0x52b2, 0xcab2, 0x4ab2, 0x2ab2, 0xaab2,
    0xccd2, 0x4cd2, 0x2cd2, 0xacd2, 0x34d2, 0xb4d2, 0xd4d2, 0x54d2,
    0x32d2, 0xb2d2, 0xd2d2, 0x52d2, 0xcad2, 0x4ad2, 0x2ad2, 0xaad2,
    0x3352, 0xb352, 0xd352, 0x5352, 0xcb52, 0x4b52, 0x2b52, 0xab52,
    0xcd52, 0x4d52, 0x2d52, 0xad52, 0x3552, 0xb552, 0xd552, 0x5552,
    0xccca, 0x4cca, 0x2cca, 0xacca, 0x34ca, 0xb4ca, 0xd4ca, 0x54ca,
    0x32ca, 0xb2ca, 0xd2ca, 0x52ca, 0xcaca, 0x4aca, 0x2aca, 0xaaca,
    0x334a, 0xb34a, 0xd34a, 0x534a, 0xcb4a, 0x4b4a, 0x2b4a, 0xab4a,
    0xcd4a, 0x4d4a, 0x2d4a, 0xad4a, 0x354a, 0xb54a, 0xd54a, 0x554a,
    0x332a, 0xb32a, 0xd32a, 0x532a, 0xcb2a, 0x4b2a, 0x2b2a, 0xab2a,
    0xcd2a, 0x4d2a, 0x2d2a, 0xad2a, 0x352a, 0xb52a, 0xd52a, 0x552a,
    0xccaa, 0x4caa, 0x2caa, 0xacaa, 0x34aa, 0xb4aa, 0xd4aa, 0x54aa,
    0x32aa, 0xb2aa, 0xd2aa, 0x52aa, 0xcaaa, 0x4aaa, 0x2aaa, 0xaaaa
};

const uint32_t VUCP_PREAMBLE_B = 0xCCE80000; // 11001100 11101000
const uint32_t VUCP_PREAMBLE_M = 0xCCE20000; // 11001100 11100010
const uint32_t VUCP_PREAMBLE_W = 0xCCE40000; // 11001100 11100100

// initialize I2S for S/PDIF transmission
void spdif_init(int rate)
{
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    	.sample_rate = (uint32_t)rate * 2,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // interrupt priority
        .dma_buf_count = psramInit()?16:4,
        .dma_buf_len = 192*2,
        .use_apll = true,
	    .tx_desc_auto_clear = true,
    };
    i2s_pin_config_t pin_config = {
        .bck_io_num = -1,
        .ws_io_num = -1,
        .data_out_num = SPDIF_OUT,
        .data_in_num = -1,
    };

    esp_err_t installErr = i2s_driver_install((i2s_port_t)I2S_NUM, &i2s_config, 0, NULL);
    if (installErr != ESP_OK) {
        log_e("SPDIF I2S driver install failed: %d", installErr);
        return;
    }
    i2s_set_pin((i2s_port_t)I2S_NUM, &pin_config);
#if (I2S_BCLK != 255)
    pinMode(I2S_BCLK, OUTPUT);
#endif
#if (I2S_LRC != 255)
    pinMode(I2S_LRC, OUTPUT);
#endif
    // Allocate the PCM queue in PSRAM when available to preserve internal RAM.
    if (!spdif_samples) {
        spdif_samples = (int16_t (*)[2])heap_caps_malloc(
            SPDIF_QUEUE_SAMPLES * sizeof(*spdif_samples),
            MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
        if (!spdif_samples) {
            spdif_samples = (int16_t (*)[2])malloc(
                SPDIF_QUEUE_SAMPLES * sizeof(*spdif_samples));
        }
    }
    if (!spdif_samples) {
        log_e("SPDIF PCM queue allocation failed");
        return;
    }
    spdif_write_index = 0;
    spdif_read_index = 0;
    spdif_ptr = spdif_buf;

    if (!spdif_task_handle) {
        BaseType_t taskCreated = xTaskCreate(
            spdif_output_task, "SPDIF_OUT", 4096, nullptr, 2, &spdif_task_handle);
        if (taskCreated != pdPASS) {
            spdif_task_handle = nullptr;
            log_e("SPDIF output task creation failed");
        }
    }
}


// Encode one stereo PCM frame into the SPDIF BMC buffer.
static void spdif_encode_sample(const int16_t smp[2]) {
    uint16_t hi, lo, aux;

    uint16_t sample_left = smp[0];
    hi = pgm_read_word(&spdif_bmclookup[(uint8_t)(sample_left >> 8)]);
    lo = pgm_read_word(&spdif_bmclookup[(uint8_t)sample_left]);
    lo ^= (~((int16_t)hi) >> 16);
    aux = 0xb333 ^ (((uint32_t)((int16_t)lo)) >> 17);
#if !defined(ARDUINO_ESP32S3_DEV)
    *spdif_ptr++ = ((uint32_t)lo << 16) | hi;
    if (spdif_ptr == spdif_buf+1) {
#else
    if (spdif_ptr == spdif_buf+0) {
#endif
        *spdif_ptr++ = VUCP_PREAMBLE_B | aux;
    } else {
        *spdif_ptr++ = VUCP_PREAMBLE_M | aux;
    }
#if defined(ARDUINO_ESP32S3_DEV)
    *spdif_ptr++ = ((uint32_t)lo << 16) | hi;
#endif

    uint16_t sample_right = smp[1];
    hi = pgm_read_word(&spdif_bmclookup[(uint8_t)(sample_right >> 8)]);
    lo = pgm_read_word(&spdif_bmclookup[(uint8_t)sample_right]);
    lo ^= (~((int16_t)hi) >> 16);
    aux = 0xb333 ^ (((uint32_t)((int16_t)lo)) >> 17);
#if defined(ARDUINO_ESP32S3_DEV)
    *spdif_ptr++ = VUCP_PREAMBLE_W | aux;
    *spdif_ptr++ = ((uint32_t)lo << 16) | hi;
#else
    *spdif_ptr++ = ((uint32_t)lo << 16) | hi;
    *spdif_ptr++ = VUCP_PREAMBLE_W | aux;
#endif
}

// Dedicated real-time task. When the PCM queue is empty, valid SPDIF
// subframes containing digital silence are generated continuously.
static void spdif_output_task(void *parameter) {
    int16_t sample[2];

    for (;;) {
        // Pause at an I2S buffer boundary while FTP is active.
        bool ftpPaused;
        do {
            portENTER_CRITICAL(&spdif_queue_mux);
            ftpPaused = spdif_ftp_paused;
            portEXIT_CRITICAL(&spdif_queue_mux);
            if (ftpPaused) ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        } while (ftpPaused);

        spdif_ptr = spdif_buf;
        while (spdif_ptr < &spdif_buf[SPDIF_BUF_ARRAY_SIZE]) {
            bool haveSample = false;

            portENTER_CRITICAL(&spdif_queue_mux);
            if (spdif_read_index != spdif_write_index) {
                sample[0] = spdif_samples[spdif_read_index][0];
                sample[1] = spdif_samples[spdif_read_index][1];
                spdif_read_index = (spdif_read_index + 1) % SPDIF_QUEUE_SAMPLES;
                haveSample = true;
            }
            portEXIT_CRITICAL(&spdif_queue_mux);

            if (!haveSample) {
                sample[0] = 0;
                sample[1] = 0;
            }
            spdif_encode_sample(sample);
        }

        size_t written = 0;
        esp_err_t err = i2s_write((i2s_port_t)I2S_NUM, spdif_buf,
                                  sizeof(spdif_buf), &written, portMAX_DELAY);

        // Apply a pending sample-rate change only after the current DMA write
        // has completed. This task is then the sole owner of I2S reconfiguration.
        uint32_t pendingRate = 0;
        portENTER_CRITICAL(&spdif_queue_mux);
        pendingRate = spdif_pending_rate;
        spdif_pending_rate = 0;
        portEXIT_CRITICAL(&spdif_queue_mux);
        if (pendingRate) {
            esp_err_t rateErr = i2s_set_sample_rates((i2s_port_t)I2S_NUM, pendingRate);
            if (rateErr != ESP_OK) log_e("SPDIF sample rate change failed: %d", rateErr);
        }

        if (err != ESP_OK) {
            log_e("SPDIF I2S write error: %d", err);
        } else if (written < sizeof(spdif_buf)) {
            log_e("Incomplete SPDIF I2S write: %u/%u",
                  (unsigned)written, (unsigned)sizeof(spdif_buf));
        }
    }
}

// Change the I2S clock without racing the output task.
void spdif_set_sample_rate(uint32_t rate) {
    // Do not wait for DMA here. The SPDIF task applies the new clock
    // immediately after its current I2S buffer has been transmitted.
    portENTER_CRITICAL(&spdif_queue_mux);
    spdif_pending_rate = rate;
    portEXIT_CRITICAL(&spdif_queue_mux);
}

// Pause/resume the output task for FTP without deleting the task or
// reinitializing I2S. Already queued DMA buffers drain naturally.
void spdif_set_ftp_mode(bool active) {
    portENTER_CRITICAL(&spdif_queue_mux);
    spdif_ftp_paused = active;
    if (active) spdif_read_index = spdif_write_index;
    portEXIT_CRITICAL(&spdif_queue_mux);
    if (!active && spdif_task_handle) xTaskNotifyGive(spdif_task_handle);
}

// Discard queued samples at a track/pause boundary. The output task keeps
// transmitting valid zero-valued SPDIF frames instead of clearing DMA to raw zeros.
void spdif_clear_queue() {
    portENTER_CRITICAL(&spdif_queue_mux);
    spdif_read_index = spdif_write_index;
    portEXIT_CRITICAL(&spdif_queue_mux);
}

// Queue decoded PCM. If the consumer falls behind, apply backpressure to
// the decoder rather than dropping audio samples.
bool spdif_write(int16_t smp[2]) {
    if (!spdif_samples || !spdif_task_handle) return false;

    for (;;) {
        bool queued = false;
        portENTER_CRITICAL(&spdif_queue_mux);
        uint16_t next = (spdif_write_index + 1) % SPDIF_QUEUE_SAMPLES;
        if (next != spdif_read_index) {
            spdif_samples[spdif_write_index][0] = smp[0];
            spdif_samples[spdif_write_index][1] = smp[1];
            spdif_write_index = next;
            queued = true;
        }
        portEXIT_CRITICAL(&spdif_queue_mux);

        if (queued) return true;
        vTaskDelay(1);
    }
}
#else
 void spdif_init(int rate) {}
 bool spdif_write(int16_t smp[2]) {return true;}
 void spdif_set_sample_rate(uint32_t rate) {}
 void spdif_clear_queue() {}
 void spdif_set_ftp_mode(bool active) {}
#endif
