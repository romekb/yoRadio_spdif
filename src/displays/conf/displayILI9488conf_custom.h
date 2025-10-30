
/*************************************************************************************
    ILI9488 480X320 displays configuration file.
    Copy this file to yoRadio/src/displays/conf/displayILI9488conf_custom.h
    and modify it
    More info on https://github.com/e2002/yoradio/wiki/Widgets#widgets-description
*************************************************************************************/

#ifndef displayILI9488conf_h
#define displayILI9488conf_h

#define DSP_WIDTH       480
#define DSP_HEIGHT      320
#define TFT_FRAMEWDT    10
#define MAX_WIDTH       DSP_WIDTH-TFT_FRAMEWDT*2

#if BITRATE_FULL
  #define TITLE_FIX 44
#else
  #define TITLE_FIX 0
#endif
#define bootLogoTop     110

/* SROLLS  */                            /* {{ left, top, fontsize, align }, buffsize, uppercase, width, scrolldelay, scrolldelta, scrolltime } */
#ifdef HIDE_TITLE2
const ScrollConfig metaConf      PROGMEM = {{ TFT_FRAMEWDT, TFT_FRAMEWDT, 5, WA_LEFT }, 140, true, MAX_WIDTH, 5000, 9, 50 };
const ScrollConfig title1Conf    PROGMEM = {{ TFT_FRAMEWDT, 66, 5, WA_LEFT}, 140, true, MAX_WIDTH, 5000, 7, 50};
#else
const ScrollConfig metaConf      PROGMEM = {{ TFT_FRAMEWDT, TFT_FRAMEWDT, 4, WA_LEFT }, 140, true, MAX_WIDTH, 5000, 9, 50 };
const ScrollConfig title1Conf    PROGMEM = {{ TFT_FRAMEWDT, 55, 3, WA_LEFT}, 140, true, MAX_WIDTH, 5000, 7, 50};
#endif
const ScrollConfig title2Conf    PROGMEM = {{ TFT_FRAMEWDT, 85, 3, WA_LEFT}, 140, true, MAX_WIDTH, 5000, 7, 50};
const ScrollConfig playlistConf  PROGMEM = {{ TFT_FRAMEWDT, 146, 4, WA_LEFT }, 140, true, MAX_WIDTH, 1000, 7, 50 };
const ScrollConfig apTitleConf   PROGMEM = {{ TFT_FRAMEWDT, TFT_FRAMEWDT, 4, WA_CENTER }, 140, false, MAX_WIDTH, 0, 7, 50 };
const ScrollConfig apSettConf    PROGMEM = {{ TFT_FRAMEWDT, 320-TFT_FRAMEWDT-16, 2, WA_LEFT }, 140, false, MAX_WIDTH, 0, 7, 50 };
const ScrollConfig weatherConf   PROGMEM = {{ TFT_FRAMEWDT, 117, 3, WA_CENTER }, 140, false, MAX_WIDTH, 5000, 6, 50 };
const ScrollConfig namedayConf   PROGMEM = {{ TFT_FRAMEWDT, 208, 3, WA_LEFT }, 80, true, 161, 0, 3, 50 };

/* BACKGROUNDS  */                       /* {{ left, top, fontsize, align }, width, height, outlined } */
#ifdef HIDE_TITLE2
const FillConfig metaBGConf      PROGMEM = {{ 5, 51, 0, WA_CENTER}, DSP_WIDTH - 10, 3, true};
const FillConfig metaBGConfInv   PROGMEM = {{ 0, 0, 0, WA_LEFT }, 0, 0, false };
#else
const FillConfig metaBGConf      PROGMEM = {{ 5, 43, 0, WA_CENTER}, DSP_WIDTH - 10, 1, true};
const FillConfig metaBGConfInv   PROGMEM = {{ 0, 0, 0, WA_LEFT }, 0, 0, false };
#endif
const FillConfig volbarConf      PROGMEM = {{TFT_FRAMEWDT, DSP_HEIGHT - TFT_FRAMEWDT - 8, 0, WA_LEFT}, MAX_WIDTH, 8, true};
const FillConfig  playlBGConf    PROGMEM = {{ 0, 138, 0, WA_LEFT }, DSP_WIDTH, 36, false };
const FillConfig  heapbarConf    PROGMEM = {{ 0, DSP_HEIGHT-2, 0, WA_LEFT }, DSP_WIDTH, 2, false };

/* WIDGETS  */ /* { left, top, fontsize, align } */
const WidgetConfig bootstrConf   PROGMEM = {0, 243, 2, WA_CENTER};
const WidgetConfig bitrateConf   PROGMEM = {TFT_FRAMEWDT, 150, 2, WA_RIGHT};
const WidgetConfig voltxtConf    PROGMEM = {0, DSP_HEIGHT - 38, 2, WA_CENTER}; // Hangerő
const WidgetConfig iptxtConf     PROGMEM = {TFT_FRAMEWDT, DSP_HEIGHT - 38, 2, WA_LEFT};
const WidgetConfig rssiConf      PROGMEM = {TFT_FRAMEWDT, DSP_HEIGHT - 48, 3, WA_RIGHT};
const WidgetConfig numConf       PROGMEM = {0, 200, 70, WA_CENTER};
const WidgetConfig apNameConf    PROGMEM = {TFT_FRAMEWDT, 88, 3, WA_CENTER};
const WidgetConfig apName2Conf   PROGMEM = {TFT_FRAMEWDT, 120, 3, WA_CENTER};
const WidgetConfig apPassConf    PROGMEM = {TFT_FRAMEWDT, 173, 3, WA_CENTER};
const WidgetConfig apPass2Conf   PROGMEM = {TFT_FRAMEWDT, 205, 3, WA_CENTER};
const WidgetConfig clockConf     PROGMEM = {10, 218, 60, WA_RIGHT}; // {jobb oldali távolság, top}
const WidgetConfig vuConf        PROGMEM = {35, 252, 1, WA_CENTER}; // center fektetett, "align" nincs használva
const WidgetConfig bootWdtConf   PROGMEM = {0, 216, 2, WA_CENTER};
const ProgressConfig bootPrgConf PROGMEM = {90, 14, 4};

//{{ left, top, fontsize, align }dimension}
const BitrateConfig fullbitrateConf PROGMEM = {{25, 148, 2, WA_RIGHT}, 60};

/* BANDS { onebandwidth (width), onebandheight (height), bandsHspace (space), bandsVspace (vspace), numofbands (perheight), fadespeed (fadespeed)} */
#ifdef BOOMBOX_STYLE
  const VUBandsConfig bandsConf PROGMEM = {200, 9, 4, 2, 20, 10};
#else
  const VUBandsConfig bandsConf PROGMEM = {400, 7, 4, 2, 30, 9};
#endif

/* STRINGS  */
const char numtxtFmt[] PROGMEM = "%d";
const char rssiFmt[] PROGMEM = "WiFi %ddBm";
const char iptxtFmt[] PROGMEM = "%s";
const char voltxtFmt[] PROGMEM = "\023\025%d%%";
const char bitrateFmt[] PROGMEM = "%d kBs";

/* MOVES  */ /* { left, top, width } */
const MoveConfig clockMove     PROGMEM = {0, 176, -1};
const MoveConfig weatherMove   PROGMEM = {10, 116, MAX_WIDTH}; // Ha a VU ki van kapcsolva (szélesített pozíció)
const MoveConfig weatherMoveVU PROGMEM = {10, 116, MAX_WIDTH}; // Az időjárás widget pozíciója.

#endif