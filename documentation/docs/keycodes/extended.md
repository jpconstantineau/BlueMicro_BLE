---
id: keycodes_extended
title: Extended Keycodes
slug: /keycodes_extended
---

Firmware only keycodes are keycodes that combine multiple keycodes from the standard HID Usage Tables to generate specific characters.

| Combination             | Usage Name              | Keycode Identifiers        |
| ----------------------- | ----------------------- | -------------------------- |
| Left Shift and Grave    | ~                       | KC_TILD                    |
| Left Shift and 1        | !                       | KC_EXLM                    |
| Left Shift and 2        | @                       | KC_AT                      |
| Left Shift and 3        | #                       | KC_HASH                    |
| Left Shift and 4        | $                       | KC_DLR                     |
| Left Shift and 5        | %                       | KC_PERC                    |
| Left Shift and 6        | ^                       | KC_CIRC                    |
| Left Shift and 7        | &                       | KC_AMPR                    |
| Left Shift and 8        | *                       | KC_ASTR                    |
| Left Shift and 9        | (                       | KC_LPRN                    |
| Left Shift and 0        | )                       | KC_RPRN                    |
| Left Shift and Minus    | \_                      | KC_UNDS                    |
| Left Shift and Equal    | +                       | KC_PLUS                    |
| Left Shift and [        | {                       | KC_LCBR                    |
| Left Shift and ]        | }                       | KC_RCBR                    |
| Left Shift and \\       | \|                      | KC_PIPE                    |
| Left Shift and ;        | :                       | KC_COLN                    |
| Left Shift and '        | "                       | KC_DQUO    KC_DQT          |
| Left Shift and ,        | <                       | KC_LT                      |
| Left Shift and .        | >                       | KC_GT                      |
| Left Shift and /        | ?                       | KC_QUES                    |
| Left Shift and Non US # | Non US Tilde            | KC_NUTL                    |
| Left Shift and Non US \\ | Non US Pipe            | KC_NUPI                    |

Table is still a work in progress.  Refer to `hid_keycodes.h` and `advanced_keycodes.h` for a detailed list of keycodes.


### Mod Keys

Mod keys are special macros you can use to send a Modifier and a Key at the same time on a single keypress.

| Macro                   | Usage Name              | Example                    |
| ----------------------- | ----------------------- | -------------------------- |
| S(KEY)                  | Left Shift + Key        | S(KC_1)                    |
| LALT(KEY)               | Left ALT + Key          | LALT(KC_TAB)               |
| RALT(KEY)               | Right ALT + Key         | RALT(KC_TAB)               |
| LCTL(KEY)               | Left CTL + Key          | LCTL(KC_C)                 |
| RCTL(KEY)               | Right CTL + Key         | RCTL(KC_C)                 |
| LSFT(KEY)               | Left Shift + Key        | LSFT(KC_1)                 |
| RSFT(KEY)               | Right Shift + Key       | LALT(KC_1)                 |
| LGUI(KEY)               | Left GUI + Key          | LGUI(KC_1)                 |
| RGUI(KEY)               | Right GUI + Key         | RGUI(KC_1)                 |



### Toggles

The Macro `TG(KC)` can be used to toggle modifiers and layers.  The keycode will be sent in every HID report to the computer, as long as a key with the same keycode isn't pressed. This is similar to how SHIFT and CAPS LOCK work.  However, this is done on the keyboard and can be applied to any modifier.
Toggle is useful with modifiers and layers.  You can toggle the key until the toggle keystroke is pressed again.

| Example                 | Description             | 
| ----------------------- | ----------------------- | 
| TG(KC_LSHIFT)           | Toggle Left Shift       | 
| TG(KC_LCTRL)            | Toggle Left Control     | 
| TG(KC_LALT  )           | Toggle Left Alt         | 
| TG(LAYER_1)             | Toggle Layer 1          | 

### One Shot

The Macro `OS(KC)` can be used to enable a specific key on the next keypress.  The keycode will be sent for a single HID report to the computer.  The keycode will be sent with the next non-null report to the computer (next keypress).  An an example, SHIFT key makes the next letter into a capital letter but no other one thereafter.  OneShot is useful for modifiers when a specific modifier should be sent along with the next key.