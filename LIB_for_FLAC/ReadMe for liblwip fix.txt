from https://4pda.to/forum/index.php?showtopic=1010378&st=17940#entry132965307 :

For those who want to listen to eRadio with aac320, flac without jerks
(problems and initial fixes are described here liblwip fix
A new version of the esp-idf v5.1 fix libraries has been compiled, used in Arduino with 3.0.5 cores (works with 3.0.X cores)

I checked the compilation of the latest mod from Maleksm
Thanks to Maleksm for tests on ESP32S3, ESP32 WROOM/WROVER
.

YOU NEED ESP32 CORE VERSION 3.0.5 up to 3.0.7. 
PLEASE UPGRADE/DOWNGRADE ESP32 CORE in BOARD MANAGER TO VERSION 3.0.5 OR 3.0.7 PRIOR TO INSTALL PATH !!


Arduino with 3.0.5 cores, you need to take liblwip.a and libesp_netif.a from and replace them in the directory:
For ESP32S3:
C:\Users\User\AppData\Local\Arduino15\packages\esp32\tools\esp32-arduino-libs\idf-release_v5.1-33fbade6\esp32s3\lib\

For ESP32:
C:\Users\User\AppData\Local\Arduino15\packages\esp32\tools\esp32-arduino-libs\idf-release_v5.1-33fbade6\esp32\lib\

(the idf-release_v5.1-33fbade6 directory may support you)

Should allow higher bitrate streams to play without warbling when compiling with Arduino IDE
