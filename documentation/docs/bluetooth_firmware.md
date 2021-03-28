---
id: bluetooth_firmware
title: A Bluetooth First Firmware
sidebar_label: Bluetooth First
slug: /bluetooth_firmware
---
## Introduction
BlueMicro_BLE is a keyboard firmware that builds on top the Adafruit nRF52 board support package (BSP) for their line of [Adafruit nRF52 Feather Boards](https://github.com/adafruit/Adafruit_nRF52_Arduino).

By starting with the simple [hid_keyboard.ino](https://github.com/adafruit/Adafruit_nRF52_Arduino/blob/master/libraries/Bluefruit52Lib/examples/Peripheral/hid_keyboard/hid_keyboard.ino) example provided with the library, we expanded it to a full blown Keyboard firmware with lots of features.  See the list [here](features.md)

## Ubiquity of the Arduino framework

Since the firmware is based on the Arduino framework, it's possible to include all sorts of functionality by simply including libraries available and using them.  As there are [several thousand libraries available](https://www.arduinolibraries.info/) (although not all are compatible with the nRF52), it's quite possible that the solution to including a special feature or hardware to your keyboard is already available.

## Design Goals

* Bluetooth First!
* nRF52 features first!  Use peripherals included in the SoC instead of bit-banging and wasting CPU Cycles and burn battery for no reason.
* Must run on batteries,
* Low Power Consumption is key to long battery life
* Keep latency in check
* Don't copy/paste features or code from QMK or other firmware (licenses are different)