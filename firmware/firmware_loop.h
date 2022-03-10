// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include <bluemicro_hid.h>
#include "firmware.h"
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>
#include "command_queues.h"
#include "datastructures.h"
#include "nrf52gpio.h"
#include "nrf52battery.h"

extern commandlist_t commandList; 
extern commandqueue_t setupQueue;
extern commandqueue_t commandQueue;
extern commandqueue_t loopQueue;

extern PersistentState keyboardconfig;
extern DynamicState keyboardstate;
extern  std::vector<uint16_t> stringbuffer; // buffer for macros to type into...
extern  std::vector<HIDKeyboard> reportbuffer; 
extern Battery batterymonitor;
extern  led_handler statusLEDs;  /// Typically a Blue LED and a Red LED


    void addloopcommands(void);
    void scanMatrix(void);
    void sendKeyPresses(void);
    void addStringToQueue(const char* str);
    void UpdateQueue(void);
    void addKeycodeToQueue(const uint16_t keycode);
    void addKeycodeToQueue(const uint16_t keycode, const uint8_t modifier);
    void process_keyboard_function(uint16_t keycode);
    void checkforsleep(void);
    #ifndef USER_MACRO_FUNCTION  
    #define USER_MACRO_FUNCTION 1  
    void process_user_macros(uint16_t macroid);
    #endif
