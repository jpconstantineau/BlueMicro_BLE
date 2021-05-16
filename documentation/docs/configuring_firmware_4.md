---
id: configure_combos
title: Configuring Advanced Features
slug: /configure_combos
---

## Configuring your keyboard - Part 4: Advanced Features

### Combo Engine: Combos, Substitutions and simple macros

:::caution

The following macros work at the keycode level; not at the keypress level.  This means that the keypress activation method (PRESS, MT_TAP, MT_HOLD, DT_TAP, DT_DOUBLETAP) will be processed before the combo engine and thus may impact desired behavior of these macros.  It is recommended to use the PRESS activation method for the keymaps for triggering these macros.

:::

You will need to add ```#define ENABLE_COMBOS``` to your keymap.h file to enable combos.


```COMB(name, keycode_to_send, trigger)``` : The ```COMB()``` Macro is responsible for accepting a combo and outputting ***a single keycode!***.

Send a single keycode. aka, replaces the trigger keys that are simultaneously pressed with the keycode to emit.  The trigger must contain 2 or more comma-separated keycodes.  Any combo with a trigger containing a single keycode will be ignored.  Trigger keycodes are removed from the list of active keycodes (keys being pressed) while the keycode to send is added to the active keycodes.

```
COMB(chord_b,    KC_B,            KC_E, KC_O);
COMB(chord_d,    KC_D,            KC_A, KC_R, KC_T);
```
The keycode to send can be any basic or extended keycode, they can be consumer or mouse keycodes as well as hardware-specific keycodes. This means that toggles, one-shots and layers cannot be used.


```SUBS(name, string_to_send, trigger)``` : Send a string (aka macro) when key or chord is triggered. The trigger must contain 1 or more comma-separated keycodes. Trigger keycodes are removed from the list of active keycodes (keys being pressed). If using 1 keycode as a trigger, it is recommended to use a keycode not used by the keyboard or operating system. Alternately, you can mark the trigger keycode with the ```MC()``` macro to further add options to use as triggers in your keymap.

```
SUBS(string_test2,    "Hello World!",                                  KC_F20);     //
SUBS(string_test1,    "The quick brown fox jumps over the lazy dog!",  KC_A, KC_R); //
```

```KEYS(name, sequence_to_send, trigger)``` : Send sequence of keycodes (aka macro) when key or chord is triggered. The trigger must contain 1 or more comma-separated keycodes. Trigger keycodes are removed from the list of active keycodes (keys being pressed). If using 1 keycode as a trigger, it is recommended to use a keycode not used by the keyboard or operating system. Alternately, you can mark the trigger keycode with the ```MC()``` macro to further add options to use as triggers in your keymap.

Note that the sequence of keycodes to send is a comma-separated list enclosed in ```({})```.  You can only use basic and extended keycodes in this list as they will directly be sent to the computer and not processed any further.  This means that toggles, one-shots, hardware and firmware keycodes cannot be used as part of the sequence to send.


```
KEYS(key_sequence_test2, ({LSFT(KC_H), KC_E, KC_L, KC_L, KC_O, KC_SPC, LSFT(KC_T), KC_E, KC_S, KC_T}), MC(KC_C));         // Hello Test
KEYS(key_sequence_test1, ({LSFT(KC_H), KC_E, KC_L, KC_L, KC_O, KC_SPC, LSFT(KC_W), KC_O, KC_R, KC_L, KC_D}), KC_E, KC_Y); // Hello World
```

### Keyboard Modes and Persistent User States

When booting up, the keyboard can use pre-saved configuration information to be able to adjust the keymap according to the mode the user has previously saved.  

The `PersistentState` structure that's saved in flash has the following fields available for the user to use to change the behavior of the keyboard when booting up:
``` c++
        uint8_t    mode;
        uint8_t    user1;  
        uint8_t    user2; 
```

Default values for all 3 fields are 0.

See the `4x4Backpack Modes` keymap to see an example of how dynamic the selection of the keymap to be loaded on startup is performed and how saving the mode is done using Macro functionality.

Since the `setupKeymap()` function also sets up the rotary encoder callback, it's possible to change the functionality of the rotary encoder depending on the mode (or other user variables) selected.