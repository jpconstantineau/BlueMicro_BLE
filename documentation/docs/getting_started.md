---
id: getting_started
title: Getting Started
sidebar_label: Getting Started
slug: /
---

## Getting Started: in 4 simple steps

Getting started with 

### Step 1: Option 1 - Install Arduino IDE
<iframe width="572" height="320" src="https://www.youtube.com/embed/0skX6HPSZnU" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Watch the video above to see how to install the Arduino IDE and get the library needed (it's all manual).

These are the steps followed in the video (Original Instructions by [Adafruit](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/arduino-bsp-setup)):
- Download and install the Arduino IDE (At least v1.8). Download it from [here](https://www.arduino.cc/en/Main/Software). Do not install it from the App Store.
- Start the Arduino IDE
- Add `https://www.adafruit.com/package_adafruit_index.json` as an **Additional Board Manager URL** (see image below)
![Board Manager](https://cdn-learn.adafruit.com/assets/assets/000/040/294/large1024/microcontrollers_Screen_Shot_2017-03-19_at_22.16.49.png)
- Open the **Boards Manager** option from the **Tools -> Board** menu and install `Adafruit nRF52 by Adafruit` (see image below)
![Board Manager](https://cdn-learn.adafruit.com/assets/assets/000/039/907/large1024/microcontrollers_nRF52BSP.png?1488964156)

It will take up to a few minutes to finish installing the cross-compiling toolchain and tools associated with this BSP.

__The delay during the installation stage shown in the image below is normal__, please be patient and let the installation terminate normally:
![Board Manager install progress](https://cdn-learn.adafruit.com/assets/assets/000/040/938/large1024/microcontrollers_Screen_Shot_2017-04-19_at_20.23.20.png)

Once the BSP is installed, select the relevant board from the **Tools -> Board** menu, which will update your system config to use the right compiler and settings for your nRF52 board:
![Board Selection](https://cdn-learn.adafruit.com/assets/assets/000/094/506/large1024/microcontrollers_image.png?1598977463)

### Step 1: Option 2 - Install Arduino CLI (Windows script)
<iframe width="572" height="320" src="https://www.youtube.com/embed/kJOem90845Y" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>


Watch the video above to see how to install the Arduino CLI and automatically get the library needed (it's in the script).  
The script follows these steps:

- Download the arduino-cli using the steps outlined [here](https://arduino.github.io/arduino-cli/latest/installation/)
- Review the version installed `arduino-cli version`
- Add the configuration file `arduino-cli.yaml` to the same folder where you have installed the executable binary for the arduino-cli.  This file contains the additional Boards Manager URLs. It's located in the utils folder of the firmware.
- Updates the index of cores from the added Boards Manager URLs: `arduino-cli core update-index`
- Upgrade all installed platforms to the latest version: `arduino-cli core upgrade`
- Make sure that the nRF52 Board Support Packages can be found: `arduino-cli core search nrf52`
- Install the Adafruit nRF52 Board Support Package by running: `arduino-cli core install adafruit:nrf52`
- Install the Community nRF52 Board Support Package by running: `arduino-cli core install community_nrf52:nrf52`
- Verify that the nRF52 boards were installed: `arduino-cli board listall`


### Step 2: Download BlueMicro_BLE Firmware
<iframe width="572" height="320" src="https://www.youtube.com/embed/eKDoVYfXWYQ" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>


To get a copy of the firmware, you have 3 options:
- Download the [zip file](https://github.com/jpconstantineau/BlueMicro_BLE/archive/master.zip) of the master branch of the repository.
- Clone the repository localy  `git clone https://github.com/jpconstantineau/BlueMicro_BLE.git`
- Fork the repo and clone locally.  If you want to save your changes and contribute back to the project, you will need to opt for this method.

Simplest is just to download the [zip file](https://github.com/jpconstantineau/BlueMicro_BLE/archive/master.zip).  In the video, I show the first 2 methods.


### Step 3: Edit 4 Keyboard Files
<iframe width="572" height="320" src="https://www.youtube.com/embed/AjT15clmnmw" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Open the firmware in the IDE or your favorite editor, edit the following 4 files:

- **hardware_config.h:** for the GPIO definition of your keyboard. This file will vary depending on the controller you select.
- **keyboard_config.h:** for the BLE definition of your keyboard
- **keymap.cpp:** for the keymaps definitions
- **keymap.h:** to support the keymaps definitions

For more details on configuring your keyboard, look here...

### Step 4: Compile and Upload
<iframe width="572" height="320" src="https://www.youtube.com/embed/kJOem90845Y" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Video presents the Arduino-cli method.

If you use the Arduino IDE, follow these steps:
- Select appropriate "Board" in the "Tools" menu
- Compile
- Connect your keyboard with USB cable
- Select apropriate serial "Port" in the "Tools" menu
- Upload - Depending on your hardware/firmware, you may need to double-press reset to put it in DFU mode
- Go to your computer's Bluetooth connections and "add device"
- You should be able to pair your keyboard