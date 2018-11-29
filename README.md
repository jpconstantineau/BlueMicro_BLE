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
| Branch  | Build  | Library  |
|---|---|---|
| Master  |  ![Build Status](http://toronto.jpconstantineau.com:8585/buildStatus/icon?job=BlueMicro_BLE%20-%20Push)  |![Adafruit Library for releases](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)  |
| Develop |![Build Status](http://toronto.jpconstantineau.com:8585/buildStatus/icon?job=BlueMicro_BLE-develop)   | ![Adafruit Library for releases](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)   |

**Compabible Hardware**  

* BlueMicro V1.0  (Serial TX/RX routed through D2 and D3; Designed for the ErgoTravel only)
* BlueMicro V1.1  (Compatible with more Keyboards - Serial TX/RX are routed separately) 
* BLE Phage       (Compatible with even more Keyboards due to its small size - Serial USB and PoLi Charger on board)
* BLE Phage Basic (Compatible with even more Keyboards due to its small size - Serial TX/RX are routed separately)
* Adafruit nRF52 Feather (Software compatible - not Pinout compabible)

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
