IF EXIST C:\Users\pierre\Documents\Arduino\hardware\Adafruit\Adafruit_nRF52_Arduino (
set nrf52librarypath=C:\Users\pierre\Documents\Arduino\hardware\Adafruit\Adafruit_nRF52_Arduino
) ELSE (
set nrf52librarypath=%localappdata%\Arduino15\packages\adafruit\hardware\nrf52
)

@echo off 
@echo Flashing Bootloader for pca10056 - nRF52840

rem set prefix=%localappdata%\Arduino15\packages\adafruit\hardware\nrf52
set prefix=%nrf52librarypath%
set search_cmd="dir /b %prefix%"
FOR /F "tokens=*" %%i IN (' %search_cmd% ') DO SET ver=%%i

set bootloaderprefix=%prefix%\%ver%\bootloader\feather_nrf52832
@echo Found it here: %bootloaderprefix%

set searchbootloader_cmd="dir  %bootloaderprefix%\*.hex /b"
FOR /F "tokens=*" %%i IN (' %searchbootloader_cmd% ') DO SET bootloader=%%i


nrfjprog --family NRF52 --recover
nrfjprog --family NRF52 --eraseall
nrfjprog --family NRF52 --program %bootloaderprefix%\%bootloader%  --chiperase --reset
rem nrfjprog --family NRF52 --program %nrf52librarypath%/bootloader\feather_nrf52832\feather_nrf52832_bootloader-0.3.0_s132_6.1.1.hex -f nrf52 --chiperase --reset 