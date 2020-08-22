# Adding a new Keyboard to BlueMicro

There are 4 files that either need to be edited or created for you to add your keyvoard

* keyboard_config.h: where the KEYMAP remapping macro is defined and where Bluetooth configuration is held.
* hardware_config.h: where your keyboard matrix is defined.
* keymap.cpp: main file you need to edit for your keymaps
* keymap.h: include file where you can add your own definitions.


A copy of these 4 files is kept in the "firmware" folder.  This is the copy of the file that's compiled when you load the firmware in the Arduino IDE.  Build scripts overwrite these files from the keyboards folder structure.

You add a new keyboard to the BlueMicro_BLE repository using the following steps:

### Prepare files and Folders

* Create a new folder in the "keyboards" folder.  The folder name is the name of your board.
* Create a sub-folder called "keymaps".
* Create a sub-folder called "config".
* Create a sub-folder called "hardware".
* Create a sub-folder in "keymaps" called "default".  
* Copy keymap.h in "default"
* Create a sub-folder for each of your config layouts. Use "single" if a single keyboard is used.  Use "left" and "right" if two halves are needed. Note that these can be named anything you like, and you can use this folder name to differentiate between different versions of the same board.
* Copy "keyboard_config.h" in each of the config folders.
* Create a sub-folder in "hardware" for the fuly qualified board name (fqbn) you have. Options are "feather52832", "feather52840", "pca10056". 
* Create a sub-folder in the fqbn folder with your GPIO configuration name. Examples are "BlueMicro840", "NiceNano", "nrfmicro".
* Copy hardware_config.h in the GPIO configuration folder (the one just created above). 

### Edit Keyboard Config

* Edit "DEVICE_NAME_R","DEVICE_NAME_L","DEVICE_NAME_M".  Default name for a single keyboard is DEVICE_NAME_M. For split boards, the other two will be used.
* Edit "DEVICE_MODEL", "MANUFACTURER_NAME"
* Edit "KEYMAP". If there are multiple different keymaps; for example with reversible left/right boards, define multiple KEYMAP with the appropriate reversed mapping. You can also use this macro transform the matrix into any shaped keyboard you like. For example an 8x8 matrix can be remapped to a 4x16 keyboard.

### Edit Hardware Config

* Edit "MATRIX_ROWS" with the number of rows
* Edit "MATRIX_COLS" with the number of columns
* Edit "DIODE_DIRECTION" to either "COL2ROW" or 'ROW2COL"
* Edit "MATRIX_ROW_PINS" to the GPIO numbers
* Edit "MATRIX_COL_PINS" to the GPIO numbers

### Edit Keymap files (.cpp and .h)

* Create the necessary defines for "Layer IDs" in h file.
* Create the KEYMAP for each layer.
* If there are multiple keyboard configs, make sure you have the appropriate #if statements to select the right/left keymap for the config.

### Compile

* Run the build scripts to test all config/map combinations.
* Fix whatever doesn't compile...
* Find more details in the building firmware page.

### Flash/Test

* Flash to your board to test that everything works fine.
* Find details on how to flash the firmware on the flashing page.

### Share

* Commit to GIT to share with everyone...