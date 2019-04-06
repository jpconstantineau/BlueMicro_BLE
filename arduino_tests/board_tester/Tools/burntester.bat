	nrfjprog --family NRF52 --recover
	nrfjprog --family NRF52 --eraseall
	nrfjprog.exe --program %localappdata%\Arduino15\packages\adafruit\hardware\nrf52\0.9.3\bootloader\feather_nrf52832\feather_nrf52832_bootloader-0.2.6_s132_6.1.1.hex -f nrf52 --chiperase --reset 
	nrfjprog --family NRF52 --reset
    %localappdata%\Arduino15\packages\adafruit\hardware\nrf52\0.9.3\tools\adafruit-nrfutil\win32\adafruit-nrfutil.exe  --verbose dfu serial -pkg board_tester.ino.zip -p %1 -b 115200 