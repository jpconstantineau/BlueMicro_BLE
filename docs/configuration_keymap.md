# Configuring your own keymap
To understand how to configure your keymap, you should know what constitutes a keycode first.

## Keycodes
A keycode is made up of four different data:
### The HID Keycode 
* this is what the key actually sends to the computer, e.g. "a"
* These are conformant with the USB standard and can be viewed in hid\_keycodes.h

### The activation method
This is how the key is activated, options are:
* PRESS: it is pressed
* MT\_HOLD: it is pressed and held
* MT\_TAP: it is pressed and then released
* DT\_DOUBLTAP: it is pressed, released and tapped again within a certain time
(DOUBLETAP\_TIME\_LIMIT in KeyStates.h)
* DT\_TAP: it is pressed, released and not pressed again for DOUBLETAP\_TIME\_LIMIT

### The activation duration
This is when the key is actually sent:
* Momentary (default): as long as the key is active
* Toggle: as long as a key with the same keycode isn't pressed
* Oneshot: whenever a non modifier or layer keycode is sent, e.g. a oneshot
Shift key makes the next letter into a capital letter

The activation duration can be defined in the following way:
<pre>
    <i>DURATION</i>(<i>HID keycode</i>)
</pre>
e.g.
<pre>
    TG(KC_LSHIFT)
</pre>

These come inside the definition for a layer or a single key.

### The layer
This defines to which layer a HID Keycode, activation method and duration triple corresponds to. 

## Configuration
### The default layer
The default layer is the layer which you will most often use. Here, you give the 
HID Keycode and optionally the activation duration for the default method on the default layer
(currently PRESS and layer 0).
<pre>
    main_layer_t matrix {
    KEYMAP(
        <i>KEYCODE1</i>, <i>KEYCODE2</i>, <i>etc.</i>)
    };
</pre>


## Further layers
You can define layers in the same way as the default layer for any activation method and layer combo, 
e.g. PRESS on layer 1 or MT\_TAP for layer 0. Most of the time, you'll only need press layers unless youuse other activation methods a lot. You will need to add a tuple of this layer using the addLayers function.
<pre>
    layer_t <i>LAYER_NAME</i> {
        KEYMAP(<i>...</i>)
    };

    addLayers({std::make_tuple(<i>LAYER</i>, <i>METHOD</i>, <i>LAYER_NAME</i>), <i>further layers</i>});
</pre>

## Single keys
You'll most likely use this to configure keys with uncommon activation methods, e.g. DT\_DOUBLETAP.
<pre> 
    matrix[<i>row</i>][<i>col</i>].addActivation(<i>LAYER</i>, <i>METHOD</i>, <i>KEYCODE</i>);
</pre>
