/*
Copyright 2018 <Pierre Constantineau>

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


//#include "bluefruit.h"  // needed for the macros...
//#undef min
//#undef max
//#include "src/services/BLEHidAdafruit.h" //this does not exist...
//#include "services/BLEHidAdafruit.h"
//#include "firmware.h"
//#include "bluetooth.h"
#include <stdint.h>
#include "hid_keycodes.h"
#include "keyboard_config.h"
#include "advanced_keycodes.h"
#include "Key.h"
#include <array>






#ifndef KEYMAP_H
#define KEYMAP_H

//extern BLEHidAdafruit blehid;        // HID Service - needed for macro functions.

#define KC_CAP_D MOD(MOD_LSHIFT, KC_D)
#define NUM_LAYERS 2

#define _QWERTY 0
#define _L1  1
#define _PRESS 0
#define _MT_TAP 1
#define _MT_HOLD 2
#define _DT_TAP 3
#define _DT_DOUBLETAP 4

#define USER_MACRO_FUNCTION   0 
void process_user_macros(uint32_t macroid);

void setupKeymap();
extern std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix;
extern void addStringToQueue(const char* str);
extern void addKeycodeToQueue(const uint16_t keycode);
#endif /* KEYMAP_H */
