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
#ifndef KEYBOARD_CONFIG_H
#define KEYBOARD_CONFIG_H
#include "hardware_variants.h"
#define HARDWARE_MAPPING  BLUEMICRO840V1_0  // note only the BlueMicro840 fits on the corne.
#include "breakout_mapping.h"

#define KEYBOARD_SIDE LEFT
//#define KEYBOARD_SIDE RIGHT
// CHANGE THIS FOR THE KEYBOARD TO MATCH WHAT IS BEING FLASHED. OPTIONS: LEFT  RIGHT  SINGLE

#define DEVICE_NAME_R                         "Corne_R"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_L                        "Corne_L"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_M                         "CorneBLE"                          /**< Name of device. Will be included in the advertising data. */

#define DEVICE_MODEL                        "CorneBLE_V1"                          /**< Name of device. Will be included in the advertising data. */

#define MANUFACTURER_NAME                   "foostan"                      /**< Manufacturer. Will be passed to Device Information Service. */


/* HARDWARE DEFINITION*/
/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 6
#define MATRIX_ROW_PINS { D4, C6, D7, E6 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3 }

#define UNUSED_PINS {}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define PERIPHERAL_COUNT 1 // more than 1 doesn't work yet... 

	#define BACKLIGHT_PWM_ON 0
	#define WS2812B_LED_PIN D3
	
	#define WS2812B_LED_COUNT 27
	#define WS2812B_LED_ON 1 

#if KEYBOARD_SIDE == RIGHT
#define KEYMAP( \
  R00, R01, R02, R03, R04, R05, \
  R10, R11, R12, R13, R14, R15, \
  R20, R21, R22, R23, R24, R25, \
  R30, R31, R32 \
  ) \
  { \
    { R05, R04, R03, R02, R01, R00 }, \
    { R15, R14, R13, R12, R11, R10 }, \
    { R25, R24, R23, R22, R21, R20 }, \
    { KC_NO, KC_NO, KC_NO, R32, R31, R30 } \
  }
#else
#define KEYMAP( \
  L00, L01, L02, L03, L04, L05,\
  L10, L11, L12, L13, L14, L15, \
  L20, L21, L22, L23, L24, L25,\
                 L33, L34, L35\
  ) \
  { \
    { L00, L01, L02, L03, L04, L05 }, \
    { L10, L11, L12, L13, L14, L15 }, \
    { L20, L21, L22, L23, L24, L25 }, \
    { KC_NO, KC_NO, KC_NO, L33, L34, L35 } \
  } 

#endif

#endif /* KEYBOARD_CONFIG_H */
