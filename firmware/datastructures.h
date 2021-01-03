/*
Copyright 2020 <Pierre Constantineau>

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
#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H
#include <array>

#define BLUEMICRO_CONFIG_VERSION 0  // this should be incremented every time the PersistentState structure definition is updated.  This will ensure that the SETTINGS_FILE file is reset when the structure is updated.

    typedef union {
        struct { 
        uint8_t  version;

        uint32_t timerkeyscaninterval;

        uint32_t timerbatteryinterval; 

        uint32_t mainloopinterval;

        uint8_t    pinBLELED;  
        uint8_t    pinKBLED; 
        uint8_t    pinPWMLED;
        uint8_t    pinRGBLED;

        uint8_t    pinVCCSwitch;
        uint8_t    pinChargerControl;

        bool    enableBLELED; 
        bool    enableKBLED; 
        bool    enablePWMLED;  
        bool    enableRGBLED;

        bool    polarityBLELED; 
        bool    polarityKBLED; 
        bool    polarityPWMLED;  
        bool    enableVCCSwitch;  

        bool    polarityVCCSwitch;  
        bool    enableChargerControl;  
        bool    polarityChargerControl;    
        bool    enableDisplay;

        bool    enableSerial;
        bool    dummy1;
        bool    dummy2;
        bool    dummy3;

        uint8_t connectionMode;
        uint8_t BLEProfile;
        uint16_t BLEProfileEdiv[3];

        char BLEProfileName[3][32];
  
       };
       char data[128]; } PersistentState;  // meant for configuration and things that we want to store in flash so that we can pick it up on the next reboot.

    typedef struct { 
        uint32_t timestamp;
        uint32_t lastupdatetime;
        uint32_t lastuseractiontime;
        uint16_t layer;
        uint8_t statuskb;
        uint8_t statusble;
        
        uint32_t vbat_raw;
        uint32_t vbat_mv;
        uint32_t vbat_vdd;
        uint32_t vbat_vddh;
        uint8_t  vbat_per;
        uint8_t  batt_type;
        uint32_t batterytimer;

        char peer_name_prph[32];
        uint16_t conn_handle_prph;
        int8_t rssi_prph;
        
        char peer_name_cent[32];
        uint16_t conn_handle_cent;
        int8_t rssi_cent;
        
        char peer_name_cccd[32];
        uint16_t conn_handle_cccd;
        int8_t rssi_cccd;
        
        uint8_t connectionState;

        bool rssi_prph_updated;
        bool rssi_cent_updated;
        bool rssi_cccd_updated;
        bool helpmode;
        bool needReset;
        bool needUnpair;
        bool needFSReset;
        bool save2flash;

    } DynamicState; // meant for keyboard and BLE status and things that are dynamic and should not be stored in flash.

    // TODO: Add the structures and function definitions for keycode buffer for user processing

    typedef void (*ledupdateCallback)(PersistentState* config, DynamicState* status);

    enum connectionState
    {
    CONNECTION_NONE,
    CONNECTION_USB,
    CONNECTION_BT
    };

    enum connectionMode
    {
    CONNECTION_MODE_AUTO,
    CONNECTION_MODE_USB_ONLY,
    CONNECTION_MODE_BLE_ONLY
    };
    #endif 


