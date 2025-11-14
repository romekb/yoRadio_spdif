/**
 * NEOPICEL LED CTRL plugin
 * To connect the plugin, copy its folder to the src/plugins directory.
 */

#include "../../core/options.h"
#ifdef NEOPIXEL_LED

#ifndef NEOPIXEL_BRIGHTNESS
 #define NEOPIXEL_BRIGHTNESS 2
#endif

#include "NeoLED.h"
#include "../../core/player.h"
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel leds(1, NEOPIXEL_LED, NEO_GRB + NEO_KHZ800);
neoled neo_led;

neoled::neoled() {
  registerPlugin();
  leds.begin();
}

void neoled::on_setup(){
  leds.setPixelColor(0, NEOPIXEL_BRIGHTNESS, NEOPIXEL_BRIGHTNESS, 0);
  leds.show();
}

void neoled::on_connect(){
  leds.setPixelColor(0, 0, NEOPIXEL_BRIGHTNESS, 0);
  leds.show();
}

void neoled::on_start_play(){
  leds.setPixelColor(0, NEOPIXEL_BRIGHTNESS/2, NEOPIXEL_BRIGHTNESS/2, NEOPIXEL_BRIGHTNESS);
  leds.show();
}

void neoled::on_stop_play(){
  if(leds.getPixelColor(0) != 0) {
    leds.setPixelColor(0, 0, NEOPIXEL_BRIGHTNESS, 0);
    leds.show();
  }
}

void neoled::on_track_change(){
  if(player.status() == PLAYING) {
    leds.setPixelColor(0, NEOPIXEL_BRIGHTNESS, 0, 0);
    leds.show();
    delay(200);
    on_start_play();
  }
}

void neoled::on_station_change(){
  on_track_change();
}

void neoled::on_display_queue(requestParams_t &request, bool& result){
  if(request.type == NEWMODE && request.payload == SCREENBLANK) {
    leds.setPixelColor(0, 0);
    leds.show();  
  }
}

#endif