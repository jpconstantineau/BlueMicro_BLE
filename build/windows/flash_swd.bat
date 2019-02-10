@echo off

if ["%~1"]==[""] goto usage
if ["%~2"]==[""] goto usage
if ["%~3"]==[""] goto usage

if exist ..\..\output\%~1\%~1-%~2-%~3.hex (
	goto flash
) else (
	@echo Compiled hex not found: running build script first.
	powershell ./build-windows.ps1 %~1 %~2 %~3

	if exist ..\..\output\%~1\%~1-%~2-%~3.hex (
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
	nrfjprog --family NRF52 --program %localappdata%\Arduino15\packages\adafruit\hardware\nrf52\0.9.3\bootloader\feather_nrf52832\feather_nrf52832_bootloader-0.2.6_s132_6.1.1.hex
	nrfjprog --family NRF52 --program ..\..\output\%~1\%~1-%~2-%~3.hex
	nrfjprog --family NRF52 --program ..\app_valid_setting_apply_nRF52832.hex
	nrfjprog --family NRF52 --reset

:usage
	@echo Usage: flash_swd keyboard keymap target


