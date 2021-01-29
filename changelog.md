# BlueMicro_BLE Changelog

## 1.0.0 - WIP

Special thanks to @akudaikon, @ckofy, @tomsaleeba, @garyjohnson, @wizarddata, @bcat for contributing and helping with this release.

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

## 0.3.0 and other Past Releases
