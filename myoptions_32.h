#ifndef myoptions_h
#define myoptions_h

/* FOR 3.2'' IPS ESP32 CYD (https://www.lcdwiki.com/3.2inch_ESP32-32E_Display) */


/* !!! Attention !!! */
/* This configuration depends on some additional libraries. Please install them using the library manager: */
/* Adafruit GFX Library, Adafruit ST7735 and ST7789 Library, XPT2046_Touchscreen */

/* !!! Do not be alarmed, all right, the default values ​​are not included in this file !!! */

#define L10N_LANGUAGE       PL

// DISPLAY
#define DSP_MODEL			      DSP_ST7789
#define DSP_HSPI			      true
#define TFT_DC			        2
#define TFT_CS			        15
#define BRIGHTNESS_PIN		  27
#define DEF_SPI_FREQ        60000000UL

// I2S DAC
#define I2S_DOUT            22
#define I2S_BCLK            26
#define I2S_LRC             21

// SPDIF
#define SPDIF_OUT           22

// RTC
//#define RTC_MODULE			    DS3231
//#define RTC_SDA			        32
//#define RTC_SCL			        25

// Touchscreen
#define TS_MODEL			      TS_MODEL_XPT2046
#define TS_HSPI				      true
#define TS_CS			          33

// SD/IR/Misc
#define SDC_CS			        5
#define IR_PIN              35
#define IR_TIMEOUT          15
#define NO_VOLUME_SCREEN
#define VU_PEAK
#define CLOCK_TTS_ENABLED   false     // Enabled (true) or disabled (false)
#define NAMEDAYS_FILE       PL        // HU, PL, NL
#define CLOCKFONT_MONO      true
//#define WEATHER_FMT_SHORT
//#define BOOMBOX_STYLE

#endif
