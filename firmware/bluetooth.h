/*
Copyright 2018 <Pierre Constantineau>

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
#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include <bluefruit.h>
#include "firmware_config.h"
#include "bluetooth_config.h"
#undef min
#undef max

#include "KeyScanner.h"
#include "battery.h"

    typedef struct {      // Payload for BLE messages between split boards. Intended for slave to master
        // BLE messages have a size limit of 20 bytes. Any extra and we have to do some ATT_MTU magic...
        uint8_t        report[8];        // 8 bytes   
        uint32_t       command;          // 4 bytes
        uint32_t       timesync;         // 4 bytes
        uint8_t        batterylevel;     // 1 byte
        uint16_t       specialkeycode;   // 2 bytes = 19 bytes...  sizeof gets 20 bytes...
    } Payload;

        typedef struct {      // Payload for BLE messages between split boards. Intended for master to slave
        // BLE messages have a size limit of 20 bytes. Any extra and we have to do some ATT_MTU magic...
        uint8_t        layer;            // 1 byte
        uint32_t       command;          // 4 bytes
        uint32_t       timesync;         // 4 bytes
    } StatePayload;


    void setupBluetooth(void);
    void startAdv(void);
    void set_keyboard_led(uint16_t conn_handle, uint8_t led_bitmap);

    void sendKeys(uint8_t currentReport[8]);
    void sendMediaKey(uint16_t keycode);
    void sendMouseKey(uint16_t keycode);

    #if BLE_PERIPHERAL ==1   | BLE_CENTRAL ==1 
    void sendlayer(uint8_t layer);
    #endif

    #if BLE_PERIPHERAL == 1
        void cccd_callback(uint16_t conn_hdl,BLECharacteristic* chr, uint16_t cccd_value)  ;
        void layer_request_callback (uint16_t conn_hdl,BLECharacteristic* chr, uint8_t* data, uint16_t len);
    #endif

    #if BLE_CENTRAL == 1
        void notify_callback(BLEClientCharacteristic* chr, uint8_t* data, uint16_t len);
        void scan_callback(ble_gap_evt_adv_report_t* report);
        void prph_connect_callback(uint16_t conn_handle);
        void prph_disconnect_callback(uint16_t conn_handle, uint8_t reason);
        void cent_connect_callback(uint16_t conn_handle);
        void cent_disconnect_callback(uint16_t conn_handle, uint8_t reason);
    #endif

#endif /* BLUETOOTH_H */
