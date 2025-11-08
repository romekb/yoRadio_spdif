#include "../../../core/options.h"
#if DSP_MODEL==DSP_NV3041A
#include "NV3041A.h"

static spi_device_handle_t spi;
SemaphoreHandle_t mutex_tft;

uint8_t initCmdsTab[][2] = {
    {0xff, 0xa5},
    {0x36, 0xc0},
    {0x3A, 0x01},   // 01---565，00---666
    {0x41, 0x03},   // 01--8bit, 03-16bit
    {0x43, 0x01},   // qspi_sbyte = 1    
    {0x7d, 0x02},   // vdds_trim[2:0]
/*
    {0x44, 0x15},   // VBP  ?????
    {0x45, 0x15},   // VFP  ?????
    {0x7d, 0x03},   // vdds_trim[2:0]
    {0xc1, 0xab},   // avdd_clp_en avdd_clp[1:0] avcl_clp_en avcl_clp[1:0]
    {0xc2, 0x17},   // vgl_clp_en vgl_clp[2:0]
    {0xc3, 0x10},   // vgl_clp_en vgl_clp[2:0]
    {0xc6, 0x3a},   // avdd_ratio_sel avcl_ratio_sel vgh_ratio_sel[1:0] vgl_ratio_sel[1:0]
    {0xc7, 0x25},   // mv_clk_sel[1:0] avdd_clk_sel[1:0] avcl_clk_sel[1:0]
    {0xc8, 0x11},   //	VGL_CLK_sel
    {0x7a, 0x49},   //	user_vgsp 4f:0.8V 3f:1.04V	5f
    {0x6f, 0x2f},   //	user_gvdd 1C:5.61	  5f	 53		   2a	    3a
    {0x78, 0x4b},   //	user_gvcl 50:-3.22	  75			58	     	66
    {0xc9, 0x00}, 
    {0x67, 0x33},
    {0x51, 0x4b},   // gate_st_o[7:0]
    {0x52, 0x7c},   // gate_ed_o[7:0]
    {0x53, 0x1c},   // gate_st_e[7:0]
    {0x54, 0x77},   // gate_ed_e[7:0]
    {0x46, 0x0a},   // fsm_hbp_o[5:0]
    {0x47, 0x2a},   // fsm_hfp_o[5:0]
    {0x48, 0x0a},   // fsm_hbp_e[5:0]
    {0x49, 0x1a},   // fsm_hfp_e[5:0]
    {0x56, 0x43},   // src_ld_wd[1:0] src_ld_st[5:0]
    {0x57, 0x42},   // pn_cs_en src_cs_st[5:0]
    {0x58, 0x3c},   // src_cs_p_wd[6:0]
    {0x59, 0x64},   // src_cs_n_wd[6:0]
    {0x5a, 0x41},   // src_pchg_st_o[6:0]
    {0x5b, 0x3c},   // src_pchg_wd_o[6:0]
    {0x5c, 0x02},   // src_pchg_st_e[6:0]
    {0x5d, 0x3c},   // src_pchg_wd_e[6:0]
    {0x5e, 0x1f},   // src_pol_sw[7:0]
    {0x60, 0x80},   // src_op_st_o[7:0]
    {0x61, 0x3f},   // src_op_st_e[7:0]
    {0x62, 0x21},   // src_op_ed_o[9:8] src_op_ed_e[9:8]
    {0x63, 0x07},   // src_op_ed_o[7:0]
    {0x64, 0xe0},   // src_op_ed_e[7:0]
    {0x65, 0x01},   // chopper
    {0xca, 0x20},   // avdd_mux_st_o[7:0]
    {0xcb, 0x52},   // avdd_mux_ed_o[7:0]
    {0xcc, 0x10},   // avdd_mux_st_e[7:0]
    {0xcD, 0x42},   // avdd_mux_ed_e[7:0]
    {0xD0, 0x20},   // avcl_mux_st_o[7:0]
    {0xD1, 0x52},   // avcl_mux_ed_o[7:0]
    {0xD2, 0x10},   // avcl_mux_st_e[7:0]
    {0xD3, 0x42},   // avcl_mux_ed_e[7:0]
    {0xD4, 0x0a},   // vgh_mux_st[7:0]
    {0xD5, 0x32},   // vgh_mux_ed[7:0]
*/
    {0x80, 0x04},   // gam_vrp0	    0	6bit
    {0xA0, 0x00},   // gam_VRN0		0-
    {0x81, 0x07},   // gam_vrp1	    1   6bit
    {0xA1, 0x05},   // gam_VRN1		1-
    {0x82, 0x06},   // gam_vrp2	    2	6bit
    {0xA2, 0x04},   // gam_VRN2	    2-
    {0x86, 0x2c},   // gam_prp0	 	8	7bit
    {0xA6, 0x2a},   // gam_PRN0	 	8-
    {0x87, 0x46},   // gam_prp1	    40  7bit
    {0xA7, 0x44},   // gam_PRN1	 	40-
    {0x83, 0x39},   // gam_vrp3	    61	6bit
    {0xA3, 0x39},   // gam_VRN3		61-
    {0x84, 0x3a},   // gam_vrp4	    62  6bit
    {0xA4, 0x3a},   // gam_VRN4		62-
    {0x85, 0x3f},   // gam_vrp5	    63	6bit
    {0xA5, 0x3f},   // gam_VRN5		63-
    {0x88, 0x08},   // gam_pkp0	  	4	5bit
    {0xA8, 0x08},   // gam_PKN0		4-
    {0x89, 0x0f},   // gam_pkp1	    5	5bit
    {0xA9, 0x0f},   // gam_PKN1		5-
    {0x8a, 0x17},   // gam_pkp2	    7	5bit
    {0xAa, 0x17},   // gam_PKN2		7-
    {0x8b, 0x10},   // gam_PKP3	    10	5bit
    {0xAb, 0x10},   // gam_PKN3		10-
    {0x8c, 0x16},   // gam_PKP4	    16	5bit
    {0xAc, 0x16},   // gam_PKN4		16-
    {0x8d, 0x14},   // gam_PKP5		22	5bit
    {0xAd, 0x14},   // gam_PKN5		22-
    {0x8e, 0x11},   // gam_PKP6		28	5bit
    {0xAe, 0x11},   // gam_PKN6		28-
    {0x8f, 0x14},   // gam_PKP7		34	5bit
    {0xAf, 0x14},   // gam_PKN7		34-
    {0x90, 0x06},   // gam_PKP8		46	5bit
    {0xB0, 0x06},   // gam_PKN8		46-
    {0x91, 0x0f},   // gam_PKP9		52	5bit
    {0xB1, 0x0f},   // gam_PKN9		52-
    {0x92, 0x16},   // gam_PKP10	58	5bit
    {0xB2, 0x16},   // gam_PKN10	58-  
    {0xff, 0x00},
    {0x11, 0x00}
};

//=================================================================================

NV3041A::NV3041A(int16_t w, int16_t h) : Adafruit_GFX(w, h) { 
    _dispHeight = h;  _dispWidth = w;
}

NV3041A::~NV3041A(void) {}

//=================================================================================

void NV3041A::begin(void) {
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
    delay(150);
    for(int i=0; i<sizeof(initCmdsTab)/sizeof(initCmdsTab[0]); ++i) {
        tftSendCmd(initCmdsTab[i][0], &initCmdsTab[i][1], 1);
    }
    delay(120);
    tftSendCmd(TFT_DISPON, NULL, 0);
    delay(120);
}
//---------------------------------------------------------------------------------
void NV3041A::setRotation(uint8_t r) {
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
void NV3041A::setAddrWindow(uint16_t x1, uint16_t y1, uint16_t lx, uint16_t ly) {
//    if(x1+lx > _dispWidth || y1+ly > _dispHeight || lx==0 || ly==0) return;
    if(lx==0 || ly==0) return;
    if(x1+lx > _dispWidth)  lx = _dispWidth-x1;   // clipping
    if(y1+ly > _dispHeight) ly = _dispHeight-y1;
    uint8_t tr[4];
    if(x1 != _gx || lx != _gw) {
        _gx = x1; _gw = lx;
        lx = x1+lx-1;
        tr[0] = (uint8_t)(x1>>8);
        tr[1] = (uint8_t)(x1 & 0xFF);
        tr[2] = (uint8_t)(lx>>8);
        tr[3] = (uint8_t)(lx & 0xFF);
        tftSendCmd(TFT_CASET, tr, 4);
    }
    if(y1 != _gy || ly != _gh) {
        _gy = y1; _gh = ly;
        ly = y1+ly-1;
        tr[0] = (uint8_t)(y1>>8);
        tr[1] = (uint8_t)(y1 & 0xFF);
        tr[2] = (uint8_t)(ly>>8);
        tr[3] = (uint8_t)(ly & 0xFF);
        tftSendCmd(TFT_RASET, tr, 4);
    }
}
//---------------------------------------------------------------------------------
void NV3041A::drawPixel(int16_t x, int16_t y, uint16_t color) {
    setAddrWindow(x,y,1,1);
    tftSendPixels(&color, 1);
}
//---------------------------------------------------------------------------------
void NV3041A::writePixels(uint16_t *data, uint32_t len) {    
   tftSendPixels(data, len);
}
//---------------------------------------------------------------------------------
void NV3041A::writeFillRect(int16_t xsta, int16_t ysta, int16_t w, int16_t h, uint16_t color) {
    fillRect(xsta, ysta, w, h, color);
}
//---------------------------------------------------------------------------------
void NV3041A::fillRect(int16_t xsta, int16_t ysta, int16_t w, int16_t h, uint16_t color) {
//    if(xsta+w > _dispWidth || ysta+h > _dispHeight || w==0 || h==0) return;
    if(w==0 || h==0) return;
    if(xsta < 0) xsta = 0;
    if(ysta < 0) ysta = 0;
    if(xsta+w > _dispWidth)  w = _dispWidth-xsta;   // clipping
    if(ysta+h > _dispHeight) h = _dispHeight-ysta;
    uint16_t *tmp = (uint16_t *)heap_caps_malloc(w*h*2, MALLOC_CAP_SPIRAM);
    if(tmp) {
        setAddrWindow(xsta, ysta, w, h);
        for(int i=0; i<w*h; ++i) tmp[i] = color;
        tftSendPixels(tmp, w*h);
        heap_caps_free(tmp);
    }
}
//---------------------------------------------------------------------------------
void NV3041A::setInvert(bool invert) {
    tftSendCmd(invert ? TFT_INVON:TFT_INVOFF, NULL, 0);
}
//---------------------------------------------------------------------------------
void NV3041A::tftSleep(bool sleepin) {
    tftSendCmd(sleepin ? TFT_SLPIN:TFT_SLPOUT, NULL, 0);
    delay(150);
}
//---------------------------------------------------------------------------------
void NV3041A::tftClearScreen(uint16_t color) {
    fillRect(0, 0, _dispWidth, _dispHeight, color);
}

//=================================================================================

void NV3041A::tftSendCmd(uint32_t cmd, uint8_t *dat, uint32_t len) {
    if(!mutex_tft) return;
    if(xSemaphoreTake(mutex_tft, 50) == pdTRUE) {    
        TFT_CS_L;
        spi_transaction_t t = {0};
        t.cmd = 0x02;
        t.addr = cmd << 8;
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
}
//---------------------------------------------------------------------------------
void NV3041A::tftSendPixels(uint16_t *data, uint32_t len)
{
    if(!mutex_tft) return;
    if(xSemaphoreTake(mutex_tft, 50) == pdTRUE) {    
        esp_err_t ret;
        bool first_send = 1;
        uint16_t *p = (uint16_t *)data;
        TFT_CS_L;
        do {
            size_t chunk_size = len;
            spi_transaction_ext_t t = {0};
            //memset(&t, 0, sizeof(t));
            if (first_send) {
                t.base.flags = SPI_TRANS_MODE_QIO;
                t.base.cmd  = 0x32;
                t.base.addr = 0x002C00;
                first_send  = 0;
            } else {
                t.base.flags = SPI_TRANS_MODE_QIO | SPI_TRANS_VARIABLE_CMD |
                            SPI_TRANS_VARIABLE_ADDR | SPI_TRANS_VARIABLE_DUMMY;
                t.command_bits = 0;
                t.address_bits = 0;
                t.dummy_bits   = 0;
            }
            if (chunk_size > SEND_BUF_SIZE) chunk_size = SEND_BUF_SIZE;
            t.base.tx_buffer = p;
            t.base.length = chunk_size * 16;    // in bits
//            ret = spi_device_transmit(spi, (spi_transaction_t *)&t);
            ret = spi_device_polling_transmit(spi, (spi_transaction_t *)&t);
            ESP_ERROR_CHECK(ret);
            len -= chunk_size;
            p += chunk_size;
        } while (len > 0);
        TFT_CS_H;
        xSemaphoreGive(mutex_tft);
    }
}
//---------------------------------------------------------------------------------

#endif

