---
id: keycodes_firmware
title: Firmware-only Keycodes
---

Firmware only keycodes are keycodes that modify the behavior of the keyboard firmware and are processed to send something different. 

### Layers

These keycodes are used by the firmware to switch from one layer to another.

| Usage ID (HEX) | Usage Name               | Keycode Identifiers        |
| -------------- | -----------------------  | -------------------------- |
| 0xF0           | Access Layer 0 (default) | LAYER_0                    |
| 0xF1           | Access Layer 1 (default) | LAYER_1                    |
| 0xF2           | Access Layer 2 (default) | LAYER_2                    |
| 0xF3           | Access Layer 3 (default) | LAYER_3                    |
| 0xF4           | Access Layer 4 (default) | LAYER_4                    |
| 0xF5           | Access Layer 0 (default) | LAYER_5                    |
| 0xF6           | Access Layer 1 (default) | LAYER_6                    |
| 0xF7           | Access Layer 2 (default) | LAYER_7                    |
| 0xF8           | Access Layer 3 (default) | LAYER_8                    |
| 0xF9           | Access Layer 4 (default) | LAYER_9                    |
| 0xFA           | Access Layer 4 (default) | LAYER_A                    |
| 0xFB           | Access Layer 0 (default) | LAYER_B                    |
| 0xFC           | Access Layer 1 (default) | LAYER_C                    |
| 0xFD           | Access Layer 2 (default) | LAYER_D                    |
| 0xFE           | Access Layer 3 (default) | LAYER_E                    |
| 0xFF           | Access Layer 4 (default) | LAYER_F                    |

If you want to activate a layer by pressing a combination of two other layer keycodes, you can use the function `process_user_layers` to define the behavior you want.

You will need to add the following two lines to your `keymap.h`

``` c++
#define USER_LAYER_FUNCTION   0 
void process_user_layers(uint16_t layermask);
```

You will also need to define which two layer activate the 3rd one. This is done by adding a few lines in `keymap.cpp`

``` c++
void process_user_layers(uint16_t layermask)
{
    KeyScanner::process_for_tri_layers(_L1, _L2, _L3);
}
```
In the example above, both LAYER_1 and LAYER_2 need to be pressed for LAYER_3 to be activated.
Note that `_L1`, `_L2` and `_L3` are not keycodes.

If combinations with more layers are needed, you can add them in that function.


### Press


### Toggles


### One Shot

Page is still a work in progress.  Refer to `hid_keycodes.h` and `advanced_keycodes.h` for a detailed list of keycodes.
