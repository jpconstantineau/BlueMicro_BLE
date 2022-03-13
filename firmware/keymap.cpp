// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include "keymap.h"


std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC, \
        KC_TAB,KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS, \
        LAYER_2,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,  \
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT, \
        KC_LCTL,KC_LGUI,KC_LALT,          KC_SPC,                     LAYER_1, KC_RALT, KC_APP,KC_RCTL) };

 
void setupKeymap() {


    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_DEL, \

        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_PSCR,KC_SLCK,KC_PAUS, KC_UP, KC_NO,KC_BSPC, \
        LAYER_2,KC_VOLDOWN,KC_VOLUP,KC_MUTE,KC_NO,KC_NO,KC_PAST,KC_PSLS,KC_HOME,KC_PGUP,KC_LEFT,KC_RGHT,KC_PENT, \
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_PPLS,KC_PMNS,KC_END, KC_PGDN,KC_DOWN,KC_NO,KC_NO, \
        KC_NO,KC_NO,KC_NO,          BIRTHDAY,                      LAYER_1,KC_NO,KC_NO,KC_NO);



    uint32_t layer2[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(

        KC_CAPS,BLEPROFILE_1,BLEPROFILE_2,BLEPROFILE_3,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,SLEEP_NOW, \
        KC_NO,KC_NO,WIN_E_GRAVE,WIN_E_ACUTE,WIN_E_CIRCU,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,PRINT_BATTERY,PRINT_INFO,PRINT_BLE, \
        LAYER_2,UF2_DFU,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,BATTERY_CALC_TEST,BATTERY_CALC_DEFAULT, \
        GITCOMMIT,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_UP, \
        DEBUG,KC_NO,KC_NO,          CHARGE,                    LAYER_1,KC_LEFT,KC_DOWN,KC_RIGHT);



    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_L1, Method::PRESS, layer1[row][col]);
            matrix[row][col].addActivation(_L2, Method::PRESS, layer2[row][col]);
        }
    }

}


void process_user_macros(uint16_t macroid)
{
    switch ((macroid))
    { 
        case GITCOMMIT:
            addStringToQueue("git add .");
            addKeycodeToQueue(KC_ENTER);
            addStringToQueue("git commit -m \"\""); 
            addKeycodeToQueue(KC_LEFT);
        break;
        case (CBR_FN):
            addStringToQueue("{}"); 
            addKeycodeToQueue(KC_LEFT);
        break;
        case (BRC_FN):
            addStringToQueue("[]");
            addKeycodeToQueue(KC_LEFT);
        break;
        case PRN_FN:
            addStringToQueue("()"); 
            addKeycodeToQueue(KC_LEFT);
        break;
        case IPADDR:
            addStringToQueue("192.168.1.");
        break;
        case SMILE:
            addStringToQueue(":)");
        break;
        case CHARGE:
            // Play a little charge melody, from:
            //  https://en.wikipedia.org/wiki/Charge_(fanfare)
            #ifdef ENABLE_AUDIO
/*            speaker.playNoteNow(NOTE_G4, EIGHTH_TRIPLE, true);
            speaker.playNoteNow(NOTE_C5, EIGHTH_TRIPLE, true);
            speaker.playNoteNow(NOTE_E5, EIGHTH_TRIPLE, false);
            speaker.playNoteNow(NOTE_G5, EIGHTH, true);
            speaker.playNoteNow(NOTE_E5, SIXTEENTH, false);
            speaker.playNoteNow(NOTE_G5, HALF, false);*/
            #endif
        break;
        case BIRTHDAY:
            // Play happy birthday tune, from:
            //  http://www.irish-folk-songs.com/happy-birthday-tin-whistle-sheet-music.html#.WXFJMtPytBw
            #ifdef ENABLE_AUDIO
          /*  speaker.playNoteNow(NOTE_D4, EIGHTH, true);
            speaker.playNoteNow(NOTE_D4, EIGHTH);
            speaker.playNoteNow(NOTE_E4, QUARTER);       // Bar 1
            speaker.playNoteNow(NOTE_D4, QUARTER);
            speaker.playNoteNow(NOTE_G4, QUARTER);
            speaker.playNoteNow(NOTE_FS4, HALF);         // Bar 2
            speaker.playNoteNow(NOTE_D4, EIGHTH, true);
            speaker.playNoteNow(NOTE_D4, EIGHTH);
            speaker.playNoteNow(NOTE_E4, QUARTER);       // Bar 3
            speaker.playNoteNow(NOTE_D4, QUARTER);
            speaker.playNoteNow(NOTE_A4, QUARTER);
            speaker.playNoteNow(NOTE_G4, HALF);          // Bar 4
            speaker.playNoteNow(NOTE_D4, EIGHTH, true);
            speaker.playNoteNow(NOTE_D4, EIGHTH);
            speaker.playNoteNow(NOTE_D5, QUARTER);       // Bar 5
            speaker.playNoteNow(NOTE_B4, QUARTER);
            speaker.playNoteNow(NOTE_G4, QUARTER);
            speaker.playNoteNow(NOTE_FS4, QUARTER);      // Bar 6
            speaker.playNoteNow(NOTE_E4, QUARTER);
            speaker.playNoteNow(NOTE_C5, EIGHTH, true);
            speaker.playNoteNow(NOTE_C5, EIGHTH);
            speaker.playNoteNow(NOTE_B4, QUARTER);       // Bar 7
            speaker.playNoteNow(NOTE_G4, QUARTER);
            speaker.playNoteNow(NOTE_A4, QUARTER);
            speaker.playNoteNow(NOTE_G4, HALF);          // Bar 8*/
            #endif
        break;
    }
}
