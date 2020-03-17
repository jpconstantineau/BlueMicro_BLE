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

#define KEYBOARD_SIDE MASTER



#define MANUFACTURER_NAME                   "keyboards.jpconstantineau.com"            /**< Manufacturer. Will be passed to Device Information Service. */


/* HARDWARE DEFINITION*/
/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12
#ifdef ARDUINO_NRF52832_FEATHER  // this is for the 4x4 backpack and the 4x4 Platform

#define DEVICE_NAME_R                         "4x4Staggered_R"                         /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_L                         "4x4Staggered_L"                         /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_M                         "4x4Staggered"                           /**< Name of device. Will be included in the advertising data. */

#define DEVICE_MODEL                        "4x4Staggered_V1"                          /**< Name of device. Will be included in the advertising data. */


	#define MATRIX_ROW_PINS {25, 26, 27, 28}
	#define MATRIX_COL_PINS {29, 30, 2, 3, 4, 5, 7, 9, 10, 11, 12, 13 } // last 4: 17,16,15, 14
#endif

#ifdef ARDUINO_NRF52840_PCA10056 // this is for the 4x4 backpack nrf52840

#define DEVICE_NAME_M                       "4x4Backpack840"                           /**< Name of device. Will be included in the advertising data. */
#define DEVICE_MODEL                        "4x4Backpack840_V1"                          /**< Name of device. Will be included in the advertising data. */


	#define MATRIX_ROW_PINS {43, 3, 28, 45}
	#define MATRIX_COL_PINS {2, 29, 30,  26, 6, 5, 8, 41, 22, 13, 20, 17} // last 4: 10, 38, 9, 24
#endif
#define UNUSED_PINS {}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define KEYMAP( \
	 K00,   K01,   K02,   K03,  K04,   K05,   K06,   K07,  K08,   K09,   K010,   K011,     \
	 K10,   K11,   K12,   K13,  K14,   K15,   K16,   K17,  K18,   K19,   K110,   K111,    \
	 K20,   K21,   K22,   K23,  K24,   K25,   K26,   K27,  K28,   K29,   K210,   K211,   \
	 K30,   K31,   K32,   K33,  K34,   K35,   K36,   K37,  K38,   K39,   K310,   K311 \
) { \
	{ K00,   K01,   K02,   K03, K04,   K05,   K06,   K07,  K08,   K09,   K010,   K011,  }, \
	{ K10,   K11,   K12,   K13, K14,   K15,   K16,   K17,  K18,   K19,   K110,   K111,  }, \
	{ K20,   K21,   K22,   K23, K24,   K25,   K26,   K27,  K28,   K29,   K210,   K211,  }, \
	{ K30,   K31,   K32,   K33, K34,   K35,   K36,   K37,  K38,   K39,   K310,   K311  } \
}



#endif /* KEYBOARD_CONFIG_H */
