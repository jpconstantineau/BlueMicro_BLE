// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef BATTERY_BM_H
#define BATTERY_BM_H 

    #include <Arduino.h>
    #include <bluemicro_hid.h>
    #include <bluefruit.h>
    #include "firmware_config.h"
    #include "keyboard_config.h"
  
  enum BatteryType {
    BATT_UNKNOWN = 0,
    BATT_CR2032 = 1,
    BATT_LIPO = 2,
    BATT_VDDH =  3,
};

typedef void (*mvToPercent_cb_t)(uint8_t & vbat_per, uint32_t mvolts, uint8_t batt_type ); 

  class Battery {
    public:
        Battery();  
         uint8_t vbat_per;
         uint32_t vbat_mv;
         uint32_t vbat_vdd;
         uint8_t batt_type;
         void updateBattery(void);
         uint32_t readVBAT(void);
         uint32_t readVDDH(void);
         void setmvToPercentCallback(mvToPercent_cb_t callback);
        
    private:
         
         uint32_t analogReadVDD();
         uint32_t vbat_raw;
         mvToPercent_cb_t _mvToPercent_cb;

  };
void mvToPercent_default(uint8_t & vbat_per, uint32_t mvolts, uint8_t batt_type );
void mvToPercent_test(uint8_t & vbat_per, uint32_t mvolts, uint8_t batt_type );
#endif
