Zmodyfikowana wersja projektu yoRadio (eRadio) z: https://github.com/e2002/yoradio

<img src="yoRadio_mis.jpg" width="560" height="400"><br />

Nowa wersja oparta na pliku yoRadio_ESP32-S3_N16R8_ILI9488_v0.9.720_V-Tom_v04.2.zip. 
DZIAŁA TYLKO Z wyświetlaczem ST7789 320x240! Powinna działać z wyświetlaczami ILI9341 320x240. 
Obsługiwany jest standardowy układ ESP32 WROVER (lub WROOM + zewnętrzna pamięć PSRAM) lub ESP32S3.

Co się zmieniło:
- Dodano obsługę wyjścia SPDIF. Może to być wyjście koncentryczne (COAX) lub optyczne (OPTICAL).
- Dodano obsługę wielu języków: EN, RU, PL, HU, NL, EL.
- Zmieniono układ wyświetlacza. Tylko dla wyświetlaczy ST7789 i ILI9341 o rozdzielczości 320x240
- Dodano przewijanie dla wyświetlania imienin (PL, NL, HU)
- Tylko przycisk „Play” na pilocie może wybudzić odtwarzacz z trybu uśpienia/wygaszacza ekranu.
- Brak strony z ustawieniami głośności. Zmiana głośności jest sygnalizowana tylko za pomocą paska głośności i wartości na głównym ekranie odtwarzacza.
- Jednoczesne działanie wielu scroll'i na ekranie.
- Zainstalowana wyszukiwarka stacji radiowych - lupka w interfejscie www.

Wyjście SPDIF może działać zamiennie ze zwykłym przetwornikiem cyfrowo-analogowym I2S lub wewnętrznym przetwornikiem cyfrowo-analogowym. Nie można używać SPDIF wraz z VS1053. 
Jedynym sposobem w tej sytuacji jest całkowite wyłączenie VS1053. 
Aktualny typ wyjścia można przełączać („w locie”) za pomocą „Ustawień” w interfejsie WWW. 
W tym celu używam przełącznika „Touch debug” na stronie ustawień. 
W folderze „data” udostępniam zmodyfikowaną stronę ustawień ze zmienionym opisem przełącznika z „Touch debug” na „SPDIF output”. 
W pliku „myoptions.h” należy dodać definicję pinu „#define SPDIF_OUT xx” dla zdefiniowania pinu wyjściowego SPDIF. 
Ten pin można zdefiniować też jako ten sam pin, co pin DATA dla konwertera I2S. 
Jeżli pozostanie niezdefiniowany lub ustawiony na 255, obsługa SPDIF zostanie wyłączona.

Sprzętoweo wyjście COAXIAL SPDIF jest proste. 
W przypadku COAX wystarczy wstawić rezystor szeregowy 470 omów między pinem zadeklarowanym jako SPDIF_OUT a gniazdem cinch, które jest wyjściem COAX. 
Do wyjścia optycznego można użyć nadajnika TOSLINK, takiego jak FCR684214T lub TOTX173, lub dowolnego innego. 
W niektórych przypadkach wystarczy nawet czerwona dioda LED z rezystorem szeregowym 100 omów.

Załączam mój plik „myoptions.h” w celach referencyjnych. 
Używam płytki ESP32 CYD z dodanym układem pamięci PSRAM, przetwornikiem cyfrowo-analogowym PCM5102A i koncentrycznym wyjœciem SPDIF podłączonym do pinu Data przetwornika DAC.

Testy przeprowadzono na radiach internetowych, korzystając ze strumieni AAC i MP3 oraz plików MP3 na karcie SD (testowano stacje MP3 o bitrate do 320 kbps i AAC o bitraate około 200 kbps).

------------------------------------------------------------------------------------------------------

This is modified version of yoRadio (eRadio) project from: https://github.com/e2002/yoradio

New version based on yoRadio_ESP32-S3_N16R8_ILI9488_v0.9.720_V-Tom_v04.2.zip.
WORKING ONLY WITH ST7789 320x240 display ! Should work on ILI9341 320x240 displays.
Standard ESP32 WROVER (or WROOM + External PSRAM) or ESP32S3 is supported.

What's changed:
- added support for SPDIF output. This can be either COAX or OPTICAL.
- added support for multiple languages: EN,RU,PL,HU,NL,EL
- changed display layout. Only for ST7789 and ILI9341 320x240 displays
- added scroll for displaying name days (PL,NL,HU)
- only "Play" key on remote can wakeup player from sleep/screensaver mode.
- no Volume page. Changing volume is indicated only via volume bar and value on main player screen.
- allow multiple scrolls working at the same time.
- installed radio stations search engine
  
The SPDIF output can coexist with normal I2S DAC, or internal DAC. You can't use SPDIF with VS1053. Only way in this situation is completly disable VS1053.
You can switch ("on the fly") current output type via "Settings" in WWW interface. For this I use the "Touch debug" switch. 
In "data" folder I provide modified settings page with changed switch description from "Touch debug" to "SPDIF output".
In "myoptions.h" file you must add "#define SPDIF_OUT xx" pin definition for spdif usage. This pin can be defined as the same pin as the DATA pin for an I2S converter.
If left undefined or set to 255, SPDIF support is disabled.

In hardware, the COAXIAL spdif output is simple. For COAX just put a 470 ohm series resistor between the pin declared as SPDIF_OUT and the cinch socket that is the COAX output.
For optical output you can use TOSLINK transmitter like FCR684214T or TOTX173, or any other. In some cases, even a red LED with a 100 ohm series resistor is sufficient.

I provide my "myoptions.h" file for reference. I use CYD module with additional PSRAM chip, PCM5102A DAC and coaxial spdif output connected to Data pin of DAC for common usage.

Tested on internet radio provided AAC and MP3 streams, and on MP3 files on SD card (testing up to 320kbps MP3 stations and about 200kbps AAC).
