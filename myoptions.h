#ifndef myoptions_h
#define myoptions_h

/* FOR STANDARD 2.8'' CYD with ST7789, XPT2046 & two USB ports */

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
#define BRIGHTNESS_PIN			21
#define DEF_SPI_FREQ        60000000UL

// I2S DAC
#define I2S_DOUT            22
#define I2S_BCLK            26
#define I2S_LRC             4

// SPDIF
#define SPDIF_OUT           22

// TOUCHSCREEN
#define TS_MODEL			      TS_MODEL_XPT2046
#define TS_SPIPINS          25, 39, 32    /* SCK, MISO, MOSI */
#define TS_CS			          33
#define TS_MIRROR_X

// SD/IR/Misc
#define SDC_CS			        5
#define IR_PIN              34
#define IR_TIMEOUT          20
#define CLOCK_TTS_ENABLED   false     // Enabled (true) or disabled (false)
#define NAMEDAYS_FILE       PL // HU, PL, NL
#define NO_VOLUME_SCREEN
#define VU_PEAK
//#define WEATHER_FMT_SHORT
//#define BOOMBOX_STYLE

#endif
