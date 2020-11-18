---
id: bluetooth_firmware
title: A Bluetooth First Firmware
sidebar_label: Bluetooth First
slug: /bluetooth_firmware
---
## Introduction
BlueMicro_BLE is a keyboard firmware that builds on top the Adafruit nRF52 board support package (BSP) for their line of [Adafruit nRF52 Feather Boards](https://github.com/adafruit/Adafruit_nRF52_Arduino).

By starting with the simple [hid_keyboard.ino](https://github.com/adafruit/Adafruit_nRF52_Arduino/blob/master/libraries/Bluefruit52Lib/examples/Peripheral/hid_keyboard/hid_keyboard.ino) example provided with the library, we expanded it to a full blown Keyboard firmware with the following features:

* Customizable matrix scanning with selectable number of rows/columns and diode direction
* Re-map a rectangular NxM matrix to another shape with the same number of keys (a 60% maped to a 8x8 matrix)
* Layers
* Tap/Double-tap keys
* Tap/Hold keys
* Battery Level BLE service
* Sleep after 10 minutes of inactivity (when connected - by default)
* PWM LED Backlight. Control the brighness of LEDs.  To save power, they automatically dim after each keypress
* Many other features...

## Design Goals

* Bluetooth First!
* nRF52 features first!  Use peripherals included in the SoC instead of bit-banging and wasting CPU Cycles and burn battery for no reason.
* Must run on batteries 
* Low Power Consumption is key to long battery life
* Keep latency in check
* Don't copy/paste features from QMK or other firmware (licenses are different)