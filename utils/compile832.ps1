$target = "$PSScriptRoot\..\arduino-cli"
$exe = "$target\arduino-cli.exe"

$buildPath = "$PSScriptRoot\..\.build"
$buildCachePath = "$PSScriptRoot\..\.build-cache"
$sourcePath = "$PSScriptRoot\..\firmware"

## cmdCompile832="/arduino-cli compile -v --fqbn adafruit:nrf52:feather52832 --build-path $buildPath --build-cache-path $buildCachePath $sourcePath/firmware.ino  -o $buildPath/firmware"
## cmdCompile840="/arduino-cli compile -v --fqbn adafruit:nrf52:pca10056:softdevice=s140v6,debug=l0 --build-path $buildPath --build-cache-path $buildCachePath $sourcePath/firmware.ino  -o $buildPath/firmware"

& $exe compile -v --fqbn adafruit:nrf52:feather52832 --build-path $buildPath --build-cache-path $buildCachePath $sourcePath/firmware.ino  -o $buildPath/firmware