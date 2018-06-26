#!/bin/bash

arduinoPath="/Applications/Arduino.app"
arduinoDataPath=$(cd ~/Library/Arduino15 && pwd)
nrf52PackagePath="$arduinoDataPath/packages/adafruit/hardware/nrf52"

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

printf "\n"
printf -- "-----------------------------------------------------------------------\n"
printf "   Arduino ${BLUE}BlueMicro${NC} Build Script\n"
printf -- "-----------------------------------------------------------------------\n"

printf "\n"
printf "Building all:all:all\n"

printf "\n"
printf "Checking file locations\n"
printf -- "-----------------------------------\n"

printf "Arduino Installation... "
if [ -d "$arduinoPath" ]
then
   printf "${GREEN}OK${NC}\n"
else
   printf "${RED}Failed${NC}\n"
   printf "\n"
   printf "Could not find Arduino installation\n"
   printf "Donwload and install to the ${arduinoPath} path\n\n"
   exit 1
fi

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
printf "\n"
