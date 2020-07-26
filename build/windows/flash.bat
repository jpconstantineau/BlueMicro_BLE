@echo off

if ["%~1"]==[""] goto usage
if ["%~2"]==[""] goto usage
if ["%~3"]==[""] goto usage
if ["%~4"]==[""] goto usage
if ["%~5"]==[""] goto usage
if ["%~6"]==[""] goto usage

if exist ..\..\output\%~1\%~1-%~2-%~3.hex (
	goto flash
) else (
	@echo Compiled hex not found: running build script first.
	powershell ./build.ps1 %~1:%~2:%~3:%~4:%~5

	if exist ..\..\output\%~1\%~1-%~4-%~5-%~2-%~3.zip (
		goto flash
	) else (
		@echo Compiled hex still not found: do you have the right keyboard, keymap and target?
		@echo %~1 %~2 %~3 %~4 %~5
		goto usage
	)

    	goto :eof
)


:flash
    REM keyboard:keymap:target:fqbn:hardware.
	REM %~1 %~2 %~3 %~4 %~5
    REM $OutputDir\$keyboard\$keyboard-$fqbn-$hardware-$keymap-$target.hex
   	set prefix=%localappdata%\Arduino15\packages\adafruit\hardware\nrf52\
   	set postfix=tools\adafruit-nrfutil\win32\adafruit-nrfutil.exe --verbose dfu serial -pkg ..\..\output\%~1\%~1-%~4-%~5-%~2-%~3.zip -p %~6 -b 115200 --singlebank 
   	set search_cmd="dir /b %prefix%"
   	FOR /F "tokens=*" %%i IN (' %search_cmd% ') DO SET ver=%%i
	set bootloaderprefix=%prefix%\%ver%\bootloader\feather_nrf52832\
	set searchbootloader_cmd="dir *.zip /b %bootloaderprefix%"
    FOR /F "tokens=*" %%i IN (' %searchbootloader_cmd% ') DO SET bootloader=%%i
	@echo Flashing Bootloader before %~1-%~4-%~5-%~2-%~3.zip
	%prefix%\%ver%/tools/adafruit-nrfutil/win32/adafruit-nrfutil.exe --verbose dfu serial -pkg %bootloaderprefix%\%bootloader% -p %~6 -b 115200 --touch 1200
    @echo Flashing %~1-%~4-%~5-%~2-%~3.zip over serial port %~4
   	%prefix%\%ver%\%postfix%

:usage
	@echo Usage: flash keyboard keymap target fqbn hardware COMPort


