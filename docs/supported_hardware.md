# Supported Hardware

## Target CPU

Nordic Semiconductor NRF52832

For more information on the NRF52832, see the [detailed 553 pages product specification](http://infocenter.nordicsemi.com/pdf/nRF52832_PS_v1.4.pdf)

The BlueMicro firmware uses the (Adafruit nrf52 feather)[https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/introduction] bootloader, libraries and allows the following features:

| Feature        | Details           | Comments  |
| ------------- |:-------------:| -----:|
| 2.4 GHz transceiver  | -96 dBm sensitivity in Bluetooth® low energy mode |  |
|               |  -20 to +4 dBm TX power, configurable in 4 dB steps      |    |
|              | 5.3 mA peak current in TX (0 dBm)     |     |
|              | 5.4 mA peak current in RX    |     |
| ARM® Cortex®-M4 32-bit processor with FPU, 64 MHz  | 58 μA/MHz running from flash memory | 3.7mA@64MHz |
|   | 51.6 μA/MHz running from flash memory | 3.3mA@64MHz |
| Power management  | 1.7 V–3.6 V supply voltage range | LiPo Batteries require 3.3V regulator. 5V Not supported.  |
| Memory  | 512 kB flash/64 kB RAM | Partitionned between softdevice, bootloader and 2 DFU regions |
| Digital IO  | 32 general purpose I/O pins | 27 Available in BlueMicro |
| Analog IO  | 12-bit, 200 ksps ADC - 8 configurable channels with programmable gain | 1 Used for battery Monitoring |
| RESET Lines  | 3 GPIO used for RESET, Device Firmware Update (DFU) and Factory Reset |  |
| UART  | 2 GPIO pre-configured for RX/TX serial lines | allows flashing using serial adapter |
| PWM  | 3x 4-channel pulse width modulator (PWM) unit with EasyDMA | Will enable backlight LEDs  |





