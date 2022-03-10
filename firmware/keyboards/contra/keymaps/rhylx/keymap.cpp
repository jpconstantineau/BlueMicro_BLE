#include "keymap.h"

// XXXXXXX = nothing    _______ = transparent = use lower layer keycode

/*
 LAYOUT 0 :
  ____ ____ ____ ____ ____ ____ ____ ____ ____ ____ ____ ____
 |    | Q  | W  | E  | R  | T  | Y  | U  | I  | O  | P  |    |
 | TAB| q  | w  | e  | r  | t  | y  | u  | i  | o  | p  | L2 |
 =============================================================
 | ^  | A  | S  | D  | F  | G  | :  | H  | J  | K  | L  | ^  |
 | |  | a  | s  | d  | f  | g  | .  | h  | j  | k  | l  | |  |
 =============================================================
 | ^  | Z  | X  | C  | V  | B  | N  | M  | É  | ^  | ?  | ç  |
 | |  | z  | x  | c  | v  | b  | n  | m  | é  | `  | !  | @  |
 =============================================================
 |    |    |    |    |    |    |    |    |    |    |    |    |
 | L1 |    |CTRL| SUP| ESC| |_|| <- | ENT| L1 | ALT|    | L2 |
 =============================================================
*/


std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {{
        {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,    KC_U,   KC_I,    KC_O,     KC_P,    LAYER_3 },
        {KC_RSE,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_DOT,  KC_H,   KC_J,    KC_K,     KC_L,    KC_RSE  },
        {KC_RSE,  KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,    KC_M,   KC_KP_1, KC_GRAVE, KC_EXLM, KC_AT   },
        {LAYER_2, XXXXXXX, KC_LCTL, KC_LGUI, KC_ESC, KC_SPC, KC_BSPC, KC_ENT, LAYER_2, KC_LALT,  XXXXXXX, LAYER_3 }
    }};


void setupKeymap() {


    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
        KC_TAB,  S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y),    S(KC_U), S(KC_I), S(KC_O), S(KC_P), LAYER_3,
        KC_RSE,  S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_SCLN), S(KC_H), S(KC_J), S(KC_K), S(KC_L), KC_RSE ,
        KC_RSE,  S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N),    S(KC_M), KC_KP_2, KC_KP_3, KC_QUES, KC_KP_4,
        LAYER_2, XXXXXXX, KC_LCTL, KC_LGUI, KC_ESC,  KC_SPC,  KC_BSPC,    KC_ENT,  LAYER_2, KC_LALT, XXXXXXX, LAYER_3 );


/*
LAYOUT 1 :
  ____ ____ ____ ____ ____ ____ ____ ____ ____ ____ ____ ____
 |    |    |    |    |    |    |    |    |    |    |    |    |
 | TAB|  # |  > |  - | {  | +  | '  | 7  | 8  | 9  |CpsL| L2 |
 =============================================================
 | ^  |    |    |    |    |    |    |    |    |    |    |  ^ |
 | |  |  § |  / |  $ | (  | [  | ,  | 4  | 5  | 6  |  | |  | |
 =============================================================
 | ^  |    |    |    |    |    |    |    |    |    |    |    |
 | |  |LEFT|DOWN| UP |RGHT|    | 0  | 1  | 2  | 3  | &  |    |
 =============================================================
 |    |    |    |    |    |    |    |    |    |    |    |    |
 | L1 |    |CTRL| SUP| ESC| |_|| <- | ENT| L1 | ALT|    | L2 |
 =============================================================
*/

    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    KC_TAB,  KC_HASH, KC_GT,   KC_MINS, KC_LCBR, KC_PLUS, KC_QUOT, KC_7,   KC_8,    KC_9,    KC_CLCK, LAYER_3,
    KC_RSE,  KC_KP_5, KC_SLSH, KC_DLR,  KC_LPRN, KC_LBRC, KC_COMM, KC_4,   KC_5,    KC_6,    KC_PIPE, KC_RSE,
    KC_RSE,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_0,    KC_1,   KC_2,    KC_3,    KC_AMPR, XXXXXXX,
    LAYER_2, XXXXXXX, KC_LCTL, KC_LGUI, KC_ESC,  KC_SPC,  KC_BSPC, KC_ENT, LAYER_2, KC_LALT, XXXXXXX, LAYER_3 );

/*
 LAYOUT 2:
  ____ ____ ____ ____ ____ ____ ____ ____ ____ ____ ____ ____
 |    |    |    |    |    |    |    |    |    |    |    |    |
 | TAB|  % |  < |  _ | }  | ´  | "  | *  |    |    |    | L2 |
 =============================================================
 | ^  |    |    |    |    |    |    |    |    |    |    |  ^ |
 | |  |  ~ |  \ |  $ | )  | ]  | ;  | =  |    |    |  | |  | |
 =============================================================
 | ^  |    |    |    |    |    |    |    |    |    |    |    |
 | |  |LEFT|DOWN| UP |RGHT| ¨  |    |    |    |    |    |    |
 =============================================================
 |    |    |    |    |    |    |    |    |    |    |    |    |
 | L1 |    |CTRL| SUP| ESC| |_|| <- | ENT| L1 | ALT|    | L2 |
 =============================================================
*/

    uint32_t layer2[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP(
    KC_TAB,  KC_PERC, KC_LT,   KC_UNDS, KC_RCBR, KC_KP_6, KC_DQT,  KC_ASTR, XXXXXXX, XXXXXXX, XXXXXXX, LAYER_3,
    KC_RSE,  KC_TILD, KC_BSLS, KC_DLR,  KC_RPRN, KC_RBRC, KC_SCLN, KC_EQL,  XXXXXXX, XXXXXXX, KC_PIPE, KC_RSE,
    KC_RSE,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_KP_7, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,
    LAYER_2, XXXXXXX, KC_LCTL, KC_LGUI, KC_ESC,  KC_SPC,  KC_BSPC, KC_ENT,  LAYER_2, KC_LALT, XXXXXXX, LAYER_3 );


    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_RAISE,  Method::PRESS,   raise[row][col]);
            matrix[row][col].addActivation(_L1,     Method::PRESS,   layer1[row][col]);
            matrix[row][col].addActivation(_L2,     Method::PRESS,   layer2[row][col]);
        }
    }

}