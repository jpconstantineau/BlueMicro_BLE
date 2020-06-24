@echo off 
@echo Flashing Bootloader for feather_nrf52832 - nrf52832 using jlink

if exist C:\Users\pierre\Documents\Arduino\hardware\Adafruit\Adafruit_nRF52_Arduino (
    set prefix=C:\Users\pierre\Documents\Arduino\hardware\Adafruit\Adafruit_nRF52_Arduino
) else (
    set prefix=%localappdata%\Arduino15\packages\adafruit\hardware\nrf52
)

if exist "C:\Program Files (x86)\Nordic Semiconductor\nrf5x\bin\nrfjprog.exe" (
    @echo Found nrfjprog.exe from Nordic Semiconductor
) else (
    @echo  nrfjprog.exe not found!
    @echo  you will need to download it from https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Command-Line-Tools/Download 
)

set search_cmd="dir /b %prefix%"
FOR /F "tokens=*" %%i IN (' %search_cmd% ') DO SET ver=%%i

set bootloaderprefix=%prefix%\%ver%\bootloader\feather_nrf52832
@echo Found it here: %bootloaderprefix%

set searchbootloader_cmd="dir  %bootloaderprefix%\*.hex /b"
FOR /F "tokens=*" %%i IN (' %searchbootloader_cmd% ') DO SET bootloader=%%i


nrfjprog --family NRF52 --recover
nrfjprog --family NRF52 --eraseall
nrfjprog --family NRF52 --program %bootloaderprefix%\%bootloader%  --chiperase --reset