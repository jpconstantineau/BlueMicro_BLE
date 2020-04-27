$url = "https://downloads.arduino.cc/arduino-cli/arduino-cli_latest_Windows_64bit.zip"
$output = "$PSScriptRoot\..\arduino-cli\arduino-cli_latest_Windows_64bit.zip"
$target = "$PSScriptRoot\..\arduino-cli"
Remove-Item "$target\*.*"
Write-Output "Downloading Arduino-cli to $output"
(New-Object Net.WebClient).DownloadFile($url,$output)
Write-Output "Uncompressing Arduino-cli zip"
Expand-Archive -Path $output  -DestinationPath $target
Write-Output "Removing Arduino-cli zip"
Remove-Item $output

Write-Output "Copying Arduino-cli config"
Copy-Item "$PSScriptRoot\arduino-cli.yaml" $target


$exe = "$target\arduino-cli.exe"
& $exe core update-index
& $exe core upgrade
& $exe core search nrf52
& $exe core install adafruit:nrf52









