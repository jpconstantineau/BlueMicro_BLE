@echo off 
@echo Flashing Bootloader for pca10056 - nRF52840

IF EXIST C:\Users\pierre\Documents\Arduino\hardware\Adafruit\Adafruit_nRF52_Arduino (
set prefix=C:\Users\pierre\Documents\Arduino\hardware\Adafruit\Adafruit_nRF52_Arduino
) ELSE (
set prefix=%localappdata%\Arduino15\packages\adafruit\hardware\nrf52
)

IF EXIST C:\Program Files (x86)\Nordic Semiconductor\nrf5x\bin (
echo Found nrfjprog.exe from Nordic Semiconductor
) ELSE (
echo  nrfjprog.exe not found!
echo  you will need to download it from https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Command-Line-Tools/Download 
)

set search_cmd="dir /b %prefix%"
FOR /F "tokens=*" %%i IN (' %search_cmd% ') DO SET ver=%%i

set bootloaderprefix=%prefix%\%ver%\bootloader\pca10056
@echo Found it here: %bootloaderprefix%

set searchbootloader_cmd="dir  %bootloaderprefix%\*.hex /b"
FOR /F "tokens=*" %%i IN (' %searchbootloader_cmd% ') DO SET bootloader=%%i

nrfjprog --family NRF52 --recover
nrfjprog --family NRF52 --eraseall
nrfjprog --family NRF52 --program %bootloaderprefix%\%bootloader%  --chiperase --reset