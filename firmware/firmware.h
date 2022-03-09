// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef FIRMWARE_H
#define FIRMWARE_H
#undef min
#undef max
#include "firmware_setup.h"
#include "firmware_config.h"
#include "bluetooth_config.h"
#include "keymap.h"
#include "keyscanner.h"
#include "sleep.h"
#include "bluetooth.h"
#include "nrf52battery.h"
#include "nrf52gpio.h"
#include "datastructures.h"

#include "combo_engine.h"



    void scanMatrix(void);
    void sendKeyPresses(void);
    void addStringToQueue(const char* str);
    void UpdateQueue(void);
    void addKeycodeToQueue(const uint16_t keycode);
    void addKeycodeToQueue(const uint16_t keycode, const uint8_t modifier);
    void process_keyboard_function(uint16_t keycode);
    #ifndef USER_MACRO_FUNCTION  
    #define USER_MACRO_FUNCTION 1  
    void process_user_macros(uint16_t macroid);
    #endif

#endif /* FIRMWARE_H */
