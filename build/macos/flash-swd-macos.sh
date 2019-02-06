#!/bin/bash
set -e
cd -- "$(dirname "$BASH_SOURCE")"

usage() {
    printf "Usage: ${0} keyboard:keymap:target\n";
    exit;
}

parameterMissing() {
    printf "${RED}Failed${NC}\n"
    printf "${1} parameter missing\n";
    usage
}

flash() {
    printf "Flashing ${keyboard}:${keymap}:${target}\n\n"
    nrfjprog --family NRF52 --recover
	nrfjprog --family NRF52 --eraseall
	nrfjprog --family NRF52 --program ${nrf52PackagePath}/0.8.6/bin/bootloader/feather52/5.1.0/dual/feather52_bootloader_5.1.0_s132_dual.hex
	nrfjprog --family NRF52 --program ../../output/${keyboard}/${keyboard}-${keymap}-${target}.hex
	nrfjprog --family NRF52 --program app_valid_setting_apply_nRF52832.hex
	nrfjprog --family NRF52 --reset
}

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

args=$1
splitArgs=(${args//:/ })
arduinoPath="/Applications/Arduino.app"
arduinoDataPath=$(cd ~/Library/Arduino15 && pwd)
nrf52PackagePath="$arduinoDataPath/packages/adafruit/hardware/nrf52"

keyboard=${splitArgs[0]}
keymap=${splitArgs[1]}
target=${splitArgs[2]}

if [ "$keyboard" == "" ]; then parameterMissing keyboard; exit; fi
if [ "$keymap" == "" ]; then parameterMissing keymap; exit; fi
if [ "$target" == "" ]; then parameterMissing target; exit; fi

if [ -e ../../output/${keyboard}/${keyboard}-${keymap}-${target}.hex ]; then
    flash
else
    printf "Compiled hex not found: running build script first."
    ./build-macos ${keyboard} ${keymap} ${target}
    if [ -e ../../output/${keyboard}/${keyboard}-${keymap}-${target}.hex ]; then
        flash
    else
        printf "Compiled hex still not found: do you have the right keyboard, keymap and target?\n"
        printf "${keyboard}:${keymap}:${target}"
        usage
        exit
    fi

fi
