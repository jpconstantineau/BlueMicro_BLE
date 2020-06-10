# BlueMicro Firmware

A Keyboard Firmware for nRF52832 and nRF52840 Boards

## Build Status
| Branch  | Windows Build nrf52832 | Docker Build nrf52832 | Docker Build nrf52840 | Adafruit BSP Version  |
|---|---|---|---|---|
| Master  |  ![Build Status](http://toronto.jpconstantineau.com:8585/buildStatus/icon?job=BlueMicro_BLE-master) |  ![Build Status](http://toronto.jpconstantineau.com:8585/buildStatus/icon?job=BlueMicro_BLE-master-Docker-nrf52832)|  ![Build Status](http://toronto.jpconstantineau.com:8585/buildStatus/icon?job=BlueMicro_BLE-master-Docker-nrf52840) |![Adafruit Library for releases](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)  |
| Develop |![Build Status](http://toronto.jpconstantineau.com:8585/buildStatus/icon?job=BlueMicro_BLE-develop) | ![Build Status](http://toronto.jpconstantineau.com:8585/buildStatus/icon?job=BlueMicro_BLE-develop-Docker-nrf52832) | ![Build Status](http://toronto.jpconstantineau.com:8585/buildStatus/icon?job=BlueMicro_BLE-develop-Docker-nrf52840) | ![Adafruit Library for releases](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)   |

[![GitHub license](https://img.shields.io/github/license/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE)

[![Current Version](https://img.shields.io/github/tag/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/tags)

[![GitHub forks](https://img.shields.io/github/forks/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/network)[![GitHub pull requests](https://img.shields.io/github/issues-pr/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE)[![GitHub issues](https://img.shields.io/github/issues/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/issues)

[![GitHub stars](https://img.shields.io/github/stars/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/stargazers)[![GitHub contributors](https://img.shields.io/github/contributors/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)[![Discord](https://img.shields.io/discord/449593318247235589.svg)](https://discord.gg/ecnCR9P)


**Compatible Hardware**  

![BlueMicro](/docs/images/BlueMicro_Hardware.jpg)

Top Row: 5x5Backpack, 4x4Backpack

Bottom Row: BlueMicro V2.0,  BlueMicro V1.0, BlueNano V2.0, BlueNano V1.0, Pro Micro (For Reference)

| Board Name | Description | Chip | Bootloader |
|---|---|---|---|
| [Adafruit nRF52 Feather](https://www.adafruit.com/product/3406) | The original from Adafruit! | nRF52832 | nrf52832 feather |
| [BlueMicro V1.0](https://github.com/jpconstantineau/NRF52-Board/tree/master/EByte_E73) | Serial TX/RX routed through D2 and D3; Designed for the ErgoTravel; Tested and Gerber available | nRF52832 | nrf52832 feather |
| [BlueMicro V1.1](https://github.com/jpconstantineau/NRF52-Board/tree/master/EByte_E73)  | Compatible with more Keyboards - Serial TX/RX are routed separately; Tested and Gerber available | nRF52832 | nrf52832 feather |
| [BlueMicro V2.0b](https://github.com/jpconstantineau/NRF52-Board/tree/master/EByte_E73_Batt) | Compatible with more Keyboards - Serial TX/RX are routed separately, LiPo Charger on board; Tested and Gerber available | nRF52832 | nrf52832 feather |
| [BlueMicro V2.0c](https://github.com/jpconstantineau/NRF52-Board/tree/master/EByte_E73_Batt_ErgoTravel) | Serial TX/RX routed through D2 and D3; Designed for the ErgoTravel. LiPo Charger on Board with battery connection connected to RAW pin. Tested and Gerber available. | nRF52832 | nrf52832 feather |
| [4x4 Backpack](https://github.com/jpconstantineau/NRF52-Board/tree/master/4x4_backpack/4x4_backpack) | For use with [40percent.club 4x4 Boards](https://www.40percent.club/2018/01/4x4x4x4x4.html). Uses a CR2032 Battery. | nRF52832 | nrf52832 feather |
| [4x4 Platform](https://github.com/jpconstantineau/NRF52-Board/tree/master/4x4_backpack/4x4_platform) | For use with [40percent.club 4x4 Boards](https://www.40percent.club/2018/01/4x4x4x4x4.html). Uses a rechargeable Battery, has a single RGB on board and has a few status LEDs and PWM driven LEDs. Has serial on board too! | nRF52832 | nrf52832 feather |
| [4x4 Backpack840](https://github.com/jpconstantineau/NRF52-Board/tree/master/4x4_backpack/4x4_backpack_nrf52840) | For use with [40percent.club 4x4 Boards](https://www.40percent.club/2018/01/4x4x4x4x4.html). Uses a rechargeable  Battery, has a single RGB on board and has a few status LEDs and PWM driven LEDs.  Most importantly, it uses a nrf52840 module instead of a nrf52832 module. | nRF52832 | nrf52832 feather |
| [5x5 Backpack](https://github.com/jpconstantineau/NRF52-Board/tree/master/5x5_backpack/5x5_backpack) | For use with [40percent.club 5x5 Boards](https://www.40percent.club/2018/04/5x5.html). Uses a CR2032 Battery. | nRF52832 | nrf52832 feather |
| BLE Phage   |    (Compatible with even more Keyboards due to its small size - Serial USB and PoLi Charger on board) | nRF52832 | nrf52832 feather |
| [BLE Phage Basic](https://southpawdesign.net/products/blue-phage-basic?variant=8958741545020) | (Compatible with even more Keyboards due to its small size - Serial TX/RX are routed separately) | nRF52832 | nrf52832 feather |
| [Adafruit nRF52840 Feather](https://www.adafruit.com/product/3406) | The updated nrf52 feather from Adafruit! | nRF52840 | nrf52840 feather express |
| [BlueMicro840]() | Bluemicro based on the design of the nrfmicro.  Still being worked on... | nRF52840 | PCA10056 |
| [nice!nano](https://docs.nicekeyboards.com/#/nice!nano/) | uses the nRF52840 chip. Same size as the Pro Micro.  | nRF52840 | nicenano |

We need your help in bringing improved support for the nrf52840.  Contact us and let us know how you want to help!

Maintainer: [/u/jpconstantineau](https://github.com/jpconstantineau)  


# Documentation
See the pages [Here](http://bluemicro.jpconstantineau.com/#)

You can contribute to the documentation by editing the markdown files located in the docs folder of the repository.


# Want to help?
Contact /u/jpconstantineau on reddit.


# Credits

The firmware uses the same Arduino Core as the [Adafruit nRF52 Feather Boards](https://github.com/adafruit/Adafruit_nRF52_Arduino)

The Adafruit NRF52 Arduino Core is based on [Arduino-nRF5](https://github.com/sandeepmistry/arduino-nRF5) by Sandeep Mistry, which in turn is based on the [Arduino SAMD Core](https://github.com/arduino/ArduinoCore-samd).

The following tools are used:

- Arduino IDE as the Editing Environment
- GCC ARM Embedded as the compiler
- Nordic's nrfutil 0.5.2 for flashing the firmware by serial interface
- J-Link for flashing the bootloader by SWD interface
