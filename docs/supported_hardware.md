# Supported Hardware

## Target CPU: Nordic Semiconductor NRF52832

With the nRF52832, you run all of your keyboard firmware code directly on the nRF52832 and no external MCU is used or required for Bluetooth functionality!

For more information on the NRF52832, see the [detailed 553 pages product specification](http://infocenter.nordicsemi.com/pdf/nRF52832_PS_v1.4.pdf)

The BlueMicro firmware uses the (Adafruit nrf52 feather)[https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/introduction] bootloader, libraries and allows for the following features:

| Feature              | Details                                           | Comments  |
| -------------------- |:------------------------------------------------- |:----- |
| 2.4 GHz transceiver  | -96 dBm sensitivity in Bluetooth® low energy mode |  |
|                      | -20 to +4 dBm TX power, configurable in 4 dB steps  |    |
|                      | 5.3 mA peak current in TX (0 dBm)     |     |
|                      | 5.4 mA peak current in RX             |     |
| ARM® Cortex®-M4      | 32-bit processor with FPU, 64 MHz     |     |
| Memory               | 512 kB flash/64 kB RAM                | Partitionned between softdevice, bootloader and 2 DFU regions |
| Power management     | 1.7 V–3.6 V supply voltage range      | LiPo Batteries require 3.3V regulator. 5V Not supported.  |
|                      | 58 μA/MHz running from flash memory   | 3.7mA@64MHz |
|                      | 51.6 μA/MHz running from flash memory | 3.3mA@64MHz |
| Digital IO           | 32 general purpose I/O pins           | 27 Available in BlueMicro |
| Analog IO            | 12-bit, 200 ksps ADC - 8 configurable channels with programmable gain | 1 Used for battery Monitoring |
| RESET Lines          | 3 GPIO used for RESET, Device Firmware Update (DFU) and Factory Reset |  |
| UART                 | 2 GPIO pre-configured for RX/TX serial lines | Enables flashing using serial adapter |
| PWM                  | 3x 4-channel pulse width modulator (PWM) unit with EasyDMA | Enables backlight LEDs PWM modulation |


## Available Modules

There are several modules available that uses the NRF52832 SoC.
For example, the reference design for the BlueMicro Hardware, the [Adafruit NRF52](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/downloads), uses the MDBT42Q module from Raytac.  Over the last few years, many modules have been made available, in various form factors and available at different price points.

Some of these modules have FCC Certifications while others don't.


## Available Breakout Boards

To be able to be used as processor for a Custom Keyboard, the NRF52832 module must be installed on a breakout board that's compatible to be inserted in the custom keyboard in question.


| Breakout Board       | Electrical Connection | Physical Dimensions    | Module        | Compatible with |
| -------------------- | --------------------- | ---------------------- | ------------- | --------------- |
| Adafruit NRF52       | Adafruit Feather      | 23mm x 51mm            | MDBT42Q       | Handwired       |
| BlueMicro V1.x, V2.x | Arduino Pro Micro     | 22mm x 68mm            | E73-2G4M04S1B | Many Custom boards using the Pro Micro but with sufficient length |
| BLE Phage            | Arduino Pro Micro     | 18mm? x 33mm?          | MDBT42Q       | Most custom boards using the Pro Micro |
| 4x4 Backpack         | 40percent.club 4x4    | 76mm x 76mm            | E73-2G4M04S1B | Any configuration from 4x4 to 4x16 |
| 5x5 Backpack         | 40percent.club 5x5    | 95mm x 95mm            | E73-2G4M04S1B | Any configuration from 5x5 to 5x15 |


## Keyboards 

The list of keyboards that can use the NRF52832 processor is countless.  However, when implemented with modules and breakout boards, compatibility most often comes down to the electrical connection and the physical dimensions available.
For example, the BlueMicro hardware (V1.x and V2.x) has an electrical connection that's compatible with the Pro Micro, but its physical dimensions is about twice as long; limiting its use to keyboards with sufficient room in line with the Pro Micro board.

Other boards uses the Teensy electrical connection to interface the ATMega32U4 to the rest of the keyboard.  Because of the row of electrical connections at the end of the Teensy board and the Keep-Out Area required around 2.4GHz antennas, it is very unlikely that any NRF52832 breakout boards will be able to be compatible with the Teensy.

Finally, since the main goal of switching to a nrf52832 processor is to convert a keyboard from wired to wireless, physical space for a battery is the next consideration for compatibility with a specific keyboard.





