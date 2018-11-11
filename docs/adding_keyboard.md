# Adding a new Keyboard to BlueMicro

You add a new keyboard to BlueMicro_BLE using the following steps

### Prepare files and Folders

* Create a new folder in the "keyboards" folder.  The folder name is the name of our board.
* Create a sub-folfer called "keymaps".
* Create a sub-folder in "keymaps" called "default".  
* Copy keymap.h in "default"
* Create a sub-folder for each of your hardware layouts. Use "master" if a single keyboard is used.  Use "left" and "right" if two halves are needed.
* copy "keyboard_config.h" in each of the layout folders.

### Edit Keyboard Config

* Edit "DEVICE_NAME", "DEVICE_MODEL", "MANUFACTURER_NAME"
* Edit "MATRIX_ROWS" with the number of rows
* Edit "MATRIX_COLS" with the number of columns
* Edit "DIODE_DIRECTION" to either "COL2ROW" or 'ROW2COL"
* Edit "MATRIX_ROW_PINS" to the GPIO pin numbers or their Pro Micro mapped equivalent
* Edit "MATRIX_COL_PINS" to the GPIO pin numbers or their Pro Micro mapped equivalent
* Edit "KEYMAP". If there are multiple different keynmaps; for example with reversible left/right boards, define multiple KEYMAP with the appropriate reversed mapping.


### Edit Keymaps

* Create the necessary defines for "Layer IDs"
* Create the KEYMAP for each layer.
* If there are multiple keyboard configs, make sure you have the appropriate #if statements to select the right keymap for the config.

### Compile

* Run the build scripts to test all config/map combinations.
* Fix whatever doesn't compile...

### Flash/Test

* Flash to your board to test that everything works fine.

### Share

* Commit to GIT to share with everyone...