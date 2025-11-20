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

#define BATT_EMPTY  1700        // set to ADC value at about 3.1V for single LiIon cell
#define BATT_FULL   2300        // set to ADC value at about 3.9V for single LiIon cell
#define BATT_FILTER 0.1f

class battMon : public Plugin {
public:
  battMon();
  void on_end_setup();
  void on_ticker();

  private:
    SliderWidget *_battIcon;
    int8_t _adcChan = -1;
    bool blink;
    float filter = 0.0f;
    const uint16_t battIconIn         = config.color565(0, 200, 0);   //Inner Color BATT OK
    const uint16_t battIconEmpty      = config.color565(255, 0, 0);   //Inner Color BATT EMPTY
    const uint16_t battIconOut        = 0xFFFF;   //Outline color
    const uint16_t battIconBackground = 0;        //Background color
                              /* {{ left, top, fontsize, align }, width, height, outlined } */
    const FillConfig battIconConf = {{285, 193, 0, WA_LEFT }, 25, 12, true };
};

extern battMon battMonitor;

#endif // battMon_H

