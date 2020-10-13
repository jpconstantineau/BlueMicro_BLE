#include "keymap.h"

#include <cstdint>

#include "KeyScanner.h"
#include "advanced_keycodes.h"
#include "hid_keycodes.h"

#define LAYER_LOWER 1
#define LAYER_RAISE 2
#define LAYER_ADJUST 3

#define LY_LWR LAYER_1
#define LY_RSE LAYER_2

#define KY_CSPC LCTL(KC_SPC)
#define KY_ZMIN LCTL(KC_EQL)
#define KY_ZMOUT LCTL(KC_MINS)
#define KY_ZMRST LCTL(KC_0)

#if KEYBOARD_SIDE == SINGLE

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix = {
    KEYMAP(
        KC_1,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,
        KC_2,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,
        KC_3,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,
                                                KC_4,     KC_5,   KC_6
    )
};

void setupKeymap() {}

#elif KEYBOARD_SIDE == LEFT

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix = {
    KEYMAP(
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,
        KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,
                                                KC_LCTL,  LY_LWR,   KC_SPC
    )
};

void setupKeymap() {
    std::uint32_t layerLower[MATRIX_ROWS][MATRIX_COLS] = KEYMAP(
        _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,
        KY_CSPC,  KY_ZMRST, KY_ZMOUT, KY_ZMIN,  KC_WBAK,  KC_WFWD,
        _______,  KC_APP,   KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_LGUI,
                                                _______,  _______,  _______
    );

    std::uint32_t layerRaise[MATRIX_ROWS][MATRIX_COLS] = KEYMAP(
        KC_CAPS,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,
        _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,
                                                _______,  _______,  _______
    );

    std::uint32_t layerAdjust[MATRIX_ROWS][MATRIX_COLS] = KEYMAP(
        _______,  _______,  KC_MPLY,  KC_VOLU,  KC_MSTP,  _______,
        _______,  _______,  KC_MPRV,  KC_VOLD,  KC_MNXT,  _______,
        _______,  _______,  _______,  KC_MUTE,  _______,  _______,
                                                _______,  _______,  _______
    );

    for (int row = 0; row < MATRIX_ROWS; ++row) {
        for (int col = 0; col < MATRIX_COLS; ++col) {
            matrix[row][col].addActivation(LAYER_LOWER, Method::PRESS, layerLower[row][col]);
            matrix[row][col].addActivation(LAYER_RAISE, Method::PRESS, layerRaise[row][col]);
            matrix[row][col].addActivation(LAYER_ADJUST, Method::PRESS, layerAdjust[row][col]);
        }
    }
}

#elif KEYBOARD_SIDE == RIGHT

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix = {
    KEYMAP(
                  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
                  KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
                  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
        KC_ENT,   LY_RSE,   KC_RALT
    )
};

void setupKeymap() {
    std::uint32_t layerLower[MATRIX_ROWS][MATRIX_COLS] = KEYMAP(
                  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______,
                  KC_PIPE,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_TILD,
                  KC_BSLS,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_GRV,
        _______,  _______,  _______
    );

    std::uint32_t layerRaise[MATRIX_ROWS][MATRIX_COLS] = KEYMAP(
                  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
                  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_F11,   KC_DEL,
                  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   KC_F12,   KC_INS,
        _______,  _______,  _______
    );

    std::uint32_t layerAdjust[MATRIX_ROWS][MATRIX_COLS] = KEYMAP(
                  _______,  _______,  _______,  _______,  _______,  _______,
                  _______,  _______,  _______,  _______,  _______,  _______,
                  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______
    );

    for (int row = 0; row < MATRIX_ROWS; ++row) {
        for (int col = 0; col < MATRIX_COLS; ++col) {
            matrix[row][col].addActivation(LAYER_LOWER, Method::PRESS, layerLower[row][col]);
            matrix[row][col].addActivation(LAYER_RAISE, Method::PRESS, layerRaise[row][col]);
            matrix[row][col].addActivation(LAYER_ADJUST, Method::PRESS, layerAdjust[row][col]);
        }
    }
}

#endif

void process_user_layers(std::uint16_t layermask) {
    KeyScanner::process_for_tri_layers(LAYER_LOWER, LAYER_RAISE, LAYER_ADJUST);
}
