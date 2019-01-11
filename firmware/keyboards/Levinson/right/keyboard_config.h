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
#include "avr_mapping.h"

//#define KEYBOARD_SIDE MASTER
//#define KEYBOARD_SIDE LEFT
#define KEYBOARD_SIDE RIGHT
// CHANGE THIS FOR THE KEYBOARD TO MATCH WHAT IS BEING FLASHED. OPTIONS: LEFT  RIGHT  MASTER

#define DEVICE_NAME_R       "LevinsonBLE_R"   /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_L       "LevinsonBLE_L"   /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_M       "LevinsonBLE"     /**< Name of device. Will be included in the advertising data. */

#define DEVICE_MODEL        "LevinsonBLE_V2"  /**< Name of device. Will be included in the advertising data. */

#define MANUFACTURER_NAME   "Keebio"          /**< Manufacturer. Will be passed to Device Information Service. */


/* HARDWARE DEFINITION*/
/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 6

// Levinson on Arduino
#define MATRIX_ROW_PINS { D4, D7, E6, B4 }
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2, B6 }

#define UNUSED_PINS {}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define PERIPHERAL_COUNT 2 // more than 1 doesn't work yet... 
#define DEBOUNCETIME 15

#endif /* KEYBOARD_CONFIG_H */


#if KEYBOARD_SIDE == LEFT

  #define KEYMAP( \
     K00,   K01,   K02,   K03,   K04,   K05,   \
     K10,   K11,   K12,   K13 ,  K14,   K15,   \
     K20,   K21,   K22,   K23,   K24,   K25,   \
     K30,   K31 ,  K32,   K33,   K34,   K35    \
  ) { \
    { K00,   K01,   K02,   K03,   K04,   K05 }, \
    { K10,   K11,   K12,   K13,   K14,   K15 }, \
    { K20,   K21,   K22,   K23,   K24,   K25 }, \
    { K30,   K31,   K32,   K33,   K34,   K35 }  \
  }

#else

  #define KEYMAP( \
     K00,   K01,   K02,   K03,   K04,   K05,   \
     K10,   K11,   K12,   K13 ,  K14,   K15,   \
     K20,   K21,   K22,   K23,   K24,   K25,   \
     K30,   K31 ,  K32,   K33,   K34,   K35   \
  ) { \
    { K05,   K04,   K03,   K02,   K01,   K00 }, \
    { K15,   K14,   K13,   K12,   K11,   K10 }, \
    { K25,   K24,   K23,   K22,   K21,   K20 }, \
    { K35,   K34,   K33,   K32,   K31,   K30 } \
  }

#endif
