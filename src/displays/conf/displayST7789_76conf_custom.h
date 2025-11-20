/*************************************************************************************
    SSD1305 265x64 displays configuration file.
    Copy this file to yoRadio/src/displays/conf/displaySSD1322conf_custom.h
    and modify it
    More info on https://github.com/e2002/yoradio/wiki/Widgets#widgets-description
*************************************************************************************/

#ifndef displayST778976conf_h
#define displayST778976conf_h

#define DSP_WIDTH       284
#define DSP_HEIGHT      76
#define TFT_FRAMEWDT    2
#define MAX_WIDTH       DSP_WIDTH-TFT_FRAMEWDT*2

#define BOOMBOX_STYLE 
#define HIDE_VOL
#define HIDE_NAMEDAYS_LABEL

#define bootLogoTop     8

/* SROLLS  */                            /* {{ left, top, fontsize, align }, buffsize, uppercase, width, scrolldelay, scrolldelta, scrolltime } */
const ScrollConfig metaConf       PROGMEM = {{ TFT_FRAMEWDT, 0, 2, WA_LEFT }, 140, true, MAX_WIDTH, 5000, 2, 25 };
#ifdef HIDE_TITLE2
const ScrollConfig title1Conf     PROGMEM = {{ TFT_FRAMEWDT, 21, 2, WA_LEFT }, 140, true, DSP_WIDTH/2+13, 5000, 2, 25 };
#else
const ScrollConfig title1Conf     PROGMEM = {{ TFT_FRAMEWDT, 20, 1, WA_LEFT }, 140, true, DSP_WIDTH/2+13, 5000, 2, 25 };
#endif
const ScrollConfig title2Conf     PROGMEM = {{ TFT_FRAMEWDT, 29, 1, WA_LEFT }, 140, true, DSP_WIDTH/2+13, 5000, 2, 25 };
const ScrollConfig playlistConf   PROGMEM = {{ TFT_FRAMEWDT, 30, 2, WA_LEFT }, 140, true, MAX_WIDTH, 500, 3, 25 };
const ScrollConfig apTitleConf    PROGMEM = {{ TFT_FRAMEWDT, 0, 2, WA_CENTER }, 140, false, MAX_WIDTH, 0, 2, 25 };
const ScrollConfig apSettConf     PROGMEM = {{ TFT_FRAMEWDT, 64-7, 1, WA_LEFT }, 140, false, MAX_WIDTH, 0, 2, 25 };
const ScrollConfig weatherConf    PROGMEM = {{ TFT_FRAMEWDT, 64-12, 1, WA_LEFT }, 140, false, DSP_WIDTH/2+13, 0, 2, 30 };
const ScrollConfig namedayConf    PROGMEM = {{ 77, 41, 1, WA_LEFT }, 80, true, 82, 0, 1, 25 };

/* BACKGROUNDS  */                       /* {{ left, top, fontsize, align }, width, height, outlined } */
const FillConfig   metaBGConf     PROGMEM = {{ 0, 16,  0, WA_LEFT }, DSP_WIDTH, 2, false };
const FillConfig   metaBGConfInv  PROGMEM = {{ 0, 0, 0, WA_LEFT }, DSP_WIDTH, 0,  false };
const FillConfig   volbarConf     PROGMEM = {{ TFT_FRAMEWDT, DSP_HEIGHT-8, 0, WA_LEFT }, DSP_WIDTH-TFT_FRAMEWDT*2, 5, true };
const FillConfig  playlBGConf     PROGMEM = {{ 0, 26, 0, WA_LEFT }, DSP_WIDTH, 12, false };
const FillConfig  heapbarConf     PROGMEM = {{ 0, DSP_HEIGHT-1, 0, WA_LEFT }, DSP_WIDTH, 1, false };

/* WIDGETS  */                           /* { left, top, fontsize, align } */
const WidgetConfig bootstrConf    PROGMEM = { 0, DSP_HEIGHT-10, 1, WA_CENTER };
const WidgetConfig bitrateConf    PROGMEM = { TFT_FRAMEWDT+20, 64-11-10, 1, WA_LEFT };
//const WidgetConfig voltxtConf     PROGMEM = { 32, 108, 1, WA_RIGHT };
const WidgetConfig  iptxtConf     PROGMEM = { TFT_FRAMEWDT, 64-12, 1, WA_LEFT };
const WidgetConfig   rssiConf     PROGMEM = { TFT_FRAMEWDT, 64-11-10, 1, WA_LEFT };
const WidgetConfig numConf        PROGMEM = { TFT_FRAMEWDT, 57, 0, WA_CENTER };
const WidgetConfig apNameConf     PROGMEM = { 0, 20, 1, WA_CENTER };
const WidgetConfig apName2Conf    PROGMEM = { 0, 28, 1, WA_CENTER };
const WidgetConfig apPassConf     PROGMEM = { 0, 38, 1, WA_CENTER };
const WidgetConfig apPass2Conf    PROGMEM = { 0, 46, 1, WA_CENTER };
const WidgetConfig clockConf      PROGMEM = { 0, 57, 0, WA_RIGHT };
const WidgetConfig vuConf         PROGMEM = { 0, DSP_HEIGHT-24, 1, WA_CENTER };
const WidgetConfig bootWdtConf    PROGMEM = { 0, DSP_HEIGHT-8*2-5, 1, WA_CENTER };

const ProgressConfig bootPrgConf  PROGMEM = { 90, 10, 4 };
const BitrateConfig fullbitrateConf PROGMEM = {{TFT_FRAMEWDT+16, 38, 1, WA_RIGHT}, 27};

/* BANDS  */                             /* { onebandwidth, onebandheight, bandsHspace, bandsVspace, numofbands, fadespeed } */
const VUBandsConfig bandsConf     PROGMEM = { (MAX_WIDTH)/2 - 4, 4, 8, 1, 17, 6 };

/* STRINGS  */
const char         numtxtFmt[]    PROGMEM = "%d";
const char           rssiFmt[]    PROGMEM = "%d";
const char          iptxtFmt[]    PROGMEM = "%s";
//const char         voltxtFmt[]    PROGMEM = "%d";
const char        bitrateFmt[]    PROGMEM = "%d kBs";

/* MOVES  */                             /* { left, top, width } */
const MoveConfig    clockMove     PROGMEM = { 0, 0, -1 };
const MoveConfig   weatherMove    PROGMEM = { 0, 0, -1 };
const MoveConfig   weatherMoveVU  PROGMEM = { 0, 0, -1 };

#endif
