@echo off 
@echo Unlocking Chip using Black Magic Probe

if exist C:\Users\pierre\Documents\Arduino\hardware\Adafruit\Adafruit_nRF52_Arduino (
    set prefix=C:\Users\pierre\Documents\Arduino\hardware\Adafruit\Adafruit_nRF52_Arduino
) else (
    set prefix=%localappdata%\Arduino15\packages\adafruit\hardware\nrf52
)

set bmpprefix=%localappdata%\Arduino15\packages\adafruit\tools\arm-none-eabi-gcc\9-2019q4\bin\arm-none-eabi-gdb.exe

if exist %bmpprefix% (
    @echo Found arm-none-eabi-gdb.exe
) else (
    @echo NOT Found arm-none-eabi-gdb.exe
)

%bmpprefix% --batch -ex "target extended-remote \\.\%1" -ex "mon tpwr enable" -ex "mon swdp_scan" -ex "att 1" -ex "mon erase_mass"  -ex "mon hard_srst" -ex "detach"


