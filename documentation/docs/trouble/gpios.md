---
id: trouble_gpios
title: Testing GPIOs
---

## Prerequisites

- You can flash an Arduino Sketch (program) to your controller.  If not, go to [Flashing/Uploading](flashing.md).


## Available Testers

There are a few programs that can be flashed to the controller to help with troubleshooting your hardware and identify if the GPIOs are working correctly.

- **[GPIO Tester](https://github.com/jpconstantineau/BlueMicro_BLE/tree/master/arduino_tests/GPIO_Tester)**: scans all GPIOs and indicates what values it reads depending if internal pull-up or internal pull-down resistors are enabled.
- **[Board tester](https://github.com/jpconstantineau/BlueMicro_BLE/tree/master/arduino_tests/board_tester)**: Used for testing new BlueMmicro and BluMicro840 boards: will blink each GPIOs.
- **[BlueMacro board tester](https://github.com/jpconstantineau/BlueMicro_BLE/tree/master/arduino_tests/BlueMacro_board_tester)**: Used for testing new BlueMacro840 boards: will blink each GPIOs.
- **[KB Key Tester](https://github.com/jpconstantineau/BlueMicro_BLE/tree/master/arduino_tests/KB_Key_Tester)**: Scans each GPIOs and identifies which ones are connected. If they are connected through a diode, the positive and negative sides will be shown. If no diodes is present, GPIOs will be shown on both positive and negative GPIOs.
- **[KB Matrix Tester](https://github.com/jpconstantineau/BlueMicro_BLE/tree/master/arduino_tests/KB_Matrix_Tester)**:Scans each GPIOs and accumulates the detected positive and negative GPIOs into an array you can use in your hardware_config.h file. If no diodes are present, GPIOs will be shown on both positive and negative GPIOs.

For an example of one of them, watch this video:

<figure class="video-container">
 <iframe src="//www.youtube.com/embed/BobS_HYZilM" frameborder="0" allowfullscreen width="100%"></iframe>
 </figure>
