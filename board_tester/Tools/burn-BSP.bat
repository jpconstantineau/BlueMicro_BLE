	nrfjprog --family NRF52 --recover
	nrfjprog --family NRF52 --eraseall
	nrfjprog --family NRF52 --program C:\Users\pierre\Documents\Arduino\hardware\Adafruit\Adafruit_nRF52_Arduino/bootloader/feather_nrf52832/6.1.1r0/feather_nrf52832_bootloader_s132_6.1.1r0.hex
	nrfjprog --family NRF52 --reset
C:\Users\pierre\Documents\Arduino\hardware\Adafruit\Adafruit_nRF52_Arduino\tools\adafruit-nrfutil\win32\adafruit-nrfutil.exe --verbose dfu serial -pkg board_tester.ino.zip -p %1 -b 115200 