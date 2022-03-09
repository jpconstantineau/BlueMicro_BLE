// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NRF52GPIO_H
#define NRF52GPIO_H

#include <Arduino.h>
#include <bluemicro_hid.h>
#include "hardware_variants.h"
#include "firmware_config.h"

  class led_handler
  {
    public:
        led_handler(PersistentState* cfg, DynamicState* stat);
        void setCallback(ledupdateCallback cb);
        void update();
        void enable();
        void disable();
        void hello();
        void sleep();
        
    private:
        bool enabled;
        ledupdateCallback callback;
        PersistentState* config;
        DynamicState* status;
  };

void defaultLedCallback(PersistentState* config, DynamicState* status);


void setupGpio(void);

void setupVCC(uint8_t pin, bool polarity);
void setupCharger(uint8_t chargerpin, bool polarity);

void switchVCC(bool value);
void switchCharger(bool value);

void setupPWM(uint8_t pin);
void sendPWM(uint16_t value);
void setupWDT(void);
void updateWDT(void);

#endif
