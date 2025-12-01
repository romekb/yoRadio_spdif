/**
 * BATTERY LEVEL DISPLAYING plugin

 I use 2:1 voltage divider from battery to PIN35 and single cell LiIon battery.
 100k resistor in series + 100k resistor to GND.
 My 1.74f scale value is for this divider and my ESP32 wroom module.
 */

#ifndef BATTMON_H
#define BATTMON_H

#include "../../pluginsManager/pluginsManager.h"
#include "../../displays/dspcore.h"
#include "../../displays/widgets/widgets.h"
#include "../../displays/widgets/pages.h"
#include "../../core/config.h"

#define BATT_EMPTY      3100          // batt empty (critical) theshold in mV
#define BATT_FULL       4000          // batt full voltage in mV
#define BATT_FILTER     0.02f         // ADC filter coefficient
#define BATT_ADC_SCALE  1.74f         // ADC scale fatcor -> set to: (measured batt voltage in mV) / (adc filtered value)
                                      // add "#define ADC_RAW_DEBUG" to myoptions.h file to get ADC reading in debug terminal

#define BATT_EMPTY_INTERVAL     60*5      // in seconds = 5min (set to 0 for disable voice empty warning), active bellow 20% of batt
#define BATT_CRITICAL_INTERVAL  60*1      // in seconds = 1min (set to 0 for disable voice critical warning), active bellow EMPTY treshold
#define BATT_ICON_POS           285,193   // X,Y for 320x240 displays. For other, need adjust

class battMon : public Plugin {
  public:
    battMon();
    void on_end_setup();
    void on_ticker();
  private:
    const uint16_t battIconIn         = config.color565(  0, 200,   0);   //Inner Color BATT OK
    const uint16_t battIconEmpty      = config.color565(255,  40,  40);   //Inner Color BATT EMPTY
    const uint16_t battIconOut        = config.color565(255, 255, 255);   //Outline color
    const uint16_t battIconOutEmpty   = config.color565(255, 128, 128);   //Outline color if empty
    const uint16_t battIconBackground = config.theme.background;
                              /* {{ left, top, fontsize, align }, width, height, outlined } */
    const FillConfig battIconConf = {{BATT_ICON_POS, 0, WA_LEFT }, 25, 12, true }; //position on TFT and icon size
    const char    *langs[6]  = {"EN","RU","HU","PL","NL","EL"};
    const char *warnings[6]  = {"Battery low",          // EN
                                "низкий заряд батареи", // RU
                                "Alacsony akkumulátor", // HU
                                "Mało prundu",          // PL
                                "Batterij bijna leeg",  // NL
                                "Χαμηλή μπαταρία"};     // EL
    const char *critical[6]  = {"Battery critical", 
                                "критический заряд батареи", 
                                "Kritikus akkumulátor", 
                                "Koniec prundu", 
                                "Batterij kritisch", 
                                "Κρίσιμη μπαταρία"};

    // do not modify any bellow
    SliderWidget *_battIcon;
    int8_t _adcChan = -1;
    bool blink, isPlaying;
    float filter = 0.0f;
    uint16_t ttsTimer, ttsStage;
    void ttsProc(bool critic);
};

extern battMon battMonitor;

#endif // battMon_H

