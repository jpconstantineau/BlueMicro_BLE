// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H
#include "hardware_variants.h"

/* HARDWARE DEFINITION*/
/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

#define MATRIX_ROW_PINS {6, 8, 15,17, 20,13,24,9}
#define MATRIX_COL_PINS {30, 26, 29, 2, 45, 3, 28, 43}
#define UNUSED_PINS {}
#define BACKLIGHT_LED_PIN 38 
#define DEFAULT_PWM_VALUE 10000            // PWM intensity
#define BACKLIGHT_PWM_ON 1  
/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
#define BATTERY_TYPE BATT_LIPO
#define VBAT_PIN  31
#define VCC_PIN 12
#define VCC_POLARITY_ON 1


//#define I2C_SDA_PIN 15  // no display for the luddite
//#define I2C_SCK_PIN 17  // no display for the luddite

#define SPEAKER_PIN 10
    
#endif /* HARDWARE_CONFIG_H */
