This is modified version of yoRadio (eRadio) project from: https://github.com/e2002/yoradio

New version based on yoRadio_ESP32-S3_N16R8_ILI9488_v0.9.720_V-Tom_v04.2.zip.
WORKING ONLY WITH ST7789 320x240 display ! Standard ESP32 WROVER (or WROOM + External PSRAM) is supported too.

What's changed:
- added support for SPDIF output. This can be either COAX or OPTICAL.
- added support for multiple languages: EN,RU,PL,HU,NL,EL
- changed display layout. Only for ST7789 320x240 display
- added scroll for displaying name days (PL,NL,HU)
  
The SPDIF output can coexist with normal I2S DAC, or internal DAC. You can't use SPDIF with VS1053. Only way in this situation is completly disable VS1053.
You can switch ("on the fly") current output type via "Settings" in WWW interface. For this I use the "Touch debug" switch. 
In "data" folder I provide modified settings page with changed switch description from "Touch debug" to "SPDIF output".
In "myoptions.h" file you must add "#define SPDIF_OUT xx" pin definition for spdif usage. This pin can be defined as the same pin as the DATA pin for an I2S converter.
If left undefined or set to 255, SPDIF support is disabled.

In hardware, the COAXIAL spdif output is simple. For COAX just put a 470 ohm series resistor between the pin declared as SPDIF_OUT and the cinch socket that is the COAX output.
For optical output you can use TOSLINK transmitter like FCR684214T or TOTX173, or any other. In some cases, even a red LED with a 100 ohm series resistor is sufficient.

I provide my "myoptions.h" file for reference. I use CYD module with additional PSRAM chip, PCM5102A DAC and coaxial spdif output connected to Data pin of DAC for common usage.

Tested on internet radio provided AAC and MP3 streams, and on MP3 files on SD card (testing up to 320kbps MP3 stations and about 200kbps AAC).
