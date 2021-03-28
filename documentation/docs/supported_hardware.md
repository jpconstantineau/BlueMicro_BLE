---
id: hardware
title: Supported Processors
sidebar_label: Supported Processors
slug: /hardware
---

## Nordic Semiconductor nRF52832 and nRF52840

With the nRF52, you run all of your keyboard firmware code directly on the nRF52 and no external MCU is used or required for Bluetooth functionality!

For more information on the nRF52832, see the [detailed 553 pages product specification](http://infocenter.nordicsemi.com/pdf/nRF52832_PS_v1.4.pdf)
For more information on the nRF52840, see the [detailed 619 pages product specification](https://infocenter.nordicsemi.com/pdf/nRF52840_PS_v1.1.pdf)

The BlueMicro firmware uses the [Adafruit nrf52 feather](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/introduction) bootloader, libraries and allows for the following features:

| Feature              | nRF52832 Details                                  | nRF52840 Details                                  | Comments  |
| -------------------- |:------------------------------------------------- |:-------------------------------------------------|:----- |
| 2.4 GHz transceiver  | -96 dBm sensitivity in Bluetooth® low energy mode | -95 dBm sensitivity in Bluetooth® low energy mode |  |
|                      | -20 to +4 dBm TX power, configurable in 4 dB steps | -20 to +8 dBm TX power, configurable in 4 dB steps |    |
|                      | 5.3 mA peak current in TX (0 dBm)    | 4.8 mA peak current in TX (0 dBm) |     |
|                      | 5.4 mA peak current in RX            | 4.6 mA peak current in RX  |     |
| ARM® Cortex®-M4      | 32-bit processor with FPU, 64 MHz    | 32-bit processor with FPU, 64 MHz |     |
| Memory               | 512 kB flash/64 kB RAM               | 1024 kB flash/256 kB RAM | Partitionned between softdevice, bootloader and firmware regions |
| Power management     | 1.7 V–3.6 V supply voltage range     | 1.7 V–5.5 V supply voltage range | LiPo Batteries require 3.3V regulator for nrf52832. 5V Not supported.  |
|                      | 58 μA/MHz running from flash memory (3.7mA@64MHz) | 52 μA/MHz running from flash memory (3.3mA@64MHz)  ||
| Digital IO           | 32 general purpose I/O pins          | 48 general purpose I/O pins |  |
| Analog IO            | 12-bit, 200 ksps ADC - 8 configurable channels with programmable gain | 12-bit, 200 ksps ADC - 8 configurable channels with programmable gain | 1 Used for battery Monitoring |
| PWM                  | 3x 4-channel pulse width modulator (PWM) unit with EasyDMA | 4x 4-channel pulse width modulator (PWM) unit with EasyDMA| Enables backlight LEDs PWM modulation |
| USB                  | none | USB 2.0 full speed (12 Mbps) controller | |


## Available Modules

There are several modules available that uses the NRF52832 or nRF52840 SoC.
For example, the reference design for the BlueMicro Hardware, the [Adafruit NRF52](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/downloads), uses the MDBT42Q module from Raytac.  Over the last few years, many modules have been made available, in various form factors and available at different price points.

Some of these modules have FCC Certifications while others don't.


## Available Breakout Boards

To be able to be used as processor for a Custom Keyboard, the NRF52832/40 module must be installed on a breakout board that's compatible to be inserted in the custom keyboard in question.


| Breakout Board       | Electrical Connection | Physical Dimensions    | Module        | Compatible with |
| -------------------- | --------------------- | ---------------------- | ------------- | --------------- |
| [Adafruit nRF52 Bluefruit LE](https://www.adafruit.com/product/3406)      | Adafruit Feather      | 23mm x 51mm            | MDBT42Q       | Handwired       |
| [Adafruit Feather nRF52840 Express](https://www.adafruit.com/product/4062)       | Adafruit Feather      | 23mm x 51mm            | MDBT50Q       | Handwired       |
| [BlueMicro](http://nrf52.jpconstantineau.com/docs/bluemicro_v2_1)            | Arduino Pro Micro     | 22mm x 68mm            | E73-2G4M04S1B | Many Custom boards using the Pro Micro but with sufficient length |
| [BlueMicro840](http://nrf52.jpconstantineau.com/docs/bluemicro840_v1)         | Arduino Pro Micro     | 20mm x 33mm            | E73-2G4M04S1C | Many Custom boards using the Pro Micro |
| [BlueMacro840](http://nrf52.jpconstantineau.com/docs/bluemacro840_v1)         | Arduino Micro         | 20mm x 48mm            | E73-2G4M04S1C | Many Custom boards using the Micro |
| [nrfmicro](https://github.com/joric/nrfmicro)             | Arduino Pro Micro     | 18mm x 33mm            | E73-2G4M04S1C | Many Custom boards using the Pro Micro |
| [Nice!Nano](https://nicekeyboards.com/nice-nano/)            | Arduino Pro Micro     | 18mm x 33mm            | nrf52840 chip | Many Custom boards using the Pro Micro |


## Keyboards - Using Breakout Boards

The list of keyboards that can use the nRF52 processors is countless.  However, when implemented with modules and breakout boards, compatibility most often comes down to the electrical connection and the physical dimensions available.
For example, the Original BlueMicro hardware (nRF52832) has an electrical connection that's compatible with the Pro Micro, but its physical dimensions is about twice as long; limiting its use to keyboards with sufficient room in line with the Pro Micro board. With the newer nRF52840 hardware, the dimensions are very similar or identical to the Pro Micro, making them compatible with even more keyboards. 

Other boards uses the Teensy electrical connection to interface the ATMega32U4 to the rest of the keyboard.  Because of the row of electrical connections at the end of the Teensy board and the Keep-Out Area required around 2.4GHz antennas, it is very unlikely that any NRF52 breakout boards will be able to be compatible with the Teensy.

Finally, since the main goal of switching to a nrf52 processor is to convert a keyboard from wired to wireless, physical space for a battery is the next consideration for compatibility with a specific keyboard.


## Keyboards - Using directly in the Keyboard

It's possible to design a keyboard to use the NRF52 chip or a NRF52 module directly on the Keyboard PCB.  This allows the most flexibility in using the available GPIOs and adding any other functionality that cannot be implemented on a breakout board due to the limited space available.

One such example is the [Blue Ortho](https://imgur.com/a/p3ZXnPM#wDFujG6).


## What about Nordic Semiconductor's...

### NRF51822

The NRF51822 is an older device that uses a 32-bit ARM Cortex M0 CPU core.  Adafruit does have a NRF51 feather, however, it does not support the NRF52 libraries.  The NRF51 based Bluefruit boards run as modules that you connect to via an external MCU sending AT style commands over SPI or UART. Not recommended.

### NRF52805, NRF52810, nRF52811, nRF52820 and NRF52833

These chips offer a varying amount of GPIOs, features, flash space and ram. There are fewer modules available with these than with the NRF52832 or nRF52840; often at higher prices due to their limited availability. For details on what feature each chip offer, refer to [Nordic's website](https://www.nordicsemi.com/Products/Low-power-short-range-wireless/Bluetooth-low-energy). The nRF52 Adafruit and Community nRF52 board support packages do not support these chips.  As such, it's recommended to go directly to the NRF52832 or nRF52840.

The NRF52833 is a new chip that sits between the 832 and 840.  It's extended temperature range makes it attractive for commercial and industrial applications. Due to comparable features with the nrf52840 and their availabilities, most will select the NRF52840 instead of the NRF52833.

### NRF5340

This is the newest chip from Nordic Semicomductors.  It has been announced November 2019.  Unlike previous generation chips, it has 2 cores: A 64 MHz network core for handling radio communications and an 64MHz or 128 MHz application core.  Both cores are ARM Cortex M33.  Chips are available for sale but are quite expensive. There are some modules available.  It's not clear if the library will support this chip in the future.