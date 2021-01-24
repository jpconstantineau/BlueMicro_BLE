---
id: configure_keyboard
title: Configuring keyboard_config.h
slug: /configure_keyboard
---

## Configuring your keyboard - Part 2: Keyboard Definition

### Keyboard Name

``` c++
#define DEVICE_NAME_R                         "ErgoTravelBLE_R"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_L                        "ErgoTravelBLE_L"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_M                         "ErgoTravelBLE"                          /**< Name of device. Will be included in the advertising data. */
```

### BLE Service configuration

Available Options:

* `SINGLE`: Use this option for a regular keyboard or for testing one of the two halves of a split keyboard. This configuration uses HID BLE Service and BAT BLE Service for communicating with the computer.
* `LEFT`: Use this option for a the left half of a split keyboard. This configuration uses HID BLE Service and BAT BLE Service for communicating with the computer. This option also turn on scanning for other halves.  The keyboard will scan specifically for BLE devices with the custom keyboard communication service.  When a device is found, it will automatically connect to it.  
* `RIGHT`: Use this option for a the right half of a split keyboard.  This turn on broadcasting of the custom keyboard service for connecting to `LEFT` halves.  This configuration does not use the HID BLE Service.  If you want to test your right half directly with your computer, consider using the `SINGLE` configuration with a test keymap.

``` c++
#define KEYBOARD_SIDE SINGLE
```

### Key Matrix Shape

The KEYMAP macro is used for 2 purposes:

* Remove the extras `{ }` which can make troubleshooting the keymaps difficult
* Relocate specific keys or re-arrange/re-shape the matrix into what the keyboard looks like.
* Hide empty matrix positions from the keymap by using KC_NO in the second part of the macro. 

The following example shows the simplest of KEYMAP macros:

``` c++
#define KEYMAP( \
      k00, k01, k02, k03, k04, k05, k06, \
      k10, k11, k12, k13, k14, k15, k16, \
      k20, k21, k22, k23, k24, k25, k26, \
      k30, k31, k32, k33, k34, k35, k36 \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06 }, \
    { k10, k11, k12, k13, k14, k15, k16 }, \
    { k20, k21, k22, k23, k24, k25, k26 }, \
    { k30, k31, k32, k33, k34, k35, k36 } \
} 
```

This next example shows the KEYMAP macro for the Luddite where all 3 purposes are used:

``` c++
#define KEYMAP( \
    K00, K01, K02, K03, K04, K05, K06, K07, K10, K11, K12, K13, K14, K15, \
    K16, K17, K20, K21, K22, K23, K24, K25, K26, K27, K30, K31, K32, K33, \
    K34, K35, K36, K37, K40, K41, K42, K43, K44, K45, K46, K47, K50, \
    K51, K52, K53, K54, K55, K56, K57, K60, K61, K62, K63, K64, \
    K65, K66, K67,                K70,                K71, K72, K73, K74\
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07 }, \
    { K10, K11, K12, K13, K14, K15, K16, K17 }, \
    { K20, K21, K22, K23, K24, K25, K26, K27 }, \
    { K30, K31, K32, K33, K34, K35, K36, K37 }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, K56, K57 }, \
    { K60, K61, K62, K63, K64, K65, K66, K67 }, \
    { K70, K71, K72, K73, K74, KC_NO,KC_NO,KC_NO } \
}
```

