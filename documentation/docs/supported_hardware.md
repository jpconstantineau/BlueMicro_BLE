---
id: hardware
title: Supported Processors
sidebar_label: Supported Processors
slug: /hardware
---

## Target CPU: Nordic Semiconductor nRF52832 and nRF52840

With the nRF52, you run all of your keyboard firmware code directly on the nRF52 and no external MCU is used or required for Bluetooth functionality!

For more information on the NRF52832, see the [detailed 553 pages product specification](http://infocenter.nordicsemi.com/pdf/nRF52832_PS_v1.4.pdf)

The BlueMicro firmware uses the [Adafruit nrf52 feather](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/introduction) bootloader, libraries and allows for the following features:

| Feature              | nRF52832 Details                                  | Comments  |
| -------------------- |:------------------------------------------------- |:----- |
| 2.4 GHz transceiver  | -96 dBm sensitivity in Bluetooth® low energy mode |  |
|                      | -20 to +4 dBm TX power, configurable in 4 dB steps  |    |
|                      | 5.3 mA peak current in TX (0 dBm)     |     |
|                      | 5.4 mA peak current in RX             |     |
| ARM® Cortex®-M4      | 32-bit processor with FPU, 64 MHz     |     |
| Memory               | 512 kB flash/64 kB RAM                | Partitionned between softdevice, bootloader and DFU regions |
| Power management     | 1.7 V–3.6 V supply voltage range      | LiPo Batteries require 3.3V regulator. 5V Not supported.  |
|                      | 58 μA/MHz running from flash memory   | 3.7mA@64MHz |
|                      | 51.6 μA/MHz running from flash memory | 3.3mA@64MHz |
| Digital IO           | 32 general purpose I/O pins           |  |
| Analog IO            | 12-bit, 200 ksps ADC - 8 configurable channels with programmable gain | 1 Used for battery Monitoring |
| PWM                  | 3x 4-channel pulse width modulator (PWM) unit with EasyDMA | Enables backlight LEDs PWM modulation |


## Available Modules

There are several modules available that uses the NRF52832 or nRF52840 SoC.
For example, the reference design for the BlueMicro Hardware, the [Adafruit NRF52](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/downloads), uses the MDBT42Q module from Raytac.  Over the last few years, many modules have been made available, in various form factors and available at different price points.

Some of these modules have FCC Certifications while others don't.


## Available Breakout Boards

To be able to be used as processor for a Custom Keyboard, the NRF52832/40 module must be installed on a breakout board that's compatible to be inserted in the custom keyboard in question.


| Breakout Board       | Electrical Connection | Physical Dimensions    | Module        | Compatible with |
| -------------------- | --------------------- | ---------------------- | ------------- | --------------- |
| Adafruit NRF52       | Adafruit Feather      | 23mm x 51mm            | MDBT42Q       | Handwired       |
| BlueMicro            | Arduino Pro Micro     | 22mm x 68mm            | E73-2G4M04S1B | Many Custom boards using the Pro Micro but with sufficient length |
| BlueMicro840         | Arduino Pro Micro     | 20mm x 33mm            | E73-2G4M04S1C | Many Custom boards using the Pro Micro |
| BlueMacro840         | Arduino Micro         | 20mm x 48mm            | E73-2G4M04S1C | Many Custom boards using the Micro |
| nrfmicro             | Arduino Pro Micro     | 18mm x 33mm            | E73-2G4M04S1C | Many Custom boards using the Pro Micro |
| Nice!Nano            | Arduino Pro Micro     | 18mm x 33mm            | nrf52840 chip | Many Custom boards using the Pro Micro |
| BLE Phage            | Arduino Pro Micro     | 18mm? x 33mm?          | MDBT42Q       | Most custom boards using the Pro Micro |
| 4x4 Backpack         | 40percent.club 4x4    | 76mm x 76mm            | E73-2G4M04S1B | Any configuration from 4x4 to 4x16 |
| 5x5 Backpack         | 40percent.club 5x5    | 95mm x 95mm            | E73-2G4M04S1B | Any configuration from 5x5 to 5x15 |


## Keyboards - Using Breakout Boards

The list of keyboards that can use the NRF52 processors is countless.  However, when implemented with modules and breakout boards, compatibility most often comes down to the electrical connection and the physical dimensions available.
For example, the BlueMicro hardware (nrf52832) has an electrical connection that's compatible with the Pro Micro, but its physical dimensions is about twice as long; limiting its use to keyboards with sufficient room in line with the Pro Micro board.

Other boards uses the Teensy electrical connection to interface the ATMega32U4 to the rest of the keyboard.  Because of the row of electrical connections at the end of the Teensy board and the Keep-Out Area required around 2.4GHz antennas, it is very unlikely that any NRF52 breakout boards will be able to be compatible with the Teensy.

Finally, since the main goal of switching to a nrf52 processor is to convert a keyboard from wired to wireless, physical space for a battery is the next consideration for compatibility with a specific keyboard.


## Keyboards - Using directly in the Keyboard

It's possible to design a keyboard to use the NRF52 chip or a NRF52 module directly on the Keyboard PCB.  This allows the most flexibility in using the available GPIOs and adding any other functionality that cannot be implemented on a breakout board due to the limited space available.

One such example is the [Blue Ortho](https://imgur.com/a/p3ZXnPM#wDFujG6).


## What about Nordic Semiconductor's...

### NRF52840

This is a relatively new chip that supports on-chip USB.  There is more Flash (1Mb), more RAM (256kb), more GPIOs (48 instead of 32), can run with 5V, and also has a USB 2.0 controller.   Wired HID functionality will be available through the use of the TinyUSB Library.  Adafruit has a couple of versions hardware that uses this chip.  They have extended the library to support this new chip.  The BlueMicro firmware supports this chip.


### NRF52810 and NRF52805

This chip is very similar to the NRF52832 but has less features, flash space and ram. There are fewer modules available with these than with the NRF52832; often at higher prices due to their limited availability.  The NRF52 Adafruit library does not support this chip.  As such, it's recommended to go directly to the NRF52832 or nRF52840.


### NRF51822

The NRF51822 is an older device that uses a 32-bit ARM Cortex M0 CPU core.  Adafruit does have a NRF51 feather, however, it does not support the NRF52 libraries.  The NRF51 based Bluefruit boards run as modules that you connect to via an external MCU sending AT style commands over SPI or UART. Not recommended.


### NRF52833

This is a new chip that sits between the 832 and 840.  It's extended temperature range makes it attractive for commercial and industrial applications. Due to comparable features with the nrf52840 and their availabilities, most will select the NRF52840 instead of the NRF52833.


### NRF5340

This is the newest chip from Nordic Semicomductors.  It has been announced November 2019.  Unlike previous generation chips, it has 2 cores: A 64 MHz network core for handling radio communications and an 64MHz or 128 MHz application core.  Both cores are ARM Cortex M33.  Chips aren't available for sale yet.  It's not clear if the library will support this chip.

![BlueMicro](http://bluemicro.jpconstantineau.com/img/BlueMicro_Hardware.jpg)

Top Row: 5x5Backpack, 4x4Backpack

Bottom Row: BlueMicro V2.0,  BlueMicro V1.0, BlueNano V2.0, BlueNano V1.0, Pro Micro (For Reference)

| Board Name | Description | Chip | Bootloader |
|---|---|---|---|
| [Adafruit nRF52 Feather](https://www.adafruit.com/product/3406) | The original from Adafruit! | nRF52832 | nrf52832 feather |
| [BlueMicro V1.0](https://github.com/jpconstantineau/NRF52-Board/tree/master/EByte_E73) | Serial TX/RX routed through D2 and D3; Designed for the ErgoTravel; Tested and Gerber available | nRF52832 | nrf52832 feather |
| [BlueMicro V1.1](https://github.com/jpconstantineau/NRF52-Board/tree/master/EByte_E73)  | Compatible with more Keyboards - Serial TX/RX are routed separately; Tested and Gerber available | nRF52832 | nrf52832 feather |
| [BlueMicro V2.0b](https://github.com/jpconstantineau/NRF52-Board/tree/master/EByte_E73_Batt) | Compatible with more Keyboards - Serial TX/RX are routed separately, LiPo Charger on board; Tested and Gerber available | nRF52832 | nrf52832 feather |
| [BlueMicro V2.0c](https://github.com/jpconstantineau/NRF52-Board/tree/master/EByte_E73_Batt_ErgoTravel) | Serial TX/RX routed through D2 and D3; Designed for the ErgoTravel. LiPo Charger on Board with battery connection connected to RAW pin. Tested and Gerber available. | nRF52832 | nrf52832 feather |
| [BlueMicro V2.1](https://store.jpconstantineau.com/#/group/bluemicro) | CH340g Serial Chip on Board for ease of programming. LiPo Charger on Board with battery connection connected to RAW pin. Tested and Gerber available. | nRF52832 | nrf52832 feather |
| [4x4 Backpack](https://github.com/jpconstantineau/NRF52-Board/tree/master/4x4_backpack/4x4_backpack) | For use with [40percent.club 4x4 Boards](https://www.40percent.club/2018/01/4x4x4x4x4.html). Uses a CR2032 Battery. | nRF52832 | nrf52832 feather |
| [4x4 Platform](https://github.com/jpconstantineau/NRF52-Board/tree/master/4x4_backpack/4x4_platform) | For use with [40percent.club 4x4 Boards](https://www.40percent.club/2018/01/4x4x4x4x4.html). Uses a rechargeable Battery, has a single RGB on board and has a few status LEDs and PWM driven LEDs. Has serial on board too! | nRF52832 | nrf52832 feather |
| [4x4 Backpack840](https://github.com/jpconstantineau/NRF52-Board/tree/master/4x4_backpack/4x4_backpack_nrf52840) | For use with [40percent.club 4x4 Boards](https://www.40percent.club/2018/01/4x4x4x4x4.html). Uses a rechargeable  Battery, has a single RGB on board and has a few status LEDs and PWM driven LEDs.  Most importantly, it uses a nrf52840 module instead of a nrf52832 module. | nRF52832 | nrf52832 feather |
| [5x5 Backpack](https://github.com/jpconstantineau/NRF52-Board/tree/master/5x5_backpack/5x5_backpack) | For use with [40percent.club 5x5 Boards](https://www.40percent.club/2018/04/5x5.html). Uses a CR2032 Battery. | nRF52832 | nrf52832 feather |
| BLE Phage   |    (Compatible with even more Keyboards due to its small size - Serial USB and PoLi Charger on board) | nRF52832 | nrf52832 feather |
| [BLE Phage Basic](https://southpawdesign.net/products/blue-phage-basic?variant=8958741545020) | (Compatible with even more Keyboards due to its small size - Serial TX/RX are routed separately) | nRF52832 | nrf52832 feather |
| [Adafruit nRF52840 Feather](https://www.adafruit.com/product/3406) | The updated nrf52 feather from Adafruit! | nRF52840 | nrf52840 feather express |
| [BlueMicro840](https://store.jpconstantineau.com/#/group/bluemicro) | Bluemicro based on the design of the nrfmicro.  | nRF52840 | PCA10056 or BlueMicro840 |
| [BlueMacro840](https://store.jpconstantineau.com/#/group/bluemicro) | Larger Bluemicro with the footprint of an Arduino Micro.  | nRF52840 | PCA10056 or BlueMicro840 |
| [nice!nano](https://docs.nicekeyboards.com/#/nice!nano/) | uses the nRF52840 chip. Same size as the Pro Micro.  | nRF52840 | nice_nano |

