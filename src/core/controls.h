#ifndef controls_h
#define controls_h
#include "common.h"

#if IR_PIN!=255
enum : uint8_t {IR_PWR, IR_UP, IR_MUTE, IR_PREV, IR_PLAY, IR_NEXT, IR_DOWN, IR_1, IR_2, IR_3, IR_4, IR_5, IR_6, IR_7, IR_8, IR_9, IR_AST, IR_0, IR_HASH };
#endif

boolean checklpdelay(int m, unsigned long &tstamp);

void initControls();
void loopControls();
#if (ENC_BTNL!=255 && ENC_BTNR!=255) || (ENC2_BTNL!=255 && ENC2_BTNR!=255)
class yoEncoder;
void encodersLoop(yoEncoder *enc, bool first=true);
#endif
void encoder1Loop();
void encoder2Loop();
void irLoop();
void irNumber(uint8_t num);
void irBlink();
void controlsEvent(bool toRight, int8_t volDelta = 0, bool allowBrightness = false);

void onBtnClick(int id);
void onBtnDoubleClick(int id);
void onBtnDuringLongPress(int id);
void onBtnLongPressStart(int id);
void onBtnLongPressStop(int id);

void setIRTolerance(uint8_t tl);
void setEncAcceleration(uint16_t acc);
void flipTS();
void DoPwrOff();

extern __attribute__((weak)) void ctrls_on_loop();

#endif
