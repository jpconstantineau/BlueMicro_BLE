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
//#define HARDWARE_MAPPING  NRFMICROV0_3 
#define HARDWARE_MAPPING  BLUEMICRO840V1_0 
#include "breakout_mapping.h"

#define KEYBOARD_SIDE SINGLE


#define DEVICE_NAME_R                         "BlueMicro_R"                         /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_L                         "BlueMicro_L"                         /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_M                         "BlueMicro"                           /**< Name of device. Will be included in the advertising data. */

#define DEVICE_MODEL                        "BM"                          /**< Name of device. Will be included in the advertising data. */

#define MANUFACTURER_NAME                   "BlueMicro Firmware"         /**< Manufacturer. Will be passed to Device Information Service. */


/* HARDWARE DEFINITION*/
/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 21
#ifdef NRF52840_XXAA // we have a nrf52840 feather
  #define MATRIX_ROW_PINS { 33 } // 33 is a not connected pin
  #define MATRIX_COL_PINS { 14, 15, 16, 17, 18, 19, 26, 25, 24, 1, 0, 2, 22, 23, 5, 6, 9, 10, 11, 12, 13 }
#else  // we have a nrf52832 feather
  #define MATRIX_ROW_PINS {23 } // 23 is a not connected pin // note, on the nrf52832 feather, RX and TX pins are connected to the serial chip.  As such, toggling these pins won't do anything.
  #define MATRIX_COL_PINS { 2, 3, 4, 5, 28, 29, 12, 13, 14, 8, 6, 20, 25, 26, 27, 30, 11, 7, 15, 16, 24 } // note: Pin Ain7 is used by the Lipo Battery measurement. Therefore not using it. replacing with not connected pin 24
#endif
#define UNUSED_PINS {}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define KEYMAP(  K00,   K01,   K02,   K03,  K04,  K05,   K06,   K07,  K08, K09,   K10,   K11,   K12,  K13,  K14,   K15,   K16,  K17, K18,   K19,   K20  ) { \
	           { K00,   K01,   K02,   K03,  K04,  K05,   K06,   K07,  K08, K09,   K10,   K11,   K12,  K13,  K14,   K15,   K16,  K17, K18,   K19,   K20 } } 

#endif /* KEYBOARD_CONFIG_H */
