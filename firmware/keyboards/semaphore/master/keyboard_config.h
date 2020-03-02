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
#ifndef KEYBOARD_CONFIG_H
#define KEYBOARD_CONFIG_H
#define HARDWARE_MAPPING  BLUEMICROV2_0C
#include "avr_mapping.h"

#define KEYBOARD_SIDE MASTER
//#define KEYBOARD_SIDE RIGHT
// CHANGE THIS FOR THE KEYBOARD TO MATCH WHAT IS BEING FLASHED. OPTIONS: LEFT  RIGHT  MASTER

#define DEVICE_NAME_R                         "SemaphoreBLE_R"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_L                        "SemaphoreBLE_L"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_M                         "SemaphoreBLE"                          /**< Name of device. Will be included in the advertising data. */

#define DEVICE_MODEL                        "SemaphoreBLE_V1"                          /**< Name of device. Will be included in the advertising data. */

#define MANUFACTURER_NAME                   "JPConstantineau.com"                      /**< Manufacturer. Will be passed to Device Information Service. */


/* HARDWARE DEFINITION*/
/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS {B2, B6, D4, C6, D7 }
#define MATRIX_COL_PINS {F4, F5, F6, F7, B1, B3 }
#define UNUSED_PINS {}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define PERIPHERAL_COUNT 1 // more than 1 doesn't work yet... 


#if KEYBOARD_SIDE == RIGHT
#define KEYMAP( \
      k00, k01, k02, k03, k04, k05,  \
      k10, k11, k12, k13, k14, k15,  \
      k20, k21, k22, k23, k24, k25,  \
      k30, k31, k32, k33, k34, k35,  \
      k40, k41, k42, k43, k44, k45  \
) \
{ \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k33, k34, k35 }, \
    { k40, k41, k42, k43, k44, k45 } \
}
#else
#define KEYMAP( \
      k00, k01, k02, k03, k04, k05,  \
      k10, k11, k12, k13, k14, k15,  \
      k20, k21, k22, k23, k24, k25,  \
      k30, k31, k32, k33, k34, k35,  \
      k40, k41, k42, k43, k44, k45  \
) \
{ \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k33, k34, k35 }, \
    { k40, k41, k42, k43, k44, k45 } \
} 

#endif

#endif /* KEYBOARD_CONFIG_H */
