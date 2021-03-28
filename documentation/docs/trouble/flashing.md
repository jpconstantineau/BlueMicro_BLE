---
id: trouble_flash
title: Flashing/Uploading
---

If you have trouble flashing the firmware, you can start with simply flashing a "Blink" program to make sure that you have everything ready and working.
You do not need the firmware at this point.

## Upload using Arduino IDE

The following steps apply to both nRF52832 and nRF52840 chips.

- Start the Arduino IDE
- Select your controller from the Arduino IDE "Tools -> Board -> Community nRF52 Add-on Boards" Menu
- Open the **blinky** example by selecting "File -> Examples -> Adafruit Bluefruit nRF52 Libraries -> Hardware -> blinky"
- Connect your keyboard. A new serial port should show up in the "Tools -> Port" menu.
- Select the serial port of your keyboard in the "Tools -> Port" menu.
- Compile **blinky** using the ✔️ button in the toolbar
- Flash (upload) **blinky** using the ➡️ button in the toolbar
- The built in LED should now blink at an interval of 2 seconds (toggle every 1 second).

If you cannot flash **blinky** to your controller and see the LED blink, then you cannot proceed to flashing your firmware.  

Items you can check if the above did not work:

- Is the serial port the correct one?
- For nRF52840 chips, press reset twice (double-reset). This should put the controller in DFU mode.  Does it now show up in the "Tools -> Port" menu? 
- Is the board selected the correct one? 

## For nRF52832 boards
USB connection to the nRF52832 chip is handled through a serial/uart USB chip.  The USB Identification is fixed to that chip and will not change depending on the state of the nRF52832.  

In the Arduino IDE, simply select the serial port that appears when connecting the controller.  If your operating system complains about needing a driver, refer to the following links for finding the drivers of various USB chips:
- CH340x: Follow the instructions from [sparkfun](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all)
- CP210x: Follow the instructions from [silabs](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all)
- FTDI: Follow the instructions from [FTDI](https://ftdichip.com/drivers/)

If the serial chip is on-board of the controller next to the nRF52832, circuitry to handle reset is likely installed and will reset the nRF52 just in time to allow for flashing.

## For nRF52840 boards

Since USB is handled by the nRF52840 bootloader and firmware, the USB identification may differ between when the chip is in bootloader mode or in the firmware. This is often the case when the firmware is compiled with a specific controller but the bootloader is configured with another.  In such case, you may need to double-reset prior to selecting the serial port of the controller.

## Computer does not detect the controller

For the nRF52832, this is most often caused by a hardware issue. For the nRF52840, the firmware may not present a serial port. When in DFU mode, this is most often caused by a hardware issue.

- Verify that the USB cable is not defective.
- For a controller you have assembled yourself, you may want to double-check the USB connector solder joins.  You may also want to double-check that power and gnd are not shorted.

## Computer does not recognize the controller

This may be caused by firmware or hardware issues.  

- If the bootloader or firmware crashes before communications between the computer and the controller are completed, the computer won't receive all the identification information in time and won't recognize the controller. This is very rare.
- For a controller you have assembled yourself, you may want to double-check the USB connector solder joins. This is one of the most frequent causes.
