#ifndef displayNV3041A_h
#define displayNV3041A_h

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include "drivers/NV3041A/NV3041A.h"
#include "fonts/bootlogo99x64.h"
#include "fonts/dsfont52.h"

typedef GFXcanvas16 Canvas;
typedef NV3041A yoDisplay;

#include "tools/commongfx.h"

#if __has_include("conf/displayNV3041Aconf_custom.h")
  #include "conf/displayNV3041Aconf_custom.h"
#else
  #include "conf/displayNV3041Aconf.h"
#endif

#endif
