# Arduino BlueMicro build script for Windows

param(
    [string]$BoardParam="ask",
    [switch]$Verbose=$false,
    [switch]$Debug=$false,
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

    $arduinoDir = Get-ItemProperty -Path HKLM:\SOFTWARE\WOW6432Node\Arduino -ErrorAction SilentlyContinue | Select-Object Install_Dir -ExpandProperty Install_Dir
    
    if ([string]::IsNullOrEmpty($arduinoDir))
    {
        Write-Host -ForegroundColor Yellow Warning
        Write-Host -ForegroundColor Yellow "Could not find Arduino installation from registry, searching common locations"
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

Function Check-Community-Nrf52-Package {
    Write-Host -NoNewline "Community nRF52 Package... "

    if(!(Test-Path -Path "$ArduinoDataDir\packages\community_nrf52\hardware\nrf52")) {
        Write-Host -ForegroundColor Red "Failed"
        Write-Host
        Write-Host -ForegroundColor Yellow "Could not find Community nRF52 Package"
        Write-Host -ForegroundColor Yellow "Follow the installation instructions at https://github.com/jpconstantineau/Community_nRF52_Arduino/wiki/Installation-Instructions"
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

Function Compile-Board($keyboard, $target, $keymap, $fqbn, $hardware) {
    Write-Host -NoNewline "$keyboard`:$keymap`:$target`:$hardware`:$fqbn... "
    Write-Verbose
    Write-Verbose

    # Create hardlinks (smylink requires admin)
    # Links cause problems when IDE is used, copy instead
    #New-Item -Path "$SourceDir\keyboard_config.h" -ItemType HardLink -Value "$KeyboardsDir\$keyboard\$target\keyboard_config.h" -Force >$null
    #New-Item -Path "$SourceDir\keymap.h" -ItemType HardLink -Value "$KeyboardsDir\$keyboard\keymaps\$keymap\keymap.h" -Force >$null

    $keymapFile = "$KeyboardsDir\$keyboard\keymaps\$keymap\keymap.h"
    $keymapcppFile = "$KeyboardsDir\$keyboard\keymaps\$keymap\keymap.cpp"
    $configFile = "$KeyboardsDir\$keyboard\config\$target\keyboard_config.h"
    $hardwareFile = "$KeyboardsDir\$keyboard\hardware\$fqbn\$hardware\hardware_config.h"

    Write-Verbose "Copying keymap and target source files"
    Write-Verbose $keymapFile
    Write-Verbose $keymapcppFile
    Write-Verbose $configFile
    Copy-Item $keymapFile "$SourceDir\keymap.h" -Force
    Copy-Item $keymapcppFile "$SourceDir\keymap.cpp" -Force
    Copy-Item $configFile "$SourceDir\keyboard_config.h" -Force
    Copy-Item $hardwareFile "$SourceDir\hardware_config.h" -Force

	# Need to sleep between compile calls else the arduino-builder does not recognise changes
	Start-Sleep -s 2
    if ($Debug) 
    {$cmdDebug = "l1"} 
    else
    {$cmdDebug = "l0"}

    if ($fqbn -eq "feather52832") 
    {$cmdfqbn = "s132v6"} 
    else
    {$cmdfqbn = "s140v6"}
    $fqbnstr = $fqbn
    
    # Run compile

    $cmdCompile = 
        '& "$BuilderExe" -compile -logger=machine -warnings "none" -verbose -ide-version "10807" -debug-level 1 ' + 
        '-hardware "$ArduinoDir\hardware" -hardware "$ArduinoDataDir\packages" ' + 
        '-tools "$ArduinoDir\tools-builder" -tools "$ArduinoDir\hardware\tools\avr" -tools "$ArduinoDataDir\packages" ' +
        '-built-in-libraries "$ArduinoDir\libraries" ' +
        '-fqbn "community_nrf52:nrf52`:$fqbn`:softdevice=$cmdfqbn,debug=$cmdDebug" ' +
        '-build-path "$BuildDir" -build-cache "$BuildCacheDir" '

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
        Write-Host -ForegroundColor Yellow "Arduino build failed with exit code $LastExitCode"
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

    Copy-Item "$BuildDir\firmware.ino.zip" "$keyboardOutputDir\$keyboard-$fqbn-$hardware-$keymap-$target.zip" -force
    Copy-Item "$BuildDir\firmware.ino.hex" "$keyboardOutputDir\$keyboard-$fqbn-$hardware-$keymap-$target.hex" -force
    Copy-Item "$BuildDir\firmware.ino.elf" "$keyboardOutputDir\$keyboard-$fqbn-$hardware-$keymap-$target.elf" -force

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
	Write-Host "./build-windows.ps1 <keyboard>:<keymap>:<keyboard_config>:<hardware>:<fqbn> -verbose -continueOnError"

    $SelectedKeyboard = "all"
    $SelectedKeymap = "all"
    $SelectedTarget = "all"
    $Selectedfqbn = "all"
    $SelectedHardware = "all"

    Write-Host
    $SelectedKeyboard = Read-Host -Prompt "Keyboard name (eg ErgoTravel) [all]"
    if ([string]::IsNullOrEmpty($SelectedKeyboard)) {
        $SelectedKeyboard = "all"
    }
    if ([string]::IsNullOrEmpty($Selectedfqbn)) {
        $Selectedfqbn = "all"
    }
    if ([string]::IsNullOrEmpty($SelectedHardware)) {
        $SelectedHardware = "all"
    }

    if ($SelectedKeyboard -ne "all") {
        $SelectedKeymap = Read-Host -Prompt "Keymap name (eg default) [all]"
        if ([string]::IsNullOrEmpty($SelectedKeymap)) {
            $SelectedKeymap = "all"
        }

        if ($SelectedKeymap -ne "all") {
            $SelectedTarget = Read-Host -Prompt "Target name (eg left / right / master) [all]"
            if ([string]::IsNullOrEmpty($SelectedTarget)) {
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

    if ($BoardParamSplit.Count -ge 4) {
        $SelectedHardware = $BoardParamSplit[3];
    } else {
        $SelectedHardware = "all"
    }
    if ($BoardParamSplit.Count -ge 5) {
        $Selectedfqbn = $BoardParamSplit[4];
    } else {
        $Selectedfqbn = "all"
    }
}

Write-Host
Write-Host "Building: $SelectedKeyboard`:$SelectedKeymap`:$SelectedTarget`:$SelectedHardware`:$Selectedfqbn"
Write-Host 
Write-Host "Checking file locations"
Write-Host -----------------------------------
$ArduinoDir = Locate-Arduino-Dir
$ArduinoDataDir = Locate-Arduino-Data-Dir
Check-Adafruit-Nrf52-Package
Check-Community-Nrf52-Package

$BuilderExe = "$ArduinoDir\arduino-builder"

$BlueMicroDir = Resolve-Path "$ScriptPath\..\.." 2>$null

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
Write-Verbose $KeyboardsDir
Get-ChildItem $KeyboardsDir | ?{ $_.PSIsContainer } | Foreach-Object {

    $keyboard = $_.Name
    if ($SelectedKeyboard -ne "all" -and $SelectedKeyboard -ne $keyboard) {
        return
    }

    Write-Verbose
    Write-Verbose "Discovering $keyboard targets"
    $targets = @()
    Get-ChildItem "$KeyboardsDir\$keyboard\config" | ?{ $_.PSIsContainer } | Foreach-Object {
        $targets += $_.Name
    }
    $fqbns = @()
    Get-ChildItem "$KeyboardsDir\$keyboard\hardware" | ?{ $_.PSIsContainer } | Foreach-Object {
        $fqbns += $_.Name
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
            continue
        }

        foreach ($target in $targets) {
            if ($SelectedTarget -ne "all" -and $SelectedTarget -ne $target) {
                continue
            }
            foreach ($fqbn in $fqbns) {
                if ($Selectedfqbn -ne "all" -and $Selectedfqbn -ne $fqbn) {
                    continue
                }
                $hardwares = @()
                Get-ChildItem "$KeyboardsDir\$keyboard\hardware\$fqbn" | ?{ $_.PSIsContainer } | Foreach-Object {
                    $hardwares += $_.Name
                }
                foreach ($hardware in $hardwares) {
                    if ($SelectedHardware -ne "all" -and $SelectedHardware -ne $hardware) {
                        continue
                    }

                    Compile-Board $keyboard $target $keymap $fqbn $hardware
                }
            }
        }
    }
}

if($SuccessfulBuilds -eq 0 -And $FailedBuilds -eq 0) {
    Write-Host -ForegroundColor yellow "Did not find anything to build for $SelectedKeyboard`:$SelectedKeymap`:$SelectedTarget`:$SelectedHardware`:$Selectedfqbn"
}

Write-Host
Write-Host "Successful: $SuccessfulBuilds Failed: $FailedBuilds"

Write-Host
Write-Host "Binaries can be found in $OutputDir"
Write-Host

if ($FailedBuilds -ne 0 -Or $SuccessfulBuilds -eq 0) {
    exit 1
}
