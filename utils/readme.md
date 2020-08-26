# Arduino-cli Utility Scripts

These scripts only compile and flash the keyboard files in the root firmware folder.
These work the same as if you were opening the firmware.ino file from the Arduino IDE.

## Installation of Arduino-cli

This script will download and install the arduino-cli in the BlueMicro_BLE\arduino-cli folder.

```

install.bat

```

## Compiling firmware.ino

Usage

```

compile.bat fqbn

```

where `fbqn` is the Fully Qualified Board Name

Examples:

```

compile.bat nrf52832

compile.bat feather52840

compile.bat pca10056

```

When compilation is successful, you will see a message similar to below (size will vary depending on keyboard):

```

Sketch uses 80916 bytes (27%) of program storage space. Maximum is 290816 bytes.
Global variables use 18600 bytes (35%) of dynamic memory, leaving 33624 bytes for local variables. Maximum is 52224 bytes.

```

## Uploading Firmware.ino to your keyboard

Usage

```

upload.bat fqbn com_port

```

where `fbqn` is the Fully Qualified Board Name
and `com_port` is the serial port your keyboard presents itself when connected to your computer using a USB cable.

Examples:

```

upload.bat nrf52832 COM30

upload.bat feather52840 COM124

upload.bat pca10056 COM12

```

To get a list of the Serial ports, call the script without any options:

```

upload.bat

```

You will get an output similar to the following:

```

Serial Port not set.
Usage:
compile.bat fqbn com_port
fqbn options: nrf52832, pca10056, feather52840
com_port options:
Port   Type              Board Name                        FQBN                          Core
COM125 Serial Port (USB) Unknown
COM88  Serial Port (USB) Adafruit Feather nRF52840 Express adafruit:nrf52:feather52840   adafruit:nrf52
                         Particle Xenon                    adafruit:nrf52:particle_xenon adafruit:nrf52
                         Raytac MDBT50Q-RX Dongle          adafruit:nrf52:mdbt50qrx      adafruit:nrf52

```

When sucessfully uploading the firmware to the board, you will see output similar to this:

```

No new serial port detected.
Upgrading target on COM3 with DFU package C:\GIT\BlueMicro_BLE\.build\firmware\firmware.ino.zip. Flow control is disabled, Single bank, Touch disabled
########################################
########################################
########################################
########################################
#######################
Activating new firmware
Device programmed.

```

If you see the output similar to the following:

```

No new serial port detected.
Upgrading target on com4 with DFU package C:\GIT\BlueMicro_BLE\.build\firmware\firmware.ino.zip. Flow control is disabled, Single bank, Touch disabled
Timed out waiting for acknowledgement from device.

Failed to upgrade target. Error is: No data received on serial port. Not able to proceed.
Traceback (most recent call last):
  File "nordicsemi\__main__.py", line 294, in serial
  File "nordicsemi\dfu\dfu.py", line 235, in dfu_send_images
  File "nordicsemi\dfu\dfu.py", line 200, in _dfu_send_image
  File "nordicsemi\dfu\dfu_transport_serial.py", line 179, in send_start_dfu
  File "nordicsemi\dfu\dfu_transport_serial.py", line 243, in send_packet
  File "nordicsemi\dfu\dfu_transport_serial.py", line 282, in get_ack_nr
nordicsemi.exceptions.NordicSemiException: No data received on serial port. Not able to proceed.

Possible causes:
- Selected Bootloader version does not match the one on Bluefruit device.
    Please upgrade the Bootloader or select correct version in Tools->Bootloader.
- Baud rate must be 115200, Flow control must be off.
- Target is not in DFU mode. Ground DFU pin and RESET and release both to enter DFU mode.

```

Although the message is very long, it does contain useful information.

Make sure of the following:
| Error | Cause | Fix | Comments |
| ----- | ----- | --- | -------- |
| No data received on serial port | Serial Port does not respond to DFU commands | Double-reset | You have not pressed on reset twice (double-reset). Some boards (nrf52840 based) require a double-reset for the board to be put in DFU mode. |
| Serial port could not be opened on com3 | Serial Port not found | Double-reset | You have not pressed on reset twice (double-reset). Some boards (nrf52840 based) require a double-reset for the board to be put in DFU mode. |
| Serial port could not be opened on com4 | Serial Port not found | Double-reset & change port | You have pressed on reset twice (double-reset) but the port in DFU mode is different. |
| WriteFile failed  | You have compiled with an incorrect fqbn. | Recompile with the correct fqbn | Trying to upload firmware compiled for a nrf52832 to a nrf52840 will return this message. |
| error | cause | fix | comments |
