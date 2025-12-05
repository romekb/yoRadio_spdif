#include "../../../core/options.h"
#if(DSP_MODEL==DSP_AXS15231B || DSP_MODEL==DSP_AXS15231B_180)
#include "AXS15231B_TFT.h"

//#define AXS_WRTIM_DEBUG

typedef struct {
    int cmd;                /*<! The specific LCD command */
    const void *data;       /*<! Buffer that holds the command specific data */
    size_t data_bytes;      /*<! Size of `data` in memory, in bytes */
    unsigned int delay_ms;  /*<! Delay in milliseconds after this command */
} axs15231b_lcd_init_cmd_t;

static const axs15231b_lcd_init_cmd_t init_seq[] = {
    {0x22, (uint8_t[]){0x00}, 0, 0},
/*    
    {0xBB, (uint8_t[]){0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5A, 0xA5}, 8, 0},
    {0xA0, (uint8_t[]){0xC0, 0x10, 0x00, 0x02, 0x00, 0x00, 0x04, 0x3F, 0x20, 0x05, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00}, 17, 0},
    {0xA2, (uint8_t[]){0x30, 0x3C, 0x24, 0x14, 0xD0, 0x20, 0xFF, 0xE0, 0x40, 0x19, 0x80, 0x80, 0x80, 0x20, 0xf9, 0x10, 0x02, 0xff, 0xff, 0xF0, 0x90, 0x01, 0x32, 0xA0, 0x91, 0xE0, 0x20, 0x7F, 0xFF, 0x00, 0x5A}, 31, 0},
    {0xD0, (uint8_t[]){0xE0, 0x40, 0x51, 0x24, 0x08, 0x05, 0x10, 0x01, 0x20, 0x15, 0xC2, 0x42, 0x22, 0x22, 0xAA, 0x03, 0x10, 0x12, 0x60, 0x14, 0x1E, 0x51, 0x15, 0x00, 0x8A, 0x20, 0x00, 0x03, 0x3A, 0x12}, 30, 0},
    {0xA3, (uint8_t[]){0xA0, 0x06, 0xAA, 0x00, 0x08, 0x02, 0x0A, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x55, 0x55}, 22, 0},
    {0xC1, (uint8_t[]){0x31, 0x04, 0x02, 0x02, 0x71, 0x05, 0x24, 0x55, 0x02, 0x00, 0x41, 0x00, 0x53, 0xFF, 0xFF, 0xFF, 0x4F, 0x52, 0x00, 0x4F, 0x52, 0x00, 0x45, 0x3B, 0x0B, 0x02, 0x0D, 0x00, 0xFF, 0x40}, 30, 0},
    {0xC3, (uint8_t[]){0x00, 0x00, 0x00, 0x50, 0x03, 0x00, 0x00, 0x00, 0x01, 0x80, 0x01}, 11, 0},
    {0xC4, (uint8_t[]){0x00, 0x24, 0x33, 0x80, 0x00, 0xea, 0x64, 0x32, 0xC8, 0x64, 0xC8, 0x32, 0x90, 0x90, 0x11, 0x06, 0xDC, 0xFA, 0x00, 0x00, 0x80, 0xFE, 0x10, 0x10, 0x00, 0x0A, 0x0A, 0x44, 0x50}, 29, 0},
    {0xC5, (uint8_t[]){0x18, 0x00, 0x00, 0x03, 0xFE, 0x3A, 0x4A, 0x20, 0x30, 0x10, 0x88, 0xDE, 0x0D, 0x08, 0x0F, 0x0F, 0x01, 0x3A, 0x4A, 0x20, 0x10, 0x10, 0x80}, 23, 0},
    {0xC6, (uint8_t[]){0x05, 0x0A, 0x05, 0x0A, 0x00, 0xE0, 0x2E, 0x0B, 0x12, 0x22, 0x12, 0x22, 0x01, 0x03, 0x00, 0x3F, 0x6A, 0x18, 0xC8, 0x22}, 20, 0},
    {0xC7, (uint8_t[]){0x50, 0x32, 0x28, 0x00, 0xa2, 0x80, 0x8f, 0x00, 0x80, 0xff, 0x07, 0x11, 0x9C, 0x67, 0xff, 0x26, 0x0c, 0x0d, 0x0e, 0x0f}, 20, 0},
    {0xC9, (uint8_t[]){0x33, 0x44, 0x44, 0x01}, 4, 0},
    {0xCF, (uint8_t[]){0x2C, 0x1E, 0x88, 0x58, 0x13, 0x18, 0x56, 0x18, 0x1E, 0x68, 0x88, 0x00, 0x65, 0x09, 0x22, 0xC4, 0x0C, 0x77, 0x22, 0x44, 0xAA, 0x55, 0x08, 0x08, 0x12, 0xA0, 0x08}, 27, 0},
    {0xD5, (uint8_t[]){0x40, 0x8E, 0x8D, 0x01, 0x35, 0x04, 0x92, 0x74, 0x04, 0x92, 0x74, 0x04, 0x08, 0x6A, 0x04, 0x46, 0x03, 0x03, 0x03, 0x03, 0x82, 0x01, 0x03, 0x00, 0xE0, 0x51, 0xA1, 0x00, 0x00, 0x00}, 30, 0},
    {0xD6, (uint8_t[]){0x10, 0x32, 0x54, 0x76, 0x98, 0xBA, 0xDC, 0xFE, 0x93, 0x00, 0x01, 0x83, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x84, 0x00, 0x20, 0x01, 0x00}, 30, 0},
    {0xD7, (uint8_t[]){0x03, 0x01, 0x0b, 0x09, 0x0f, 0x0d, 0x1E, 0x1F, 0x18, 0x1d, 0x1f, 0x19, 0x40, 0x8E, 0x04, 0x00, 0x20, 0xA0, 0x1F}, 19, 0},
    {0xD8, (uint8_t[]){0x02, 0x00, 0x0a, 0x08, 0x0e, 0x0c, 0x1E, 0x1F, 0x18, 0x1d, 0x1f, 0x19}, 12, 0},
    {0xD9, (uint8_t[]){0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F}, 12, 0},
    {0xDD, (uint8_t[]){0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F}, 12, 0},
    {0xDF, (uint8_t[]){0x44, 0x73, 0x4B, 0x69, 0x00, 0x0A, 0x02, 0x90}, 8, 0},
    {0xE0, (uint8_t[]){0x3B, 0x28, 0x10, 0x16, 0x0c, 0x06, 0x11, 0x28, 0x5c, 0x21, 0x0D, 0x35, 0x13, 0x2C, 0x33, 0x28, 0x0D}, 17, 0},
    {0xE1, (uint8_t[]){0x37, 0x28, 0x10, 0x16, 0x0b, 0x06, 0x11, 0x28, 0x5C, 0x21, 0x0D, 0x35, 0x14, 0x2C, 0x33, 0x28, 0x0F}, 17, 0},
    {0xE2, (uint8_t[]){0x3B, 0x07, 0x12, 0x18, 0x0E, 0x0D, 0x17, 0x35, 0x44, 0x32, 0x0C, 0x14, 0x14, 0x36, 0x3A, 0x2F, 0x0D}, 17, 0},
    {0xE3, (uint8_t[]){0x37, 0x07, 0x12, 0x18, 0x0E, 0x0D, 0x17, 0x35, 0x44, 0x32, 0x0C, 0x14, 0x14, 0x36, 0x32, 0x2F, 0x0F}, 17, 0},
    {0xE4, (uint8_t[]){0x3B, 0x07, 0x12, 0x18, 0x0E, 0x0D, 0x17, 0x39, 0x44, 0x2E, 0x0C, 0x14, 0x14, 0x36, 0x3A, 0x2F, 0x0D}, 17, 0},
    {0xE5, (uint8_t[]){0x37, 0x07, 0x12, 0x18, 0x0E, 0x0D, 0x17, 0x39, 0x44, 0x2E, 0x0C, 0x14, 0x14, 0x36, 0x3A, 0x2F, 0x0F}, 17, 0},
    {0xA4, (uint8_t[]){0x85, 0x85, 0x95, 0x82, 0xAF, 0xAA, 0xAA, 0x80, 0x10, 0x30, 0x40, 0x40, 0x20, 0xFF, 0x60, 0x30}, 16, 0},
    {0xA4, (uint8_t[]){0x85, 0x85, 0x95, 0x85}, 4, 0},
    {0xBB, (uint8_t[]){0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 8, 0},
*/    
    {0x13, (uint8_t[]){0x00}, 0, 0},
    {0x11, (uint8_t[]){0x00}, 0, 200},
    {0x29, (uint8_t[]){0x00}, 0, 200},
    {0x2C, (uint8_t[]){0x00, 0x00, 0x00, 0x00}, 4, 0}
};

static spi_device_handle_t spi;
static uint16_t *frameBuffer = NULL;
static uint16_t *frameBuffer2 = NULL;
static volatile bool cmdreq, inSleep;
static uint32_t _buflen;
SemaphoreHandle_t mutex_tft;
spi_transaction_ext_t t;
void tftSendChunk(uint8_t chunk);

//=================================================================================

AXS15231B_TFT::AXS15231B_TFT(int16_t w, int16_t h) : Adafruit_GFX(w, h) { 
    _dispHeight = h;  _dispWidth = w;
    _buflen = w*h;
    frameBuffer = (uint16_t *)heap_caps_aligned_alloc(16, _buflen*2, MALLOC_CAP_SPIRAM);
    frameBuffer2 = (uint16_t *)heap_caps_aligned_alloc(16, _buflen*2, MALLOC_CAP_SPIRAM);
    if(!frameBuffer || !frameBuffer2) {
        Serial.println("##[AXS display driver]#: Out of PSRAM !");
        ESP.restart();
    }
}

AXS15231B_TFT::~AXS15231B_TFT(void) {
  if(frameBuffer) heap_caps_free(frameBuffer);
  if(frameBuffer2) heap_caps_free(frameBuffer2);
  frameBuffer = NULL;
  frameBuffer2 = NULL;
}

//=================================================================================

static void AxsTask(void * pvParameters){
  static uint8_t chunk;
  spi_transaction_t *res;

  while(true) {
    if(mutex_tft && !inSleep && !cmdreq && xSemaphoreTake(mutex_tft, 10) == pdTRUE) {
        tftSendChunk(chunk);
        while(spi_device_get_trans_result(spi, &res, 1) != ESP_OK) yield();
        xSemaphoreGive(mutex_tft);
        if(++chunk >= 12) { 
            vTaskDelay(7); 
            chunk = 0; 
            memcpy(frameBuffer2, frameBuffer, _buflen*2); 
        }
    } else {
        if(cmdreq || inSleep) chunk = 0;
        vTaskDelay(10);
    }
  }
  vTaskDelete( NULL );
}

void AXS15231B_TFT::begin(void) {
    mutex_tft = xSemaphoreCreateMutex();
    pinMode(TFT_CS, OUTPUT);
    TFT_CS_H;
#if TFT_RST >= 0    
    pinMode(TFT_RST, OUTPUT);
    TFT_RES_L;
    delay(10);
    TFT_RES_H;
#endif    
    esp_err_t ret;
    spi_bus_config_t buscfg = {
        .data0_io_num = TFT_D0,
        .data1_io_num = TFT_D1,
        .sclk_io_num  = TFT_SCK,
        .data2_io_num = TFT_D2,
        .data3_io_num = TFT_D3,
        .max_transfer_sz = (SEND_BUF_SIZE * 16) + 16,
        .flags = SPICOMMON_BUSFLAG_MASTER | SPICOMMON_BUSFLAG_GPIO_PINS,
    };
    spi_device_interface_config_t devcfg = {
        .command_bits = 8,
        .address_bits = 24,
        .mode = TFT_SPI_MODE,
        .clock_speed_hz = DEF_SPI_FREQ,
        .spics_io_num = -1,
        .flags = SPI_DEVICE_HALFDUPLEX | SPI_DEVICE_NO_DUMMY,
        .queue_size = 2,
    };
    ret = spi_bus_initialize(TFT_SPI_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
    ret = spi_bus_add_device(TFT_SPI_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);
#if TFT_RST == -1
    tftSendCmd(TFT_SWRST, NULL, 0);    // soft reset
#endif
    delay(250);
    int initSize = sizeof(init_seq) / sizeof(axs15231b_lcd_init_cmd_t);
    for (int i = 0; i < initSize; i++) {
        tftSendCmd(init_seq[i].cmd, (uint8_t *)init_seq[i].data, init_seq[i].data_bytes);
        if(init_seq[i].delay_ms) delay(init_seq[i].delay_ms);
    }
    uint16_t wh = _dispHeight-1;
    uint8_t tr[] = {0, 0, (uint8_t)(wh>>8), (uint8_t)(wh & 0xFF)};
    tftSendCmd(TFT_CASET, tr, 4); 
    inSleep = false;
    xTaskCreatePinnedToCore(AxsTask, "AXSTask", 4096, NULL, 5, NULL, 0);
}
//---------------------------------------------------------------------------------
void AXS15231B_TFT::setRotation(uint8_t r) {
    Adafruit_GFX::setRotation(r);
    uint8_t gbr = TFT_MAD_RGB;        
    switch (r) {
    case 0: break;  // Portrait
    case 1:         // Landscape (Portrait + 90)
        gbr |= TFT_MAD_MX | TFT_MAD_MV;  break;
    case 2:         // Inverter portrait
        gbr |= TFT_MAD_MX | TFT_MAD_MY;  break;
    case 3:         // Inverted landscape
        gbr |= TFT_MAD_MV | TFT_MAD_MY;  break;
    }
    tftSendCmd(TFT_MADCTL, &gbr, 1);
}
//---------------------------------------------------------------------------------
void AXS15231B_TFT::setAddrWindow(uint32_t x1, uint32_t y1, uint32_t lx, uint32_t ly) {
    if(lx==0 || ly==0) return;
    if(x1+lx > _dispWidth)  lx = _dispWidth-x1;   // clipping
    if(y1+ly > _dispHeight) ly = _dispHeight-y1;
    _gx=x1; _gy=y1, _gw=lx; _gh=ly;
}
//---------------------------------------------------------------------------------
void AXS15231B_TFT::drawPixel(int16_t x, int16_t y, uint16_t color) {
    uint32_t addr = (_dispWidth-1-x) * _dispHeight + y;
    if(addr < _buflen) frameBuffer[addr] = __builtin_bswap16(color);
}
//---------------------------------------------------------------------------------
void AXS15231B_TFT::writePixels(uint16_t *data, uint32_t len) {
    uint16_t *p = (uint16_t *)data;
    uint16_t newX = _gy;
    uint16_t newY = _gx;
    if(len > _buflen) return;
    while(len--) {
        frameBuffer[(_dispWidth-1-newY)*_dispHeight + newX] = __builtin_bswap16(*p++);
        if(++newY >= _gx+_gw) { newY = _gx; if(++newX >= _gy+_gh) newX = _gy; }   
    }
}
//---------------------------------------------------------------------------------
void AXS15231B_TFT::fillRect(int16_t xsta, int16_t ysta, int16_t w, int16_t h, uint16_t color) {
//    if(xsta<0 || ysta<0 || xsta+w > _dispWidth || ysta+h > _dispHeight || w==0 || h==0) return;
    if(w==0 || h==0) return;
    if(xsta < 0) xsta = 0;
    if(ysta < 0) ysta = 0;
    if(xsta+w > _dispWidth)  w = _dispWidth-xsta;   // clipping
    if(ysta+h > _dispHeight) h = _dispHeight-ysta;
    color = __builtin_bswap16(color);
    xsta = _dispWidth-1 - xsta;
    for(int i=0; i<w; ++i) {
        uint32_t xx = (xsta - i) * _dispHeight + ysta;
        for(int j=0; j<h; ++j) frameBuffer[xx + j] = color;
    }
}
//---------------------------------------------------------------------------------
void AXS15231B_TFT::setInvert(bool invert) {
    tftSendCmd(invert ? TFT_INVON:TFT_INVOFF, NULL, 0);
}
//---------------------------------------------------------------------------------
void AXS15231B_TFT::tftSleep(bool sleepin) {
    inSleep = sleepin;
    tftSendCmd(sleepin ? TFT_SLPIN:TFT_SLPOUT, NULL, 0);
    delay(200);
}
//---------------------------------------------------------------------------------
void AXS15231B_TFT::tftClearScreen(uint16_t color) {
    if(color==0) {
        memset(frameBuffer, 0, _buflen*2);
        memset(frameBuffer2, 0, _buflen*2);
        tftSendCmd(TFT_PIXELS_OFF, NULL, 0);
        delay(10);
    } else {
        color = __builtin_bswap16(color);
        for(int i=0; i<_buflen; ++i) {frameBuffer[i] = color; frameBuffer2[i] = color;}
    }
}

//=================================================================================

void AXS15231B_TFT::tftSendCmd(uint32_t cmd, uint8_t *dat, uint32_t len) {
    cmdreq = true;
    if(mutex_tft && xSemaphoreTake(mutex_tft, 50) == pdTRUE) {
        TFT_CS_H;
        spi_transaction_t t = {0};
        t.cmd = 0x02;
        t.addr = cmd << 8;
        TFT_CS_L;
        if (len != 0) {
            t.tx_buffer = dat; 
            t.length = 8 * len;
        } else {
            t.tx_buffer = NULL;
            t.length = 0;
        }
        spi_device_polling_transmit(spi, &t);
        TFT_CS_H;
        xSemaphoreGive(mutex_tft);
    }
    cmdreq = false;
}
//---------------------------------------------------------------------------------
void tftSendChunk(uint8_t chunk)
{
    esp_err_t ret;
    uint16_t *p = (uint16_t *)frameBuffer2 + chunk*SEND_BUF_SIZE;
    if (chunk == 0) {
        TFT_CS_H;
        t.base.flags = SPI_TRANS_MODE_QIO;
        t.base.cmd  = 0x32;
        t.base.addr = 0x002C00;
        TFT_CS_L;
    } else {
        t.base.flags = SPI_TRANS_MODE_QIO | SPI_TRANS_VARIABLE_CMD |
                        SPI_TRANS_VARIABLE_ADDR | SPI_TRANS_VARIABLE_DUMMY;
        t.command_bits = 0;
        t.address_bits = 0;
        t.dummy_bits   = 0;
    }
    t.base.tx_buffer = p;
    t.base.length = SEND_BUF_SIZE * 16;    // in bits
    ret = spi_device_queue_trans(spi, (spi_transaction_t *)&t, 5);    // DMA write
    ESP_ERROR_CHECK(ret);
}
//---------------------------------------------------------------------------------

#endif

