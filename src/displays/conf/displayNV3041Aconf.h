/*************************************************************************************
    NV3041A 480x270 displays configuration file.
    Copy this file to yoRadio/src/displays/conf/displayNV3041Aconf_custom.h
    and modify it
    More info on https://github.com/e2002/yoradio/wiki/Widgets#widgets-description
*************************************************************************************/

#ifndef displayNV3041Aconf_h
#define displayNV3041Aconf_h

#define DSP_WIDTH       480
#define DSP_HEIGHT      272
#define TFT_FRAMEWDT    8
#define MAX_WIDTH       DSP_WIDTH-TFT_FRAMEWDT*2

#if BITRATE_FULL
  #define TITLE_FIX 44
#else
  #define TITLE_FIX 0
#endif
#define bootLogoTop     90

/* SROLLS  */                            /* {{ left, top, fontsize, align }, buffsize, uppercase, width, scrolldelay, scrolldelta, scrolltime } */
const ScrollConfig metaConf       PROGMEM = {{ TFT_FRAMEWDT, 0, 4, WA_LEFT }, 140, true, MAX_WIDTH, 5000, 6, 40 };
const ScrollConfig title1Conf     PROGMEM = {{ TFT_FRAMEWDT, 43, 3, WA_LEFT }, 140, true, MAX_WIDTH, 5000, 5, 40 };
const ScrollConfig title2Conf     PROGMEM = {{ TFT_FRAMEWDT, 73, 3, WA_LEFT }, 140, true, MAX_WIDTH, 5000, 5, 40 };
const ScrollConfig playlistConf   PROGMEM = {{ TFT_FRAMEWDT, 110, 3, WA_LEFT }, 140, true, MAX_WIDTH, 1000, 7, 30 };
const ScrollConfig apTitleConf    PROGMEM = {{ TFT_FRAMEWDT, TFT_FRAMEWDT, 4, WA_CENTER }, 140, false, MAX_WIDTH, 0, 7, 40 };
const ScrollConfig apSettConf     PROGMEM = {{ TFT_FRAMEWDT, DSP_HEIGHT-TFT_FRAMEWDT-16, 2, WA_LEFT }, 140, false, MAX_WIDTH, 0, 6, 40 };
const ScrollConfig weatherConf    PROGMEM = {{ TFT_FRAMEWDT, 104, 3, WA_CENTER }, 140, false, MAX_WIDTH, 0, 6, 50 };
const ScrollConfig namedayConf    PROGMEM = {{ TFT_FRAMEWDT, 182, 2, WA_LEFT }, 80, true, 161, 0, 3, 40 };

/* BACKGROUNDS  */                       /* {{ left, top, fontsize, align }, width, height, outlined } */
const FillConfig  metaBGConf      PROGMEM = {{ 5, 34, 0, WA_CENTER }, DSP_WIDTH-10, 2, true };
const FillConfig  metaBGConfInv   PROGMEM = {{ 0, 0, 0, WA_LEFT }, 0, 0, false };
const FillConfig  volbarConf      PROGMEM = {{ TFT_FRAMEWDT, DSP_HEIGHT-14, 0, WA_LEFT }, MAX_WIDTH, 7, true };
const FillConfig  playlBGConf     PROGMEM = {{ 0, 138, 0, WA_LEFT }, DSP_WIDTH, 36, false };
const FillConfig  heapbarConf     PROGMEM = {{ 0, DSP_HEIGHT-2, 0, WA_LEFT }, DSP_WIDTH, 2, false };

/* WIDGETS  */                           /* { left, top, fontsize, align } */
const WidgetConfig bootstrConf    PROGMEM = { 0, 210, 2, WA_CENTER };
const WidgetConfig bitrateConf    PROGMEM = { TFT_FRAMEWDT, 115, 2, WA_RIGHT };
const WidgetConfig voltxtConf     PROGMEM = { 0, DSP_HEIGHT-34, 2, WA_CENTER };
const WidgetConfig iptxtConf      PROGMEM = { TFT_FRAMEWDT, DSP_HEIGHT-28, 1, WA_LEFT };
const WidgetConfig rssiConf       PROGMEM = { TFT_FRAMEWDT, DSP_HEIGHT-42, 3, WA_RIGHT };
const WidgetConfig numConf        PROGMEM = { 0, 170, 9, WA_CENTER };
const WidgetConfig apNameConf     PROGMEM = { TFT_FRAMEWDT, 88, 3, WA_CENTER };
const WidgetConfig apName2Conf    PROGMEM = { TFT_FRAMEWDT, 120, 3, WA_CENTER };
const WidgetConfig apPassConf     PROGMEM = { TFT_FRAMEWDT, 173, 3, WA_CENTER };
const WidgetConfig apPass2Conf    PROGMEM = { TFT_FRAMEWDT, 205, 3, WA_CENTER };
const WidgetConfig clockConf      PROGMEM = { TFT_FRAMEWDT, 180, 0, WA_RIGHT };
const WidgetConfig vuConf         PROGMEM = { 35, 211, 1, WA_CENTER };
const WidgetConfig bootWdtConf    PROGMEM = { 0, 180, 2, WA_CENTER };
const ProgressConfig bootPrgConf  PROGMEM = { 40, 14, 4 };

//{{ left, top, fontsize, align }dimension}
const BitrateConfig fullbitrateConf PROGMEM = {{25, 135, 2, WA_LEFT}, 54 };

/* BANDS  */       /* { onebandwidth, onebandheight, bandsHspace, bandsVspace, numofbands, fadespeed } */
#ifdef BOOMBOX_STYLE
  const VUBandsConfig bandsConf PROGMEM = {200, 7, 4, 2, 20, 10};
#else
  const VUBandsConfig bandsConf PROGMEM = {400, 7, 4, 2, 30, 12};
#endif

/* STRINGS  */
const char         numtxtFmt[]    PROGMEM = "%d";
const char           rssiFmt[]    PROGMEM = "WiFi %d";
const char          iptxtFmt[]    PROGMEM = "%s";
const char         voltxtFmt[]    PROGMEM = "\023\025%d%%";
const char        bitrateFmt[]    PROGMEM = "%d kBs";

/* MOVES  */                             /* { left, top, width } */
const MoveConfig    clockMove     PROGMEM = { 48, 194, -1 }; // -1 disables move
const MoveConfig   weatherMove    PROGMEM = { 10, 92,  -1 };
const MoveConfig   weatherMoveVU  PROGMEM = { 10, 92,  -1 };

#endif