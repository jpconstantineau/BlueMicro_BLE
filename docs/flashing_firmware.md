# Flashing BlueMicro_BLE to your keyboard


# Preparing your build and flashing environment

Follow the instructions on the Arduino BSP Setup page for the [Adafruit nRF52 Feather](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/arduino-bsp-setup).  The BlueMicro_BLE firmware uses the same libraries and bootloader.

Depending on whether your hardware has on-board serial or not, you will need a serial USB adapter.  Note that the hardware is +3.3V.  As such, a standard +5V serial adapter may damage the nRF52 processor.

**macOS installation**

While following the above Adafruit article, to install nrfutil on macOS High Sierra the following commands may be required for part 2 "Third Party Tool Installation".

- `curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py`
- `sudo python get-pip.py`
- `sudo pip install pip==9.0.3`
- `sudo pip install tornado nosem`
- `sudo pip install nrfutil==0.5.3 --ignore-installed six`

This will install python pip and downgrade it to version 9 (nrfutil fails with "No module named pip.req" when using the latest version). Next install the tornado and nosem packages and finally the version of nrfutil that can be used with Adafruits library (DFU via Serial).

# Building the Firmware for your Keyboard

- Clone the Repository
- If the keyboard already exists in the Keyboards folder, copy the keyboard_config.h and keymap.h files to the "firmware" folder
- If example files are not available, take the keyboard config files that are the closest to yours.
- Make necessary adjustments to the two files.  keyboard_config.h contains the configuration that should be relevant to the keyboard, regardless of the keymap.   keymap.h is "your personal" keymap file.
- Compile the firmware
- Flash the firmware by serial.  Depending if the hardware uses the DTR line to automatically  reset the chip, you may have to manually press reset just before the flashing command gets called.  If it doesn't work, make sure that the the lines are crossed (TX -> RX and RX <- TX).

## Building from Windows PowerShell script

Has been tested on Windows 7 and 10.

**Quick and easy**

- Double cick the build-windows-shortcut in the build folder
- Follow on screen instructions

**Command line with parameters**

- Press the windows key, type "powershell", right click "Windows PowerShell", select "Run as Administrator", enter the command "Set-ExecutionPolicy Bypass" and select Yes
- Run PowerShell and navigate to the build directory
- Run ./build-windows keyboard:keymap:target
- You can replace either keyboard, keymap or target with "all" as a wildcard
- Optional switches are -verbose and -continueOnError

Examples

- ./build-windows all
- ./build-windows ErgoTravel -verbose
- ./build-windows gherkin:default -continueOnError
- ./build-windows iris:default:left

## Building from macOS shell script

The Arduino IDE must be installed in the /Application directory. Tested on macOS High Sierra.

**Quick and easy**

After opening this way once you can simply double click to execute

- Right click the build-macos script in the build folder and choose open, then press open on the developer warning
- Follow on screen instructions

**Terminal script with parameters**

- Run ./build-macos keyboard:keymap:target
- You can replace either keyboard, keymap or target with "all" as a wildcard
- Optional switches are -v for verbose output and -c for continue on build error

Examples

- ./build-macos all
- ./build-macos -v ErgoTravel 
- ./build-macos -c gherkin:default
- ./build-macos iris:default:left

## Building from Linux

Follow the instructions [here](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/arduino-bsp-setup), then 
find your arduino avr installation (should be somewhere in /usr/share/arduino/hardware/) and replace the arduinoAvrPath
variable in build-linux with yours.

Usage is the same as detailed in the windows and mac sections.

# Need to flash the bootloader?

Follow the instructions on the Flashing the Bootloader page for the [Adafruit nRF52 Feather](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/flashing-the-bootloader).  You will need a j-link and connect it to the SWD lines of the hardware.

In the case that you are customizing your bootloader, or progamming a non-feather board using SWD, the following steps should be taken (provided by [reschue](https://forums.adafruit.com/viewtopic.php?f=57&t=167184#wrap))  Read this post in details if you need to follow these steps.

These are specific to the nRF52832 but can be adapted to the 840 as well. Note that with a custom bootloader, the 'Burn Bootloader' feature in the Arduino IDE needs to be used at least once if you're starting with a blank chip.

- Open up Arduino, select the "Adafruit Feather nrf52832" board under "Tools"
- Also under "Tools", select "Programmer: J-Link for Bluefruit nrf52"
- Connect the Segger J-Link to your computer
- Connect the J-Link to your board, and power it up.
- Select "Burn Bootloader" under "Tools". It should complete without errors. At this point the red LED (GPIO 17) should begin the dim-bright-dim cycle. This is the idle loop of the bootloader waiting for a application program to be loaded.
- Install the Segger JLink command line tools, if you've not already done so.
- In a DOS "Command Prompt" window enter the command: nrfjprog --memwr 0x7F000 --val 0x01
- Now, back in the Arduino IDE, select "Upload Using Programmer" and you should be good to go.

You can make changes to your sketch and repeat the Upload Using Programmer as many times as you wish without having to execute any of the "nrfjprog" commands.

