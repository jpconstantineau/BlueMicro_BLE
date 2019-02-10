#!/bin/bash
set -e
cd -- "$(dirname "$BASH_SOURCE")"

arduinoDataPath=$(cd ~/Library/Arduino15 && pwd)
nrf52PackagePath="$arduinoDataPath/packages/adafruit/hardware/nrf52"

nrfjprog --program ${nrf52PackagePath}/0.8.6/bin/bootloader/feather52/5.1.0/dual/feather52_bootloader_5.1.0_s132_dual.hex -f nrf52 --chiperase --reset
