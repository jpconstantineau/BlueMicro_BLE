@echo off

if ["%~1"]==[""] goto usage
if ["%~2"]==[""] goto usage
if ["%~3"]==[""] goto usage

if exist ..\..\output\%~1\%~1-%~2-%~3.hex (
	goto flash
) else (
	@echo Compiled hex not found: running build script first.
	powershell ./build.ps1 %~1 %~2 %~3

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
   	echo Flashing Bootloader before %~1-%~2-%~3
	nrfjprog --family NRF52 --recover
	nrfjprog --family NRF52 --eraseall
	nrfjprog --program %localappdata%\Arduino15\packages\adafruit\hardware\nrf52\0.13.0\bootloader\feather_nrf52832\feather_nrf52832_bootloader-0.2.12_s132_6.1.1.hex -f nrf52 --chiperase --reset 
	nrfjprog --family NRF52 --reset

    @echo Flashing %~1-%~2-%~3 over serial port %~4
   	set prefix=%localappdata%\Arduino15\packages\adafruit\hardware\nrf52\
   	set postfix=tools\adafruit-nrfutil\win32\adafruit-nrfutil.exe --verbose dfu serial -pkg ..\..\output\%~1\%~1-%~2-%~3.zip -p %~4 -b 115200 --singlebank
   	set search_cmd="dir /b %prefix%"
   	FOR /F "tokens=*" %%i IN (' %search_cmd% ') DO SET ver=%%i
   	%prefix%\%ver%\%postfix%

:usage
	@echo Usage: flash_swd keyboard keymap target COMPort


