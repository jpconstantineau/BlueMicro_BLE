#!/bin/bash
set -e
cd -- "$(dirname "$BASH_SOURCE")"

usage() {
    printf "Usage: ${0} keyboard:keymap:target /path/to/serial/device\n";
    printf "If you need to find your serial device, try running: ls /dev/cu.*"
    exit;
}

parameterMissing() {
    printf "${RED}Failed${NC}\n"
    printf "${1} parameter missing\n";
    usage
}

flash() {
    printf "Flashing ${keyboard}:${keymap}:${target} over serial port\n\n"
    nrfutil --verbose dfu serial -pkg ../output/${keyboard}/${keyboard}-${keymap}-${target}.zip -p ${port} -b 115200
}

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

args=$1
port=$2
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
if [ "$port" == "" ]; then parameterMissing port; exit; fi

if [ -e ../output/${keyboard}/${keyboard}-${keymap}-${target}.zip ]; then
    flash
else
    printf "Compiled zip not found: running build script first."
    ./build-macos ${keyboard} ${keymap} ${target}
    if [ -e ../output/${keyboard}/${keyboard}-${keymap}-${target}.zip ]; then
        flash
    else
        printf "Compiled zip still not found: do you have the right keyboard, keymap and target?\n"
        printf "${keyboard}:${keymap}:${target}"
        usage
        exit
    fi

fi
