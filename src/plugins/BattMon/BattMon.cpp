/**
 * BATTERY LEVEL DISPLAYING plugin
 */

#include "../../core/options.h"
#ifdef BATT_MON_PIN
#define CONFIG_ADC_SUPPRESS_DEPRECATE_WARN true
#include "BattMon.h"
#include "../../core/display.h"
#include "../../core/player.h"
#include "../../core/network.h"
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
    Serial.printf("ADC= %4d, ", adcraw);
    #endif
    if(filter < 500) filter = (float)adcraw;
    filter = (1.0f-BATT_FILTER)*filter + BATT_FILTER*(float)adcraw;
    adcraw = filter * BATT_ADC_SCALE;
    #ifdef ADC_RAW_DEBUG
    Serial.printf("Filtered= %4d, Voltage= %04dmV\r\n", (uint16_t)filter, adcraw);
    #endif
    if(adcraw > BATT_FULL) adcraw = BATT_FULL;
    uint16_t battpercent = map(adcraw, BATT_EMPTY, BATT_FULL, 0, 100);
    if(adcraw <= BATT_EMPTY) {
      battpercent = 0;
      blink = !blink;
      _battIcon->setActive(blink, !blink);
      dsp.fillRect(battIconConf.widget.left + battIconConf.width, battIconConf.widget.top + 3, 3,6, blink ? battIconOutEmpty:battIconBackground);
      if(BATT_CRITICAL_INTERVAL) ttsProc(true);
    } else {
      if(!blink) _battIcon->setActive(true);
      dsp.fillRect(battIconConf.widget.left + battIconConf.width, battIconConf.widget.top + 3, 3,6, (battpercent <= 20) ? battIconOutEmpty : battIconOut);
      blink = true;
    }
    if(battpercent <= 20) {_battIcon->setColor(battIconEmpty, battIconOutEmpty); if(battpercent && BATT_EMPTY_INTERVAL) ttsProc(false);}
    else                  {_battIcon->setColor(battIconIn, battIconOut); ttsTimer = 0;}
    _battIcon->setValue(battpercent);
  }  
}

void battMon::ttsProc(bool critic) {
  const char *buf;
  if(network.status != CONNECTED || L10N_LANGUAGE==0) return;
  if(ttsTimer == 0) ttsStage = 0;
  switch(ttsStage) {
    case 0: if(++ttsTimer == 30) {
        isPlaying = (player.status() == PLAYING);
        if(isPlaying && config.getMode()==PM_SDCARD) config.sdResumePos = player.getFilePos()-player.inBufferFilled();
        ttsStage = 1;
      }
      break;
    case 1:
        buf = (critic ? critical[L10N_LANGUAGE-1] : warnings[L10N_LANGUAGE-1]);
        player.connecttospeech(buf, langs[L10N_LANGUAGE-1]);
        ttsStage = 2;
        break;
    case 2:
      if(!player.isRunning()) {
        if(isPlaying) player.toggle();
        ttsStage = 3;
      }
      break;
    case 3:
      if(++ttsTimer >= (critic ? BATT_CRITICAL_INTERVAL : BATT_EMPTY_INTERVAL)) {
        ttsTimer = 0;
        ttsStage = 0;
      }
      break;

  }
  //Serial.printf("Tim:%d, Stag:%d\r\n", ttsTimer, ttsStage);
}

#endif