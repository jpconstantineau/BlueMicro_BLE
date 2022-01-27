# BlueMicro Firmware  [![Current Version](https://img.shields.io/github/v/tag/jpconstantineau/BlueMicro_BLE)](https://github.com/jpconstantineau/BlueMicro_BLE/tags)  ![Build on Docker](https://github.com/jpconstantineau/BlueMicro_BLE/workflows/Build%20on%20Docker/badge.svg)

## Currently Upgrading to support Adafruit nRF52 release 1.3.0!

Work is currently under way to update BlueMicro_BLE to be able to use the latest release of the Adafruit Board Support Package.  This will enable the following

* BLE profiles 
* USB/BLE switching on the nrf52840



**A Keyboard Firmware for nRF52832 and nRF52840 Boards**

BlueMicro_BLE is a keyboard firmware that builds on top the Adafruit nRF52 board support package (BSP) for their line of Adafruit nRF52 Feather Boards.

By starting with the simple hid_keyboard.ino example provided with the Arduino board support package, we expanded it to a full blown Keyboard firmware with lots of features.

[![GitHub forks](https://img.shields.io/github/forks/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/network) [![GitHub stars](https://img.shields.io/github/stars/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/stargazers) [![GitHub contributors](https://img.shields.io/github/contributors/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors) [![Discord](https://img.shields.io/discord/449593318247235589.svg)](https://discord.gg/ecnCR9P) [![GitHub pull requests](https://img.shields.io/github/issues-pr/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE) [![GitHub issues](https://img.shields.io/github/issues/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/issues)

## Build Status

| Branch  | Github Actions - Docker (Adafruit BSP) | Github Actions - Docker (Community BSP) |Github Actions - Ubuntu Builder | 
| ------  | ------           | ------       | ------                  | 
| Master  | [![Build on Docker - Adafruit](https://github.com/jpconstantineau/BlueMicro_BLE/actions/workflows/build_docker_adafruit.yml/badge.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/actions/workflows/build_docker_adafruit.yml) | [![Build on Docker - Community](https://github.com/jpconstantineau/BlueMicro_BLE/actions/workflows/build_docker_community.yml/badge.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/actions/workflows/build_docker_community.yml) | [![build firmware on Ubuntu](https://github.com/jpconstantineau/BlueMicro_BLE/actions/workflows/builder-ubuntu.yml/badge.svg)](https://github.com/jpconstantineau/BlueMicro_BLE/actions/workflows/builder-ubuntu.yml) |
| Develop |![Build on Docker - Adafruit](https://github.com/jpconstantineau/BlueMicro_BLE/workflows/Build%20on%20Docker%20-%20Adafruit/badge.svg)|![Build on Docker - Community](https://github.com/jpconstantineau/BlueMicro_BLE/workflows/Build%20on%20Docker%20-%20Community/badge.svg) |  


# Documentation
See the pages [Here](http://bluemicro.jpconstantineau.com/#)

You can contribute to the documentation by editing the markdown files located in the docs folder of the repository.


## Video Documentation - BlueMicro Youtube Channel

See a number of tutorials, builds and other keyboard related videos on the [BlueMicro Youtube Channel](https://www.youtube.com/channel/UCFpGp4hHe03nvF9c8_gF_jA/featured).


# Compatible Hardware 

Any nRF52832 or nRF52840 boards that support either of the following 2 Arduino Board Support Packages:

* [Arduino Core for Adafruit Bluefruit nRF52 Boards](https://github.com/adafruit/Adafruit_nRF52_Arduino)
* [Community Add-on to the Adafruit_nRF52_Arduino Board Support Package](https://github.com/jpconstantineau/Community_nRF52_Arduino)

If you use the Adafruit nRF52 Boards in the Arduino IDE, you should select either of the following:

| Chip      | Default Board Selection       |
| ------    | ------                        | 
| nRF52832  | Adafruit Feather nRF52832     |
| nRF52840  | Nordic nRF52840DK (PCA10056)  | 

If your board needs a **special bootloader** or a configuration that's not compatible with the above boards, you should consider adding your board to the Community Add-on to the Adafruit_nRF52_Arduino Board Support Package.  This will make it simpler for others to re-use your special configuration and flashing the bootloader.


# Contributing

We're very happy to have your contributions in BlueMicro_BLE Firmware

**Contributing New Features**: First, make sure you've run a full set of builds for all boards if adding new functionality (./build.ps1 all). This will ensure that the new functionality doesn't break the build of other keyboards.  Then, make a pull request to this repo. Thanks!

**Adding a new keyboard**: First, add your new keyboard to the folder structure.  You will need to create the apropriate folders and place the 4 necessary keyboard files.  Then, make sure you've run a build for all keymaps applicable to your keyboard (./build.ps1 keyboardname). This will ensure that your keymap can support future hardware configurations.  Then, make a pull request to this repo. Thanks!

**Adding your keymaps**: First, make sure you've run a build for all keymaps applicable to your keyboard (./build.ps1 keyboardname). This will ensure that your keymap can support other hardware configurations.  Then, make a pull request to this repo. Thanks!

**Looking for a feature**: Lots of features are already available; however, not everything is documented yet.  Join in on the [Discord server](https://discord.gg/ecnCR9P) and ask if it's already available, or if anyone is working on what you are looking for.  If you are willing to help adding or testing a new feature, join the team!

**Filing an issue**: Submit issues to the [GitHub Issues](https://github.com/jpconstantineau/BlueMicro_BLE/issues) page.

 **Want to help**: take one of issues in the list [here](https://github.com/jpconstantineau/BlueMicro_BLE/issues) where you think you could help. Comment on it as you start work and join in on the [Discord server](https://discord.gg/ecnCR9P) for a live discussion.


# Credits

The firmware uses the same Arduino Board Support Package as the [Adafruit nRF52 Feather Boards](https://github.com/adafruit/Adafruit_nRF52_Arduino)

[![GitHub license](https://img.shields.io/github/license/jpconstantineau/BlueMicro_BLE.svg)](https://github.com/jpconstantineau/BlueMicro_BLE)

BlueMicro_BLE uses the following projects, each are licensed separately.

| Project | Details | Release |
| ------- | -------- | -------- |
| [Arduino IDE](https://github.com/arduino/Arduino) | Development Platform | [![Arduino IDE](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino)  |
| [Arduino CLI](https://github.com/arduino/arduino-cli) | Alternate platform | [![Arduino CLI](https://img.shields.io/github/release/arduino/arduino-cli.svg)](https://github.com/arduino/arduino-cli) |
| [Community nRF52 Arduino](https://github.com/jpconstantineau/Community_nRF52_Arduino) | Board Support Package | [![Community nRF52 releases](https://img.shields.io/github/release/jpconstantineau/Community_nRF52_Arduino.svg)](https://github.com/jpconstantineau/Community_nRF52_Arduino) |
| [Adafruit nRF52 Arduino](https://github.com/adafruit/Adafruit_nRF52_Arduino) | Board Support Package | [![Adafruit Library for releases](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino) |
| [Adafruit nRF52 Bootloader](https://github.com/adafruit/Adafruit_nRF52_Bootloader) | Bootloader | [![Adafruit Bootloader for releases](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Bootloader.svg)](https://github.com/adafruit/Adafruit_nRF52_Bootloader) |
| [Adafruit Neopixel](https://github.com/adafruit/Adafruit_NeoPixel) | RGB LED Library  | [![Adafruit_NeoPixel](https://img.shields.io/github/release/adafruit/Adafruit_NeoPixel.svg)](https://github.com/adafruit/Adafruit_NeoPixel) |
| [Adafruit TinyUSB Arduino](https://github.com/adafruit/Adafruit_TinyUSB_Arduino) | USB Library for nRF52840  | [![Adafruit_TinyUSB_Arduino](https://img.shields.io/github/release/adafruit/Adafruit_TinyUSB_Arduino.svg)](https://github.com/adafruit/Adafruit_TinyUSB_Arduino) | 
| [Hathach TinyUSB](https://github.com/hathach/tinyusb) | USB Library for nRF52840 | [![Hathach TinyUSB](https://img.shields.io/github/release/hathach/tinyusb.svg)](https://github.com/hathach/tinyusb) |
| [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) | Monochrome OLEDs Library based on SSD1306 drivers  | [![Adafruit_SSD1306](https://img.shields.io/github/release/adafruit/Adafruit_SSD1306.svg)](https://github.com/adafruit/Adafruit_SSD1306) |
| [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library) | core graphics library  | [![Adafruit-GFX-Library](https://img.shields.io/github/release/adafruit/Adafruit-GFX-Library.svg)](https://github.com/adafruit/Adafruit-GFX-Library) |
| [Adafruit_BusIO](https://github.com/adafruit/Adafruit_BusIO) | helper libary to abstract away I2C & SPI transactions and registers  | [![Adafruit_BusIO](https://img.shields.io/github/release/adafruit/Adafruit_BusIO.svg)](https://github.com/adafruit/Adafruit_BusIO) |
| [Olikraus U8g2](https://github.com/olikraus/u8g2) | U8g2: Library for monochrome displays, version 2 | [![u8g2](https://img.shields.io/github/release/olikraus/U8g2_Arduino.svg)](https://github.com/olikraus/U8g2_Arduino)  |
