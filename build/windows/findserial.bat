@echo off
if exist ..\..\arduino-cli\arduino-cli.exe (
	..\..\arduino-cli\arduino-cli.exe board list
) else (
	@echo Install arduino-cli!
    @echo run install.bat from the utils folder
)
