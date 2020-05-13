	nrfjprog --family NRF52 --recover
	nrfjprog --family NRF52 --eraseall
	nrfjprog --family NRF52 --program %localappdata%\Arduino15\packages\adafruit\hardware\nrf52\0.14.6\bootloader\feather_nrf52832\feather_nrf52832_bootloader-0.2.13_s132_6.1.1.hex -f nrf52 --chiperase --reset 
%localappdata%\Arduino15\packages\adafruit\hardware\nrf52\0.13.0\tools\adafruit-nrfutil\win32\adafruit-nrfutil.exe  --verbose dfu serial -pkg board_tester.ino.zip -p %1 -b 115200 --singlebank