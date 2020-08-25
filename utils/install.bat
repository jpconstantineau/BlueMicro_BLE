@echo off
SET URL='https://downloads.arduino.cc/arduino-cli/arduino-cli_latest_Windows_64bit.zip'
SET OUTPUT='%~dp0..\arduino-cli\arduino-cli_latest_Windows_64bit.zip'
SET TARGET='%~dp0..\arduino-cli'

del /Q %~dp0\..\arduino-cli 
mkdir %~dp0\..\arduino-cli 
echo "Downloading Arduino-cli to %OUTPUT%"
powershell -c "(New-Object Net.WebClient).DownloadFile(%URL%,%OUTPUT%)"
echo "Uncompressing Arduino-cli zip"
powershell -c "Expand-Archive -Path %OUTPUT%  -DestinationPath %TARGET%"
echo "Removing Arduino-cli zip"
del %~dp0..\arduino-cli\arduino-cli_latest_Windows_64bit.zip

echo "Copying Arduino-cli config"
copy "%~dp0arduino-cli.yaml" %~dp0..\arduino-cli

SET EXE="%~dp0..\arduino-cli\arduino-cli.exe"
%EXE% core update-index
%EXE% core upgrade
%EXE% core search nrf52
%EXE% core install adafruit:nrf52
%EXE% version