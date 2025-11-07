#ifndef displayST7789_h
#define displayST7789_h

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#if DSP_MODEL==DSP_ST7789_76
  #include "fonts/bootlogo62x40.h"
  #include "fonts/dsfont35.h"
#else
  #include "fonts/bootlogo99x64.h"
  #include "fonts/dsfont52.h"
#endif

typedef GFXcanvas16 Canvas;
typedef Adafruit_ST7789 yoDisplay;

#include "tools/commongfx.h"


#if DSP_MODEL==DSP_ST7789
  #if __has_include("conf/displayST7789conf_custom.h")
    #include "conf/displayST7789conf_custom.h"
  #else
    #include "conf/displayST7789conf.h"
  #endif
#elif DSP_MODEL==DSP_ST7789_170
  #if __has_include("conf/displayST7789_170conf_custom.h")
    #include "conf/displayST7789_170conf_custom.h"
  #else
    #include "conf/displayST7789_170conf.h"
  #endif
#elif DSP_MODEL==DSP_ST7789_76
  #if __has_include("conf/displayST7789_76conf_custom.h")
    #include "conf/displayST7789_76conf_custom.h"
  #else
    #include "conf/displayST7789_76conf.h"
  #endif
#else
  #if __has_include("conf/displayST7789_240conf_custom.h")
    #include "conf/displayST7789_240conf_custom.h"
  #else
    #include "conf/displayST7789_240conf.h"
  #endif
#endif

#endif
