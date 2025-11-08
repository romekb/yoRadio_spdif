//v0.9.720
#include "../core/options.h"
#if DSP_MODEL==DSP_NV3041A
#include "dspcore.h"
#include "../core/config.h"

DspCore::DspCore(): NV3041A(DSP_WIDTH, DSP_HEIGHT) {}

void DspCore::initDisplay() {
  begin();
  invert();
  cp437(true);
  flip();
  setTextWrap(false);
  setTextSize(1);
  //fillScreen(0x0000);
  clearDsp(0);
}

void DspCore::clearDsp(bool black){ tftClearScreen( black ? 0 : config.theme.background); }
void DspCore::flip(){ setRotation(config.store.flipscreen?2:0); }
void DspCore::invert(){ setInvert(!config.store.invertdisplay); }
void DspCore::sleep(void){ tftSleep(true); }
void DspCore::wake(void) { tftSleep(false); }

#endif