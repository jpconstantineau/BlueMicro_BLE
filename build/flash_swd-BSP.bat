@echo off

if ["%~1"]==[""] goto usage
if ["%~2"]==[""] goto usage
if ["%~3"]==[""] goto usage

if exist ..\output\%~1\%~1-%~2-%~3.hex (
	goto flash
) else (
	@echo Compiled hex not found: running build script first.
	powershell ./build-windows-BSP.ps1 %~1 %~2 %~3

	if exist ..\output\%~1\%~1-%~2-%~3.hex (
		goto flash
	) else (
		@echo Compiled hex still not found: do you have the right keyboard, keymap and target?
		@echo %~1 %~2 %~3
		goto usage
	)

    	goto :eof
)


:flash
   	echo Flashing %~1-%~2-%~3
	nrfjprog --family NRF52 --recover
	nrfjprog --family NRF52 --eraseall
	nrfjprog --family NRF52 --program C:\Users\pierre\Documents\Arduino\hardware\Adafruit\Adafruit_nRF52_Arduino/bootloader/feather_nrf52832/6.1.1r0/feather_nrf52832_bootloader_s132_6.1.1r0.hex
	nrfjprog --family NRF52 --program ..\output\%~1\%~1-%~2-%~3.hex
	nrfjprog --family NRF52 --program app_valid_setting_apply_nRF52832.hex
	nrfjprog --family NRF52 --reset

:usage
	@echo Usage: flash_swd keyboard keymap target


