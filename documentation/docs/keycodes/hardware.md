---
id: keycodes_hardware
title: Hardware-specific Keycodes
slug: /keycodes_hardware
---


Hardware-specific keycodes are keycodes that trigger specific hardware functionality.


| Group               | Usage Name               | Keycode Identifiers        | Status |
| --------------      | -----------------------  | -------------------------- | ----   |
| Hardware Status     | Print Battery Information | PRINT_BATTERY             | ✅  | 
| Hardware Status     | Print Keyboard Information | PRINT_INFO               | ✅  | 
| Hardware Status     | Print BLE Information    | PRINT_BLE                  | ✅  |
| nRF52               | Put Keyboard to Sleep Now | SLEEP_NOW                 | ✅    | 
| nRF52               | Restart Firmware (RESET) | RESET                      | ✅    | 
| nRF52               | Toggle Debug Serial CLI  | DEBUG                      | ✅    | 
| nRF52               | Reformat User Flash      | EEPROM_RESET      EEP_RST  | ✅    | 
| nRF52               | Enter OTA DFU            | DFU                        | ✅    |
| nRF52               | Enter Serial DFU         | SERIAL_DFU                 | ✅    | 
| nRF52               | Enter UF2 DFU (nrf52840 only) | UF2_DFU               | ✅    | 
| nRF52               | Toggle Help Mode         | HELP_MODE                  | ✅    | 
| nRF52               | Use default Battery Level Calculation    | BATTERY_CALC_DEFAULT       | ✅    | 
| nRF52               | Use test Battery Level Calculation  (4.2V = 42%)   | BATTERY_CALC_TEST   | ✅    | 
| nRF52 BLE HID       | Switch to BLE Profile 1  | BLEPROFILE_1               | ✅    | 
| nRF52 BLE HID       | Switch to BLE Profile 2  | BLEPROFILE_2               | ✅    | 
| nRF52 BLE HID       | Switch to BLE Profile 3  | BLEPROFILE_3               | ✅    | 
| nRF52840 USB HID    | Automatic Switch between USB and BLE   | OUT_AUTO     | ✅    |  
| nRF52840 USB HID    | Output to USB Only       | OUT_USB                    | ✅    |  
| nRF52840 USB HID    | Output to BLE Only       | OUT_BT                     | ✅    |  
| Custom Hardware     | External VCC ON          | VCC_ON                     | ✅  |
| Custom Hardware     | External VCC OFF         | VCC_OFF                    | ✅  |
| Custom Hardware     | External VCC Toggle      | VCC_TOGGLE                 | ✅  |
| Custom Hardware     | Battery Charger ON       | CHARGER_ON                 | ✅  |
| Custom Hardware     | Battery Charger OFF      | CHARGER_OFF                | ✅  |
| Custom Hardware     | Battery Charger Toggle   | CHARGER_TOGGLE             | ✅  |
| LED PWM Backlight   | Toggle Backlight ON/OFF | BL_TOGG                     | ✅   | 
| LED PWM Backlight   | Step through Backlight Modes | BL_STEP                | ✅  | 
| LED PWM Backlight   | Turn Backlight ON        | BL_ON                      | ✅  | 
| LED PWM Backlight   | Turn Backlight OFF       | BL_OFF                     | ✅  | 
| LED PWM Backlight   | Increase Maximum Intensity | BL_INC                   | ✅  | 
| LED PWM Backlight   | Decrease Maximum Intensity | BL_DEC                   | ✅  | 
| LED PWM Backlight   | Set to Breathing Mode    | BL_BRTG                    | ✅  | 
| LED PWM Backlight   | Set to React Mode (default) | BL_REACT                | ✅  | 
| LED PWM Backlight   | Increase PWM Step Size   | BL_STEPINC                 | ✅  | 
| LED PWM Backlight   | Decrease PWM Step Size   | BL_STEPDEC                 | ✅  | 
| RGB LEDs            |   |   RGB_TOG     | 🚧  | 
| RGB LEDs            |   |   RGB_MODE_FORWARD     | 🚧  | 
| RGB LEDs            |   |   RGB_MODE_REVERSE     | 🚧  | 
| RGB LEDs            |   |   RGB_HUI     | 🚧  | 
| RGB LEDs            |   |   RGB_HUD     | 🚧  | 
| RGB LEDs            |   |   RGB_SAI     | 🚧  | 
| RGB LEDs            |   |   RGB_SAD     | 🚧  | 
| RGB LEDs            |   |   RGB_VAI     | 🚧  | 
| RGB LEDs            |   |   RGB_VAD     | 🚧  | 
| RGB LEDs            |   |   RGB_MODE_PLAIN     | 🚧  | 
| RGB LEDs            |   |   RGB_MODE_BREATHE     | 🚧  | 
| RGB LEDs            |   |   RGB_MODE_RAINBOW     | 🚧  | 
| RGB LEDs            |   |   RGB_MODE_SWIRL     | 🚧  | 
| RGB LEDs            |   |   RGB_MODE_SNAKE     | 🚧  | 
| RGB LEDs            |   |   RGB_MODE_KNIGHT     | 🚧  | 
| RGB LEDs            |   |   RGB_MODE_PLAIN     | 🚧  | 
| RGB LEDs            |   |   RGB_MODE_XMAS     | 🚧  | 
| RGB LEDs            |   |   RGB_MODE_GRADIENT     | 🚧  | 
| RGB LEDs            |   |   RGB_MODE_RGBTEST     | 🚧  | 
| RGB LEDs            |   |   RGB_SPI     | 🚧  | 
| RGB LEDs            |   |   RGB_SPD     | 🚧  |


Table is still a work in progress.  Refer to `hid_keycodes.h` and `advanced_keycodes.h` for a detailed list of keycodes.