#!/bin/bash
set -e
cd -- "$(dirname "$BASH_SOURCE")"

arduinoDataPath=$(cd ~/Library/Arduino15 && pwd)
nrf52PackagePath="$arduinoDataPath/packages/adafruit/hardware/nrf52"

nrfjprog --program ${nrf52PackagePath}/0.11.1/bootloader/feather_nrf52832/feather_nrf52832_bootloader-0.2.11_s132_6.1.1.hex -f nrf52 --chiperase --reset
