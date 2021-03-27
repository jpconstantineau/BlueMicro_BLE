# BlueMicro_BLE Changelog

## 1.0.0 - WIP

Special thanks to @akudaikon, @ckofy, @tomsaleeba, @garyjohnson, @wizarddata, @bcat for contributing and helping with this release.

### Known Issues

See the [list of issues](https://github.com/jpconstantineau/BlueMicro_BLE/issues) for the latest details.

### BREAKING CHANGES 

For most breaking changes, you will need to install and compile with the Community nrf52 BSP instead of the Adafruit nrf52 Board Support Package. See [here](https://github.com/jpconstantineau/Community_nRF52_Arduino/wiki/Installation-Instructions) for instructions how to install the Community nRF52 Board Support Package.

- **RGB** The Adafruit NeoPixel library was removed from the firmware and included in the Community BSP.
- **BLE Profiles** Due to a change required to the Adafruit nRF52 BSP (0.21.0) in order to allow for profiles, this feature is only supported by the Community BSP.
- **OLED Support** The Olikraus U8g2 library was removed for OLED Support.  The necessary libraries for OLED Support were added to the community BSP.

If you want to use the features listed above, switch to the community BSP.  The Firmware will compile with the Adafruit BSP but the features won't be available.

### USB HID

Thanks to @akudaikon for his contributions showing a working example on how to bring support for USB HID in his fork.

### BLE Profiles

Thanks to @akudaikon for his contributions showing a working example on how to bring support for BLE Profiles in his fork.

### Rotary Encoders

Added support for Rotary Encoders. You can refer to the configuration of the solfle keyboard - default configuration for a working example.

### Persistent Modes and Mode Switching

Added support to save the mode selected by the user so that the keymap to be loaded on bootup can be dynamically changed.  This enables a keyboard to have multiple keymaps and retain that keymap on reboot. Switching to an alternate keymap is as simple as calling a macro.  Other user variables have been added in addition to mode in order to allow for more flexibility.

### Combo Engine: Combos, Substitutions and simple macros

Added support for combos and longer chords. The following functions are now  available:

- **COMB()** Press 2 or more keys, replace with another key.
- **SUBS()** Press 1 or more keys, send a string.
- **KEYS()** Press 1 or more keys, send a sequence of keycodes.

### Documentation

Migrated documentation web pages to docusaurus. See them [here](http://bluemicro.jpconstantineau.com/docs/).

### New and Updated Keyboards/Keymaps

- **cradio**
- **crkbd** 
- **Contra (4x12)**
- **Dactyl**
- **Luddite**
- **Blue Wizard**
- **Corne**
- **Iris**
- **5x5x5 (5x15)**
- **Sofle**
- **BlueZero with Keypad Zero**

## 0.3.0 and other Past Releases
