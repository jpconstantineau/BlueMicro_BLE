// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef SLEEP_H
#define SLEEP_H
#include <Arduino.h>
#include <bluemicro_hid.h>
#include "keyboard_config.h"
#include "firmware_config.h"
#include "nrf52gpio.h"

// Keyboard Matrix
extern byte rows[]  ;      // Contains the GPIO Pin Numbers defined in keyboard_config.h
extern byte columns[] ;     // Contains the GPIO Pin Numbers defined in keyboard_config.h  

void prepareSleep(void);
void sleepNow(void);
void gotoSleep(unsigned long timesincelastkeypress,bool connected);

#endif
