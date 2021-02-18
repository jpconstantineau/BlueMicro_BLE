

[Macro details](https://blog.gboards.ca/2020/02/adventures-in-obscure-c-features-2020.html)
[Combos details](http://combos.gboards.ca/docs/combos/)

From [Germ's Combos and Chords](https://github.com/qmk-combos/qmk-combos.github.io)


# notes

```COMB(ident, keycodeToEmit, SimultaneousPressedKeys...)``` : Send a single keycode. aka, replaces the trigger keys that are simultaneously pressed with the keycode to emit. 

```SUBS(ident, sendStringArg, SimultaneousPressedKeys...)``` : Send Strings and sequences  (aka macro) when the trigger keys are simultaneously pressed.

```PRES(chord, keyOut)``` : Send a single keycode when chord is triggered. Similar to COMB but defined with chord definition.

```KEYS(chord, id, keys)``` : Send keypresses simultaneously when chord is triggered. (shift - A for example)

```SUBS(chord, id, string)``` : Send Strings and sequences  (aka macro) when chord is triggered.

```SPEC(chord, func, arg)``` : Trigger Special functionality when chord is triggered. 

# Parts of a Combo

Using this library with combos you have two functions avalaible for use ```SUBS``` and ```COMB```. 
They stand for Substitute and Combo respectfully. Lets take a look at a dictionary

germ-vim-helpers.def
<script src="https://gist.github.com/germ/49787a86b5693f79b21ef1e3549595c1.js?file=germ-vim-helpers.def"></script>

## COMB()
The ```COMB()``` Macro is responsible for take in a combo and outputting ***a single keypress!***. The general form is ```COMB(ident, keycodeToEmit, keySequence...)``` So Line 3 in the above dictionary takes WE and outputs Escape. 

***Ident***:A unique identifier, something descriptive works, but asdfffdsadf also works.

***keycodeToEmit:***A keycode from the [QMK Keycode list](https://beta.docs.qmk.fm/using-qmk/simple-keycodes/keycodes_basic). This includes Mouse, Shifted and Quantum keycodes.

***keySequence:*** a series of keycodes to be pressed before triggering this output.

## SUBS()
Subs is a very powerful macro and is used for all other sequences. For multicharacter, shifted or well _anything else_ you're going to use SUBS. At it's core it relys on QMKs SEND_STRING()
The general form is similar to COMBs, ```SUBS(ident, sendStringArg, keySequence...)```. So Line 10 outputs
the start of the Interjection copypasta.

***Ident***:A unique identifier, something descriptive works, but asdfffdsadf also works.

***sendStringArg:*** The macro or string to be send by SEND_STRING()

***keySequence:*** a series of keycodes to be pressed before triggering this output.


There is a fundamental difference between the two! A Combo is a native QMK
feature and only applies to multi-key sequences and SEND_STRING(). However
it can't handle layering, processing strokes in chords and many other things
required on smaller or heavily chorded keyboards! The Chording engine is the
solution to this, but only has limited interoperability with QMK.

If you are only using Combos for _augmenting_ a keymap, don't use the chording engine, use the Combos!

## Function Docs

If you have not read the Combo Docs, give those a quick browse. The format used for these chords is similar.
Back? Awesome.

There are four functions that you can call in a dictionary, they are 

```PRES(chord, keyOut)``` : Send a single QMK keycode  
```KEYS(chord, id, keys)``` : Send a sequence of keypresses  
```SUBS(chord, id, string)``` : Send Strings and sequences  
```SPEC(chord, func, arg)``` : Trigger Special functionality/QMK Interop  

And you can use these to make any chorded dictionary! 

## Usage: 
example.def (excerpts from en-keymap.def)

```
PRES(GA,                                  KC_P)                        // Send P
KEYS(GA|GO,        cmb_9df323cdb026f7ce,  {KC_LSFT, KC_9, COMBO_END})  // Send (
SUBS(GR|GI|GO|GP,  str_E21E9A5405E9A529,  "pool ")                     // "pool "
SPEC(GA|GT|GN|GP,  SPEC_STICKY,           NUM)                         // Activate StickyBit for NUM
```

Notes:

-- Only QMK Basic Keycodes can be sent using this engine. For shifted stuff you _must_ use ```KEYS()```!
-- ID can be set to whatever, however it _must_ be unique. If it's not the compiler will yell at you
-- For KEYS the brackets must be included, or the compiler will yell at you.

## SPEC()

There's a few special things that can be done through this code that changes how the engine operates. Heres 
a table of the currently implemented stuff

KeyCode | Arg | Function
-|-|-
SPEC_STICKY | Chord     | This set's/removes the specified bits from stickybits
SPEC_REPEAT | none      | Toggle the repeat mode until toggled off
SPEC_CLICK  | Keycode   | Send the specified mousekey to the mouse subsytem. Requires mousekeys
SPEC_SWITCH | QMK Layer | Turn on the given layer. The user is left to change back to the chorded layer

## Chords 

A chord is just a bitmask made by or'ing together keys. These keys are defined in your ```ENGINE_CONFIG```  
section. When the listed keys are pressed the action is run. The engine will match the longest chord possible!



The default engine mappings are below, if you're doing a custom engine yours will be different. If you're doing this on a normalish keyboard, just make a layout with the following keycode (using the function keys for your thumb keys!

QMK Keycode | Chord Equivelent
-|-
KC_Q|GQ
KC_W|GW
KC_E|GE
KC_R|GR
KC_T|GT
KC_Y|GY
KC_U|GU
KC_I|GI
KC_O|GO
KC_P|GP
KC_A|GA
KC_S|GS
KC_D|GD
KC_F|GF
KC_G|GG
KC_H|GH
KC_J|GJ
KC_K|GK
KC_L|GL
KC_SCLN|GCL
KC_Z|GZ
KC_X|GX
KC_C|GC
KC_V|GV	
KC_B|GB	
KC_N|GN	
KC_M|GM	
KC_COMM|GLT
KC_DOT|GGT
KC_SLSH|GQU
KC_F1|GL1
KC_F2|GL2
KC_F3|GL3
KC_F4|GR3
KC_F5|GR2
KC_F6|GR1		


Clear as mud? Good! Go take a look at some of the dictionaries, they'll make more sense now :)


### C_SIZE

This is the width of your chords in native c++ types. As of right now the engine supports up to 64 states (uint64_t). If you're only using a board that uses 10 keys, you can probably squeeze it into a uint16. 

Helpfully, if you have a STN() call of higher then C_SIZE, the compiler will get angry :)

uint64_t				
uint32_t				
uint16_t	