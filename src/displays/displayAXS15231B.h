#ifndef AXS15231B_h
#define AXS15231B_h

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include "../AXS15231B/AXS15231B_TFT.h"
#include "fonts/bootlogo99x64.h"
#include "fonts/dsfont70.h"

typedef GFXcanvas16 Canvas;
typedef AXS15231B_TFT yoDisplay;

#include "tools/commongfx.h"

#if DSP_MODEL==DSP_AXS15231B_270
  #if __has_include("conf/displayAXS15231B_270conf_custom.h")
    #include "conf/displayAXS15231B_270conf_custom.h"
  #else
    #include "conf/displayAXS15231B_270conf.h"
  #endif
#else  
  #if __has_include("conf/displayAXS15231Bconf_custom.h")
    #include "conf/displayAXS15231Bconf_custom.h"
  #else
    #include "conf/displayAXS15231Bconf.h"
  #endif
#endif

#endif
