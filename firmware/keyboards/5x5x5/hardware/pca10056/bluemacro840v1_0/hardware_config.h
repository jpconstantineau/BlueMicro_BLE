/*
Copyright 2020 <Pierre Constantineau>

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
#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H
#include "hardware_variants.h"


/* HARDWARE DEFINITION*/
/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* Column  pin configuration
 * col:  0  1  2  3    4  5  6    7  8  9  10 11 12 13 14
 * pin:  D7 E6 B4 B5   B6 B7 D6   F7 F6 F5 F4 F1 F0 B3 B1
 * GPIO: 6  5  8  1.09 4  12 1.06 24 22 13 15 ?? ?? 9  10
 */
/* Row  pin configuration
 * row:  0    1  2  3  4   
 * pin:  B2   D1 D0 D4 C6
 * GPIO: 1.11 30 2  29 26
 */

#define MATRIX_ROW_PINS {43,30,2,29,26} 
#define MATRIX_COL_PINS {6,5,8,41,4,12,38,24,22,13,15,17,20,9,10} 

#define UNUSED_PINS {}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
        #define BATTERY_TYPE BATT_LIPO
        #define VBAT_PIN  31
        #define VCC_PIN 32
#define VCC_POLARITY_ON 1

#define  STATUS_BLE_LED_PIN  42  //blue = 1.10
#define  STATUS_KB_LED_PIN 46  //red = 1.04

#endif /* HARDWARE_CONFIG_H */