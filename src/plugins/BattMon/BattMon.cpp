/**
 * BATTERY LEVEL DISPLAYING plugin
 */

#include "../../core/options.h"
#ifdef BATT_MON_PIN
#define CONFIG_ADC_SUPPRESS_DEPRECATE_WARN true
#include "BattMon.h"
#include "../../core/display.h"
#include <driver/adc.h>
#include <esp_private/sar_periph_ctrl.h>

battMon battMonitor;

battMon::battMon() {
  registerPlugin();
}

void battMon::on_end_setup() {  
  _adcChan = digitalPinToAnalogChannel(BATT_MON_PIN);
  if(_adcChan >= 0) {
    #if((BATT_MON_PIN==36) || (BATT_MON_PIN==39))
      sar_periph_ctrl_adc_oneshot_power_acquire();
    #endif
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten((adc1_channel_t)_adcChan, ADC_ATTEN_DB_12);   // 0 - 3.3V

    _battIcon = new SliderWidget(battIconConf, battIconIn, battIconBackground, 100, battIconOut);
    display.playerpage->addWidget(_battIcon);
  }
}

void battMon::on_ticker() {
  if(config.store.dspon && _adcChan >= 0 && display.mode() == PLAYER) {
    uint16_t adcraw = adc1_get_raw((adc1_channel_t)_adcChan);
    #ifdef ADC_RAW_DEBUG
    Serial.printf("ADC= %4d,  ", adcraw);
    #endif
    if(filter < 500) filter = (float)adcraw;
    filter = (1.0f-BATT_FILTER)*filter + BATT_FILTER*(float)adcraw;
    adcraw = filter;
    #ifdef ADC_RAW_DEBUG
    Serial.printf("Filtered= %4d\r\n", adcraw);
    #endif
    if(adcraw < BATT_EMPTY) {
      adcraw = BATT_EMPTY;
      blink = !blink;
      _battIcon->setActive(blink, !blink);
      dsp.fillRect(battIconConf.widget.left + battIconConf.width, battIconConf.widget.top + 3, 3,6, blink ? battIconOut:battIconBackground);
    } else {
      if(!blink) _battIcon->setActive(true);
      dsp.fillRect(battIconConf.widget.left + battIconConf.width, battIconConf.widget.top + 3, 3,6, battIconOut);
      blink = true;
    }
    if(adcraw > BATT_FULL) adcraw = BATT_FULL;
    uint16_t ubatt = map(adcraw, BATT_EMPTY, BATT_FULL, 0, 100);
    if(ubatt < 25) _battIcon->setColor(battIconEmpty, false); 
    else           _battIcon->setColor(battIconIn, false);
    _battIcon->setValue(ubatt);
  }  
}

#endif