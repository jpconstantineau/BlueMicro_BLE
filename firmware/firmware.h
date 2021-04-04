/*
Copyright 2018-2021 <Pierre Constantineau>

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
#ifndef FIRMWARE_H
#define FIRMWARE_H
#undef min
#undef max
#include "firmware_config.h"
#include "bluetooth_config.h"
#include "keymap.h"
#include "KeyScanner.h"
#include "sleep.h"
#include "bluetooth.h"
#include "nrf52battery.h"
#include "LedPwm.h"
#include "LedRGB.h"
#include "nrf52gpio.h"
#include "datastructures.h"
#include "debug_cli.h"
#include "usb.h"
#include "BlueMicro_display.h"
#include "BlueMicro_tone.h"
#include "combo_engine.h"


    void setupConfig(void);
    void loadConfig(void);
    void saveConfig(void);
    void resetConfig(void);
    void setupMatrix(void);
    void scanMatrix(void);
    void sendKeyPresses(void);
    void LowestPriorityloop(void);
    void NormalPriorityloop(void);
    void keyscantimer_callback(TimerHandle_t _handle);
    void batterytimer_callback(TimerHandle_t _handle);
    void RGBtimer_callback(TimerHandle_t _handle);
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
