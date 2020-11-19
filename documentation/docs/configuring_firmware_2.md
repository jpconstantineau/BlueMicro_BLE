---
id: configure_keyboard
title: Configuring BLE
slug: /configure_keyboard
---

## Configuring your keyboard - Part 2: Keyboard Definition

### keyboard_config.h

#### Keyboard Name

``` c++
#define DEVICE_NAME_R                         "ErgoTravelBLE_R"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_L                        "ErgoTravelBLE_L"                          /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_M                         "ErgoTravelBLE"                          /**< Name of device. Will be included in the advertising data. */
```

#### BLE Service configuration

``` c++
#define KEYBOARD_SIDE SINGLE
```

#### Key Matrix Shape


``` c++
#define KEYMAP( \
      k00, k01, k02, k03, k04, k05, k06, \
      k10, k11, k12, k13, k14, k15, k16, \
      k20, k21, k22, k23, k24, k25, k26, \
      k30, k31, k32, k33, k34, k35,  k36 \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06 }, \
    { k10, k11, k12, k13, k14, k15, k16 }, \
    { k20, k21, k22, k23, k24, k25, k26 }, \
    { k30, k31, k32, k33, k34, k35, k36 } \
} 
```