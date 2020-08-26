# Arduino-cli Utility Scripts

These scripts only compile and flash the keyboard files in the root firmware folder.
These work the same as if you were opening the firmware.ino file from the Arduino IDE.

## Installation or Arduino-cli

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

## Uploading Firmware.ino to your keyboard

Usage

```

compile.bat fqbn com_port

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