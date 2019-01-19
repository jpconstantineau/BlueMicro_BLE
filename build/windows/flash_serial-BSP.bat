@echo off

if ["%~1"]==[""] goto usage
if ["%~2"]==[""] goto usage
if ["%~3"]==[""] goto usage
if ["%~4"]==[""] goto usage

if exist ..\..\output\%~1\%~1-%~2-%~3.zip (
	goto flash
) else (
	@echo Compiled zip package not found: running build script first.
	powershell ./build-windows-BSP.ps1 %~1 %~2 %~3

	if exist ..\..\output\%~1\%~1-%~2-%~3.zip (
		goto flash
	) else (
		@echo Compiled zip package still not found: do you have the right keyboard, keymap and target?
		@echo %~1 %~2 %~3
		goto usage
	)

    	goto :eof
)


:flash
   	echo Flashing %~1-%~2-%~3 over serial port %~4
	C:\Users\pierre\Documents\Arduino\hardware\Adafruit\Adafruit_nRF52_Arduino\tools\adafruit-nrfutil\win32\adafruit-nrfutil.exe --verbose dfu serial -pkg ..\..\output\%~1\%~1-%~2-%~3.zip -p %~4 -b 115200 --singlebank


:usage
	@echo Usage: flash_serial keyboard keymap target serial-port





