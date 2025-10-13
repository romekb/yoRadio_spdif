#ifndef dsfont_h
#define dsfont_h

#ifdef CLOCKFONT_7SEG
  #if CLOCKFONT_MONO
    #include "DS_DIGI42pt7b_mono.h"        // https://tchapi.github.io/Adafruit-GFX-Font-Customiser/
    #include "DS_DIGI15pt7b_mono.h"
  #else
    #include "DS_DIGI42pt7b.h"
    #include "DS_DIGI15pt7b.h"
  #endif
#else
  #include "VT_DIGI_27x15.h"
  #include "VT_DIGI_47x26.h"
#endif

#endif
