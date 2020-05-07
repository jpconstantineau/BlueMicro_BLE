	nrfjprog --family NRF52 --recover
	nrfjprog --family NRF52 --eraseall
	nrfjprog --family NRF52 --program %localappdata%\Arduino15\packages\adafruit\hardware\nrf52\0.13.0\bootloader\pca10056\pca10056_bootloader-0.2.12_s140_6.1.1.hex 
