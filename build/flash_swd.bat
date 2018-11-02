@echo off

if ["%~1"]==[""] goto usage
if ["%~2"]==[""] goto usage
if ["%~3"]==[""] goto usage

if exist ..\output\%~1\%~1-%~2-%~3.hex (
	goto flash
) else (
	@echo Compiled hex not found: running build script first.
	powershell ./build-windows.ps1 %~1 %~2 %~3

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
	nrfjprog --family NRF52 --program %localappdata%\Arduino15\packages\adafruit\hardware\nrf52\0.8.6/bin/bootloader/feather52/5.1.0/dual/feather52_bootloader_5.1.0_s132_dual.hex
	nrfjprog --family NRF52 --program ..\output\%~1\%~1-%~2-%~3.hex
	nrfjprog --family NRF52 --program app_valid_setting_apply_nRF52832.hex
	nrfjprog --family NRF52 --reset

:usage
	@echo Usage: flash_swd keyboard keymap target


