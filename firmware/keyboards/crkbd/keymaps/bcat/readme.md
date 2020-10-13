# bcat's Corne layout

This is a BlueMicro port of [my Crkbd layout in
QMK](https://github.com/qmk/qmk_firmware/tree/master/keyboards/crkbd/keymaps/bcat).
See the QMK layout's readme file for layout images and KLE links.

This is a faithful reproduction of the QMK layout, except that RGB controls have
been omitted since my Bluetooth Corne doesn't have LEDs installed, and my custom
Alt+Tab macro has been omitted since as of October 2020, BlueMicro doesn't
appear to provide an equivalent of QMK's `register_code` function for it.
