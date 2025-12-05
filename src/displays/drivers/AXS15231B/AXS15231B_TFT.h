#pragma once

#include "stdint.h"
#include "SPI.h"
#include "Arduino.h"
#include "driver/spi_master.h"
#include "pins_config.h"
#include <Adafruit_GFX.h>

#pragma GCC optimize ("Ofast")

#ifndef DEF_SPI_FREQ
 #define DEF_SPI_FREQ  40000000
#endif
#define TFT_SPI_MODE   SPI_MODE0
#define TFT_SPI_HOST   SPI2_HOST
#define SEND_BUF_SIZE  12800       // 12 chunks // 15360      // 10 chunks per screen 320x480

#define TFT_MADCTL      0x36
#define TFT_MAD_MY      0x80
#define TFT_MAD_MX      0x40
#define TFT_MAD_MV      0x20
#define TFT_MAD_ML      0x10
#define TFT_MAD_BGR     0x08
#define TFT_MAD_MH      0x04
#define TFT_MAD_RGB     0x00

#define TFT_SWRST       0x01
#define TFT_SLPIN       0x10
#define TFT_SLPOUT      0x11
#define TFT_INVOFF      0x20
#define TFT_INVON       0x21
#define TFT_PIXELS_OFF  0x22
#define TFT_CASET       0x2A
#define TFT_RASET       0x2B

#define TFT_RES_H     digitalWrite(TFT_RST, 1);
#define TFT_RES_L     digitalWrite(TFT_RST, 0);
#define TFT_CS_H      digitalWrite(TFT_CS, 1);
#define TFT_CS_L      digitalWrite(TFT_CS, 0);

class AXS15231B_TFT : public Adafruit_GFX {
  public:
    AXS15231B_TFT(int16_t w, int16_t h);
    ~AXS15231B_TFT(void);

    void begin(void);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void setAddrWindow(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
    void writePixels(uint16_t *data, uint32_t len);
    void fillRect(int16_t xsta, int16_t ysta, int16_t w, int16_t h, uint16_t color);
    void setRotation(uint8_t r);
    void setInvert(bool invert);
    void tftSleep(bool sleepin);
    void tftClearScreen(uint16_t color);
  private:
    void tftSendCmd(uint32_t cmd, uint8_t *dat, uint32_t len);
    uint32_t _dispHeight, _dispWidth;
    uint32_t _gx, _gy, _gw, _gh;
};

           