/*
Copyright 2019-2021 <Pierre Constantineau>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include "LedRGB.h"

#ifdef NEOPIXEL_AVAILABLE
Adafruit_NeoPixel pixels = Adafruit_NeoPixel();
#endif

uint8_t RGBval = 150;
uint8_t RGBcounter = 0;
rgb_color colors[WS2812B_LED_COUNT];
uint32_t rgb_mode = RGB_MODE_PLAIN;

// Converts a color from HSV to RGB.
// h is hue, as a number between 0 and 360.
// s is the saturation, as a number between 0 and 255.
// v is the value, as a number between 0 and 255.
// what is HSV and how does it compare to RGB?: https://www.kirupa.com/design/little_about_color_hsv_rgb.htm
rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v) {
  uint8_t f = (h % 60) * 255 / 60;
  uint8_t p = (255 - s) * (uint16_t)v / 255;
  uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t r = 0, g = 0, b = 0;
  switch ((h / 60) % 6) {
  case 0:
    r = v;
    g = t;
    b = p;
    break;
  case 1:
    r = q;
    g = v;
    b = p;
    break;
  case 2:
    r = p;
    g = v;
    b = t;
    break;
  case 3:
    r = p;
    g = q;
    b = v;
    break;
  case 4:
    r = t;
    g = p;
    b = v;
    break;
  case 5:
    r = v;
    g = p;
    b = q;
    break;
  }
  return rgb_color(r, g, b);
}

void setupRGB(void) {
#ifdef NEOPIXEL_AVAILABLE
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setPin(WS2812B_LED_PIN);
  pixels.updateLength(WS2812B_LED_COUNT);
#endif
}
void updateRGBmode(uint32_t mode) { rgb_mode = mode; }

void updateRGB(unsigned long timesincelastkeypress) {

  if (timesincelastkeypress < PWM_TOUCH_INTERVAL) {
    RGBval = 255;

  } else {
    // if (RGBval  > 1) {RGBval -- ;} else {RGBval  = 0 ;}
    if (timesincelastkeypress / 10 > 255) {
      RGBval = 0;
    } else {
      RGBval = 255 - timesincelastkeypress / 10;
    }
  }
#ifdef NEOPIXEL_AVAILABLE
  pixels.clear();
  uint16_t time = millis() >> 2;
  switch (rgb_mode) {
  case 0: // OFF
    // cppcheck-suppress unsignedLessThanZero
    for (uint16_t i = 0; i < WS2812B_LED_COUNT; i++) { // For each pixel...
      pixels.setPixelColor(i, 0, 0, 0);
    }
    break;
  case RGB_MODE_PLAIN: // RAINBOW

    // cppcheck-suppress unsignedLessThanZero
    for (uint16_t i = 0; i < WS2812B_LED_COUNT; i++) { // For each pixel...
      byte x = (time >> 2) - (i << 3);
      colors[i] = hsvToRgb((uint32_t)x * 359 / 256, 255, RGBval);
      pixels.setPixelColor(i, colors[i].red, colors[i].green, colors[i].blue);
    }
    break;
  case RGB_MODE_BREATHE:
    break;
  case RGB_MODE_RAINBOW:
    break;
  case RGB_MODE_SWIRL:
    break;
  case RGB_MODE_SNAKE:
    break;
  case RGB_MODE_KNIGHT:
    break;
  case RGB_MODE_XMAS:
    break;
  case RGB_MODE_GRADIENT:
    break;
  case RGB_MODE_RGBTEST:
    if (RGBcounter > 3)
      RGBcounter = 1;
    // cppcheck-suppress unsignedLessThanZero
    for (uint16_t i = 0; i < WS2812B_LED_COUNT; i++) { // For each pixel...
      if (RGBcounter == 1) {
        colors[i].red = RGBval;
      } else {
        colors[i].red = 0;
      }
      if (RGBcounter == 2) {
        colors[i].green = RGBval;
      } else {
        colors[i].green = 0;
      }
      if (RGBcounter == 3) {
        colors[i].blue = RGBval;
      } else {
        colors[i].blue = 0;
      }
      pixels.setPixelColor(i, colors[i].red, colors[i].green, colors[i].blue);
    }
    RGBcounter++;
    break;
  default:
    // unknown mode.  switch to mode 0
    // cppcheck-suppress unsignedLessThanZero
    for (int i = 0; i < WS2812B_LED_COUNT; i++) { // For each pixel...
      pixels.setPixelColor(i, 0, 0, 0);
    }
    break;
  }
  pixels.setBrightness(RGBval);
  pixels.show(); // Send the updated pixel colors to the hardware.
#endif
}

void suspendRGB(void) {
#ifdef NEOPIXEL_AVAILABLE
  pixels.clear();
  // cppcheck-suppress unsignedLessThanZero
  for (int i = 0; i < WS2812B_LED_COUNT; i++) { // For each pixel...
    pixels.setPixelColor(i, 0, 0, 0);
  }
  pixels.show(); // Send the updated pixel colors to the hardware.
#endif
}
