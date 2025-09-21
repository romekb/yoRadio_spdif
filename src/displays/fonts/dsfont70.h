#ifndef dsfont_h
#define dsfont_h

/*
#if CLOCKFONT_MONO
  #include "DS_DIGI56pt7b_mono.h"        // https://tchapi.github.io/Adafruit-GFX-Font-Customiser/
#else
  #include "DS_DIGI56pt7b.h"
#endif
*/
#include "VT_DIGI_34x19.h"
#if CLOCKFONT_MONO
  #include "VT_DIGI_68x38.h"        // Módosítás az óra nagyméretű fontjának betöltése.
#else
  #include "VT_DIGI_68x38.h"
#endif

#endif
