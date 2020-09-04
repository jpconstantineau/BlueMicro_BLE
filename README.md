# BlueMicro Firmware  [![Current Version](https://img.shields.io/github/v/tag/jpconstantineau/BlueMicro_BLE)](https://github.com/jpconstantineau/BlueMicro_BLE/tags)  ![Build on Docker](https://github.com/jpconstantineau/BlueMicro_BLE/workflows/Build%20on%20Docker/badge.svg)

A Keyboard Firmware for nRF52832 and nRF52840 Boards

## Build Status

| Branch  | Github Actions - Docker | Github Actions - Ubuntu | Jenkins - Windows |
| ------  | ------                  | ------                  | ------            |
| Master  |![Build on Docker](https://github.com/jpconstantineau/BlueMicro_BLE/workflows/Build%20on%20Docker/badge.svg?branch=master) | !![Build on Ubuntu](https://github.com/jpconstantineau/BlueMicro_BLE/workflows/Build%20on%20Ubuntu/badge.svg?branch=master) | ![Build Status](http://toronto.jpconstantineau.com:8585/buildStatus/icon?job=BlueMicro_BLE-master) |
| Develop |![Build on Docker](https://github.com/jpconstantineau/BlueMicro_BLE/workflows/Build%20on%20Docker/badge.svg?branch=develop) | ![Build on Ubuntu](https://github.com/jpconstantineau/BlueMicro_BLE/workflows/Build%20on%20Ubuntu/badge.svg?branch=develop) | ![Build Status](http://toronto.jpconstantineau.com:8585/buildStatus/icon?job=BlueMicro_BLE-develop) |

| Component  | Version | 
| ------  | ------                  |
| BlueMicro_BLE | [![Current Version](https://img.shields.io/github/v/tag/jpconstantineau/BlueMicro_BLE)](https://github.com/jpconstantineau/BlueMicro_BLE/tags) |
| Adafruit_nRF52_Arduino | [![Adafruit Library for releases](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino) |

[![GitHub forks](https://img.shields.io/github/forks/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/network)[![GitHub stars](https://img.shields.io/github/stars/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/stargazers)[![GitHub contributors](https://img.shields.io/github/contributors/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)[![Discord](https://img.shields.io/discord/449593318247235589.svg)](https://discord.gg/ecnCR9P)

[![GitHub pull requests](https://img.shields.io/github/issues-pr/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE)[![GitHub issues](https://img.shields.io/github/issues/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/issues)



# Documentation
See the pages [Here](http://bluemicro.jpconstantineau.com/#)

You can contribute to the documentation by editing the markdown files located in the docs folder of the repository.

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
| [nice!nano](https://docs.nicekeyboards.com/#/nice!nano/) | uses the nRF52840 chip. Same size as the Pro Micro.  | nRF52840 | nice_nano |

We need your help in bringing improved support for the nrf52840.  Contact us and let us know how you want to help!

Maintainer: [/u/jpconstantineau](https://github.com/jpconstantineau)  



# Contributing

We're very happy to have your contributions in BlueMicro_BLE Firmware

**Contributing New Features**: First, make sure you've run a full set of builds for all boards if adding new functionality (./build.ps1 all). This will ensure that the new functionality doesn't break the build of other keyboards.  Then, make a pull request to this repo. Thanks!

**Adding a new keyboard**: First, add your new keyboard to the folder structure.  You will need to create the apropriate folders and place the 4 necessary keyboard files.  Then, make sure you've run a build for all keymaps applicable to your keyboard (./build.ps1 keyboardname). This will ensure that your keymap can support future hardware configurations.  Then, make a pull request to this repo. Thanks!

**Adding your keymaps**: First, make sure you've run a build for all keymaps applicable to your keyboard (./build.ps1 keyboardname). This will ensure that your keymap can support other hardware configurations.  Then, make a pull request to this repo. Thanks!

**Looking for a feature**: Lots of features are already available; however, not everything is documented yet.  Join in on the [Discord server](https://discord.gg/8pZsrxP) and ask if it's already available, or if anyone is working on what you are looking for.  If you are willing to help adding or testing a new feature, join the team!

**Filing an issue**: Submit issues to the [GitHub Issues](https://github.com/jpconstantineau/BlueMicro_BLE/issues) page.

 **Want to help**: take one of issues in the list [here](https://github.com/jpconstantineau/BlueMicro_BLE/issues) where you think you could help. Comment on it as you start work and join in on the [Discord server](https://discord.gg/8pZsrxP) for a live discussion.


# Credits

The firmware uses the same Arduino Board Support Package as the [Adafruit nRF52 Feather Boards](https://github.com/adafruit/Adafruit_nRF52_Arduino)

[![GitHub license](https://img.shields.io/github/license/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE)

BlueMicro_BLE uses the following projects, each are licensed separately.

| Project | Details |
| ------- | -------- |
| [Arduino IDE](https://github.com/arduino/Arduino) | Development Platform | 
| [Arduino CLI](https://github.com/arduino/arduino-cli) | Alternate platform |
| [Adafruit nRF52 Arduino](https://github.com/adafruit/Adafruit_nRF52_Arduino) | Board Support Package |
| [Adafruit nRF52 Bootloader](https://github.com/adafruit/Adafruit_nRF52_Bootloader) | Bootloader |
| [Adafruit Neopixel](https://github.com/adafruit/Adafruit_NeoPixel) | RGB LED Library |
| [Adafruit TinyUSB Arduino](https://github.com/adafruit/Adafruit_TinyUSB_Arduino) | USB Library for nRF52840 |
| [Hathach TinyUSB](https://github.com/hathach/tinyusb) | USB Library for nRF52840 |
| [Olikraus U8g2](https://github.com/olikraus/u8g2) | U8g2: Library for monochrome displays, version 2 |