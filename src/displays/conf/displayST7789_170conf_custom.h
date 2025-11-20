/*************************************************************************************
    ST7789 320x170 displays configuration file.
    Copy this file to yoRadio/src/displays/conf/displayST7789conf_custom.h
    and modify it
    More info on https://github.com/e2002/yoradio/wiki/Widgets#widgets-description
*************************************************************************************/

#ifndef displayST7789conf_h
#define displayST7789conf_h

#define DSP_WIDTH       320
#define TFT_FRAMEWDT    3
#define MAX_WIDTH       DSP_WIDTH-TFT_FRAMEWDT*2

#define TITLE_FIX 0
#define bootLogoTop     40
#define HIDE_VOL
#define HIDE_DATE
#define HIDE_NAMEDAYS_LABEL

/* SROLLS  */                            /* {{ left, top, fontsize, align }, buffsize, uppercase, width, scrolldelay, scrolldelta, scrolltime } */
const ScrollConfig metaConf     PROGMEM = {{ TFT_FRAMEWDT, 0, 3, WA_LEFT }, 140, true, MAX_WIDTH, 5000, 5, 30 };
#ifdef HIDE_TITLE2
 const ScrollConfig title1Conf  PROGMEM = {{ TFT_FRAMEWDT, 36, 3, WA_LEFT }, 140, true, DSP_WIDTH-3, 5000, 4, 30 };
 const ScrollConfig weatherConf PROGMEM = {{ TFT_FRAMEWDT, 67, 2, WA_LEFT }, 300, false, MAX_WIDTH, 0, 4, 30 };
#else
 const ScrollConfig title1Conf  PROGMEM = {{ TFT_FRAMEWDT, 32, 2, WA_LEFT }, 140, true, DSP_WIDTH-3, 5000, 4, 30 };
 const ScrollConfig weatherConf PROGMEM = {{ TFT_FRAMEWDT, 70, 2, WA_LEFT }, 300, false, MAX_WIDTH, 0, 4, 30 };
#endif
const ScrollConfig title2Conf   PROGMEM = {{ TFT_FRAMEWDT, 51, 2, WA_LEFT }, 140, true, DSP_WIDTH-3, 5000, 4, 30 };
const ScrollConfig playlistConf PROGMEM = {{ TFT_FRAMEWDT, 112, 3, WA_LEFT }, 140, true, MAX_WIDTH, 1000, 4, 30 };
const ScrollConfig apTitleConf  PROGMEM = {{ TFT_FRAMEWDT, TFT_FRAMEWDT, 3, WA_CENTER }, 140, false, MAX_WIDTH, 0, 4, 20 };
const ScrollConfig apSettConf   PROGMEM = {{ TFT_FRAMEWDT, 170-20, 1, WA_LEFT }, 140, false, MAX_WIDTH, 0, 4, 30 };
const ScrollConfig namedayConf  PROGMEM = {{ TFT_FRAMEWDT, 118, 2, WA_LEFT }, 80, true, 105, 0, 2, 30 };

/* BACKGROUNDS  */                       /* {{ left, top, fontsize, align }, width, height, outlined } */
const FillConfig  metaBGConf     PROGMEM = {{ 0, 24, 0, WA_LEFT }, DSP_WIDTH, 2, false };
const FillConfig  metaBGConfInv  PROGMEM = {{ 0, 0, 0, WA_LEFT }, DSP_WIDTH, 0, false };
const FillConfig  volbarConf     PROGMEM = {{ TFT_FRAMEWDT, 157, 0, WA_LEFT }, 277, 7, true };
const FillConfig  playlBGConf    PROGMEM = {{ 0, 107, 0, WA_LEFT }, DSP_WIDTH, 24, false };
const FillConfig  heapbarConf    PROGMEM = {{ 0, 167, 0, WA_LEFT }, DSP_WIDTH, 2, false };

/* WIDGETS  */                           /* { left, top, fontsize, align } */
const WidgetConfig bootstrConf    PROGMEM = { 0, 150, 1, WA_CENTER };
const WidgetConfig bitrateConf    PROGMEM = { TFT_FRAMEWDT, 32,  2, WA_RIGHT};
const WidgetConfig voltxtConf     PROGMEM = { TFT_FRAMEWDT, 214,  1, WA_CENTER };
const WidgetConfig iptxtConf      PROGMEM = { TFT_FRAMEWDT+10, 144, 1, WA_LEFT };
const WidgetConfig rssiConf       PROGMEM = { TFT_FRAMEWDT, 150, 2, WA_RIGHT };
const WidgetConfig numConf        PROGMEM = {  0, 120, 72, WA_CENTER };
const WidgetConfig apNameConf     PROGMEM = { TFT_FRAMEWDT, 40, 2, WA_CENTER };
const WidgetConfig apName2Conf    PROGMEM = { TFT_FRAMEWDT, 65, 2, WA_CENTER };
const WidgetConfig apPassConf     PROGMEM = { TFT_FRAMEWDT, 100, 2, WA_CENTER };
const WidgetConfig apPass2Conf    PROGMEM = { TFT_FRAMEWDT, 125, 2, WA_CENTER };
const WidgetConfig clockConf      PROGMEM = { 0, 135, 52, WA_RIGHT };  /* 52 is a fixed font size. do not change */
const WidgetConfig vuConf         PROGMEM = { TFT_FRAMEWDT+17, 170-29, 1, WA_CENTER };
const WidgetConfig bootWdtConf    PROGMEM = { TFT_FRAMEWDT, 120, 2, WA_CENTER };

const ProgressConfig  bootPrgConf  PROGMEM = { 100, 14, 4 };
const BitrateConfig fullbitrateConf PROGMEM = {{TFT_FRAMEWDT+10, 91, 2, WA_LEFT}, 42};

/* BANDS  */              /* { onebandwidth, onebandheight, bandsHspace, bandsVspace, numofbands, fadespeed } */
#ifdef BOOMBOX_STYLE
 const VUBandsConfig bandsConf    PROGMEM = {130, 6, 3, 2, 20, 12};
#else 
 const VUBandsConfig bandsConf   	PROGMEM = {273, 4, 2, 2, 30, 6 };
#endif

/* STRINGS  */
const char         numtxtFmt[]    PROGMEM = "%d";
const char           rssiFmt[]    PROGMEM = "rssi %d dBm";
const char          iptxtFmt[]    PROGMEM = "%s";
const char         voltxtFmt[]    PROGMEM = "\023\025%d";
const char        bitrateFmt[]    PROGMEM = "%d kBs";

/* MOVES  */                             /* { left, top, width (0 - auto, -1 - lock )} */
const MoveConfig    clockMove     PROGMEM = { 12, 141, -1 };
const MoveConfig   weatherMove    PROGMEM = { TFT_FRAMEWDT, 100, -1 };
const MoveConfig   weatherMoveVU  PROGMEM = { TFT_FRAMEWDT, 100, -1 };

#endif
