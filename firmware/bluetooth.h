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

    void bt_setup(uint8_t BLEProfile);
    void bt_startAdv(void);

    ble_gap_addr_t bt_getMACAddr(void);
    void set_keyboard_led(uint16_t conn_handle, uint8_t led_bitmap);

    void rssi_changed_callback(uint16_t conn_hdl, int8_t rssi);
    void advertizing_slow_callback(void);
    void advertizing_stop_callback(void);
    void prph_connect_callback(uint16_t conn_handle);
    void prph_disconnect_callback(uint16_t conn_handle, uint8_t reason);


#endif /* BLUETOOTH_H */
