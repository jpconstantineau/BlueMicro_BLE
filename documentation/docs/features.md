---
id: features
title: Features Compared
sidebar_label: Features Compared
slug: /Features
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
| Hardware Troubleshooting tools                                                                                         |      ✅   |     |    |
| User Configuration Repositories                                                                                        |            |     | ✅  |
| Realtime Keymap Updating                                                                                               |            | ✅  |  💡  |



| Feature           | BlueMicro  | QMK        |
| ----------------- | ---------- | ---------- |
| Wireless          | Native BLE | Using add-on module  |
|  * HID Service    |  Yes       |    Yes     |
|  * Device Information Service |  Yes  |  Yes |
|  * Battery Service | Yes       |    (?)      |
|  * Wireless Device Firmware Update    |    Yes        |   No    |
|  * Central/Peripheral Communications | Yes  | No  |
|  * Dongle free    | Yes | Depends |
|                   |            |            |
| Accented Keys èéê | Yes (windows)  | Yes        |
|                   |            |            |
| N-Key rollover    | HID standard: Mods + 6 keys  |   Yes   |
|                   |            |            |
| Advanced Keycodes | Partial    | Yes  |
| * Layers          | Yes        | Yes  |
| * Momentary Keys  | Yes     | Yes  |
| * One Shot Keys   | Yes     | Yes  |
| * Toggle Keys     | Yes     | Yes  |
| * Mod-Tap Keys    | Yes     | Yes  |
|                   |            |            |
| Audio             | No         | Yes  |
|                   |            |            |
| Auto Shift        | Key Timing | Yes  |
|                   | Required   |            |
| Leader Key        | Future     | Yes  |
|                   |            |            |
| Stenography       | Partial No NKRO.  | Yes  |
|                   |            |            |
| Tap Dance         | Tap/Double Tap | Yes  |
|                   | Tap/Hold   |            |
