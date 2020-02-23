/*
Copyright 2018 <Pierre Constantineau, Julian Komaromy>

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
//#include <array>
#include <utility>
#include <cstdint>
#include <vector>
#include <algorithm>

#include "hid_keycodes.h"
#include "keyboard_config.h"
#include "firmware_config.h"
#include "keymap.h"
#include "KeyState.h"


#include "advanced_keycodes.h"
#include "Key.h"

#ifndef KEYSCANNER_H
#define KEYSCANNER_H

#ifndef USER_MACRO_FUNCTION  
#define USER_MACRO_FUNCTION 1  
        void process_user_macros(uint16_t macroid);

#endif
        extern void sendString(const char* str);
        extern void sendKeycode(const char* keycode);
class KeyScanner {
    public:
        KeyScanner();
 
        static bool scanMatrix(const int& currentState,unsigned long millis, const int& row, const int& col);
        static void updateRemoteReport(uint8_t data0 , uint8_t data1, uint8_t data2,uint8_t data3, uint8_t data4, uint8_t data5,uint8_t data6);
        static void updateRemoteLayer(uint8_t data0);
        static bool getReport();
        static unsigned long getLastPressed();
        static bool layerChanged;
        static bool reportChanged;
        static uint8_t localLayer;
        static uint8_t layerMode;
        static uint8_t currentReport[8];

    private:
        static void resetReport();
        static void updateBuffer(uint8_t layer);
        static bool updateLayer();
        static bool updateModifiers();
        static void copyRemoteReport();
        static void resetRemoteReport();
        static bool processingmacros;

        
        static uint8_t remoteReport[8];
        static uint8_t previousReport[8];
        static unsigned long timestamps[MATRIX_ROWS][MATRIX_COLS]; 
        static unsigned long lastPressed;

        static uint8_t remoteLayer;
        static uint8_t currentMod;
        static uint8_t remoteMod;
        static uint8_t bufferposition;

        static std::vector<uint16_t> activeKeys; 
        static std::vector<uint16_t> macroBuffer; 
        static std::vector<uint16_t> toggleBuffer; 
        static std::vector<uint16_t> leaderBuffer; 
        static std::vector<uint16_t> oneshotBuffer; 
};
#endif /* KEYSCANNER_H */
