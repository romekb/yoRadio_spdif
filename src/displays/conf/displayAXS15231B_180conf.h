/*************************************************************************************
    AXS15231B 640x180 displays configuration file.
    Copy this file to yoRadio/src/displays/conf/displayAXS15231B_180conf_custom.h
    and modify it
    More info on https://github.com/e2002/yoradio/wiki/Widgets#widgets-description
*************************************************************************************/

#ifndef displayAXS15231B_180conf_h
#define displayAXS15231B_180conf_h

#define DSP_WIDTH       640
#define DSP_HEIGHT      180
#define TFT_FRAMEWDT    8
#define MAX_WIDTH       DSP_WIDTH-TFT_FRAMEWDT*2

#if BITRATE_FULL
  #define TITLE_FIX 44
#else
  #define TITLE_FIX 0
#endif
#define bootLogoTop     40

/* SROLLS  */                            /* {{ left, top, fontsize, align }, buffsize, uppercase, width, scrolldelay, scrolldelta, scrolltime } */
const ScrollConfig metaConf       PROGMEM = {{ TFT_FRAMEWDT, TFT_FRAMEWDT, 3, WA_LEFT }, 140, true, MAX_WIDTH, 5000, 9, 40 };
const ScrollConfig title1Conf     PROGMEM = {{ TFT_FRAMEWDT, 32, 2, WA_LEFT }, 140, true, MAX_WIDTH, 5000, 7, 40 };
const ScrollConfig title2Conf     PROGMEM = {{ TFT_FRAMEWDT, 51, 2, WA_LEFT }, 140, true, MAX_WIDTH, 5000, 7, 40 };
const ScrollConfig playlistConf   PROGMEM = {{ TFT_FRAMEWDT, 112, 3, WA_LEFT }, 140, false, MAX_WIDTH, 1000, 7, 40 };
const ScrollConfig apTitleConf    PROGMEM = {{ TFT_FRAMEWDT, TFT_FRAMEWDT, 3, WA_CENTER }, 140, false, MAX_WIDTH, 0, 7, 40 };
const ScrollConfig apSettConf     PROGMEM = {{ TFT_FRAMEWDT, DSP_HEIGHT-TFT_FRAMEWDT-16, 2, WA_LEFT }, 140, false, MAX_WIDTH, 0, 7, 40 };
const ScrollConfig weatherConf    PROGMEM = {{ TFT_FRAMEWDT, 70, 3, WA_LEFT }, 140, true, MAX_WIDTH+20, 0, 7, 40 };
const ScrollConfig namedayConf    PROGMEM = {{ TFT_FRAMEWDT, 128, 3, WA_LEFT }, 80, true, 161, 0, 3, 40 };

/* BACKGROUNDS  */                       /* {{ left, top, fontsize, align }, width, height, outlined } */
const FillConfig  metaBGConf       PROGMEM = {{ 0, 0, 0, WA_LEFT }, DSP_WIDTH, 28, false };
const FillConfig  metaBGConfInv  PROGMEM = {{ 0, 0, 0, WA_LEFT }, DSP_WIDTH, 2, false };
const FillConfig  volbarConf         PROGMEM = {{ 0, 156, 0, WA_LEFT }, 273, 8, true };
const WidgetConfig   rssiConf     PROGMEM = { 47, 146, 1, WA_RIGHT };
const FillConfig  playlBGConf      PROGMEM = {{ 0, 107, 0, WA_LEFT }, DSP_WIDTH, 24, false };
const FillConfig  heapbarConf     PROGMEM = {{ 0, 165, 0, WA_LEFT }, 273, 5, true };

/* WIDGETS  */                           /* { left, top, fontsize, align } */
const WidgetConfig bootstrConf    PROGMEM = { 0, 150, 1, WA_CENTER };
const WidgetConfig bitrateConf    PROGMEM = { TFT_FRAMEWDT, 32,  2, WA_RIGHT};
const WidgetConfig voltxtConf     PROGMEM = {  TFT_FRAMEWDT, 214,  1, WA_CENTER };
const WidgetConfig  iptxtConf     PROGMEM = { 50, 146, 1, WA_LEFT };
const WidgetConfig numConf        PROGMEM = {  0, 120, 72, WA_CENTER };
const WidgetConfig apNameConf     PROGMEM = { TFT_FRAMEWDT, 40, 2, WA_CENTER };
const WidgetConfig apName2Conf    PROGMEM = { TFT_FRAMEWDT, 65, 2, WA_CENTER };
const WidgetConfig apPassConf     PROGMEM = { TFT_FRAMEWDT, 100, 2, WA_CENTER };
const WidgetConfig apPass2Conf    PROGMEM = { TFT_FRAMEWDT, 125, 2, WA_CENTER };
const WidgetConfig  clockConf     PROGMEM = { 30, 141, 52, WA_RIGHT };  /* 52 is a fixed font size. do not change */
const WidgetConfig vuConf         PROGMEM = { 0, 91, 1, WA_LEFT };
const WidgetConfig bootWdtConf    PROGMEM = { TFT_FRAMEWDT, 120, 2, WA_CENTER };

const ProgressConfig  bootPrgConf  PROGMEM = { 100, 14, 4 };
//const BitrateConfig  fullbitrateConf   PROGMEM = {{DSP_WIDTH-TFT_FRAMEWDT-34, 36, 1, WA_LEFT}, 40 };
const BitrateConfig fullbitrateConf PROGMEM = {{DSP_WIDTH-TITLE_FIX, 29, 2, WA_CENTER}, TITLE_FIX };

/* BANDS  */                             /* { onebandwidth, onebandheight, bandsHspace, bandsVspace, numofbands, fadespeed } */
//const VUBandsConfig bandsConf     PROGMEM = { 40, 100, 6, 2, 8, 10 };
#ifdef BOOMBOX_STYLE
  const VUBandsConfig bandsConf PROGMEM = {250, 7, 4, 2, 20, 10};
#else
  const VUBandsConfig bandsConf PROGMEM = {500, 7, 4, 2, 30, 12};
#endif

/* STRINGS  */
const char         numtxtFmt[]    PROGMEM = " %d      ";
const char           rssiFmt[]    PROGMEM = "WiFi %d";
const char          iptxtFmt[]    PROGMEM = "%s";
const char         voltxtFmt[]    PROGMEM = "VOL %d";
const char        bitrateFmt[]    PROGMEM = "%d kBs";

/* MOVES  */                             /* { left, top, width } */
const MoveConfig    clockMove     PROGMEM = { 48, 194, -1}; // -1 disables move
const MoveConfig   weatherMove    PROGMEM = { 10, 92, -1};
const MoveConfig   weatherMoveVU  PROGMEM = { 10, 92, -1};

#endif