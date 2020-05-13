SET TARGET='%~dp0..\arduino-cli'
SET EXE="%~dp0..\arduino-cli\arduino-cli.exe"

SET buildPath="%~dp0..\.build"
SET buildCachePath="%~dp0..build-cache"
SET sourcePath="%~dp0..\firmware"

rem cmdCompile832="/arduino-cli compile -v --fqbn adafruit:nrf52:feather52832 --build-path $buildPath --build-cache-path $buildCachePath $sourcePath/firmware.ino  -o $buildPath/firmware"
rem cmdCompile840="/arduino-cli compile -v --fqbn adafruit:nrf52:pca10056:softdevice=s140v6,debug=l0 --build-path $buildPath --build-cache-path $buildCachePath $sourcePath/firmware.ino  -o $buildPath/firmware"

%EXE% compile -v --fqbn adafruit:nrf52:feather52832 --build-path %buildPath% --build-cache-path %buildCachePath% %sourcePath%/firmware.ino  -o %buildPath%/firmware
%EXE% compile -v --fqbn adafruit:nrf52:pca10056:softdevice=s140v6,debug=l0  --build-path %buildPath% --build-cache-path %buildCachePath% %sourcePath%/firmware.ino  -o %buildPath%/firmware