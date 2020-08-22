# Installing Tools

## Windows

Install the Arduino IDE via the installer (NOT the Windows App Store variant): https://www.arduino.cc/en/main/software

Open Arduino, add `https://www.adafruit.com/package_adafruit_index.json` as an `Additional Board Manager URL` in Preferences. While you're at it, checking the two "verbose" checkboxes in preferences will help you see compilation details and the commands being used from the IDE.

Install required packages from `Tools -> Board: "some boardName" -> Boards manager`.

* Adafruit nRF52

After this you are ready to build using `build.ps1` in `build/windows` in PowerShell

## MacOS

```
$ brew cask install arduino
```

Open Arduino, add `https://www.adafruit.com/package_adafruit_index.json` as an `Additional Board Manager URL` in Preferences. While you're at it, checking the two "verbose" checkboxes in preferences will help you see compilation details and the commands being used from the IDE.

Install required packages from `Tools -> Board: "some boardName" -> Boards manager`.

* Adafruit nRF52
* Arduino SAMD Boards (note: It's unclear if this is really needed)
* Adafruit SAMD Boards (note: It's unclear if this is really needed)

After this you are ready to build using `build-macos` in `build/macos/`

## Linux
