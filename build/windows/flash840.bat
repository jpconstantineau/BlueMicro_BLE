@echo off

if ["%~1"]==[""] goto usage
if ["%~2"]==[""] goto usage
if ["%~3"]==[""] goto usage


	powershell ./build.ps1 %~1:%~2:%~3 -nrf52840

	if exist ..\..\output\%~1\%~1-%~2-%~3.hex (
		goto flash
	) else (
		@echo Compiled hex still not found: do you have the right keyboard, keymap and target?
		@echo %~1 %~2 %~3
		goto usage
	)

    	goto :eof



:flash

   	set prefix=%localappdata%\Arduino15\packages\adafruit\hardware\nrf52\
   	set postfix=tools\adafruit-nrfutil\win32\adafruit-nrfutil.exe --verbose dfu serial -pkg ..\..\output\%~1\%~1-%~2-%~3.zip -p %~4 -b 115200 --singlebank
   	set search_cmd="dir /b %prefix%"
   	FOR /F "tokens=*" %%i IN (' %search_cmd% ') DO SET ver=%%i
	set bootloaderprefix=%prefix%\%ver%\bootloader\feather_nrf52832\
	set searchbootloader_cmd="dir *.zip /b %bootloaderprefix%"
    FOR /F "tokens=*" %%i IN (' %searchbootloader_cmd% ') DO SET bootloader=%%i
	@echo Flashing Bootloader before %~1-%~2-%~3
	echo %prefix%\%ver%/tools/adafruit-nrfutil/win32/adafruit-nrfutil.exe --verbose dfu serial -pkg %bootloaderprefix%\%bootloader% -p %~4 -b 115200 --touch 1200
    @echo Flashing %~1-%~2-%~3 over serial port %~4
   	%prefix%\%ver%\%postfix%

:usage
	@echo Usage: flash_swd keyboard keymap target COMPort


