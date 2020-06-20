# Installing Tools

## Windows

Install the Arduino IDE: https://www.arduino.cc/en/main/software

Open Arduino, add `https://www.adafruit.com/package_adafruit_index.json` as an `Additional Board Manager URL` in Preferences, then restart Arduino IDE.

Install required packages from `Tools -> Board: "some boardName" -> Boards manger`.

* Adafruit nRF52

After this you are ready to build using `build.ps1` in `build/windows` in PowerShell

## MacOS

```
$ brew cask install arduino
```

Open Arduino, add `https://www.adafruit.com/package_adafruit_index.json` as an `Additional Board Manager URL` in Preferences, then restart Arduino IDE.

Install required packages from `Tools -> Board: "some boardName" -> Boards manger`.

* Adafruit nRF52
* Arduino SAMD Boards 
* Adafruit SAMD Boards

After this you are ready to build using `build-macos` in `build/macos/`

## Linux
