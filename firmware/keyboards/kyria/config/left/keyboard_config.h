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
#include "hardware_config.h"

#define KEYBOARD_SIDE LEFT
// #define KEYBOARD_SIDE RIGHT
// CHANGE THIS FOR THE KEYBOARD TO MATCH WHAT IS BEING FLASHED. OPTIONS: LEFT  RIGHT  MASTER

#define DEVICE_NAME_R                         "Kyria_R"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_L                         "Kyria_L"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_M                         "KyriaBLE"                         /**< Name of device. Will be included in the advertising data. */

#define DEVICE_MODEL                          "KyriaBLE_V1"                      /**< Name of device. Will be included in the advertising data. */

#define MANUFACTURER_NAME                     "Thomas Baart"                     /**< Manufacturer. Will be passed to Device Information Service. */


#if KEYBOARD_SIDE == RIGHT
#define KEYMAP( \
            R00, R01, R02, R03, R04, R05, \
            R10, R11, R12, R13, R14, R15, \
  R20, R21, R22, R23, R24, R25, R26, R27, \
  R30, R31, R32, R33, R34 \
  ) \
  { \
    { KC_NO,KC_NO, R00, R01, R02, R03,  R04,  R05 }, \
    { KC_NO,KC_NO, R10, R11, R12, R13,  R14,  R15 }, \
    { R20,  R21,   R22, R23, R24, R25,  R26,  R27 }, \
    { R30,  R31,   R32, R33, R34, KC_NO,KC_NO,KC_NO }\
  }
#else
#define KEYMAP( \
  L00, L01, L02, L03, L04, L05,\
  L10, L11, L12, L13, L14, L15, \
  L20, L21, L22, L23, L24, L25, L26, L27,\
                 L30, L31, L32, L33, L34 \
  ) \
  { \
    { KC_NO,KC_NO, L05, L04, L03, L02,  L01,  L00 }, \
    { KC_NO,KC_NO, L15, L14, L13, L12,  L11,  L10 }, \
    { L27,  L26,   L25, L24, L23, L22,  L21,  L20 }, \
    { L34,  L33,   L32, L31, L30, KC_NO,KC_NO,KC_NO } \
  } 

#endif

#endif /* KEYBOARD_CONFIG_H */
