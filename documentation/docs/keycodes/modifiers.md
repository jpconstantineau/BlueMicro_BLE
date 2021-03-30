---
id: keycodes_modifiers
title: Toggles and One-Shot
slug: keycodes_modifiers
---


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

The Macro `OS(KC)` can be used to enable a specific key on the next keypress.  The keycode will be sent for a single HID report to the computer.  The keycode will be sent with the next non-null report to the computer (next keypress).  An an example, SHIFT key makes the next letter into a capital letter but no other one thereafter.  OneShot is useful for modifiers when a specific modifier should be sent along with the next key.v