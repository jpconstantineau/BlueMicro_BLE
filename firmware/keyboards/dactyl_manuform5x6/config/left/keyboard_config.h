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
// CHANGE THIS FOR THE KEYBOARD TO MATCH WHAT IS BEING FLASHED. OPTIONS: LEFT  RIGHT  MASTER

#define DEVICE_NAME_R                        "Manuform(5x6)_R"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_L                        "Manuform(5x6)_L"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_M                        "Manuform(5x6)BLE"                          /**< Name of device. Will be included in the advertising data. */

#define DEVICE_MODEL                        "Dactyl_Manuform(5x6)BLE"                          /**< Name of device. Will be included in the advertising data. */

#define MANUFACTURER_NAME                   "/u/crystalhand"                      /**< Manufacturer. Will be passed to Device Information Service. */


#if KEYBOARD_SIDE == LEFT
#define KEYMAP( \
      k00,  k01,  k02, k03, k04, k05, \
      k10,  k11,  k12, k13, k14, k15, \
      k20,  k21,  k22, k23, k24, k25, \
      k30,  k31,  k32, k33, k34, k35, \
	              k42, k43,           \
							k44, k45, \
							k54, k55, \
							k52, k53  \
) \
{ \
    { k00,  k01,  k02, k03, k04, k05 }, \
    { k10,  k11,  k12, k13, k14, k15 }, \
    { k20,  k21,  k22, k23, k24, k25 }, \
    { k30,  k31,  k32, k33, k34, k35 }, \
	{KC_NO, KC_NO,k42, k43, k44, k45 }, \
	{KC_NO, KC_NO,k52, k53, k54, k55 }  \
} 
#else
#define KEYMAP( \
      k00,  k01,  k02, k03, k04, k05, \
      k10,  k11,  k12, k13, k14, k15, \
      k20,  k21,  k22, k23, k24, k25, \
      k30,  k31,  k32, k33, k34, k35, \
	              k42, k43,           \
	  k40,  k41,	                  \		  
	  k50,  k51,  					  \
	  k52,  k53                       \
) \
{ \
    {k00, k01, k02, k03, k04,   k05  }, \
    {k10, k11, k12, k13, k14,   k15  }, \
    {k20, k21, k22, k23, k24,   k25  }, \
    {k30, k31, k32, k33, k34,   k35  }, \
	{k40, k41, k42, k43, KC_NO, KC_NO}, \
	{k50, k51, k52, k53, KC_NO, KC_NO}  \
}
#endif

#endif /* KEYBOARD_CONFIG_H */
