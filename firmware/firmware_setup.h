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

extern commandlist_t commandList; 
extern commandqueue_t setupQueue;
extern commandqueue_t commandQueue;
extern PersistentState keyboardconfig;
extern DynamicState keyboardstate;
extern  std::vector<uint16_t> stringbuffer; // buffer for macros to type into...
extern  std::vector<HIDKeyboard> reportbuffer; 

extern  led_handler statusLEDs;  /// Typically a Blue LED and a Red LED

    void setupConfig(void);
    void loadConfig(void);
    void saveConfig(void);
    void resetConfig(void);
    void setupMatrix(void);

    void setuphid(void);
    void setupnrf52(void);
    void serialsplash(void);
    void addsetupcommands(void);
