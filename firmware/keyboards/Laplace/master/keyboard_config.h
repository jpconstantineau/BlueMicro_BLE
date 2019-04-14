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

#define COL2ROW       1
#define ROW2COL       0

#define LEFT 0
#define RIGHT 1
#define MASTER 2

#define KEYBOARD_SIDE MASTER

#if   KEYBOARD_SIDE == RIGHT
#define DEVICE_NAME                         "LaplaceBLE_R"                          /**< Name of device. Will be included in the advertising data. */
#elif KEYBOARD_SIDE == LEFT
#define DEVICE_NAME                         "LaplaceBLE_L"                          /**< Name of device. Will be included in the advertising data. */
#else
#define DEVICE_NAME_M                         "LaplaceBLE"                          /**< Name of device. Will be included in the advertising data. */
#endif

#define DEVICE_MODEL                        "LaplaceBLE_v1"                          /**< Name of device. Will be included in the advertising data. */

#define MANUFACTURER_NAME                   "SouthpawDesign"                      /**< Manufacturer. Will be passed to Device Information Service. */

// Set max power. Accepted values are: -40, -30, -20, -16, -12, -8, -4, 0, 4
#define DEVICE_POWER 0
#define PNP_ID_VENDOR_ID_SOURCE             0x02                                       /**< Vendor ID Source. */
#define PNP_ID_VENDOR_ID                    0x1915                                     /**< Vendor ID. */
#define PNP_ID_PRODUCT_ID                   0xEEEE                                     /**< Product ID. */
#define PNP_ID_PRODUCT_VERSION              0x0001                                     /**< Product Version. */



/* HARDWARE DEFINITION*/
/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 7

/* key matrix pins */
#define MATRIX_ROW_PINS {D3, F4, D2, F5, D7, B4, C6, E6}
#define MATRIX_COL_PINS {D1, F6, F7, B1, B3, B2, B6}
#define UNUSED_PINS {}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define DEBOUNCETIME 15


#define KEYMAP( \
    A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, \
    B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11,      B13, \
    C1, C2, C3, C4, C5, C6, C7,     C9, C10, C11, C12, C13, \
    D1, D2, D3, D4, D5,     D7,         D10, D11, D12, D13 \
    ) { \
        {A1, A2, A3, A4, A5, A6, A7}, \
        {KC_NO, A13, A12, A11, A10, A9, A8}, \
        {B1, B2, B3, B4, B5, B6, B7}, \
        {KC_NO, B13, KC_NO, B11, B10, B9, B8}, \
        {C1, C2, C3, C4, C5, C6, C7}, \
        {KC_NO, C13, C12, C11, C10, C9, KC_NO}, \
        {D1, D2, D3, D4, D5, KC_NO, D7}, \
        {KC_NO, D13, D12, D11, D10, KC_NO, KC_NO} \
    }

#endif /* KEYBOARD_CONFIG_H */
