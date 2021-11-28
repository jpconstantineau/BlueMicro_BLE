@echo off 
@echo Flashing Bootloader for BlueMicro840 - nRF52840 using jlink

set prefix=%localappdata%\Arduino15\packages\community_nrf52\hardware\nrf52


set search_cmd="dir /b %prefix%"
FOR /F "tokens=*" %%i IN (' %search_cmd% ') DO SET ver=%%i

set bootloaderprefix=%prefix%\%ver%\bootloader\bluemicro_nrf52840
@echo Found it here: %bootloaderprefix%

set searchbootloader_cmd="dir  %bootloaderprefix%\*.hex /b"
FOR /F "tokens=*" %%i IN (' %searchbootloader_cmd% ') DO SET bootloader=%%i

nrfjprog --family NRF52 --recover
nrfjprog --family NRF52 --eraseall
nrfjprog --family NRF52 --program %bootloaderprefix%\%bootloader%  --chiperase --reset