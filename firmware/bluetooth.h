// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include <bluemicro_hid.h>
#include <bluefruit.h>
#include "firmware_config.h"
#include "bluetooth_config.h"
#include "nrf52gpio.h"
#undef min
#undef max

#include "keyscanner.h"
#include "nrf52battery.h"
#include "datastructures.h"

    typedef   struct {      // Payload for BLE messages between split boards. Intended for slave to master
        // BLE messages have a size limit of 20 bytes. Any extra and we have to do some ATT_MTU magic...
        uint8_t        keycode[6];       // 6 bytes
        uint8_t        modifier;         // 1 byte
        uint8_t        batterylevel;     // 1 byte
        uint16_t       layer;            // 2 byte   
        //uint32_t       command;          // 4 bytes
        //uint32_t       timesync;         // 4 bytes
        
        uint16_t  __attribute__((packed))     specialkeycode;   // 2 bytes = 20 bytes...  
    } Payload;

        typedef  struct {      // Payload for BLE messages between split boards. Intended for master to slave
        // BLE messages have a size limit of 20 bytes. Any extra and we have to do some ATT_MTU magic...
        uint32_t       command;          // 4 bytes
        uint32_t       timesync;         // 4 bytes
        uint16_t       layer;            // 1 byte
    } __attribute__((packed)) StatePayload;


    void bt_setup(uint8_t BLEProfile);
    void bt_startAdv(void);


    ble_gap_addr_t bt_getMACAddr(void);
    void set_keyboard_led(uint16_t conn_handle, uint8_t led_bitmap);

    void rssi_changed_callback(uint16_t conn_hdl, int8_t rssi);
    void advertizing_slow_callback(void);
    void advertizing_stop_callback(void);
    void prph_connect_callback(uint16_t conn_handle);
    void prph_disconnect_callback(uint16_t conn_handle, uint8_t reason);



    #if BLE_PERIPHERAL == 1
        void cccd_callback(uint16_t conn_hdl,BLECharacteristic* chr, uint16_t cccd_value)  ;
        void layer_request_callback (uint16_t conn_hdl,BLECharacteristic* chr, uint8_t* data, uint16_t len);
    #endif

    #if BLE_CENTRAL == 1
        void notify_callback(BLEClientCharacteristic* chr, uint8_t* data, uint16_t len);
        void scan_callback(ble_gap_evt_adv_report_t* report);
        void cent_connect_callback(uint16_t conn_handle);
        void cent_disconnect_callback(uint16_t conn_handle, uint8_t reason);
    #endif

#endif /* BLUETOOTH_H */
