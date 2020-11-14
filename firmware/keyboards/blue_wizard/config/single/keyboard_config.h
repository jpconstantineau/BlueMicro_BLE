/*
Copyright (C) 2020 Andrew Wells <andrew.wells88@gmail.com>

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

#define KEYBOARD_SIDE MASTER
#define BATTERY_TYPE = BATT_LIPO;

#define DEVICE_NAME_M "Blue Wizard" /**< Name of device. Will be included in the advertising data. */
#define DEVICE_MODEL "Blue Wizard" /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME "awells" /**< Manufacturer. Will be passed to Device Information Service. */


#define KEYMAP( \ 
    kC0, kD0, kE0, kC1, kD1, kE1, kC2, kD2, kE2,  \
    k00, k10, k20, k30, k40, k50,                 \
    k01, k11, k21, k31, k41, k51,                 \
    k02, k12, k22, k32, k42, k52,                 \
    k03, k13, k23, k33, k43, k53,                 \
         k14, k24, k34, k54,                      \
                             k56, k55,            \
                                  k35,            \
                        k36, k46, k25,            \
                                                  \
    kC3, kD3, kE3, kC4, kD4, kE4, kC5, kE5, kD5,  \
                   k60, k70, k80, k90, kA0, kB0,  \
                   k61, k71, k81, k91, kA1, kB1,  \
                   k62, k72, k82, k92, kA2, kB2,  \
                   k63, k73, k83, k93, kA3, kB3,  \
                        k64, k84, k94, kA4,       \
              k96, k85,                           \
              k86,                                \
              k66, k75, k65                       \
) {                                              \
        { k00, k01, k02, k03, KC_NO,    KC_NO,    KC_NO      }, \
        { k10, k11, k12, k13, k14,      KC_NO,    KC_NO      }, \
        { k20, k21, k22, k23, k24,      k25,      KC_NO      }, \
        { k30, k31, k32, k33, k34,      k35,      k36   }, \
        { k40, k41, k42, k43, KC_NO,    KC_NO,    k46   }, \
        { k50, k51, k52, k53, k54,      k55,      k56   }, \
        { k60, k61, k62, k63, k64,      k65,      k66   }, \
        { k70, k71, k72, k73, KC_NO,    k75,      KC_NO      }, \
        { k80, k81, k82, k83, k84,      k85,      k86   }, \
        { k90, k91, k92, k93, k94,      KC_NO,    k96   }, \
        { kA0, kA1, kA2, kA3, kA4,      KC_NO,    KC_NO      }, \
        { kB0, kB1, kB2, kB3, KC_NO,    KC_NO,    KC_NO      }, \
        { kC0, kC1, kC2, kC3, kC4,      kC5,      KC_NO      }, \
        { kD0, kD1, kD2, kD3, kD4,      kD5,      KC_NO      }, \
        { kE0, kE1, kE2, kE3, kE4,      kE5,      KC_NO      } \
}

#endif /* KEYBOARD_CONFIG_H */
