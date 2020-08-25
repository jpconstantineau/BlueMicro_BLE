@echo off 
SET TARGET='%~dp0..\arduino-cli'
SET EXE="%~dp0..\arduino-cli\arduino-cli.exe"

SET buildPath="%~dp0..\.build"
SET buildCachePath="%~dp0..build-cache"
SET sourcePath="%~dp0..\firmware"

SET verbose = "-v"


IF "%1%"=="nrf52832" (
    SET fqbn="feather52832"
)

IF "%1%"=="pca10056" (
    SET fqbn="pca10056"
)

IF "%1%"=="feather52840" (
    SET fqbn="feather52840"
)

IF "%2%"=="" (
    ECHO Serial Port not set.
    GOTO :options
)


IF NOT DEFINED fqbn (
    ECHO ERROR FQBN not set.
    GOTO :options
)

IF EXIST %EXE% (
    %EXE% upload --fqbn adafruit:nrf52:%fqbn%  %sourcePath%/firmware.ino  --input-dir %buildPath%/firmware --port %2
) ELSE (
    ECHO arduino-cli not found. Run install.bat first, then run compile.bat
)
GOTO :end
:options
    ECHO Usage:
    ECHO compile.bat fqbn com_port
    ECHO fqbn options: nrf52832, pca10056, feather52840
    ECHO com_port options:
    %EXE% board list

:end