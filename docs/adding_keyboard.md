# Adding a new Keyboard to BlueMicro

You add a new keyboard to BlueMicro_BLE using the following steps

### Prepare files and Folders

* Create a new folder in the "keyboards" folder.  The folder name is the name of our board.
* Create a sub-folder called "keymaps".
* Create a sub-folder in "keymaps" called "default".  
* Copy keymap.h in "default"
* Create a sub-folder for each of your hardware layouts. Use "master" if a single keyboard is used.  Use "left" and "right" if two halves are needed. Note that these can be named anything you like, and you can use this to differentiate between different versions of the same board including different Pro Micro hardware mappings.
* Copy "keyboard_config.h" in each of the layout folders.

### Edit Keyboard Config

* Edit "DEVICE_NAME", "DEVICE_MODEL", "MANUFACTURER_NAME"
* Edit "MATRIX_ROWS" with the number of rows
* Edit "MATRIX_COLS" with the number of columns
* Edit "DIODE_DIRECTION" to either "COL2ROW" or 'ROW2COL"
* Edit "MATRIX_ROW_PINS" to the GPIO pin numbers or their Pro Micro mapped equivalent
* Edit "MATRIX_COL_PINS" to the GPIO pin numbers or their Pro Micro mapped equivalent
* Edit "KEYMAP". If there are multiple different keymaps; for example with reversible left/right boards, define multiple KEYMAP with the appropriate reversed mapping. You can also use this macro transform the matrix into any shaped keyboard you like. For example an 8x8 matrix can be remapped to a 4x16 keyboard.
* Edit "HARDWARE_MAPPING" if your board uses a Pro Micro footprint board. Pick your variant from `breakout_mapping.h`.


### Edit Keymaps

* Create the necessary defines for "Layer IDs"
* Create the KEYMAP for each layer.
* If there are multiple keyboard configs, make sure you have the appropriate #if statements to select the right keymap for the config.

### Compile

* Run the build scripts to test all config/map combinations.
* Fix whatever doesn't compile...
* Find more details in the building firmware page.

### Flash/Test

* Flash to your board to test that everything works fine.
* Find details on how to flash the firmware on the flashing page.

### Share

* Commit to GIT to share with everyone...