Zmodyfikowana wersja projektu yoRadio (eRadio) z: https://github.com/e2002/yoradio

Nowa wersja oparta na pliku yoRadio_ESP32-S3_N16R8_ILI9488_v0.9.720_V-Tom_v04.2.zip. 
DZIA£A TYLKO Z wyœwietlaczem ST7789 320x240! Powinna dzia³aæ z wyœwietlaczami ILI9341 320x240. 
Obs³ugiwany jest standardowy uk³ad ESP32 WROVER (lub WROOM + zewnêtrzna pamiêæ PSRAM) lub ESP32S3.

Co siê zmieni³o:
- Dodano obs³ugê wyjœcia SPDIF. Mo¿e to byæ wyjœcie koncentryczne (COAX) lub optyczne (OPTICAL).
- Dodano obs³ugê wielu jêzyków: EN, RU, PL, HU, NL, EL.
- Zmieniono uk³ad wyœwietlacza. Tylko dla wyœwietlaczy ST7789 i ILI9341 o rozdzielczoœci 320x240
- Dodano przewijanie dla wyœwietlania imienin (PL, NL, HU)
- Tylko przycisk „Play” na pilocie mo¿e wybudziæ odtwarzacz z trybu uœpienia/wygaszacza ekranu.
- Brak strony z ustawieniami g³oœnoœci. Zmiana g³oœnoœci jest sygnalizowana tylko za pomoc¹ paska g³oœnoœci i wartoœci na g³ównym ekranie odtwarzacza.
- Jednoczesne dzia³anie wielu scroll'i na ekranie.

Wyjœcie SPDIF mo¿e dzia³aæ zamiennie ze zwyk³ym przetwornikiem cyfrowo-analogowym I2S lub wewnêtrznym przetwornikiem cyfrowo-analogowym. Nie mo¿na u¿ywaæ SPDIF wraz z VS1053. 
Jedynym sposobem w tej sytuacji jest ca³kowite wy³¹czenie VS1053. 
Aktualny typ wyjœcia mo¿na prze³¹czaæ („w locie”) za pomoc¹ „Ustawieñ” w interfejsie WWW. 
W tym celu u¿ywam prze³¹cznika „Touch debug” na stronie ustawieñ. 
W folderze „data” udostêpniam zmodyfikowan¹ stronê ustawieñ ze zmienionym opisem prze³¹cznika z „Touch debug” na „SPDIF output”. 
W pliku „myoptions.h” nale¿y dodaæ definicjê pinu „#define SPDIF_OUT xx” dla zdefiniowania pinu SPDIF. Ten pin mo¿na zdefiniowaæ te¿ jako ten sam pin, co pin DATA dla konwertera I2S. 
Jeœli pozostanie niezdefiniowany lub ustawiony na 255, obs³uga SPDIF zostanie wy³¹czona.

W wersji sprzêtowej wyjœcie COAXIAL SPDIF jest proste. 
W przypadku COAX wystarczy umieœciæ rezystor szeregowy 470 omów miêdzy pinem zadeklarowanym jako SPDIF_OUT a gniazdem cinch, które jest wyjœciem COAX. 
Do wyjœcia optycznego mo¿na u¿yæ nadajnika TOSLINK, takiego jak FCR684214T lub TOTX173, lub dowolnego innego. 
W niektórych przypadkach wystarczy nawet czerwona dioda LED z rezystorem szeregowym 100 omów.

Za³¹czam plik „myoptions.h” w celach referencyjnych. 
U¿ywam modu³u CYD z dodatkowym uk³adem PSRAM, przetwornikiem cyfrowo-analogowym PCM5102A i koncentrycznym wyjœciem SPDIF pod³¹czonym do pinu Data przetwornika DAC.

Testy przeprowadzono na radiach internetowych, korzystaj¹c ze strumieni AAC i MP3 oraz plików MP3 na karcie SD (testowano stacje MP3 o przep³ywnoœci do 320 kbps i AAC o przep³ywnoœci oko³o 200 kbps).

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
  
The SPDIF output can coexist with normal I2S DAC, or internal DAC. You can't use SPDIF with VS1053. Only way in this situation is completly disable VS1053.
You can switch ("on the fly") current output type via "Settings" in WWW interface. For this I use the "Touch debug" switch. 
In "data" folder I provide modified settings page with changed switch description from "Touch debug" to "SPDIF output".
In "myoptions.h" file you must add "#define SPDIF_OUT xx" pin definition for spdif usage. This pin can be defined as the same pin as the DATA pin for an I2S converter.
If left undefined or set to 255, SPDIF support is disabled.

In hardware, the COAXIAL spdif output is simple. For COAX just put a 470 ohm series resistor between the pin declared as SPDIF_OUT and the cinch socket that is the COAX output.
For optical output you can use TOSLINK transmitter like FCR684214T or TOTX173, or any other. In some cases, even a red LED with a 100 ohm series resistor is sufficient.

I provide my "myoptions.h" file for reference. I use CYD module with additional PSRAM chip, PCM5102A DAC and coaxial spdif output connected to Data pin of DAC for common usage.

Tested on internet radio provided AAC and MP3 streams, and on MP3 files on SD card (testing up to 320kbps MP3 stations and about 200kbps AAC).
