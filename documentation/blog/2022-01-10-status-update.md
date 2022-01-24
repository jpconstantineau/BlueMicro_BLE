---
slug: State of BlueMicro 2022
title: State of BlueMicro 2022
author: Pierre Constantineau
author_title: Wireless electronics enthousiast in Canada
author_url: https://github.com/jpconstantineau
author_image_url: https://avatars3.githubusercontent.com/u/1149816?s=460&u=521fbf5035ea442b1d07281c0c7573ca3596cf3f&v=4
tags: [BlueMicro, Status Update, CircuitPython, CircuitPython2022]
---

## A BlueMicro Review of 2021

2021 was an eventful year in the word of wireless mechanical keyboards and BlueMicro. 

### Wireless Hardware

Although BlueMicro was the precursor to many breakout boards now used as controllers for keyboard builds, the [nice!nano](https://nicekeyboards.com/nice-nano/) is now the most popular in the mechanical keyboard community, followed by the nRF52840 feather express for handwired builds and the [nrfmicro](https://github.com/joric/nrfmicro) for more adventurous builders. The [BlueMicro840](https://www.tindie.com/search/?q=bluemicro840) is still an option but as my time is limited and they are manually assembled, their supply was limited, even before the chip shortage hit the needed modules (more to come on that...).  For more GPIOs, there is the BlueMacro840 which makes available more GPIOs.

The first all-in-one keyboards I designed in 2021 was the [BlueHand](https://www.tindie.com/products/jpconstantineau/2x4-ble-macropad-for-mechanical-switches/). A simple 8-keys hand-sized wireless mechanical keyboard that's been designed for [Artsey.io](https://artsey.io/); a one-handed keyboard typing system that uses chording for registering keypresses.  

The chip shortage has affected the supply of processors for many projects. The nrf52840 modules used for the Bluemicro840, BlueHand and nrfmicro became scarce and the few modules that could be found went for 6x their original prices; making the modules even more expensive than a Nice!Nano. 

This has prompted me to create the [BlueMicro833](https://www.tindie.com/products/jpconstantineau/ebyte-e73-2g4m08s1e-breakout-bluemicro833-pcba/), based on the now available nrf52833 modules which are almost identical to the 840 modules at a similar price as the original nRF52840 modules a year ago.  The most important differences are RAM and Flash sizes.  Unfortunately, firmware support is lacking.  A BlueMicro833 was sent to the ZMK team for testing and it tested fine with ZMK. 

### Is new hardware even possible with the chip shortage?

In early 2021, Raspberry Pi introduced the RP2040.  The RP2040 is a dual core ARM Cortex M0+ chip with interesting peripherals and is very cheap.  It's only wired - no BLE with this chip.  Because the RP2040 is the first microcontroller from Raspberry Pi, it had no pre-existing users (for example, car manufacturers), it saw really good availability, even [JLCPCB](https://jlcpcb.com/parts/componentSearch?isSearch=true&searchTxt=rp2040) has it for PCBA. Circuitpython was available relatively quickly. A few [videos are on Youtube](https://www.youtube.com/watch?v=X00Cm5LMNQk) on how to design a rp2040 board made the task quite simple.  Raspberry PI even provided a [reference design](https://datasheets.raspberrypi.com/rp2040/hardware-design-with-rp2040.pdf).  As such, I introduced [PyKey](https://circuitpython.org/downloads?q=pykey), a suite of mechanical keyboards with a RP2040 as the processor, starting with [PyKey60](https://circuitpython.org/board/jpconstantineau_pykey60/), a 60% keyboard based on the GH60 form factor (More sizes are now available: Numpad, TKL, 44-keys Ergo).



### Wireless Firmware

QMK has retained the dominant firmware for mechanical keyboards but ZMK became the dominant choice for newcomers to wireless DIY mechanical keyboards. Based on the Zephyr project, it has a good follower base. Just like QMK, it focuses on a readily available firmware and not on basic troubleshooting tools that can help the DIY builder troubleshooting their hardware troubles.  Additionnaly, as ZMK uses the Zephyr BLE stack and not the Nordic SoftDevice, some users have faced issues pairing with some devices (Apple mostly). Some of these users have gone to BlueMicro_BLE and their pairing troubles were resolved. 

Bluemicro_BLE being based on the Arduino nRF52 board support package from Adafruit, is much more friendly in case the user needs to create their own code to troubleshoot their hardware. 

Since Adafruit will only include boards that they [sell](https://github.com/adafruit/Adafruit_nRF52_Arduino/pull/596#issuecomment-714900359) within their nRF52 Arduino Board support package, I created a fork of the BSP (and disconnected it) and created the [Community Add-On nRF52 Board Support Package](https://github.com/jpconstantineau/Community_nRF52_Arduino) to which changes were made; most importantly, the addition of many nRF52 boards and keyboards available to the community.  My decision to split the code base from the source repository was mainly based on the desire remove the problematic code causing [high current consumption](https://github.com/adafruit/Adafruit_nRF52_Arduino/issues/600), but also to keep a fork for me to be able to contribute to the main repository while having a separate repo for the Community boards.  Unfortunately, this decision came to bite me when many positive changes were pushed to the Adafruit nRF52 Arduino Board Support Package.



In order to make more options available for users, support for CircuitPython was added for the BlueMicro840. Circuitpython adds a new framework by which one can code their keyboards and even troubleshoot their hardware. You can go to the [PyKey](http://pykey.jpconstantineau.com/docs/testing_hardware/keymatrix) project to see lots of keyboard troubleshooting tips with CircuitPython.

CircuitPython also makes [KMK](https://github.com/KMKfw/kmk_firmware) an option for BlueMicro840 users. I even designed an ultra-portable wireless keyboard that uses 44 Kailh Thin keys that saw KMK as the first firmware to run on it.  I year ago, I never coded any Python. Today, I can count a few of my keyboards within the [KMK repo](https://github.com/KMKfw/kmk_firmware/tree/master/boards/jpconstantineau); all Python code I wrote...

### Firmware for nRF52833

Unfortunately, support for the Nordic nRF52833 in the Arduino IDE is non-existent. There were a [few PRs](https://github.com/adafruit/Adafruit_nRF52_Arduino/pulls?q=is%3Apr++nrf52833+) but none were included in the Adafruit nRF52 Arduino Board Support Package. An issue was raised to ask if the nRF52833 Dev Kit from Nordic would be merged in if a PR would be made (even if on a not-supported basis). [No clear response yet](https://github.com/adafruit/Adafruit_nRF52_Arduino/issues/696).   Without Arduino support for ths chip, BlueMicro_BLE firmware won't be able to run on it.  In the meantime, try CircuitPython,KMK or ZMK!  

### BlueMicro_BLE

2021 started great for BlueMicro_BLE with the addition of a few great features:
- USB and BLE switching - Wireless and Wired on the same keyboard - switched automatically!
- Mutiple BLE Profiles - making it possible to choose which computer to connect it to
- Combos/chording: a new keycode-based chording engine that replaces keycodes when two or more keycodes are detected. (press multiple keys, send something else...). Unlike other firmwares, the engine is not key based but keycode-based.
- BlueMicro_Builder: Inspired by the simple build process of ZMK, a new [BlueMicro_Builder](https://github.com/jpconstantineau/BlueMicro_Builder) repository template has made available the option for nRF52840 users to have their firmware built by GitHub Actions. Check out the [video](https://www.youtube.com/watch?v=hKw3TPNu-BQ) to see how it works!

With new features, new bugs and issues always come to haunt us, along with more feature requests...  2022 will look at resolving some of the more fundamental problems, bringing 1.3.0 BSP support all while enabling easier future improvements. 

## What's coming in 2022 for BlueMicro?

### Update to Latest Adafruit nRF52 Arduino BSP.
With all the major changes to TinyUSB completed and rolled into the adafruit nRF52 board support package, as well as the support for multiple Bluetooth profiles from the Adafruit BSP itself, there are no core changes in the Community Board Support pachages that are needed, except for the additional boards.  As such, a staged approach will be taken to update both the [BlueMicro_BLE](https://github.com/jpconstantineau/BlueMicro_BLE) firmware and the [Community Add-On nRF52 Board Support Package](https://github.com/jpconstantineau/Community_nRF52_Arduino) to the latest BSP.


### Unifying the interface for USB and BLE HID
In 2021, I started the effort to unify the BLE and USB calls into a single library, starting from thr ground up using the HID_Composite examples.  After countless hours of unsuccessful and hair-pulling code streams, I finally have something working.

I am planning to make a common HID library that handles both BLE on the nRF52 chips and USB on boards with TinyUSB support. This would be publised as an Arduino Library.  By migrating to this library, this means that Bluemicro_BLE will be able to support the nrf52 chips, the RP2040 and the SAMD21 and SAMD51 chips; at least from a single keyboard point of view. Split keyboards would be next.  The prototype code already runs on multiple Adafruit Feathers (nrf52832, nrf52840, RP2040, SAMD21, SAMD51).

### Making Mousekeys work (and make sense)

Since the unified library described above is based on the HID_Composite examples, the library would enable parallel keyboard/mouse/consumer keyscodes to be sent (as opposed to only one of the 3).  This would enable refactoring the code to simplify how the different HID messages are handled.

## What else?

What are you looking for as improvements to your keyboard firmware and hardware?

Here are some of the ideas I have received:

- Enable Pointing devices to be easily integrated within BlueMicro_BLE.  I have had various requests for enabling mouse movements as part of the keyboard functions.  
  - [Digital Joystick/5 way switches](https://datasheet.lcsc.com/lcsc/2110151630_XKB-Connectivity-TM-2027_C318948.pdf)
  - [Analog Joystick](https://www.tindie.com/products/robotart/joystick-game-controller-for-arduino/)
  - [Pimoroni Trackball Breakout](https://shop.pimoroni.com/products/trackball-breakout)
  - [PMW3360 Motion Sensor](https://www.tindie.com/products/jkicklighter/pmw3360-motion-sensor/)  
  - [Cirque Trackpads](https://www.cirque.com/glidepoint-circle-trackpads)
- RGB Effects.
- Better handling of USB on secondary side of split keyboards
- Sharing of Toggles and One-shots between sides.
- Improvements to key state logic to handle Tap/Double-Tap/Hold on the same key. 
- Enable "delays" in macros.

## CircuitPython 2022

Since BlueMicro has a focus on keyboards and other HID/Input devices, this will obviously have a keyboard focus; either to help generic firmware, KMK or enable users develop more complex keyboards from a common set of building blocks.  As I am not a Python developer, I don't expect to be able to make significant contributions to libraries but I can contribute to new boards reviews, minor core additions and commenting on use of specific libraries I might use.

### Keypad extensions

The keypad core module defines a simple interface by which keypress/keyrelease events are provided to the user for acting upon.  Using this common interface for detecting key presses is currently a Work in Progress in [KMK](https://github.com/KMKfw/kmk_firmware/issues/237). 

Expanding the use of the keypad API to non-board GPIOs would be a natural extension.

To enable flexibility in how people design their keyboards, the following GPIO expanders should be included as part of an add-on keypad library (or family of libraries).
- [MCP23017 GPIO Expander](https://www.adafruit.com/product/5346)
- [PCA9505 GPIO Expander](https://www.nxp.com/products/interfaces/ic-spi-serial-interface-devices/ic-general-purpose-i-o/40-bit-ic-bus-i-o-port-with-reset-oe-and-int:PCA9505_06)
- PCF8574 GPIO Expander
- [Adafruit ATSAMD09 Breakout with seesaw](https://www.adafruit.com/product/3657)
- [Adafruit ATtiny817 Breakout with seesaw](https://www.adafruit.com/product/5233)

The add-on library would make I2C devices available with the same API as the core keypad module.  This way, people could use the same code regardless where their keys and keypads are connected to.

A great example of a split keyboard that uses multiple GPIO expanders is Zack Freedman's MiRage keyboard. Check out his [video](https://youtu.be/Fg0V5M0llaE) and his [repo](https://github.com/ZackFreedman/MiRage).  

### Hide your [ghosts](https://www.youtube.com/watch?v=CFSjnV7zUYM)

Another possible extension but to the core keypad module would be to enable key matrices that do not have anti-ghosting diodes.  One of the BlueMicro_BLE contributors has  an [example](https://bitbucket.org/akudaikon/bluemicro-model-m/src/3ac5081226541f5c06abdcb7b2676a80f0b867bb/firmware/firmware_main.cpp?at=master#firmware_main.cpp-248) where ghost key detection and filtering is done so that ghost keys are not included as part of the key state transitions.  Adding diodes is not always possible as this code is used as part of a Model M keyboard Wireless retrofit. Other keyboards might not have the room for diodes - check out this [Tiny Pico Keyboard](https://youtu.be/iWWTJKWFNok) for an idea how small one can go.  I have my own wireless one that's based on the BlueMicro840 but has the footprint of a Raspberry Pi Zero.

### Make your own SeeSaw

Adafruit has led an interesting I2C revolution with the introduction of multiple SeeSaw input devices:
- [NeoKey 1x4 QT I2C](https://www.adafruit.com/product/4980)
- [Adafruit I2C QT Rotary Encoder](https://www.adafruit.com/product/4991)
- [Adafruit NeoSlider I2C QT Slide](https://www.adafruit.com/product/5295)
- [Adafruit Joy FeatherWing for all Feathers](https://www.adafruit.com/product/3632)
- [Adafruit 1.8" Color TFT Shield w/microSD and Joystick](https://www.adafruit.com/product/802)
- [Adafruit Mini Color TFT with Joystick FeatherWing](https://www.adafruit.com/product/3321)

Split keyboards could be designed with the secondary side being a custom SeeSaw device, while the primary side would be standard CircuitPython or Arduino code.

There is an [Arduino Library](https://github.com/adafruit/Adafruit_seesawPeripheral) for creating your own seesawPeripheral, however, it seems that it's only supported by the megaTinyCore (AVR) chips (although the library properties seems to indicate otherwise).  It would be very useful to be able to create your own SeeSaw device using CircuitPython.  Take a KB2040, a Raspberry Pi Pico, a Feather M4 or a small SAMD21 board and re-purpose it as a SeeSaw co-processor for handling remote input/output devices.  If CircuitPython can't be used due to size limitations, an Arduino library for use with the SAMD21 would be useful.  I believe porting the I2C peripheral module to other chips would be the starting  point.


### Split keyboards and the KB2040 (and Pro Micro RP2040):

To understand the potential issues with the RP2040 on a board with the form factor of the Pro Micro, we need to see a brief history of split keyboards and how communications was handled between the halves. 

#### A recent history of split keyboards
The table below presents a brief list of split keyboards, starting with the Original Ergodox from 2013.  The Let's Split V2 is the board that truely kicked-off the DIY Split keyboard explosion of options.  It's inspired from the Planck but divided into two halves.

A number of commercial keyboards have not been included due to their closed source PCBs. Nevertheless, this list is very small. Have a look [here](https://golem.hu/boards/) is you want to see a large database of split boards...

| Board | Date | PCB Repo | Build Guide | Serial Pin | I2C |
| ---  | ---  | ---      | ---         | ---        | --- |
| ErgoDox Original | July 2013 | [PCB](https://github.com/bishboria/ErgoDox) | - |n/a| | 
| ErgoDox IO | Dec 2016 | [PCB](https://github.com/Ergodox-io/ErgoDox/blob/master/README.md) | - |n/a| MCP23018 | 
| Let's Split V2 | April 2017 | [PCB Repo](https://github.com/climbalima/let-s-Split-v2)|[Build Guide](https://github.com/nicinabox/lets-split-guide)|D0| D1/D0  |
|Minidox | August 2017 | [PCB](https://github.com/That-Canadian/MiniDox_PCB) | Guide | D0 | n/a |
| Helix | February 2018 | [PCB](https://github.com/MakotoKurauchi/helix) |[Guide](https://github.com/MakotoKurauchi/helix/blob/master/Doc/buildguide_en.md)|D0 (V1), D2 (V2)| Oled |
| ErgoTravel | June 2018 | [PCB](https://github.com/jpconstantineau/ErgoTravel) | [Guide](https://github.com/jpconstantineau/ErgoTravel/blob/master/BuildInstructions.md) | D0 | D1/D0 |
|  Lily58  | October 2018 | [PCB](https://github.com/kata0510/Lily58) |  | D2 | Oled |
|Sofle|Sept 2019| [PCB](https://github.com/josefadamcik/SofleKeyboard) | Guide | D2 | Oled |
|Corne|October 2019 | [PCB](https://github.com/foostan/crkbd)|Guide| D2 | Oled |

On the Pro Micro, D0/D1 are SCL/SDA and D2/D3 are RX/TX.

As you can see from the table, the design of the Let's Split opted for making the selection of I2C an option by using the SCL line as a serial line between the two boards.  This freed a data line for users to add RGB data between the two halves.  Most builds that used the Let's Split as a template used D0 with software serial.  Some kept the option for I2C, others dropped it.

However, with the addition of I2C OLED screens on the Helix, serial communications between the two halves was relocated to be on D2 (See differences between V1 and V2).  Since D2 is RX, on one side hardware UART can be used but software UART has to be used on the other side.  This allows for 1-way communications.  2-way comms would need to use software serial with some software handshaking to handle direction changes (and perhaps a resistor to limit current in case of TX on both sides at the same time); 2-way serial is probably not generally implemented on a single line due to the additional complexity.  

#### The problem with the RP2040 and hardware UART

Unlike the nRF52 where any GPIO can be used for I2C and UART, the RP2040 has some restrictions on what functions are available for each GPIO.  If one wants to use non-standard (i.e. not in the table of page 13-14 of the [datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)), you have to use the PIO to create your own UART RX or TX (Datasheet Page 373) peripherals.  Since most pro-micro keyboards that used  I2C, relied on hardware for I2C.  However, to keep build flexibility and cost of PCB designs low, the same I2C pins were re-used but for serial.  Serial communications were slao setup with a single line to leave a line free for "RGB Data".  Using the same data pin on each side allowed for mirrored builds and for the possibility of setting up both sides identically and automatically detecting which side is primary or secondary by monitoring whether USB is connected; hence detecting the desired data direction on the serial line.  

This means that serial connection of many (if not most) split keyboards will rely on "non-standard" RX/TX pins definition compared to the default Arduino Pro Micro definitions.

For existing split keyboards to work, we need software UART (or PIO UART) in CircuitPython.


### I2CPeripheral for other chips (RP2040, SAMD21, nRF52, etc)

To enable I2C communications between keyboard halves or to build your own seesaw board using CircuitPython, I2CPeripheral on the RP2040 and other chips is needed.  Once available, a seesaw_peripheral library will be possible.  Possibly leveraging the adafruit_register.i2c_struct.Struct function, perhaps in a bi-directional way: define the same registers on both sides of the communication channel and let the I2C "magic" do its thing...   


### Very Deep Sleep on the nRF52

I have an [article](http://pykey.jpconstantineau.com/docs/testing_hardware/sleep) that compares ZMK, BlueMicro_BLE and CircuitPython running and sleep current on the same device.  Unlike the other two, CircuitPython isn't a compiled language.  As such, power consumption when running will never be able to reach the level of designed-for-purpose compiled code. Nevertheless, when going in deep sleep, the chip shouldn't be running and one would expect a comparable current.  Unfortonately, how deep sleep is implemented in CircuitPython is more of a "nap" than a sleep.  The chip regularly wakes up to check the state of alarm pins, then goes back napping until the next check.

As such, there is the possibility for an even deeper sleep for the nRF52 chips running CircuitPython.  I don't know what it should be called as "deep sleep" is already taken. The article mentionned above highlights how it's done and how it behaves (full reboot on wake-up).  This "Very Deep Sleep" needs an external pin to be toggled for the wake-up to occur.  For keyboards, a simple keeypress does the job.

### BlueMicro833
  Detailed testing of the Bluemicro 833 with Circuitpython and KMK is needed to see how much useful room is available, both for Ram and Flash space.  Having half the flash and ram as the nRF52840, I suspect that we may run into similar issues as the SAMD21.  The SAMD21 has so little ram that it runs out of it pretty quickly.  The nRF52833 has more, however as this is chip is meant for BLE functions and that the Softdevice consumes a chunk of space already, what's left to the user for Python code will be limited.  Testing and Time will tell... 

### Circuitpython.org Improvements

I would like to recommend a few minor improvements to the download page of CircuitPython.org, especially when it gets to filtering by chip family/chip type.  With 269 boards, and going up regularly, filtering will become more important to find a board of choice for your next project.

The Atmel-Samd Processor Family includes SAMD21 and SAMD51 boards (ARM M0/M4) while the nRF52 Family is non-existant but nRF52840 is present instead of having nRF52833 and nRF52840 as separate chips.

A filter hierarchy similar to the tree below would enable users to search for boards with a specific processor.

- Atmel-Samd
  - SAMD21
  - SAMD51
- Broadcom
- Cxd56
- Espressif
    - Esp32c3
    - Esp32s2
    - Esp32s3
- Litex
- Mimxrt10xx
- nRF52
  - nRF52833
  - nRF52840
- Raspberry Pi
  - RP2040
- STM
    - F4
    - H7
    - F7
    - L4

Some people might be interested in filtering by the core type as follows:
 - ARM Cortex M0 
 - ARM Cortex M4
 - RISC-V
 - ARM Cortex-A7
 - ARM Cortex-A53

However, as you can already filter by the processor family, I doubt this will provide much value;  only those asking "Does it run on RISC-V?" will get an answer...

### Awesome CircuitPython Improvements

It would be neat to add a section/page/subpage to Awesome CircuitPython called *Popular Projects Enabled by CircuitPython*

This could include:
- [KMK Keyboard Firmware](https://github.com/KMKfw/kmk_firmware)
- [Pico Ducky](https://github.com/dbisu/pico-ducky)
