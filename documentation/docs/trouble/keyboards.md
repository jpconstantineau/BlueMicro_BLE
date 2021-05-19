---
id: trouble_keyboard
title: Testing keyboards
---

## Useful Keyboard Testers
Here are a few useful keyboard testers:

* [QMK Keyboard Tester](https://config.qmk.fm/#/test)
* [keyboard Tester](https://www.keyboardtester.com/)
* [Keyboard Checker](https://keyboardchecker.com/)


## Troubleshooting tools

* Multimeter with continuity testing and diode testing modes
* Circuit Diagram of your keyboard
* Pinout diagram

## Specific Key is not working

If a specific key is not working but other keys in the same column and row are working, then it's likely the following:

* diode is installed in the reverse orientation
* diode is partially soldered (soldered only one side)
* diode is not functionning properly (unlikely - test with diode testing mode of multimeter)
* switch is not partially soldered (soldered only one side)
* switch is faulty (unlikely)
* PCB traces have been cut

Most often this is due to a diode installed in the reverse direction.  Unsolder the diode and re-install it the other way around.

## A whole Column or a whole Row is not working

If a whole column (or row) is not working, then it's the conection between the column/row and the microcontroller that's problematic.
With a continuity meter, check the following:

* (for columns) continuity between the non-diode side of the switches for that column and the contgroller pin - on the PCB socket.
* (for rows) continuity between the "band-side" of the diodes for that row and the controller pin - on the PCB socket.
* continuity between the PCB socket and the controller pin.

Very often when using a socket and diode legs, the issue is that the connection between the socket and the diode leg is faulty.  This is due to a "thin" diode leg that doesn't conctact the socket properly.
Resolving this issue is as simple as slightly bending the diode legs in a "S" shape rather than perfectly shaped "I" (curvy instead of straight).  This will improve the side to side contact between the socket and the diode legs and generally resolve the connection issue.

Very rarely (but it happens), the issue is on the controller board itself. This is usually quite difficult to troubleshoot and solve.

## Two adjacent keys are being registered when a single one is pressed

This can occur with cheap grab bag kecaps.  The keycaps have some plastic injection points that protrude under the next keycap.  When pressing the key, the small plastic tab is long/big enough to get caught under and force the second key to go down as well.
Remove the keycap and cut the protruding plastic tab and re-install.  

If this occurs when there are no keycaps on the switches, then go to the next section.

## Two adjacent rows or columns are being registered when a single key is pressed.

This is likely due to a short between two colums or two rows.  Check the soldering on the controller pins and verify that adjacent pins don't have continuity.  If this is the case, remove solder from these pins and re-check for a short.

It's unlikely but not impossible that the short is at the microcontroller itself. Visually check the microcontroller pins for a short between two microcontroller pins.

