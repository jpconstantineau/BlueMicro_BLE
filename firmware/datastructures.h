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

    typedef struct { 
        bool    ledbacklight;  
        bool    ledrgb; 
        bool    VCCSwitchAvailable;  
        bool    VCCSwitchEnabled;  
        bool    ChargerControlAvailable;  
        bool    ChargerControlEnabled; 
        bool    WakeUpBLELED; 
        bool    WakeUpKBLED;  
        uint32_t timerkeyscaninterval;
        uint32_t timerbatteryinterval;   
         
  
    } PersistentState;

    typedef struct { 
        uint32_t timestamp;
        uint32_t lastupdatetime;
        uint16_t layer;
        uint8_t statusled;

        bool helpmode;
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
    } DynamicState;

    #endif 