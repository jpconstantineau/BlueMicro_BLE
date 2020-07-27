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
#include "breakout_mapping.h"

#define KEYBOARD_SIDE SINGLE


#define DEVICE_NAME_R                         "25_BLE_R"                         /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_L                         "25_BLE_L"                         /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_M                         "25_BLE"                           /**< Name of device. Will be included in the advertising data. */

#define DEVICE_MODEL                        "25_V1"                          /**< Name of device. Will be included in the advertising data. */

#define MANUFACTURER_NAME                   "40Percent.Club"         /**< Manufacturer. Will be passed to Device Information Service. */


/* HARDWARE DEFINITION*/
/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 5

#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1 }
#define UNUSED_PINS {}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define KEYMAP( \
	 K00,   K01,   K02,   K03,  K04,    \
	 K10,   K11,   K12,   K13,  K14,   \
	 K20,   K21,   K22,   K23,  K24,   \
	 K30,   K31,   K32,   K33,  K34,  \
	 K40,   K41,   K42,   K43,  K44 \
) { \
	{ K00,   K01,   K02,   K03, K04,  }, \
	{ K10,   K11,   K12,   K13, K14,  }, \
	{ K20,   K21,   K22,   K23, K24,  }, \
	{ K30,   K31,   K32,   K33, K34  }, \
	{ K40,   K41,   K42,   K43, K44  } \
}



#endif /* KEYBOARD_CONFIG_H */
