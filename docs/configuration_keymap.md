# Configuring your own keymap
To understand how to configure your keymap, you should first know what constitutes a keycode:

## Keycodes
A single keycode field is made up of four different pieces of information:

### The HID Keycode 
* this is what the key actually sends to the computer, e.g. "KC_A" for "a"
* These conform with the USB HID standard and can be viewed in hid\_keycodes.h
* there are special keycodes defined in advanced\_keycodes.h where a modifier is sent at the same time as the keycode.

### The activation method
This is how the key is activated. options are:
* PRESS: it is pressed.  This is the normal operation of a keyboard where a key will be sent, and kept in the HID report until the key is released.  If you want to use another activation method, use **KC_NO** in the standard PRESS to make sure that the standard activations don't get sent to the computer.
* MT\_TAP: it is pressed and then released.  The key is sent as soon as the key is released.  
* MT\_HOLD: it is pressed and held.  The key is sent when the time limit expires.  The key is not repeated.  HOLD is useful for toggling modifiers or layers.
* DT\_TAP: it is pressed, released and not pressed again for DOUBLETAP\_TIME\_LIMIT. The keyboard will wait for the double tap time limit until the single tap key is sent.
* DT\_DOUBLETAP: it is pressed, released and tapped again within a certain time.  The keyboard will send the key as soon as a double tap is detected.
(DOUBLETAP\_TIME\_LIMIT duration (in ms) is defined in KeyStates.h)

There is a difference between MT\_TAP and DT\_TAP:  The key difference is when the keycode is sent.  With MT, the keycode is sent as soon as the key is released.  With DT, the keycode is sent some time after the key is released: delay time is there to detect the double taps.

Note: if you receive repeated keypresses, check that you do not have PRESS, MT_TAP and DT_TAP are not all defined.  
It is recommended that you use one of the 3 methods and do not combine them:
* PRESS: key is sent with every HID report. The computer will automatically detect this and repeat the keycode until a HID report without the keycode is received. Default behaviour.  Note that if the computer loose connection with the keyboard, it will not receive the "empty" HID report and will start repeating the keypress.
* MT_TAP/MT_HOLD: This adds a timer to the keyboard to detect when the key is being held.  When held, a different keycode can be sent.  For each activation state of this method, a single HID report will be sent and then immediately released.
* DT_TAP/DT_DOUBLETAP: This adds a timer to  the keyboard to detect if the same key is pressed again within a given time period.  When double-tapped, a different keycode can be sent. For each activation state of this method, a single HID report will be sent and then immediately released.

### The activation duration
Once Activated, sending of the keycode can be sent at different times:
* Momentary (default): as long as the key is active the keycode will be sent in every HID report to the computer.  This is the normal operation of a keyboard. Note that if the computer loose connection with the keyboard, it will not receive the "empty" HID report and will keep repeating the keypress.
* Toggle: The keycode will be sent in every HID report to the computer, as long as a key with the same keycode isn't pressed. This is similar to how SHIFT and CAPS LOCK work.  However, this is done on the keyboard and can be applied to any modifier.
Toggle is useful with modifiers and layers.  You can toggle the key until the toggle keystroke is pressed again.

* Oneshot: The keycode will be sent for a single HID report to the computer.  The keycode will be sent with the next non-null report to the computer (next keypress).  An an example, SHIFT key makes the next letter into a capital letter but no other one thereafter.  OneShot is useful for modifiers when a specific modifier should be sent along with the next key.  OneShot currently do not work for selecting layers.

The activation duration can be defined in the following way:
<pre>
    <i>DURATION</i>(<i>HID keycode</i>)
</pre>
e.g.
<pre>
    TG(KC_LSHIFT)
    OS(KC_LSHIFT)
</pre>

The activation duration are included as part of the definition for a layer or a single key.  As such, it does not get 

### The layer
The Layer ID is needed to identify which layer the keypresses are being mapped to.  These map out to 0-15. 


The three key pieces of information needed to define each key press are:
* Layer ID
* activation method (default press & repeat, tap, double-tap hold)
* HID Keycode;  includes the activation duration modifier when needed (toggle, one shot)



## Configuration
### The default layer
The default layer is the layer which you will most often use. Generally this is the "QWERTY" Layer.
Here, you give the 
HID Keycode and optionally the activation duration for the default method on the default layer
(currently PRESS and layer 0).
<pre>
    std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS>  matrix {
    KEYMAP(
        <i>KEYCODE1</i>, <i>KEYCODE2</i>, <i>etc.</i>)
    };
</pre>
For example for the gherkin:
<pre>
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ESC,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_SPC,  KC_BKSPC,KC_B,    KC_N,    KC_M,    KC_NO )};
</pre>


## Further layers
You can define layers in the same way as the default layer for any activation method and layer combo, 
e.g. PRESS on layer 1 or MT\_TAP for layer 0. Most of the time, you'll only need press layers unless you use other activation methods a lot. You will need to add a tuple ** people won't understand what a tuple is...** of this layer using the addLayers function.
<pre>
    uint32_t <i>LAYER_NAME</i> {
        KEYMAP(<i>...</i>)
    };
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(<i>LAYER</i>, <i>METHOD</i>, <i>KEYCODE</i>));

        }
    }  
</pre>

## Single keys
You'll most likely use this to configure keys with uncommon activation methods, e.g. DT\_DOUBLETAP.  However, when using a remapping macro (KEYMAP), it is recommended to create a full matrix with KC_NO everywhere except for where the specific activation method is desired.  However, for keyboards with no need for the KEYMAP macro, you can use the specific row and column directly (instead of looping over each row/column as shown above).
<pre> 
    matrix[<i>row</i>][<i>col</i>].addActivation(<i>LAYER</i>, <i>METHOD</i>, <i>KEYCODE</i>);
</pre>

