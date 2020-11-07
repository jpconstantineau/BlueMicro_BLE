---
id: customize_BSP
title: Customizing Adafruit BSP
slug: /customize_BSP
---

**RECOMMENDED**

We have created a new Community BSP for you to be able to include your module variant so that your changes can benefit everyone. 

Go to the [Community nRF52 Add-on Boards](https://github.com/jpconstantineau/Community_nRF52_Arduino) project and add your module variant there.  You will then be able to use it directly when compiling your keyboard.  Everyone else will aslo be able to use your module as part of their project.

**ALTERNATE OPTION**
:::caution

When Updating the BSP, you will loose all your changes

:::

In the case where you are building a project with a nRF module that is not from adafruit and that you want to exclude the LF oscillator to reduce your BOM. Or perhaps you forgot to include one in your design and want to test the rest of your hardware. Modifying the Adafruit BSP to support this configuration is shown in the example below:

In this example, an nRF52832 module is being used and a LF oscillator was not included in it's design. The nRF52832 can make use of an internal oscillator for this purpose. The paramater to make this change can be found in the following file:

. . .\Arduino15\packages\adafruit\hardware\nrf52\0.20.5\variants\feather_nrf52832\variant.h

//define USE_LFXO      // Board uses 32khz crystal for LF

#define USE_LFRC    // Board uses RC for LF

These lines can be commented/uncommented as needed. Note that this change will affect any other projects that utilize the BSP that you have edited.

The same edit can be done on the other boards, such as the PCA10056 to support nrf52840 variants without the LF oscillator (32.768kHz crystal).

