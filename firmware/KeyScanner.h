/*
Copyright 2018-2020 <Pierre Constantineau, Julian Komaromy>

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
#include "Key.h" //already included through keymap.h do we need it here?

#ifndef KEYSCANNER_H
#define KEYSCANNER_H

#ifndef USER_LAYER_FUNCTION  
#define USER_LAYER_FUNCTION 1  
void process_user_layers(uint16_t layermask);
#endif


class KeyScanner {
    public:
        KeyScanner();
 
        static bool scanMatrix(const int& currentState,unsigned long millis, const int& row, const int& col);
        static void press(unsigned long millis, const int& row, const int& col);
        static void release(unsigned long millis, const int& row, const int& col);
        static void updateRemoteReport(uint8_t data0 , uint8_t data1, uint8_t data2,uint8_t data3, uint8_t data4, uint8_t data5,uint8_t data6);
        static void updateRemoteLayer(uint8_t data0);
        static void process_for_tri_layers(uint8_t if_layer1, uint8_t and_layer2, uint8_t use_layer3);
        static bool getReport();
        static unsigned long getLastPressed();
        static bool layerChanged;
        static bool reportChanged;
        static uint16_t macro;
        static uint16_t specialfunction;
        static uint16_t consumer;
        static uint16_t mouse;
        static uint16_t localLayer;
        static uint16_t special_key;
       // static uint8_t layerMode;
        static uint16_t remotespecialkeycode;
        static uint8_t currentReport[8];
        
        static uint8_t bufferposition;
        static uint8_t ledStatus;

    private:
        static void resetReport();
        static void updateBuffer();
        static bool updateLayer();

        static void copyRemoteReport();

       
        static uint8_t getlayer(uint16_t layers);
        static bool processingmacros;
        static uint16_t oneshotLayer;
        static uint8_t remoteReport[8];
        static uint8_t previousReport[8];
        static unsigned long timestamps[MATRIX_ROWS][MATRIX_COLS]; 
        static unsigned long lastPressed;
        static uint16_t detectedlayerkeys;
        static uint16_t remoteLayer;
        
        static uint8_t remoteMod;
         static uint8_t currentMod;

        static std::vector<uint16_t> activeKeys; 
        static std::vector<uint16_t> macroBuffer; 
        static std::vector<uint16_t> toggleBuffer; 
        static std::vector<uint16_t> leaderBuffer; 
        static std::vector<uint16_t> oneshotBuffer; 
};
#endif /* KEYSCANNER_H */
