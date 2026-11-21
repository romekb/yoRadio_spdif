# Patch biblioteki SD dla Arduino-ESP32 3.0.7

Ten katalog zawiera gotowy plik `sd_diskio.cpp` do ręcznej podmiany w zainstalowanym pakiecie Arduino-ESP32 **3.0.7**. To rozwiązanie jest przeznaczone dla Arduino IDE — nie wymaga PlatformIO ani dodawania lokalnej biblioteki do projektu.

## Instalacja

1. Zamknij Arduino IDE.
2. Odszukaj katalog pakietu ESP32 w Arduino15.
3. Zrób kopię zapasową oryginalnego pliku `sd_diskio.cpp`.
4. Zastąp go plikiem z tego katalogu.
5. Uruchom ponownie Arduino IDE i skompiluj yoRadio.

Ścieżka docelowa:

```
Arduino15/packages/esp32/hardware/esp32/3.0.7/libraries/SD/src/sd_diskio.cpp
```

Typowe lokalizacje katalogu Arduino15:

- Windows: `%LOCALAPPDATA%/Arduino15`
- Linux: `~/.arduino15`
- macOS: `~/Library/Arduino15`

Pełna ścieżka zależy od systemu, ale końcówka pozostaje taka sama:
`packages/esp32/hardware/esp32/3.0.7/libraries/SD/src/sd_diskio.cpp`.

## Co zawiera backport

Zmiany pochodzą z późniejszych poprawek Espressif dla Arduino-ESP32:

- `4e086ff` — poprawki inicjalizacji karty SPI, ponowienie CMD0, obsługa CRC i argumentów ACMD41/CMD1 oraz limit czasu inicjalizacji.
- `c1edb83` — poprawne dekodowanie odpowiedzi karty po zapisie, STOP TRAN wraz z bajtem dopełniającym oraz oczekiwanie na zakończenie wewnętrznego zapisu karty przed CMD13.

Nie zmienia to wersji core Arduino-ESP32, Wi-Fi, lwIP ani kodu FTP yoRadio.

## Ważne

Patch jest przygotowany dla oryginalnego źródła biblioteki SD z Arduino-ESP32 3.0.7. Po aktualizacji lub ponownej instalacji pakietu ESP32 Arduino IDE może przywrócić oryginalny plik — wtedy podmianę trzeba wykonać ponownie.

Przed testem zachowaj kopię oryginału, aby można było łatwo cofnąć zmianę.
