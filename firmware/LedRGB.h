/*
Copyright 2019 <Pierre Constantineau>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef LEDRGB_H
#define LEDRGB_H
#include <Arduino.h>
#include "keyboard_config.h"
#include "firmware_config.h"
#include "src\Adafruit_NeoPixel.h"
#include "hid_keycodes.h"
#include "advanced_keycodes.h"

// IMPORTANT NOTES:
// See https://arduino.stackexchange.com/questions/34095/how-do-i-configure-the-arduino-ide-to-look-for-source-code-in-a-subdirectory-wit
// We need to copy the adafruit library files and copy to the firmware folder.
// This is because the arduino IDE can't really work with folders properly
// if one renames the "libraries" folder to "src", then it tries to compile all the examples and link everything.  Something we don't want to do (and ultimately fails)

  typedef struct rgb_color
  {
    unsigned char red, green, blue;
    rgb_color() {};
    rgb_color(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {};
  } rgb_color;

extern Adafruit_NeoPixel pixels;
void setupRGB(void);
void updateRGBmode(uint32_t mode);
void updateRGB(unsigned long timesincelastkeypress);
void suspendRGB(void);

#endif