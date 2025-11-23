/**
 * BATTERY LEVEL DISPLAYING plugin
 */

#ifndef BATTMON_H
#define BATTMON_H

#include "../../pluginsManager/pluginsManager.h"
#include "../../displays/dspcore.h"
#include "../../displays/widgets/widgets.h"
#include "../../displays/widgets/pages.h"
#include "../../core/config.h"

#define BATT_EMPTY  1790        // set to ADC value at about 3.1V for single LiIon cell
#define BATT_FULL   2300        // set to ADC value at about 3.9V for single LiIon cell
#define BATT_FILTER 0.02f
#define BATT_EMPTY_INTERVAL     60*5  // 5min
#define BATT_CRITICAL_INTERVAL  60*1  // 1min

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
    const FillConfig battIconConf = {{285, 193, 0, WA_LEFT }, 25, 12, true };
    const char    *langs[6]  = {"EN","RU","HU","PL","NL","EL"};
    const char *warnings[6]  = {"Battery low",        // EN
                                "Battery low",        // RU
                                "Battery low",        // HU
                                "Mało prundu",        // PL
                                "Battery low",        // NL
                                "Battery low"};       // EL
    const char *critical[6]  = {"Battery critical", 
                                "Battery critical", 
                                "Battery critical", 
                                "Koniec prundu", 
                                "Battery critical", 
                                "Battery critical"};

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

