#!/bin/bash
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
scriptPath="$(dirname "$BASH_SOURCE")"
blueMicroPath=$(cd $scriptPath/../.. && pwd)
firmwarePath="${blueMicroPath}/firmware"
outputPath="${blueMicroPath}/output"
outputTempPath="/tmp"
buildPath="${outputTempPath}/.build"
buildCachePath="${outputTempPath}/.build-cache"

sourcePath="${outputTempPath}/.source/firmware"
keyboardsPath="${sourcePath}/keyboards"

successfulBuilds=0
failedBuilds=0


RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

arduino_compile() {
   local keyboard=$1
   local keymap=$2
   local target=$3
   local fqbn=$4
   local hardware=$5

   printf "$keyboard:$keymap:$target:$fqbn:$hardware"

   keymapFile="$keyboardsPath/$keyboard/keymaps/$keymap/keymap.h"
   keymapcppFile="$keyboardsPath/$keyboard/keymaps/$keymap/keymap.cpp"
   configFile="$keyboardsPath/$keyboard/config/$target/keyboard_config.h"
   hardwareFile="$keyboardsPath/$keyboard/hardware/$fqbn/$hardware/hardware_config.h"

   cp -f $keymapFile $sourcePath/
   cp -f $keymapcppFile $sourcePath/
   cp -f $configFile $sourcePath/
   cp -f $hardwareFile $sourcePath/

   if $continueOnError; then
      set +e
   fi

   #Need to sleep between compile calls else arduino-builder does not recognise changes
   #sleep 2

   #Compile

   cmdCompile="arduino-cli compile -v --fqbn adafruit:nrf52:$fqbn --build-path $buildPath --build-cache-path $buildCachePath $sourcePath/firmware.ino"
 
    if $verbose; then 
      $cmdCompile
    else
       $cmdCompile > /dev/null
    fi

   (($? != 0)) && failed=true || failed=false

   set -e
   
   if $failed; then
     failedBuilds=$((failedBuilds+1))
     printf "${RED}Failed${NC} "
   else
     [[ -d $outputPath/$keyboard ]] || mkdir $outputPath/$keyboard
   
     cp -f $buildPath/firmware.ino.zip $outputPath/$keyboard/$keyboard-$fqbn-$hardware-$keymap-$target.zip
     cp -f $buildPath/firmware.ino.hex $outputPath/$keyboard/$keyboard-$fqbn-$hardware-$keymap-$target.hex

     successfulBuilds=$((successfulBuilds+1))
     printf "${GREEN}OK${NC} "
   fi
}

printf "\n"
printf -- "-----------------------------------------------------------------------\n"
printf "   Arduino ${BLUE}BlueMicro${NC} Build Script\n"
printf -- "-----------------------------------------------------------------------\n"

if [ -z "$boardParam" ]; then

   printf "\n"
   printf "This script can be run with paramters\n"
   printf "./build-macos [-v] [-c] keyboard:keymap:target:fqbn:hardware\n"

   selectedKeyboard="all"
   selectedKeymap="all"
   selectedTarget="all"
   selectedFqbn="all"
   selectedHardware="all"
   
   printf "\n"
   read -p "Keyboard name (eg ErgoTravel) [all]: " selectedKeyboard
   selectedKeyboard=${selectedKeyboard:-all}

   if [ "$selectedKeyboard" != "all" ]; then
      read -p "Keymap name (eg default) [all]: " selectedKeymap
      selectedKeymap=${selectedKeymap:-all}

      if [ "$selectedKeymap" != "all" ]; then
         read -p "Target name (eg left / right / single) [all]: " selectedTarget
         selectedTarget=${selectedTarget:-all}

         if [ "$selectedFqbn" != "all" ]; then
            read -p "fqbn name [all]: " selectedFqbn
            selectedFqbn=${selectedFqbn:-all}

            if [ "$selectedHardware" != "all" ]; then
               read -p "hardware name [all]: " selectedHardware
               selectedHardware=${selectedHardware:-all}
            fi
         fi
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
   
   selectedHardware="${boardParamSplit[3]}"
   if [ -z "$selectedHardware" ]; then
      selectedHardware="all"
   fi

   selectedFqbn="${boardParamSplit[4]}"
   if [ -z "$selectedFqbn" ]; then
      selectedFqbn="all"
   fi

fi

printf "\n"
printf "Building $selectedKeyboard:$selectedKeymap:$selectedTarget:$selectedFqbn:$selectedHardware\n"


[[ -d $outputPath ]] || mkdir $outputPath
[[ -d $buildPath ]] || mkdir $buildPath
[[ -d $buildCachePath ]] || mkdir $buildCachePath

printf "\n"
printf "Compiling keyboard:keymap:target:fqbn:hardware\n"
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

   fqbns=()
   for fqbn in $sourcePath/keyboards/$keyboard/hardware/*/
   do
      fqbn=${fqbn%*/}
      fqbn=${fqbn##*/}

      if [ "$selectedFqbn" != "all" ] && [ "$selectedFqbn" != "$fqbn" ]; then
         continue
      fi

      fqbns+=($fqbn)
   done

   targets=()
   for target in $sourcePath/keyboards/$keyboard/config/*/
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
         for fqbn in "${fqbns[@]}"; do
               hardwares=()
               for hardware in $sourcePath/keyboards/$keyboard/hardware/$fqbn/*/
               do
                  hardware=${hardware%*/}
                  hardware=${hardware##*/}

                  if [ "$selectedHardware" != "all" ] && [ "$selectedHardware" != "$hardware" ]; then
                     continue
                  fi
                  hardwares+=($hardware)
               done
               for hardware in "${hardwares[@]}"; do
                  arduino_compile $keyboard $keymap $target $fqbn $hardware
               done
         done
      done
   done
done

if ((successfulBuilds == 0)) && ((failedBuilds == 0)); then
   printf "Did not find anything to build for $selectedKeyboard:$selectedKeymap:$selectedTarget:$selectedFqbn:$selectedHardware\n"
fi

printf "\n"
printf "Successful: ${successfulBuilds} Failed: ${failedBuilds}\n"
printf "\n"
printf "Binaries can be found in ${outputPath}\n"
printf "\n"

if ((failedBuilds != 0 || successfulBuilds == 0)); then
   exit 1
fi

