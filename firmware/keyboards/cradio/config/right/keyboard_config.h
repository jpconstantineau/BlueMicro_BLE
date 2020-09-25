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

#define TIME_TILL_HOLD 110
#define TIME_TILL_RELEASE 20 // was 80 

#define KEYBOARD_SIDE RIGHT
//#define KEYBOARD_SIDE RIGHT
// CHANGE THIS FOR THE KEYBOARD TO MATCH WHAT IS BEING FLASHED. OPTIONS: LEFT  RIGHT  MASTER

#define DEVICE_NAME_R                         "Cradio_Right"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_L                        "Cradio_Left"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_M                         "Cradio_BLE"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_MODEL                        "CradioBLE_V2"                          /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                   "broomlabs"                      /**< Manufacturer. Will be passed to Device Information Service. */

#if KEYBOARD_SIDE == RIGHT
#define KEYMAP( \
  R00, R01, R02, R03, R04, \
  R10, R11, R12, R13, R14, \
  R20, R21, R22, R23, R24, \
  R30,R31 \
  ) \
  { R04, R03, R02, R01, R00, R14, R13, R12, R11, R10, R24, R23, R22, R21, R20, R31, R30 }
#else
#define KEYMAP( \
  L00, L01, L02, L03, L04,\
  L10, L11, L12, L13, L14,\
  L20, L21, L22, L23, L24,\
                 L33, L34 \
  ) \
  { \
    L00, L01, L02, L03, L04, L10, L11, L12, L13, L14, L20, L21, L22, L23, L24, KC_NO, KC_NO, KC_NO,L33, L34 \
  } 
  
#endif
#endif /* KEYBOARD_CONFIG_H */
