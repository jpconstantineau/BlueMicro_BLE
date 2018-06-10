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
#include "avr_mapping.h"
#ifndef KEYBOARD_CONFIG_H
#define KEYBOARD_CONFIG_H

#define COL2ROW       0
#define ROW2COL       1

#define LEFT 0
#define RIGHT 1
#define MASTER 2

#define KEYBOARD_SIDE RIGHT

#if   KEYBOARD_SIDE == RIGHT
#define DEVICE_NAME                         "Minidox_R"                          /**< Name of device. Will be included in the advertising data. */
#elif KEYBOARD_SIDE == LEFT
#define DEVICE_NAME                         "Minidox_L"                          /**< Name of device. Will be included in the advertising data. */
#else
#define DEVICE_NAME                         "Minidox"                          /**< Name of device. Will be included in the advertising data. */
#endif

#define DEVICE_MODEL                        "Minidox_V1"                          /**< Name of device. Will be included in the advertising data. */

#define MANUFACTURER_NAME                   "ThatCanadian"                      /**< Manufacturer. Will be passed to Device Information Service. */

// Set max power. Accepted values are: -40, -30, -20, -16, -12, -8, -4, 0, 4
#define DEVICE_POWER 0
#define PNP_ID_VENDOR_ID_SOURCE             0x02                                       /**< Vendor ID Source. */
#define PNP_ID_VENDOR_ID                    0x1915                                     /**< Vendor ID. */
#define PNP_ID_PRODUCT_ID                   0xEEEE                                     /**< Product ID. */
#define PNP_ID_PRODUCT_VERSION              0x0001                                     /**< Product Version. */


#define DEBUG_SERIAL 1  

#if KEYBOARD_SIDE == LEFT
#define BLE_HID 1
#define BLE_CENTRAL 1
#define BLE_PERIPHERAL 0
#define BLE_PAIRS 1
#define PERIPHERAL_COUNT 1
#define CENTRAL_COUNT 1
#endif
#if KEYBOARD_SIDE == RIGHT
#define BLE_HID 0
#define BLE_CENTRAL 0
#define BLE_PERIPHERAL 1
#define BLE_PAIRS 1
#define PERIPHERAL_COUNT 1
#define CENTRAL_COUNT 0
#endif
#if KEYBOARD_SIDE == MASTER
#define BLE_CENTRAL 0
#define BLE_PERIPHERAL 0
#define BLE_PAIRS 0
#define BLE_HID 1
#define PERIPHERAL_COUNT 1
#define CENTRAL_COUNT 0
#endif


/* HARDWARE DEFINITION*/
/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 5

// Minidox on Arduino
//#define MATRIX_ROW_PINS { B2, B6, B4, B5 }
//#define MATRIX_COL_PINS { F4, D3, D2, D1, D4 } 

#define MATRIX_ROW_PINS { B2, B6, B4, B5 }
#define MATRIX_COL_PINS { F4, D3, D2, D1, D4 }
#define UNUSED_PINS {}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define DEBOUNCETIME 20

#endif /* KEYBOARD_CONFIG_H */

