/*
Copyright 2018-2021 <Pierre Constantineau>

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

#ifndef BLUEMICRO_DISPLAY_H
#define BLUEMICRO_DISPLAY_H
#include "datastructures.h"
#include "firmware_config.h"
#include "keyboard_config.h"
#include "nrf52gpio.h"
#include <Arduino.h>
#include <bluefruit.h>

// see fonts here: https://github.com/olikraus/u8g2/wiki/fntlistall
// see constructors here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp

#ifdef BLUEMICRO_CONFIGURED_DISPLAY
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#endif

enum DisplayUpdateType {
  DISPLAY_UPDATE_STARTUP = 0,
  DISPLAY_UPDATE_STATUS = 1,
  DISPLAY_UPDATE_DEBUG = 2,
};

class BlueMicro_Display {
public:
  BlueMicro_Display(PersistentState *cfg, DynamicState *stat);

  void begin(void);
  void update(void);

  void setStartupDisplayCallback(updateDisplay_cb_t callback);
  void setStatusDisplayCallback(updateDisplay_cb_t callback);
  void setDebugDisplayCallback(updateDisplay_cb_t callback);
  void changeUpdateMode(DisplayUpdateType mode);
  void sleep(void);
  void clear();

private:
  DisplayUpdateType updatemode;

  updateDisplay_cb_t _startupUpdateDisplay_cb; // this one is called during bootup
  updateDisplay_cb_t _statusUpdateDisplay_cb;  // this one is called regularly
  updateDisplay_cb_t _debugUpdateDisplay_cb;   // this one is called on demand

  PersistentState *config;
  DynamicState *status;
};

void battery(uint8_t x, uint8_t y, uint8_t data);
void printline(uint8_t x, uint8_t y, char *data);
void printline(uint8_t x, uint8_t y, int8_t data);
void printline(uint8_t x, uint8_t y, uint16_t data);
void printline(uint8_t x, uint8_t y, uint32_t data);

void drawStartup(PersistentState *cfg, DynamicState *stat);
void drawStatus(PersistentState *cfg, DynamicState *stat);
void drawDebug(PersistentState *cfg, DynamicState *stat);

#endif // DISPLAY_H