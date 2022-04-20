// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

//#include <array>

#ifndef KEYSCANNER_H
#define KEYSCANNER_H
#include <utility>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <tuple>
#include <bluemicro_hid.h>
#include "hid_keycodes.h"
#include "keyboard_config.h"
#include "firmware_config.h"
#include "keymap.h"
#include "keystate.h"
#include "advanced_keycodes.h"
#include "combo_engine.h"
#include "key.h" //already included through keymap.h do we need it here?


#ifndef USER_LAYER_FUNCTION  
#define USER_LAYER_FUNCTION 1  
void process_user_layers(uint16_t layermask);
#endif

class KeyScanner {
    public:
        
        KeyScanner(PersistentState* cfg, DynamicState* stat);

        static void press(unsigned long millis, const int& row, const int& col);
        static void release(unsigned long millis, const int& row, const int& col);
        static void updateRemoteReport(uint8_t data0 , uint8_t data1, uint8_t data2,uint8_t data3, uint8_t data4, uint8_t data5,uint8_t data6);
        static void updateRemoteLayer(uint16_t data0);
        static void process_for_tri_layers(uint8_t if_layer1, uint8_t and_layer2, uint8_t use_layer3);
        static void add_to_encoderKeys(uint16_t keycode);
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
        static uint16_t remotespecialkeycode;
        //static uint8_t currentReport[8];
        static HIDKeyboard currentReport;
        static std::vector<HIDMouse> mouseReports;
        static uint8_t bufferposition;

    private:
        static void resetReport();
        static void updateBuffer();
        static bool updateLayer();

        static void copyRemoteReport();

        
        static uint8_t getlayer(uint16_t layers);
        static bool processingmacros;
        static uint16_t oneshotLayer;
        static uint8_t remoteReport[8];
        //static HIDKeyboard remoteReport;
        //static uint8_t previousReport[8];
        static HIDKeyboard previousReport;
        
        static unsigned long lastPressed;
        static uint16_t detectedlayerkeys;
        static uint16_t remoteLayer;
        static uint32_t combotimer;
        static uint32_t triggerkeytimer;
        static uint8_t remoteMod;
        static uint8_t currentMod;

        

        static std::vector<uint16_t> activeKeys; 
        static std::vector<uint16_t> encoderKeys; 
        static std::vector<uint16_t> macroBuffer; // not used
        static std::vector<uint16_t> toggleBuffer; 
        static std::vector<uint16_t> leaderBuffer; // not used
        static std::vector<uint16_t> oneshotBuffer; 

        static PersistentState* config;
        static DynamicState* status;
};
#endif /* KEYSCANNER_H */
