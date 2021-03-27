/*
Copyright 2018-2021 <Pierre Constantineau, Julian Komaromy>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef DEBUG_CLI_H
#define DEBUG_CLI_H

#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>
#include <bluefruit.h>

#include "bluetooth_config.h"
#include "datastructures.h"
#include "firmware.h"
#include "firmware_config.h"
#include "nrf52battery.h"
#include "nrf52gpio.h"
#include <algorithm>
#include <vector>

typedef volatile uint32_t REG32;
#define pREG32 (REG32 *)

#define DEVICE_ID_HIGH (*(pREG32(0x10000060)))
#define DEVICE_ID_LOW (*(pREG32(0x10000064)))
#define MAC_ADDRESS_HIGH (*(pREG32(0x100000a8)))
#define MAC_ADDRESS_LOW (*(pREG32(0x100000a4)))

extern SoftwareTimer keyscantimer, batterytimer;
extern Battery batterymonitor;
extern PersistentState keyboardconfig;
extern DynamicState keyboardstate;

void gpiotester(void);
void handleSerial(void);
uint8_t testlink(uint8_t setpin, uint8_t readpin);
void matrix_key_init_separator(bool singlekey);
void matrix_key_init(bool singlekey);
void matrix_key_end(bool singlekey);
void matrix_key_test(bool singlekey);
void helpline(void);

#endif /* DEBUG_CLI_H */
