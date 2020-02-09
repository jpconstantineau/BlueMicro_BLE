IF EXIST C:\Users\pierre\Documents\Arduino\hardware\Adafruit\Adafruit_nRF52_Arduino (
set nrf52librarypath=C:\Users\pierre\Documents\Arduino\hardware\Adafruit\Adafruit_nRF52_Arduino
) ELSE (
set nrf52librarypath=%localappdata%\Arduino15\packages\adafruit\hardware\nrf52\0.18.0
)

nrfjprog --family NRF52 --program %nrf52librarypath%/bootloader\feather_nrf52832\feather_nrf52832_bootloader-0.3.0_s132_6.1.1.hex -f nrf52 --chiperase --reset 