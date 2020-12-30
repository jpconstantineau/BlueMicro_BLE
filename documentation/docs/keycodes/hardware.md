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
| nRF52               | Restart Firmware (RESET) | RESET                      | ✅    | 
| nRF52               | Toggle Debug Serial CLI  | DEBUG                      | 🚧    | 
| nRF52               | Reformat User Flash      | EEPROM_RESET      EEP_RST  | ✅    | 
| nRF52               | Enter OTA DFU            | DFU                        | ✅    |
| nRF52               | Enter Serial DFU         | SERIAL_DFU                 | ✅    | 
| nRF52               | Enter UF2 DFU (nrf52840 only) | UF2_DFU               | ✅    | 
| nRF52               | Toggle Help Mode         | HELP_MODE                  | ✅    | 
| nRF52840 USB HID    | Automatic Switch between USB and BLE   | OUT_AUTO     | 🚧    |  
| nRF52840 USB HID    | Output to USB Only       | OUT_USB                    | 🚧    |  
| nRF52840 USB HID    | Output to BLE Only       | OUT_BT                     | 🚧    |  
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



Table is still a work in progress.  Refer to `hid_keycodes.h` and `advanced_keycodes.h` for a detailed list of keycodes.