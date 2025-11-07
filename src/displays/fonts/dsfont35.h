#ifndef dsfont_h
#define dsfont_h

#ifdef CLOCKFONT_7SEG
  #if CLOCKFONT_MONO
    #include "DS_DIGI28pt7b_mono.h"                          // https://tchapi.github.io/Adafruit-GFX-Font-Customiser/
  #else
    #include "DS_DIGI28pt7b.h"
  #endif
#else
  #include "VT_DIGI_34x19.h"
#endif

#define Clock_GFXfont Clock_GFXfont_sec
#endif
