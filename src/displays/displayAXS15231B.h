#ifndef AXS15231B_h
#define AXS15231B_h

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include "drivers/AXS15231B/AXS15231B_TFT.h"
#include "fonts/bootlogo99x64.h"

typedef GFXcanvas16 Canvas;
typedef AXS15231B_TFT yoDisplay;

#include "tools/commongfx.h"

#if DSP_MODEL==DSP_AXS15231B_180
  #include "fonts/dsfont52.h"
  #if __has_include("conf/displayAXS15231B_180conf_custom.h")
    #include "conf/displayAXS15231B_180conf_custom.h"
  #else
    #include "conf/displayAXS15231B_180conf.h"
  #endif
#else  
  #include "fonts/dsfont70.h"
  #if __has_include("conf/displayAXS15231Bconf_custom.h")
    #include "conf/displayAXS15231Bconf_custom.h"
  #else
    #include "conf/displayAXS15231Bconf.h"
  #endif
#endif

#endif
