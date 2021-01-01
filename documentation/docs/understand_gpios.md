---
id: understand_gpios
title: Understand GPIOs
slug: /understand_gpios
---
The BlueMicro firmware uses GPIO (General Purpose Input/Output) numbers as the identifiers to configure how the processor is connected to the keyboard matrix and other keyboard devices.

The general purpose input/output pins (GPIOs) are grouped as one or more ports with each port having up to 32 GPIOs. The number of ports and GPIOs per port might vary with product variant and package. The nRF52832 has 1 port (32 GPIOs) while the nRF52840 has 2 ports 48 (GPIOs).  Some of the GPIOs are already used for specific purposes by the chip for various purposes (32.768 kHz crystal or reset pin).  As such, not all GPIOs are available for use. 

## Understanding nRF52 Modules and how GPIOs are numbered

### Adafruit Feather nRF52832

The __Adafruit Feather nRF52832__ uses the GPIO numbers in the IDE to call the specific pins.  This can be seen as the purple numbers in the following pinout image:
![Adafruit Feather nRF52832](https://cdn-learn.adafruit.com/assets/assets/000/046/248/original/microcontrollers_Feather_NRF52_Pinout_v1.2-1.png?1504885794)

Since there is a direct mapping between the Arduino IDE numbers and the GPIO number, the numbers used while programming are the same as the GPIOs.  __**This makes the Adafruit Feather nRF52832 compatible with most nRF52832 modules.**__

You can find a schematic of the Adafruit Feather nRF52832 [here](https://cdn-learn.adafruit.com/assets/assets/000/039/913/original/microcontrollers_BluefruitnRF52Feather_Rev-F.png).


### Adafruit Feather nRF52840 Express

Unlike for the nRF52832 Feather, Adafruit has opted to use the labels on the module itself as the numbers to use when programming the __Adafruit Feather nRF52840 Express__.  This means that there is no longer a direct representation between what's used while programming and the GPIO Port and Bit on the nRF52840 chip.  __**This makes the Adafruit Feather nRF52840 Express incompatible with other modules.**__

![Adafruit Feather nRF52840 Express](https://cdn-learn.adafruit.com/assets/assets/000/068/578/large1024/circuitpython_Screenshot_2019-01-02_at_12.04.27.png?1546446487)

For more details on the pinout of the Adafruit Feather nRF52840 Express, go to Adafruit's [documentation page](https://learn.adafruit.com/introducing-the-adafruit-nrf52840-feather/pinouts)

You can find a schematic of the Adafruit Feather nRF52840 Express [here](https://cdn-learn.adafruit.com/assets/assets/000/068/545/original/circuitpython_nRF52840_Schematic_REV-D.png).


### Nordic nRF52840DK (PCA10056)

Adafruit was very helpful when they included the __Nordic Semiconductor nRF52840 Development Kit__ in the Adafruit nRF52 Board Support Package. Unlike for the __Adafruit Feather nRF52840 Express__, the __PCA10056__ does not remap GPIO and Pin Numbers.  As such, we can use the GPIO number directly when programming.  __**This makes the Nordic nRF52840DK (PCA10056) compatible with most nRF52840 modules.**__

To find how to calculate the GPIO number, refer to the method described in the next section.

You can find more information on the PCA10056 [here](https://www.nordicsemi.com/Software-and-tools/Development-Kits/nRF52840-DK)

### Other nRF52832 and nRF52840 modules

This includes the BlueMicro, BlueMicro840, nRFMicro, Nice!Nano.  These modules reuse the __Adafruit Feather nRF52832__ or __Nordic nRF52840DK (PCA10056)__ boards in the Adafruit nRF52 Board Support Package.  As described above, the definition of these boards do not remap pins in code.

To find how to calculate the GPIO number, refer to the method described in the next section.

## Selecting GPIOs numbers

### Adafruit Feather nRF52840 Express

Use the Pin number as per what's written on the module itself. See picture in the  __Adafruit Feather nRF52840 Express__ section above.

### All other modules (nRF52832 or nRF52840)

The nRF52832 has 32 GPIOs on 1 port (Port 0) while the nRF52840 has 48 GPIOs on 2 ports (Port 0 and 1).  

To be able to address GPIOs on Port 1, we need to use this simple definition to convert port and bit to a single number.

``` c++
#define _PINNUM(port, bit)    ((port)*32 + (bit))
```
For __Port 0__, the GPIO number will be the same as the Bit number. For example, `P(0.11) = 0 + 11 = 11`

For __Port 1__, the GPIO number will be the Bit number plus 32. For example, `P(1.11) = 32 + 11 = 43`

| Port              | Bit        | GPIO Number to use       |
| ----------------- | ---------- | ---------- |
| 0                 | 0-31       | 0-31       |
| 1                 | 0-15       | 32-47      |
