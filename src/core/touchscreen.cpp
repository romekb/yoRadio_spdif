#include "options.h"
#if (TS_MODEL!=TS_MODEL_UNDEFINED) && (DSP_MODEL!=DSP_DUMMY)
#include "Arduino.h"
#include "touchscreen.h"
#include "config.h"
#include "controls.h"
#include "display.h"
#include "player.h"

#ifndef TS_X_MIN
  #define TS_X_MIN              400
#endif
#ifndef TS_X_MAX
  #define TS_X_MAX              3800
#endif
#ifndef TS_Y_MIN
  #define TS_Y_MIN              260
#endif
#ifndef TS_Y_MAX
  #define TS_Y_MAX              3800
#endif
#ifndef TS_STEPS
  #define TS_STEPS              100
#endif

#if TS_MODEL==TS_MODEL_XPT2046
  #ifdef TS_SPIPINS
    SPIClass  TSSPI(HSPI);
  #endif
  #include <XPT2046_Touchscreen.h>
  XPT2046_Touchscreen ts(TS_CS);
  typedef TS_Point TSPoint;
#elif TS_MODEL==TS_MODEL_GT911
  #include "../GT911_Touchscreen/TAMC_GT911.h"
  TAMC_GT911 ts = TAMC_GT911(TS_SDA, TS_SCL, TS_INT, TS_RST, 0, 0);
  typedef TP_Point TSPoint;
#elif TS_MODEL==TS_MODEL_AXS15231B
  #include "../AXS15231B_Touchscreen/AXS15231B_Touch.h"
  AXS15231B_Touch ts = AXS15231B_Touch(TS_SDA, TS_SCL, TS_INT, TS_RST, 0, 0);
  typedef TP_Point TSPoint;
#endif


void TouchScreen::init(uint16_t w, uint16_t h){
  
  _width  = w;
  _height = h;
#if TS_MODEL==TS_MODEL_XPT2046
  #ifdef TS_SPIPINS
    TSSPI.begin(TS_SPIPINS);
    ts.begin(TSSPI);
  #else
    #if TS_HSPI
      ts.begin(SPI2);
    #else
      ts.begin();
    #endif
  #endif
  ts.setRotation(config.store.fliptouch?3:1);
#elif TS_MODEL==TS_MODEL_GT911
  ts.begin();
  #if DSP_MODEL == DSP_NV3041A
  ts.setRotation(config.store.fliptouch?3:1);
  #else
  ts.setRotation(config.store.fliptouch?0:2);
  #endif
  ts.setResolution(_width, _height);
#elif TS_MODEL==TS_MODEL_AXS15231B
  ts.begin();
  ts.setRotation(config.store.fliptouch?1:3);
  ts.setResolution(_width, _height);
#endif
}

tsDirection_e TouchScreen::_tsDirection(uint16_t x, uint16_t y) {
  int16_t dX = x - _oldTouchX;
  int16_t dY = y - _oldTouchY;
  if (abs(dX) > _width/8 || abs(dY) > _height/6) {
    if (abs(dX) > abs(dY)) {
      if (dX > 0) {
        return TSD_RIGHT;
      } else {
        return TSD_LEFT;
      }
    } else {
      if (dY > 0) {
        return TSD_DOWN;
      } else {
        return TSD_UP;
      }
    }
  } else {
    return TSD_REQUEST;
  }
}

void TouchScreen::flip(){
#if TS_MODEL==TS_MODEL_XPT2046
  ts.setRotation(config.store.fliptouch?3:1);
#elif (TS_MODEL==TS_MODEL_GT911)
  #if DSP_MODEL == DSP_NV3041A
  ts.setRotation(config.store.fliptouch?3:1);
  #else
  ts.setRotation(config.store.fliptouch?0:2);
  #endif
#elif (TS_MODEL==TS_MODEL_AXS15231B)
  ts.setRotation(config.store.fliptouch?1:3);
#endif
}

void TouchScreen::loop(){
  uint16_t touchX, touchY;
  static bool wastouched = true;
  static uint32_t touchLongPress;
  static tsDirection_e direct;
  static uint16_t touchVol, touchStation;
  if (!_checklpdelay((config.isScreensaver) ? 100:20, _touchdelay)) return;
#if (TS_MODEL==TS_MODEL_GT911) || (TS_MODEL==TS_MODEL_AXS15231B)
  ts.read();
#endif
  bool istouched = _istouched();
  if(istouched){
  #if TS_MODEL==TS_MODEL_XPT2046
    TSPoint p = ts.getPoint();
    touchX = map(p.x, TS_X_MIN, TS_X_MAX, 0, _width);
    touchY = map(p.y, TS_Y_MIN, TS_Y_MAX, 0, _height);
  #elif (TS_MODEL==TS_MODEL_GT911) || (TS_MODEL==TS_MODEL_AXS15231B)
    TSPoint p = ts.points[0];
    touchX = p.x;
    touchY = p.y;
  #endif
  #ifdef TS_MIRROR_X
    touchX = _width - touchX;
  #endif
  #ifdef TS_MIRROR_Y
    touchY = _height - touchY;
  #endif
#if(TS_MODEL==TS_MODEL_AXS15231B && defined(TS_AXS15231_FIX)) // ghost touch on AXS15231 - accident wakeup elimination
  if(config.isScreensaver) {
    uint16_t siz = _height/4;
    if(touchX<_width-siz || touchY<_height-siz) return;       // accept only square corner of 1/4 screen height
    if(config.store.screensaverBlank && player.status() == STOPPED) {
      config.setBrightness(config.store.brightness, false);   // fast visual feedback
    }
  }
#endif
  if (!wastouched) { /*     START TOUCH     */
      _oldTouchX = touchX;
      _oldTouchY = touchY;
      touchVol = touchX;
      touchStation = touchY;
      direct = TSD_REQUEST;
      touchLongPress=millis();
    } else { /*     SWIPE TOUCH     */
      direct = _tsDirection(touchX, touchY);
      switch (direct) {
        case TSD_STAY: return;
        case TSD_LEFT:
        case TSD_RIGHT: {
            touchLongPress=millis();
            if(display.mode()==PLAYER || display.mode()==VOL){
              int16_t xDelta = map(abs(touchVol - touchX), 0, _width, 0, TS_STEPS);
              #ifndef NO_VOLUME_SCREEN
                display.putRequest(NEWMODE, VOL);
              #endif
              if (xDelta>2) {
                if(config.getMode()==PM_SDCARD && player.status() == PLAYING) {
                  if(touchX - touchVol < 0) xDelta = -xDelta;
                  player.SDSeekTo(xDelta);
                } else controlsEvent((touchVol - touchX)<0, 0, true);
                touchVol = touchX;
              }
            }
            break;
          }
        case TSD_UP:
        case TSD_DOWN: {
            touchLongPress=millis();
            if(display.mode()==PLAYER) display.putRequest(NEWMODE, STATIONS);
            if(display.mode()==STATIONS) {
              int16_t yDelta = map(abs(touchStation - touchY), 0, _height, 0, TS_STEPS);
              if (yDelta>2) {
                controlsEvent((touchStation - touchY)<0);
                touchStation = touchY;
              }
            }
            break;
          }
        default:
            break;
      }
    }
    if(0) { // (config.store.dbgtouch) {
      Serial.print("x = ");
      Serial.print(touchX);
      Serial.print(", y = ");
      Serial.println(touchY);
    }
    // volume control with repeat  
    if(istouched && direct == TSD_REQUEST && (display.mode()==PLAYER || display.mode()==VOL) && 
       millis()>_repeatDelay+500 && _oldTouchY<_height/3) {
          if(_oldTouchX < _width/3)     {onBtnClick(EVT_BTNLEFT);  touchLongPress = millis(); }  // Left-bottom = vol_down
          if(_oldTouchX > (_width*2)/3) {onBtnClick(EVT_BTNRIGHT); touchLongPress = millis(); }  // Right-bottom = vol_up
          _repeatDelay = millis() - (_repeatDelay ? 300:0);     // first delay 500ms, then repeat every 200ms
    }
    // up/down (1/10) in playlist/stations mode
    if(istouched && direct==TSD_REQUEST && display.mode()==STATIONS && millis()>_repeatDelay+500 && _oldTouchX>(_width*2)/3) {      
        if(_oldTouchY < _height/2) { 
          if(_repeatDelay) display.currentPlItem -= 9;            // if not first touch, list-10
          controlsEvent(false); 
          touchLongPress = millis(); 
        }
        else if(_oldTouchY > _height/2) { 
          if(_repeatDelay) display.currentPlItem += 9;            // if not first touch, list+10
          controlsEvent(true);  
          touchLongPress = millis(); 
        }
        _repeatDelay = millis() - (_repeatDelay ? 200:0);         // first delay 500ms, then repeat +- 10 every 300ms
    }
  }else{
    if (wastouched) {/*     END TOUCH     */
      if (direct == TSD_REQUEST) {
        uint32_t pressTicks = millis()-touchLongPress;
        if( pressTicks < BTN_PRESS_TICKS*2) {
          if(pressTicks > 50) {
            if(display.mode()==PLAYER && _oldTouchY>(_height*2)/3) {
              if(_oldTouchX < _width/3)          { player.prev(); goto _exit; }     // Left-top - prevous
              else if(_oldTouchX > (_width*2)/3) { player.next(); goto _exit; }     // Right-top - next
              else { onBtnClick(EVT_BTNMODE); goto _exit; }                         // Middle-top - Radio/SD
            } else if((display.mode()==PLAYER || display.mode()==VOL) && _oldTouchY<_height/3) {  
              if((_oldTouchX < _width/3) || _oldTouchX > (_width*2)/3) goto _exit;  // Right-bottom && Left-bottom
            } else if(display.mode()==STATIONS && _oldTouchX > (_width*2)/3) {      // stations mode, right side of TFT
              goto _exit;
            }
            onBtnClick(EVT_BTNCENTER);    // Other area - Play/Pause
          }
        } else { 
          if(player.status() == STOPPED && display.mode() == PLAYER && display.mode() != SCREENSAVER) {
            DoPwrOff();
          } else {                                    // longpress during stations -> return
            display.allowReboot = true;               // longpress during sleep -> reboot
            display.putRequest(NEWMODE, display.mode() == PLAYER ? STATIONS : PLAYER); 
          }
        }
      }
_exit:      
      direct = TSD_STAY;
      _repeatDelay = 0;
    }
  }
  wastouched = istouched;
}

bool TouchScreen::_checklpdelay(int m, uint32_t &tstamp) {
  if (millis() - tstamp > m) {
    tstamp = millis();
    return true;
  } else {
    return false;
  }
}

bool TouchScreen::_istouched(){
#if TS_MODEL==TS_MODEL_XPT2046
  return ts.touched();
#elif (TS_MODEL==TS_MODEL_GT911) || (TS_MODEL==TS_MODEL_AXS15231B)
  return ts.isTouched;
#endif
}

#endif  // TS_MODEL!=TS_MODEL_UNDEFINED
