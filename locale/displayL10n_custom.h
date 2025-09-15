#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to yoRadio/locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
const char mon[] PROGMEM = "pon";
const char tue[] PROGMEM = "wto";
const char wed[] PROGMEM = "śro";
const char thu[] PROGMEM = "czw";
const char fri[] PROGMEM = "pią";
const char sat[] PROGMEM = "sob";
const char sun[] PROGMEM = "nie";

const char monf[] PROGMEM = "poniedziałek";
const char tuef[] PROGMEM = "wtorek";
const char wedf[] PROGMEM = "środa";
const char thuf[] PROGMEM = "czwartek";
const char frif[] PROGMEM = "piątek";
const char satf[] PROGMEM = "sobota";
const char sunf[] PROGMEM = "niedziela";

const char jan[] PROGMEM = "styczeń";
const char feb[] PROGMEM = "luty";
const char mar[] PROGMEM = "marzec";
const char apr[] PROGMEM = "kwiecień";
const char may[] PROGMEM = "maj";
const char jun[] PROGMEM = "czerwiec";
const char jul[] PROGMEM = "lipiec";
const char aug[] PROGMEM = "sierpień";
const char sep[] PROGMEM = "wrzesień";
const char octt[] PROGMEM = "październik";
const char nov[] PROGMEM = "listopad";
const char decc[] PROGMEM = "grudzień";

const char wn_N[]      PROGMEM = "NORTH";
const char wn_NNE[]    PROGMEM = "NNE";
const char wn_NE[]     PROGMEM = "NE";
const char wn_ENE[]    PROGMEM = "ENE";
const char wn_E[]      PROGMEM = "EAST";
const char wn_ESE[]    PROGMEM = "ESE";
const char wn_SE[]     PROGMEM = "SE";
const char wn_SSE[]    PROGMEM = "SSE";
const char wn_S[]      PROGMEM = "SOUTH";
const char wn_SSW[]    PROGMEM = "SSW";
const char wn_SW[]     PROGMEM = "SW";
const char wn_WSW[]    PROGMEM = "WSW";
const char wn_W[]      PROGMEM = "WEST";
const char wn_WNW[]    PROGMEM = "WNW";
const char wn_NW[]     PROGMEM = "NW";
const char wn_NNW[]    PROGMEM = "NNW";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, octt, nov, decc };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[ready]";
const char  const_PlStopped[]    PROGMEM = "[stopped]";
const char  const_PlConnect[]    PROGMEM = "[connecting]";
const char  const_DlgVolume[]    PROGMEM = "VOLUME";
const char    const_DlgLost[]    PROGMEM = "* LOST *";
const char  const_DlgUpdate[]    PROGMEM = "* UPDATING *";
const char const_DlgNextion[]    PROGMEM = "* NEXTION *";
const char const_getWeather[]    PROGMEM = "";
const char  const_waitForSD[]    PROGMEM = "INDEX SD";

const char        apNameTxt[]    PROGMEM = "AP NAME";
const char        apPassTxt[]    PROGMEM = "PASSWORD";
const char       bootstrFmt[]    PROGMEM = "Connecting %s";
const char        apSettFmt[]    PROGMEM = "SETTINGS PAGE ON: HTTP://%s/";
#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 odczuwalna: %.1f\011C \007 ciśnienie: %d hPa \007 wilgotność: %s%% \007 wiatr: %.1f m/s [%s]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 pressure: %d hPa \007 humidity: %s%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "pl";       /* https://openweathermap.org/current#multi */

#endif
