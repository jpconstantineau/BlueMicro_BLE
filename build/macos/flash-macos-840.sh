#!/bin/bash

printf "This script must be run with a parameter indicating the serial port your controller is connected to\n"
printf "./flash-macos-840.sh /dev/cu.usbmodem2101  \n"

arduinoDataPath=$(cd ~/Library/Arduino15 && pwd)
nrf52PackagePath="$arduinoDataPath/packages/adafruit/hardware/nrf52"
scriptPath="$(dirname "$BASH_SOURCE")"
blueMicroPath=$(cd $scriptPath/../.. && pwd)
outputPath="${blueMicroPath}/output"
buildPath="${outputPath}/.build"

printf "\n"
printf "Checking file locations\n"
printf -- "-----------------------------------\n"


printf "Arduino Data Location... "
if [ -d "$arduinoDataPath" ]
then
   printf "${GREEN}OK${NC}\n"
else
   printf "${RED}Failed${NC}\n"
   printf "\n"
   printf "Could not find Arduino Data path\n"
   printf "Expected data in ${arduinoDataPath}\n\n"
   exit 1
fi

printf "Adafruit nRF52 Package... "
if [ -d "$nrf52PackagePath" ]
then
   printf "${GREEN}OK${NC}\n"
else
   printf "${RED}Failed${NC}\n"
   printf "\n"
   printf "Could not find Adafruit nRF52 Package\n"
   printf "Follow the installation instructions at https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/arduino-bsp-setup\n\n"
   exit 1
fi

printf "Build Location... "
if [ -d "$buildPath" ]
then
   printf "${GREEN}OK${NC}\n"
else
   printf "${RED}Failed${NC}\n"
   printf "\n"
   printf "Could not find build path\n"
   printf "Expected data in ${buildPath}\n\n"
   exit 1
fi

## adafruit-nrfutil --verbose dfu serial -pkg ../../output/$1 -b 115200 -p $2

$nrf52PackagePath/0.21.0/tools/adafruit-nrfutil/macos/adafruit-nrfutil --verbose dfu serial -pkg $buildPath/firmware.ino.zip  -b 115200 --singlebank -p $1