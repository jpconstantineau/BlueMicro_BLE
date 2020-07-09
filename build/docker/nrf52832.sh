#!/bin/bash
# Called by jenkins docker job BlueMicro_BLE-develop-Docker-nrf52832 on docker:8080
# Called by jenkins docker job BlueMicro_BLE-master-Docker-nrf52832 on docker:8080

set -e
cd -- "$(dirname "$BASH_SOURCE")"

verbose=false
continueOnError=false

while getopts ":hvc" option; do
  case $option in
    h) echo "usage: $0 [-h] [-v] [-c] keyboard:keymap:target"; exit ;;
    v) verbose=true ;;
    c) continueOnError=true ;;
    ?) echo "error: option -$OPTARG is not implemented"; exit ;;
  esac
done

shift $(($OPTIND - 1))
boardParam=$1

arduinoPath="/usr/share/arduino"
arduinoDataPath=$(cd ~/.arduino15 & pwd)
nrf52PackagePath="/home/$USER/.arduino15/packages/adafruit/hardware/nrf52"

scriptPath="$(dirname "$BASH_SOURCE")"

#replace this variable with path to your avr installation
arduinoAvrPath="$arduinoPath/hardware/arduino/avr"

blueMicroPath=$(cd $scriptPath/../.. && pwd)
firmwarePath="${blueMicroPath}/firmware"
outputPath="${blueMicroPath}/output"
outputTempPath="/tmp"
buildPath="${outputTempPath}/.build"
buildCachePath="${outputTempPath}/.build-cache"

sourcePath="${outputTempPath}/.source/firmware"
keyboardsPath="${sourcePath}/keyboards"

successfulBuilds832=0
failedBuilds832=0
successfulBuilds840=0
failedBuilds840=0

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

arduino_compile() {
   local keyboard=$1
   local keymap=$2
   local target=$3

   printf "$keyboard:$keymap:$target... "

   keymapFile="$keyboardsPath/$keyboard/keymaps/$keymap/keymap.h"
   keymapcppFile="$keyboardsPath/$keyboard/keymaps/$keymap/keymap.cpp"
   configFile="$keyboardsPath/$keyboard/$target/keyboard_config.h"

   cp -f $keymapFile $sourcePath/
   cp -f $keymapcppFile $sourcePath/
   cp -f $configFile $sourcePath/

   if $continueOnError; then
      set +e
   fi



   #Compile
   cmdCompile832="/arduino-cli compile -v --fqbn adafruit:nrf52:feather52832 --build-path $buildPath --build-cache-path $buildCachePath $sourcePath/firmware.ino  -o $buildPath/firmware"
   cmdCompile840="/arduino-cli compile -v --fqbn adafruit:nrf52:feather52840 --build-path $buildPath --build-cache-path $buildCachePath $sourcePath/firmware.ino  -o $buildPath/firmware"
    if $verbose; then 
      $cmdCompile832
    else
       $cmdCompile832 > /dev/null
    fi

   (($? != 0)) && failed=true || failed=false

   set -e
   
   if $failed; then
     failedBuilds832=$((failedBuilds832+1))
     printf "${RED}Failed${NC} \n"
   else
     [[ -d $outputPath/$keyboard ]] || mkdir $outputPath/$keyboard

     cp -f $buildPath/firmware.ino.zip $outputPath/$keyboard/$keyboard-$keymap-$target.nrf52832.zip
     cp -f $buildPath/firmware.ino.hex $outputPath/$keyboard/$keyboard-$keymap-$target.nrf52832.hex

     successfulBuilds832=$((successfulBuilds832+1))
     printf "${GREEN}OK${NC} \n"
   fi
      #Need to sleep between compile calls else arduino-builder does not recognise changes
   #sleep 2
}

printf "\n"
printf -- "-----------------------------------------------------------------------\n"
printf "   Arduino ${BLUE}BlueMicro${NC} Build Script\n"
printf -- "-----------------------------------------------------------------------\n"

if [ -z "$boardParam" ]; then

   printf "\n"
   printf "This script can be run with paramters\n"
   printf "./build-macos [-v] [-c] keyboard:keymap:target\n"

   selectedKeyboard="all"
   selectedKeymap="all"
   selectedTarget="all"
   
   printf "\n"
   read -p "Keyboard name (eg ErgoTravel) [all]: " selectedKeyboard
   selectedKeyboard=${selectedKeyboard:-all}

   if [ "$selectedKeyboard" != "all" ]; then
      read -p "Keymap name (eg default) [all]: " selectedKeymap
      selectedKeymap=${selectedKeymap:-all}

      if [ "$selectedKeymap" != "all" ]; then
         read -p "Target name (eg left / right / master) [all]: " selectedTarget
         selectedTarget=${selectedTarget:-all}
      fi
   fi

else

   IFS=':' read -r -a boardParamSplit <<< "$boardParam"
   selectedKeyboard="${boardParamSplit[0]}"
   if [ -z "$selectedKeyboard" ]; then
      selectedKeyboard="all"
   fi

   selectedKeymap="${boardParamSplit[1]}"
   if [ -z "$selectedKeymap" ]; then
      selectedKeymap="all"
   fi

   selectedTarget="${boardParamSplit[2]}"
   if [ -z "$selectedTarget" ]; then
      selectedTarget="all"
   fi

fi

printf "\n"
printf "Building $selectedKeyboard:$selectedKeymap:$selectedTarget\n"


[[ -d $outputPath ]] || mkdir $outputPath
[[ -d $buildPath ]] || mkdir $buildPath
[[ -d $buildCachePath ]] || mkdir $buildCachePath

printf "\n"
printf "Compiling keyboard:keymap:target  nRF52832 \n"
printf -- "-----------------------------------------------------\n"

rm -rf $sourcePath
mkdir -p $sourcePath
cp -r $firmwarePath/* $sourcePath

for keyboard in $sourcePath/keyboards/*/
do
   keyboard=${keyboard%*/}
   keyboard=${keyboard##*/}

   if [ "$selectedKeyboard" != "all" ] && [ "$selectedKeyboard" != "$keyboard" ]; then
      continue
   fi

   keymaps=()
   for keymap in $sourcePath/keyboards/$keyboard/keymaps/*/
   do
      keymap=${keymap%*/}
      keymap=${keymap##*/}

      if [ "$selectedKeymap" != "all" ] && [ "$selectedKeymap" != "$keymap" ]; then
         continue
      fi

      keymaps+=($keymap)
   done

   targets=()
   for target in $sourcePath/keyboards/$keyboard/*/
   do
      target=${target%*/}
      target=${target##*/}

      if [[ "$target" == "keymaps" ]]; then
         continue
      fi

      if [ "$selectedTarget" != "all" ] && [ "$selectedTarget" != "$target" ]; then
         continue
      fi

      targets+=($target)
   done
   
   for keymap in "${keymaps[@]}"; do
      for target in "${targets[@]}"; do
         arduino_compile $keyboard $keymap $target
      done
   done
done

if ((successfulBuilds832 == 0)) && ((failedBuilds832 == 0)); then
   printf "Did not find anything to build for $selectedKeyboard:$selectedKeymap:$selectedTarget\n"
fi

printf "\n"
printf "nRF52832 Successful: ${successfulBuilds832} Failed: ${failedBuilds832}\n"
printf "\n"
printf "Binaries can be found in ${outputPath}\n"
printf "\n"

if ((failedBuilds832 != 0 || successfulBuilds832 == 0)); then
   exit 1
fi

