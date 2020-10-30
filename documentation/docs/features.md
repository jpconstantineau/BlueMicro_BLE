---
id: features
title: Features Compared
sidebar_label: Features Compared
---


BlueMicro is currently missing some features found in other popular firmware. This table compares the features supported by BlueMicro, QMK and ZMK:

| **Feature**                                                                                                            | [BlueMicro](http://bluemicro.jpconstantineau.com/) | [QMK nRF52 Fork](https://github.com/joric/nrfmicro/wiki/QMK) | [ZMK](https://zmkfirmware.dev/) |
| ---------------------------------------------------------------------------------------------------------------------- |  :-------: | :-: | :-: |
| **Connectivity and Power Saving Options**                                                                              |            |     |    |
| Low Latency BLE Support                                                                                                |     ✅    |      | ✅  |
| Multi-Device BLE Support (Several Computers)                                                                           |     🚧    |      | ✅  | 
| USB HID                                                                                                                |     🚧    | ✅  | ✅  |
| Battery Reporting (BLE Battery Service)                                                                                |     ✅    |      | 🚧  |
| Low Power Sleep States                                                                                                 |     ✅    |      | 🚧  |
| Low Active Power Usage                                                                                                 |            |      | ✅  |
| **Firmware Options**                                                                                                   |            |      |    |
| Keymaps and Layers                                                                                                     |     ✅     | ✅  | ✅  |
| Basic Keycodes                                                                                                         |     ✅     | ✅  | ✅  | 
| Basic consumer (Media) Keycodes                                                                                        |     ✅     | ✅  | ✅  |
| Mouse Keys                                                                                                             |     ✅     | ✅  |      |
| Hold-Tap (which includes Mod-Tap and Layer-Tap)                                                                        |     ✅     | ✅  | ✅  | 
| One Shot Keys                                                                                                          |     ✅     | ✅  | 🚧  |
| Combo Keys                                                                                                             |             | ✅  | 🚧  |
| Macros                                                                                                                 |     ✅     | ✅  | 🚧  |
| **Keyboard and Controller Board Hardware Options**                                                                     |            |     |    |
| Split Keyboard Support                                                                                                 |     ✅     | ✅  | ✅  |
| Key Backlight LED PWM Control                                                                                          |     ✅     | ✅  |      |
| RGB Underglow                                                                                                          |     ✅     | ✅  | ✅  |
| Encoders                                                                                                               |     🚧     | ✅  | ✅  |
| OLED Display Support                                                                                                   |     🚧     | ✅  | 🚧  |
| Low Power Mode (VCC Shutoff)                                                                                           |     ✅     |     | 🚧  |
| **Microcontroller Support**                                                                                            |            |     |    |
| Support for Nordic nRF52 Microcontrollers                                                                              |     ✅     |     |  ✅  |
| Support for Wide Range of ARM Microcontrollers                                                                         |            |     | ✅  |
| Support for AVR/8 Bit Microcontrollers                                                                                 |            | ✅  |     |
| **Tooling and Build Configuration**                                                                                    |            |     |    |
| Serial Debug CLI                                                                                                       |      ✅   |     |    |
| Web Bluetooth Configuration                                                                                            |      💡    |     |    |
| Hardware Troubleshooting tools                                                                                         |      ✅   |     |    |
| User Configuration Repositories                                                                                        |            |     | ✅  |
| Realtime Keymap Updating                                                                                               |            | ✅  |  💡  |


This __Features Compared__ page is licenced under [CC-BY-NC-SA-4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/) and was adapted from [ZMK Firmware Documentation](https://zmkfirmware.dev/docs/) originally created by the ZMK Project Contributors.

