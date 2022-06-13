// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause


#include <bluemicro_hid.h>
#include <bluemicro_engine.h>
#include "firmware.h"
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>
#include "datastructures.h"
#include "nrf52gpio.h"
#include "nrf52battery.h"

extern commandlist_t commandList;           // map of all possible commands
extern commandqueue_t setupQueue;           // these are the commands that are run once - during the setup call
extern commandqueue_t commandQueue;         // these are the commands that are additionnal to every scan
extern commandqueue_t loopQueue;            // these are the command that are run for every scan - during the loop call

extern PersistentState keyboardconfig;      // configuration that's saved to flash
extern DynamicState keyboardstate;          // current state of the keyboard.  gets reset on reboot.

extern Battery batterymonitor;              // Should this be moved somewhere else?
extern  led_handler statusLEDs;             // Typically a Blue LED and a Red LED

void setupConfig(void);
void loadConfig(void);
void saveConfig(void);
void resetConfig(void);
void setupMatrix(void);

void setuphid(void);
void serialsplash(void);
void addsetupcommands(void);
void addkeyboardcommands(void);
