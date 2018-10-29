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


#ifndef FIRMWARE_CONFIG_H
#define FIRMWARE_CONFIG_H

#include "avr_mapping.h"
#include "keyboard_config.h"

#if KEYBOARD_SIDE == LEFT
#define BLE_HID 1
#define BLE_CENTRAL 1
#define BLE_PERIPHERAL 0
#define BLE_PAIRS 1
#define PERIPHERAL_COUNT 1
#define CENTRAL_COUNT 1
#define MATRIX_SCAN 1
#define SEND_KEYS 1
#define DEVICE_NAME DEVICE_NAME_L
#endif
#if KEYBOARD_SIDE == RIGHT
#define BLE_HID 0
#define BLE_CENTRAL 0
#define BLE_PERIPHERAL 1
#define BLE_PAIRS 1
#define PERIPHERAL_COUNT 1
#define CENTRAL_COUNT 0
#define MATRIX_SCAN 1
#define SEND_KEYS 1
#define DEVICE_NAME DEVICE_NAME_R
#endif
#if KEYBOARD_SIDE == MASTER
#define BLE_CENTRAL 0
#define BLE_PERIPHERAL 0
#define BLE_PAIRS 0
#define BLE_HID 1
#define PERIPHERAL_COUNT 1
#define CENTRAL_COUNT 0
#define MATRIX_SCAN 1
#define SEND_KEYS 1
#define DEVICE_NAME DEVICE_NAME_M
#endif
#if KEYBOARD_SIDE == TEST
#define BLE_CENTRAL 1  /// adding central adds 5 mA - this is due to the scanner.
#define BLE_PERIPHERAL 0 /// adding peripheral adds 0 mA
#define BLE_PAIRS 0  /// NOT SURE WHAT THIS ACTIVATES
#define BLE_HID 1 //1 // 
#define PERIPHERAL_COUNT 1 //1
#define CENTRAL_COUNT 0
#define MATRIX_SCAN 1 // 1 // adding matrix scanning adds 0.2-0.4 mA
#define SEND_KEYS 1 // 1 //
#define DEVICE_NAME DEVICE_NAME_M
#endif




#ifndef BOOT_MODE_COMMANDS
#define BOOT_MODE_COMMANDS {{KC_SPACE, STATE_MONITOR_MODE},{ KC_K,  STATE_BOOT_CLEAR_BONDS },{ KC_F, STATE_BOOT_SERIAL_DFU},{ KC_W, STATE_BOOT_WIRELESS_DFU}}
#define BOOT_MODE_COMMANDS_COUNT 4
#endif

#ifndef KEYSCANNINGTIMER 
#define KEYSCANNINGTIMER 2
#endif

#ifndef DEBOUNCETIME 
#define DEBOUNCETIME 10
#endif

#ifndef HIDREPORTINGINTERVAL
#define HIDREPORTINGINTERVAL 25
#endif

// Battery Service definitions.

#ifndef BLE_LIPO_MONITORING
#define BLE_LIPO_MONITORING 0
#endif

#define VBAT_PIN          (A7)
#define VBAT_MV_PER_LSB   (0.73242188F)   // 3.0V ADC range and 12-bit ADC resolution = 3000mV/4096
#define VBAT_DIVIDER      (0.71275837F)   // 2M + 0.806M voltage divider on VBAT = (2M / (0.806M + 2M))
#define VBAT_DIVIDER_COMP (1.403F)        // Compensation factor for the VBAT divider

#endif /* FIRMWARE_CONFIG_H */
