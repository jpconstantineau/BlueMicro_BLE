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

#replace this variable with path to your avr installation


blueMicroPath=$(cd $scriptPath/../.. && pwd)
firmwarePath="${blueMicroPath}/firmware"
outputPath="${blueMicroPath}/output"
outputTempPath="/tmp"
buildPath="${outputTempPath}/.build"
buildCachePath="${outputTempPath}/.build-cache"

sourcePath="${outputTempPath}/.source/firmware"
keyboardsPath="${firmwarePath}/keyboards"

echo $keyboardsPath

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

  # keymapFile="$keyboardsPath/$keyboard/keymaps/$keymap/keymap.h"
  # keymapcppFile="$keyboardsPath/$keyboard/keymaps/$keymap/keymap.cpp"
  # configFile="$keyboardsPath/$keyboard/$target/keyboard_config.h"

  # cp -f $keymapFile $sourcePath/
  # cp -f $keymapcppFile $sourcePath/
  # cp -f $configFile $sourcePath/

   if $continueOnError; then
      set +e
   fi

   #Need to sleep between compile calls else arduino-builder does not recognise changes
   #sleep 2

   #Compile

   cmduf2conv840="python /uf2conv.py -f 0xADA52840 -c -o  $buildPath/firmware.uf2   $buildPath/firmware.hex "
#echo $cmduf2conv840
cp -f $outputPath/$keyboard/$keyboard-$keymap-$target.nrf52840.hex $buildPath/firmware.hex 

    if $verbose; then 
      $cmduf2conv840
    else
       $cmduf2conv840 > /dev/null
    fi

   (($? != 0)) && failed=true || failed=false

   set -e
   
   if $failed; then
     failedBuilds840=$((failedBuilds840+1))
     printf "${RED}Failed${NC}\n"
   else
   
     cp -f $buildPath/firmware.uf2 $outputPath/$keyboard/$keyboard-$keymap-$target.nrf52840.uf2

     successfulBuilds840=$((successfulBuilds840+1))
     printf "${GREEN}OK${NC}\n"
   fi
}

printf "\n"
printf -- "-----------------------------------------------------------------------\n"
printf "   Arduino ${BLUE}BlueMicro${NC} UF2 Script\n"
printf -- "-----------------------------------------------------------------------\n"

if [ -z "$boardParam" ]; then

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
printf "Converting HEX to UF2 keyboard:keymap:target  nRF52840\n"
printf -- "----------------------------------------------------------\n"

rm -rf $sourcePath
mkdir -p $sourcePath
cp -r $firmwarePath/* $sourcePath
printf "sourcepath c \n" 
ls $sourcePath
for keyboard in $sourcePath/keyboards/*/
do
printf "keyboard $keyboard \n"
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

if ((successfulBuilds840 == 0)) && ((failedBuilds840 == 0)); then
   printf "Did not find anything to build for $selectedKeyboard:$selectedKeymap:$selectedTarget\n"
fi

printf "\n"

printf "nRF52840 Successful: ${successfulBuilds840} Failed: ${failedBuilds840}\n"
printf "\n"
printf "Binaries can be found in ${outputPath}\n"
printf "\n"

if ((failedBuilds != 0 || successfulBuilds == 0)); then
   exit 1
fi

