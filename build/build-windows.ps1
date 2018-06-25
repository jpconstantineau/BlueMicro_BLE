# Arduino BlueMicro build script for Windows

param(
    [string]$BoardParam="ask",
    [switch]$Verbose=$false,
    [switch]$ContinueOnError=$false
)

$ErrorActionPreference = "Stop"

Function Write-Verbose($message) {
    if ($Verbose) {
        Write-Host $message
    }
}

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
        Write-Host -ForegroundColor Yellow "Could not find Arduino installation directory"
        Write-Host -ForegroundColor Yellow "Download and install the Arduino IDE from https://www.arduino.cc/en/main/software"
        Write-Host
        exit 1
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
        Write-Host -ForegroundColor Yellow "Could not find Arduino App Data Directory"
        Write-Host -ForegroundColor Yellow "Run the Arduino IDE at least once before this script"
        Write-Host
        exit 1
    }

    Write-Host -ForegroundColor Green "OK"
    return $arduinoDataDir
}

Function Check-Adafruit-Nrf52-Package {
    Write-Host -NoNewline "Adafruit nRF52 Package... "

    if(!(Test-Path -Path "$ArduinoDataDir\packages\adafruit\hardware\nrf52")) {
        Write-Host -ForegroundColor Red "Failed"
        Write-Host
        Write-Host -ForegroundColor Yellow "Could not find Adafruit nRF52 Package"
        Write-Host -ForegroundColor Yellow "Follow the installation instructions at https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/arduino-bsp-setup"
        Write-Host
        exit 1
    }

    Write-Host -ForegroundColor Green "OK"
}

function render() {
    [CmdletBinding()]
    param ( [parameter(ValueFromPipeline = $true)] [string] $str)

    "@`"`n$str`n`"@" | iex
}

Function Compile-Board($keyboard, $target, $keymap) {
    Write-Host -NoNewline "$keyboard`:$keymap`:$target... "
    Write-Verbose
    Write-Verbose

    # Create hardlinks (smylink requires admin)
    # Links cause problems when IDE is used, copy instead
    #New-Item -Path "$SourceDir\keyboard_config.h" -ItemType HardLink -Value "$KeyboardsDir\$keyboard\$target\keyboard_config.h" -Force >$null
    #New-Item -Path "$SourceDir\keymap.h" -ItemType HardLink -Value "$KeyboardsDir\$keyboard\keymaps\$keymap\keymap.h" -Force >$null

    $keymapFile = "$KeyboardsDir\$keyboard\keymaps\$keymap\keymap.h"
    $configFile = "$KeyboardsDir\$keyboard\$target\keyboard_config.h"

    Write-Verbose "Copying keymap and target source files"
    Write-Verbose $keymapFile
    Write-Verbose $configFile
    Copy-Item $keymapFile "$SourceDir\keymap.h" -Force
    Copy-Item $configFile "$SourceDir\keyboard_config.h" -Force

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
        #$cmdCompile += '-verbose '
    }

    $cmdCompile += '"$SourceDir\firmware.ino"'

    $cmdCompile = $cmdCompile | render

    Write-Verbose
    Write-Verbose "Running arduino-builder compile"
    Write-Verbose $cmdCompile
    Write-Verbose

    $ErrorActionPreference = "SilentlyContinue"
    $Error.Clear()
    if ($Verbose) {
        iex $cmdCompile 2>&1
    } else {
        iex $cmdCompile >$null 2>&1
    }
    $ErrorActionPreference = "Stop"

    if ($LastExitCode -ne 0) {
        $script:FailedBuilds++;

        Write-Host -ForegroundColor Red "Failed"
        Write-Host 
        Write-Host -ForegroundColor Yellow "Arduio build failed with exit code $LastExitCode"
        Write-Host 
        Write-Host -ForegroundColor Yellow "$error"
        Write-Host

        if ($ContinueOnError) {
            return
        }

        exit $LastExitCode
    }

    Write-Verbose "Copying compiled output"
    $keyboardOutputDir = "$OutputDir\$keyboard";
    if(!(Test-Path -Path $keyboardOutputDir)) {
        New-Item -Path $keyboardOutputDir -ItemType Directory >$null 2>&1
    }

    Copy-Item "$BuildDir\firmware.ino.zip" "$keyboardOutputDir\$keyboard-$keymap-$target.zip" -force
    Copy-Item "$BuildDir\firmware.ino.hex" "$keyboardOutputDir\$keyboard-$keymap-$target.hex" -force

    Write-Host -ForegroundColor Green "OK"
    Write-Verbose

    $script:SuccessfulBuilds++;
}

$ScriptPath = split-path -parent $MyInvocation.MyCommand.Definition
$ArduinoDirSearchList = @("${env:ProgramFiles}\Arduino", "${env:ProgramFiles(x86)}\Arduino")
$ArduinoDataDirSearchList = @("${env:LocalAppData}\Arduino15")
$SuccessfulBuilds = 0
$FailedBuilds = 0

Write-Host 
Write-Host "-----------------------------------------------------------------------"
Write-Host -NoNewline "   Arduino "
Write-Host -NoNewline -ForegroundColor Cyan "BlueMicro"
Write-Host " Build Script"
Write-Host "-----------------------------------------------------------------------"

Write-Verbose "Verbose output enabled"
Write-Verbose 
Write-Verbose ("Windows Version: " + [System.Environment]::OSVersion.Version)
Write-Verbose ("Powershell Version: " + $PSVersionTable.PSVersion)

if ($BoardParam -eq "ask") {
	Write-Host
	Write-Host "This script can be run with parameters"
	Write-Host "./build-windows.ps1 <keyboard>:<keymap>:<target> -verbose -continueOnError"

    $SelectedKeyboard = "all"
    $SelectedKeymap = "all"
    $SelectedTarget = "all"

    Write-Host
    $SelectedKeyboard = Read-Host -Prompt "Keyboard name (eg ErgoTravel) [all]"
    if ([string]::IsNullOrWhiteSpace($SelectedKeyboard)) {
        $SelectedKeyboard = "all"
    }

    if ($SelectedKeyboard -ne "all") {
        $SelectedKeymap = Read-Host -Prompt "Keymap name (eg default) [all]"
        if ([string]::IsNullOrWhiteSpace($SelectedKeymap)) {
            $SelectedKeymap = "all"
        }

        if ($SelectedKeymap -ne "all") {
            $SelectedTarget = Read-Host -Prompt "Target name (eg left / right / master) [all]"
            if ([string]::IsNullOrWhiteSpace($SelectedTarget)) {
                $SelectedTarget = "all"
            }
        }
    }
} else {
    $BoardParamSplit = $BoardParam.Split(":")
    $SelectedKeyboard = $BoardParamSplit[0];
    if ($BoardParamSplit.Count -ge 2) {
        $SelectedKeymap = $BoardParamSplit[1];
    } else {
        $SelectedKeymap = "all"
    }
    if ($BoardParamSplit.Count -ge 3) {
        $SelectedTarget = $BoardParamSplit[2];
    } else {
        $SelectedTarget = "all"
    }
}

Write-Host
Write-Host "Building: $SelectedKeyboard`:$SelectedKeymap`:$SelectedTarget"
Write-Host 
Write-Host "Checking file locations"
Write-Host -----------------------------------
$ArduinoDir = Locate-Arduino-Dir
$ArduinoDataDir = Locate-Arduino-Data-Dir
Check-Adafruit-Nrf52-Package

$BuilderExe = "$ArduinoDir\arduino-builder"

$BlueMicroDir = Resolve-Path "$ScriptPath\.." 2>$null

$FirmwareDir = "$BlueMicroDir\firmware"
$OutputDir = "$BlueMicroDir\output"
$BuildDir = "$OutputDir\.build"
$BuildCacheDir = "$OutputDir\.build-cache"

$SourceDir = "$OutputDir\.source\firmware"
$KeyboardsDir = "$SourceDir\keyboards"

Write-Verbose
Write-Verbose "Creating output directories"

if(!(Test-Path -Path $OutputDir)) {
    New-Item -Path $OutputDir -ItemType Directory >$null 2>&1
}
if(!(Test-Path -Path $BuildDir)) {
    New-Item -Path $BuildDir -ItemType Directory >$null 2>&1
}
if(!(Test-Path -Path $BuildCacheDir)) {
    New-Item -Path $BuildCacheDir -ItemType Directory >$null 2>&1
}

Write-Verbose 
Write-Verbose "Arduino: $ArduinoDir"
Write-Verbose "Arduino Data: $ArduinoDataDir"
Write-Verbose "Blue Micro Repo: $BlueMicroDir"
Write-Verbose "Output: $OutputDir"

Write-Host 
Write-Host "Compiling"
Write-Host "-----------------------------------"

Write-Verbose "Copying source files"
Write-Verbose

if(Test-Path -Path $SourceDir) {
    Remove-Item $SourceDir -Force -Recurse
}
Copy-Item -Path $FirmwareDir -Recurse -Destination $SourceDir -Container

Write-Verbose "Discovering keyboards"
Get-ChildItem $KeyboardsDir | ?{ $_.PSIsContainer } | Foreach-Object {

    $keyboard = $_.Name
    if ($SelectedKeyboard -ne "all" -and $SelectedKeyboard -ne $keyboard) {
        return
    }

    Write-Verbose
    Write-Verbose "Discovering $keyboard targets"
    $targets = @()
    Get-ChildItem "$KeyboardsDir\$keyboard" -Exclude "keymaps" | ?{ $_.PSIsContainer } | Foreach-Object {
        $targets += $_.Name
    }

    Write-Verbose "Discovering $keyboard keymaps"
    $keymaps = @()
    if(Test-Path -Path "$KeyboardsDir\$keyboard\keymaps") {
        Get-ChildItem "$KeyboardsDir\$keyboard\keymaps" | ?{ $_.PSIsContainer } | Foreach-Object {
            $keymaps += $_.Name
        }
    } else {
        Write-Host -ForegroundColor Red "$keyboard contains no keymaps"
    }

    foreach ($keymap in $keymaps) {
        if ($SelectedKeymap -ne "all" -and $SelectedKeymap -ne $keymap) {
            return
        }

        foreach ($target in $targets) {
            if ($SelectedTarget -ne "all" -and $SelectedTarget -ne $target) {
                return
            }

            Compile-Board $keyboard $target $keymap
        }
    }
}

if($SuccessfulBuilds -eq 0 -And $FailedBuilds -eq 0) {
    Write-Host -ForegroundColor yellow "Did not find anything to build for $SelectedKeyboard`:$SelectedKeymap`:$SelectedTarget"
}

Write-Host
Write-Host "Successful: $SuccessfulBuilds Failed: $FailedBuilds"

Write-Host
Write-Host "Binaries can be found in $OutputDir"
Write-Host

if ($FailedBuilds -ne 0) {
    exit 1
}
