#ifndef myoptions_h
#define myoptions_h

/* FOR 3.5'' 480x320, ESP32S3, IPS screen with AXS15231B driver & capacitive touchscreen - JC3248W535 module */
/* !!! Do not be alarmed, all right, the default values ​​are not included in this file !!! */

#define L10N_LANGUAGE       PL

// DISPLAY
#define DSP_MODEL			      DSP_AXS15231B
#define TFT_CS  			      45                /*  QSPI CS pin  */    
#define TFT_SCK 			      47                /*  QSPI SCK pin */
#define TFT_D0 				      21                /*  QSPI D0 pin  */
#define TFT_D1 				      48                /*  QSPI D1 pin  */
#define TFT_D2 				      40                /*  QSPI D2 pin  */
#define TFT_D3 				      39                /*  QSPI D3 pin  */
#define BRIGHTNESS_PIN		  1
#define IR_TS_BRIGHTNESS_CONTROL

// Touchscreen
#define TS_MODEL 			      TS_MODEL_AXS15231B
#define TS_SDA 				      4
#define TS_SCL 				      8
#define TS_INT 				      3
#define TS_RST 				      -1
#define TS_AXS15231_FIX                   // ghost touch on AXS15231 - accident wakeup elimination

// SD CARD
#define SDC_CS			        10
#define SD_HSPI     		    true          // use HSPI for SD (SCK=14, MISO=12, MOSI=13) instead of VSPI (by default)
#define SD_SPIPINS    		  12, 13, 11    // SCK, MISO, MOSI

// INTERNAL DAC/AMP
#define I2S_DOUT            41
#define I2S_BCLK            42
#define I2S_LRC             2
#define PLAYER_FORCE_MONO   true

// EXTERNAL DAC
//#define I2S_DOUT            14
//#define I2S_BCLK            9
//#define I2S_LRC             46

// SPDIF OUT PIN
#define SPDIF_OUT           18

// RTC
//#define RTC_MODULE			    DS3231
//#define RTC_SDA			        17
//#define RTC_SCL			        18

// IR/Misc
#define IR_PIN              6
#define IR_TIMEOUT          15
#define NO_VOLUME_SCREEN
#define VU_PEAK

#define CLOCK_TTS_ENABLED   false     // Enabled (true) or disabled (false)
#define CLOCK_TTS_INTERVAL_MINUTES 30
#define CLOCK_TTS_LANGUAGE  "PL"      // "EN", "DE", "RU", "RO", "NL", "HU", "FR", "PL" 

#define NAMEDAYS_FILE       PL        // HU, PL, NL
#define POWER_SAVE          2         // 0=off, 1=on sleep, 2=always
#define WAKEUP_REBOOT                 // reboot on "power on" via IR remote or touchscreen longpress 
//#define CLOCKFONT_7SEG
//#define WEATHER_FMT_SHORT
//#define BOOMBOX_STYLE 

// AUTOBACKLIGHT       
//#define LIGHT_SENSOR        5        // lower pin voltage = higher brightness
#define AUTOBACKLIGHT_DARK  4000      // max ADC value - at dark condition (0 - 4095)
#define AUTOBACKLIGHT_BRI   100       // min ADC value - at bright condition (0 - 4095)
#define AUTOBACKLIGHT_MIN   20        // min brightness [%] (0 - 100)

#endif
