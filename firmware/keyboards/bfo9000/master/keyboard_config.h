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
#define HARDWARE_MAPPING  BLUEMICROV2_0C
#include "breakout_mapping.h"

#define KEYBOARD_SIDE MASTER
//#define KEYBOARD_SIDE RIGHT
// CHANGE THIS FOR THE KEYBOARD TO MATCH WHAT IS BEING FLASHED. OPTIONS: LEFT  RIGHT  MASTER

#define DEVICE_NAME_R                         "BFO-9000BLE_R"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_L                         "BFO-9000BLE_L"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_M                         "BFO-9000BLE"                          /**< Name of device. Will be included in the advertising data. */

#define DEVICE_MODEL                          "BFO-9000BLE_V1"                          /**< Name of device. Will be included in the advertising data. */

#define MANUFACTURER_NAME                     "keebio"                      /**< Manufacturer. Will be passed to Device Information Service. */


/* HARDWARE DEFINITION*/
/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 9

#define MATRIX_ROW_PINS { D3, D2, D4, C6, D7, E6 }
#define MATRIX_COL_PINS {B5, B6, B2, B3, B1, F7, F6, F5, F4  }
#define UNUSED_PINS {}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define PERIPHERAL_COUNT 1 // more than 1 doesn't work yet... 


	#define BACKLIGHT_PWM_ON 0
	#define WS2812B_LED_PIN B4
	
	#define WS2812B_LED_COUNT 20
	#define WS2812B_LED_ON 1 

#if KEYBOARD_SIDE == RIGHT
#define KEYMAP( \
      k00, k01, k02, k03, k04, k05, k06, k07, k08, \
      k10, k11, k12, k13, k14, k15, k16, k17, k18, \
      k20, k21, k22, k23, k24, k25, k26, k27, k28, \
      k30, k31, k32, k33, k34, k35, k36, k37, k38,  \
      k40, k41, k42, k43, k44, k45, k46, k47, k48, \
      k50, k51, k52, k53, k54, k55, k56, k57, k58 \
) \
{ \
    { k08, k07, k06, k05, k04, k03, k02, k01, k00 }, \
    { k18, k17, k16, k15, k14, k13, k12, k11, k10 }, \
    { k28, k27, k26, k25, k24, k23, k22, k21, k20 }, \
    { k38, k37, k36, k35, k34, k33, k32, k31, k30 }, \
    { k48, k47, k46, k45, k44, k43, k42, k41, k40 }, \
    { k58, k57, k56, k55, k54, k53, k52, k51, k50 } \
}
#else
#define KEYMAP( \
      k00, k01, k02, k03, k04, k05, k06, k07, k08, \
      k10, k11, k12, k13, k14, k15, k16, k17, k18, \
      k20, k21, k22, k23, k24, k25, k26, k27, k28, \
      k30, k31, k32, k33, k34, k35, k36, k37, k38,  \
      k40, k41, k42, k43, k44, k45, k46, k47, k48, \
      k50, k51, k52, k53, k54, k55, k56, k57, k58 \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58 } \
} 

#endif

#endif /* KEYBOARD_CONFIG_H */
