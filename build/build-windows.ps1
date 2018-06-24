# Arduino BlueMicro build script for Windows

param($Arguments)
if (!$Arguments) {
	# Run in new windows to prevent closing on exit / error
    $script = $MyInvocation.MyCommand.Path
    invoke-expression "cmd /c start powershell -noexit -file `"$script`" 1"
    return
}

$Verbose = $false

$ArduinoDirSearchList = @("${env:ProgramFiles}\Arduino", "${env:ProgramFiles(x86)}\Arduino")
$ArduinoDataDirSearchList = @("${env:LocalAppData}\Arduino15")

$ErrorActionPreference = "Stop"

Function Locate-Dir($searchList) {
    $foundDir = ''
    foreach ($directory in $searchList) {
        if(Test-Path -Path $directory) {
            $foundDir = $directory
            break
        }
    }

    return $foundDir
}

Function Locate-Arduino-Dir { 
    Write-Host -NoNewline "Arduino Installation... "

    $arduinoDir = Locate-Dir($ArduinoDirSearchList)

    if ([string]::IsNullOrEmpty($arduinoDir)) {
        Write-Host -ForegroundColor Red "Failed"
        Write-Host
        Write-Host "Could not find Arduino installation directory"
        Write-Host "Download and install the Arduino IDE from https://www.arduino.cc/en/main/software"
        exit
    }

    Write-Host -ForegroundColor Green "OK"
    return $arduinoDir
}

Function Locate-Arduino-Data-Dir { 
    Write-Host -NoNewline "Arduino App Location... "

    $arduinoDataDir = Locate-Dir($ArduinoDataDirSearchList)

    if ([string]::IsNullOrEmpty($arduinoDataDir)) {
        Write-Host -ForegroundColor Red "Failed"
        Write-Host
        Write-Host "Could not find Arduino App Data Directory"
        exit
    }

    Write-Host -ForegroundColor Green "OK"
    return $arduinoDataDir
}

Function Check-Adafruit-Nrf52-Package {
    Write-Host -NoNewline "Adafruit nRF52 Package... "

    if(!(Test-Path -Path "$ArduinoDataDir\packages\adafruit\hardware\nrf52")) {
        Write-Host -ForegroundColor Red "Failed"
        Write-Host
        Write-Host "Could not find Adafruit nRF52 Package"
        Write-Host "Follow the installation instructions at https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/arduino-bsp-setup"
        exit
    }

    Write-Host -ForegroundColor Green "OK"
}

Function Compile-Board($keyboard, $target, $keymap) {
    Write-Host -NoNewline "$keyboard`:$keymap`:$target... "

    # Create hardlinks (smylink requires admin)
    # Links cause problems when IDE is used, copy instead
    #New-Item -Path "$FirmwareDir\keyboard_config.h" -ItemType HardLink -Value "$KeyboardsDir\$keyboard\$target\keyboard_config.h" -Force >$null
    #New-Item -Path "$FirmwareDir\keymap.h" -ItemType HardLink -Value "$KeyboardsDir\$keyboard\keymaps\$keymap\keymap.h" -Force >$null

    Copy-Item "$KeyboardsDir\$keyboard\$target\keyboard_config.h" "$FirmwareDir\keyboard_config.h" -Force
    Copy-Item "$KeyboardsDir\$keyboard\keymaps\$keymap\keymap.h" "$FirmwareDir\keymap.h" -Force

    # Run compile
    $cmdCompile = 
        '& "$BuilderExe" -compile -logger=machine -warnings "none" -ide-version "10805" -debug-level 1 ' + 
        '-hardware "$ArduinoDir\hardware" -hardware "$ArduinoDataDir\packages" ' + 
        '-tools "$ArduinoDir\tools-builder" -tools "$ArduinoDir\hardware\tools\avr" -tools "$ArduinoDataDir\packages" ' +
        '-built-in-libraries "$ArduinoDir\libraries"' +
        '-fqbn "adafruit:nrf52:feather52:softdevice=s132v201,debug=l0" ' +
        '-build-path "$BuildDir" -build-cache "$BuildCacheDir" '
        #'-prefs "build.warn_data_percentage=75" -prefs "runtime.tools.nrfjprog.path=$ArduinoDataDir\packages\adafruit\tools\nrfjprog\9.4.0" -prefs "runtime.tools.gcc-arm-none-eabi.path=$ArduinoDataDir\packages\adafruit\tools\gcc-arm-none-eabi\5_2-2015q4" '

    if ($Verbose) {
        $cmdCompile += '-verbose '
    }

    $cmdCompile += '"C:\Development\BlueMicro_BLE\firmware\firmware.ino"'

    $cmdError = ""
    $cmdCompile = $ExecutionContext.InvokeCommand.ExpandString($cmdCompile)

    if ($Verbose) {
        iex $cmdCompile -ErrorVariable cmdError
    } else {
        iex $cmdCompile 1>$null 2>&1 -ErrorVariable cmdError
    }

    if (!([string]::IsNullOrEmpty($cmdError))) {
        Write-Host -ForegroundColor Red "Failed"
        Write-Host 
        Write-Host -ForegroundColor Yellow $cmdError
        exit
    }

    $keyboardOutputDir = "$OutputDir\$keyboard";
    if(!(Test-Path -Path $keyboardOutputDir)) {
        New-Item -Path $keyboardOutputDir -ItemType Directory >$null 2>&1
    }

    Copy-Item "$BuildDir\firmware.ino.zip" "$keyboardOutputDir\$keyboard-$keymap-$target.zip" -force
    Copy-Item "$BuildDir\firmware.ino.hex" "$keyboardOutputDir\$keyboard-$keymap-$target.hex" -force

    Write-Host -ForegroundColor Green "OK"
}

Write-Host 
Write-Host "-----------------------------------------------------------------------"
Write-Host -NoNewline "   Arduino "
Write-Host -NoNewline -ForegroundColor Cyan "BlueMicro"
Write-Host " Build Script"
Write-Host "-----------------------------------------------------------------------"

Write-Host 
Write-Host "Checking file locations"
Write-Host -----------------------------------
$ArduinoDir = Locate-Arduino-Dir
$ArduinoDataDir = Locate-Arduino-Data-Dir
Check-Adafruit-Nrf52-Package

$BuilderExe = "$ArduinoDir\arduino-builder"

$BlueMicroDir = Resolve-Path "$PSScriptRoot\.." 2>$null
$FirmwareDir = "$BlueMicroDir\firmware"
$KeyboardsDir = "$BlueMicroDir\firmware\keyboards"

$OutputDir = "$BlueMicroDir\output"
$BuildDir = "$OutputDir\.build"
$BuildCacheDir = "$OutputDir\.build-cache"

if(!(Test-Path -Path $OutputDir)) {
    New-Item -Path $OutputDir -ItemType Directory >$null 2>&1
}
if(!(Test-Path -Path $BuildDir)) {
    New-Item -Path $BuildDir -ItemType Directory >$null 2>&1
}
if(!(Test-Path -Path $BuildCacheDir)) {
    New-Item -Path $BuildCacheDir -ItemType Directory >$null 2>&1
}

Write-Host 
Write-Host "Compiling"
Write-Host "-----------------------------------"

Get-ChildItem $KeyboardsDir -Directory | Foreach-Object {

    $keyboard = $_.Name

    $targets = @()
    Get-ChildItem "$KeyboardsDir\$keyboard" -Directory -Exclude "keymaps" | Foreach-Object {
        $targets += $_.Name
    }

    $keymaps = @()
    if(Test-Path -Path "$KeyboardsDir\$keyboard\keymaps") {
        Get-ChildItem "$KeyboardsDir\$keyboard\keymaps" -Directory | Foreach-Object {
            $keymaps += $_.Name
        }
    } else {
        Write-Host -ForegroundColor Red "$keyboard contains no keymaps"
    }

    foreach ($keymap in $keymaps) {
        foreach ($target in $targets) {
            Compile-Board $keyboard $target $keymap
        }
    }
}

Write-Host
Write-Host "Binaries can be found in $OutputDir"
Write-Host
