# A Bluetooth First Firmware

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

