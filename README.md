# BlueMicro Firmware

[![GitHub license](https://img.shields.io/github/license/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE)
[![Current Version](https://img.shields.io/github/tag/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/tags)

[![GitHub forks](https://img.shields.io/github/forks/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/network)
[![GitHub stars](https://img.shields.io/github/stars/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/stargazers)
[![GitHub contributors](https://img.shields.io/github/contributors/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)

[![Discord](https://img.shields.io/discord/449593318247235589.svg)](https://discord.gg/ecnCR9P)


[![GitHub pull requests](https://img.shields.io/github/issues-pr/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE)

[![GitHub issues](https://img.shields.io/github/issues/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/issues)

A Keyboard Firmware for nRF52832 Boards with a pinout compatible with the Arduino Pro Micro

![BlueMicro](https://i.imgur.com/0SJpnoA.jpg)




## Build Status
| Branch  | Build  | Adafruit BSP Version  |
|---|---|---|
| Master  |  ![Build Status](http://toronto.jpconstantineau.com:8585/buildStatus/icon?job=BlueMicro_BLE%20-%20Push)  |![Adafruit Library for releases](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)  |
| Develop |![Build Status](http://toronto.jpconstantineau.com:8585/buildStatus/icon?job=BlueMicro_BLE-develop)   | ![Adafruit Library for releases](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)   |

**Compabible Hardware**  


* [Adafruit nRF52 Feather](https://www.adafruit.com/product/3406) (Software compatible - not Pinout compabible)
* [BlueMicro V1.0](https://github.com/jpconstantineau/NRF52-Board/tree/master/EByte_E73)  (Serial TX/RX routed through D2 and D3; Designed for the ErgoTravel only)
* [BlueMicro V1.1](https://github.com/jpconstantineau/NRF52-Board/tree/master/EByte_E73)  (Compatible with more Keyboards - Serial TX/RX are routed separately) 
* [BlueMicro V2.0b](https://github.com/jpconstantineau/NRF52-Board/tree/master/EByte_E73_Batt) (Compatible with more Keyboards - Serial TX/RX are routed separately, LiPo Charger on board) 
* [BlueMicro V2.0c](https://github.com/jpconstantineau/NRF52-Board/tree/master/EByte_E73_Batt_ErgoTravel) Serial TX/RX routed through D2 and D3; Designed for the ErgoTravel. LiPo Charger on Board with battery connection connected to RAW pin.
* [BlueNano V1.0](https://github.com/jpconstantineau/NRF52-Board/tree/master/NRF52832-base/NRF52832%20Base) Compatible with even more Keyboards due to its small size 3.3v regulator on board.
* [BlueNano V2.0](https://github.com/jpconstantineau/NRF52-Board/tree/master/NRF52832-base/NRF52832%20Lipo) Compatible with even more Keyboards due to its small size - Serial USB and PoLi Charger on board. Lots of 0402 components and 2 QFN packages to solder.
* [4x4 Backpack](https://github.com/jpconstantineau/NRF52-Board/tree/master/4x4_backpack/4x4_backpack)
* [5x5 Backpack](https://github.com/jpconstantineau/NRF52-Board/tree/master/5x5_backpack/5x5_backpack)

* BLE Phage       (Compatible with even more Keyboards due to its small size - Serial USB and PoLi Charger on board)
* BLE Phage Basic (Compatible with even more Keyboards due to its small size - Serial TX/RX are routed separately)


Maintainer: [/u/jpconstantineau](https://github.com/jpconstantineau)  

For the Help Pages go [here](https://jpconstantineau.github.io/BlueMicro_BLE/)


# Want to help?
Contact /u/jpconstantineau on reddit.

https://github.com/adafruit/Adafruit_nRF52_Arduino

# Credits

The firmware uses the same Arduino Core as the [Adafruit nRF52 Feather Boards](https://github.com/adafruit/Adafruit_nRF52_Arduino)

The Adafruit NRF52 Arduino Core is based on [Arduino-nRF5](https://github.com/sandeepmistry/arduino-nRF5) by Sandeep Mistry, which in turn is based on the [Arduino SAMD Core](https://github.com/arduino/ArduinoCore-samd).

The following tools are used:

- Arduino IDE as the Editing Environment
- GCC ARM Embedded as the compiler
- Nordic's nrfutil 0.5.2 for flashing the firmware by serial interface
- J-Link for flashing the bootloader by SWD interface
