// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include "firmware.h"
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>
#include "datastructures.h"
#include <numeric>

extern commandlist_t commandList; 
extern commandqueue_t setupQueue;
extern commandqueue_t commandQueue;
extern commandqueue_t loopQueue;

extern PersistentState keyboardconfig;
extern DynamicState keyboardstate;

//extern Battery batterymonitor;
//extern  led_handler statusLEDs;  /// Typically a Blue LED and a Red LED

void processing_loop(uint32_t interval);
void addloopcommands(void);
void scanMatrix(void);
void sendKeyPresses(void);
void addStringToQueue(const char* str);
void addKeycodeToQueue(const uint16_t keycode);
void addKeycodeToQueue(const uint16_t keycode, const uint8_t modifier);
uint16_t hid_GetMediaUsageCode(uint16_t keycode);
void checkforsleep(void);
#ifndef USER_MACRO_FUNCTION  
#define USER_MACRO_FUNCTION 1  
void process_user_macros(uint16_t macroid);
#endif
