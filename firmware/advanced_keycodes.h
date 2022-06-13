// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include <cstdint>
#ifndef ADVANCED_KEYCODES_H
#define ADVANCED_KEYCODES_H

enum class Duration {
    MOMENTARY = 0,
    TOGGLE = 1,
    ONE_SHOT = 2,
};

#define MOD(M, KC) ((uint16_t) KC | (uint16_t) M)

#define BIT_LCTRL (1)
#define BIT_LSHIFT (2)
#define BIT_LALT (4)
#define BIT_LGUI (8)
#define BIT_RCTRL (16)
#define BIT_RSHIFT (32)
#define BIT_RALT (64)
#define BIT_RGUI (128)

#define MOD_LCTRL (BIT_LCTRL << 8)
#define MOD_LSHIFT (BIT_LSHIFT << 8)
#define MOD_LALT (BIT_LALT << 8)
#define MOD_LGUI (BIT_LGUI << 8)
#define MOD_RCTRL (BIT_RCTRL << 8)
#define MOD_RSHIFT (BIT_RSHIFT << 8)
#define MOD_RALT (BIT_RALT << 8)
#define MOD_RGUI (BIT_RGUI << 8)

#define MC(KC) (((uint16_t) KC << 8 ) | KC_RESERVED_A5 )             // move KC to upper 8 bits and use KC_RESERVED_A5 keycode for marking this as a macro.
#define KB(KC) (((uint16_t) KC << 8 ) | KC_RESERVED_A6 )             // move KC to upper 8 bits and use KC_RESERVED_A6 keycode for marking this as a special keyboard function.
#define MK(KC) (((uint16_t) KC << 8 ) | KC_RESERVED_A7 )             // move KC to upper 8 bits and use KC_RESERVED_A7 keycode for marking this as a media key.
#define MR(KC) (((uint16_t) KC << 8 ) | KC_RESERVED_A8 )             // move KC to upper 8 bits and use KC_RESERVED_A8 keycode for marking this as a repeating media key.
#define MS(KC) (((uint16_t) KC << 8 ) | KC_RESERVED_A9 )             // move KC to upper 8 bits and use KC_RESERVED_A9 keycode for marking this as a mouse key.
#define KS(KC) (((uint16_t) KC << 8 ) | KC_RESERVED_AA )             // move KC to upper 8 bits and use KC_RESERVED_AA keycode for marking this as a special key.
#define KI(KC) (((uint16_t) KC << 8 ) | KC_RESERVED_AB )             // move KC to upper 8 bits and use KC_RESERVED_AB keycode for marking this as a macro for international/special characters (ALT-0233 = é).
#define KINT(KC) (((uint16_t) KC << 8 ) | KC_RESERVED_AE )             // Internal Keyboard Functions

#define TG(KC) ((static_cast<int>(Duration::TOGGLE) << 16) | KC)
#define OS(KC) ((static_cast<int>(Duration::ONE_SHOT) << 16) | KC)
#define MAC(KC) ((static_cast<int>(Duration::ONE_SHOT) << 16) |  (KC << 8 ) | KC_RESERVED_A5)
#define S(KC) MOD(MOD_LSHIFT, KC)

#define SEND_KC(KC) (static_cast<uint8_t>(KC & 0x00FF))

// define any shift/ctl/alt key combinations
#define KC_TILD MOD(MOD_LSHIFT, KC_GRV)
#define KC_EXLM MOD(MOD_LSHIFT, KC_1)
#define KC_AT   MOD(MOD_LSHIFT, KC_2)
#define KC_HASH MOD(MOD_LSHIFT, KC_3)
#define KC_DLR  MOD(MOD_LSHIFT, KC_4)
#define KC_PERC MOD(MOD_LSHIFT, KC_5)
#define KC_CIRC MOD(MOD_LSHIFT, KC_6)
#define KC_AMPR MOD(MOD_LSHIFT, KC_7)
#define KC_ASTR MOD(MOD_LSHIFT, KC_8)
#define KC_LPRN MOD(MOD_LSHIFT, KC_9)
#define KC_RPRN MOD(MOD_LSHIFT, KC_0)
#define KC_UNDS MOD(MOD_LSHIFT, KC_MINUS)
#define KC_PLUS MOD(MOD_LSHIFT, KC_EQUAL)

#define KC_LCBR MOD(MOD_LSHIFT, KC_LBRC)
#define KC_RCBR MOD(MOD_LSHIFT, KC_RBRC)
#define KC_PIPE MOD(MOD_LSHIFT, KC_BSLS)

#define KC_COLN MOD(MOD_LSHIFT, KC_SCLN)
#define KC_DQUO MOD(MOD_LSHIFT, KC_QUOTE)
#define KC_DQT  KC_DQUO

#define KC_LT   MOD(MOD_LSHIFT, KC_COMMA)
#define KC_GT   MOD(MOD_LSHIFT, KC_DOT)
#define KC_QUES MOD(MOD_LSHIFT, KC_SLASH)

#define KC_NUTL MOD(MOD_LSHIFT,KC_NUHS) // Non-US # and ~
#define KC_NUPI MOD(MOD_LSHIFT,KC_NUBS) // Non-US \ and |

#define LALT(KEY) MOD(MOD_LALT, KEY)
#define RALT(KEY) MOD(MOD_RALT, KEY)
#define LCTL(KEY) MOD(MOD_LCTRL, KEY)
#define RCTL(KEY) MOD(MOD_RCTRL, KEY)
#define RSFT(KEY) MOD(MOD_RSHIFT, KEY)
#define LSFT(KEY) MOD(MOD_LSHIFT, KEY)
#define LGUI(KEY) MOD(MOD_LGUI, KEY)
#define RGUI(KEY) MOD(MOD_RGUI, KEY)


#define SETUP_HID       COMMANDID(0)
#define SETUP_GPIO      COMMANDID(1) 
#define SETUP_WDT       COMMANDID(2)
#define SETUP_SERIAL    COMMANDID(3)
#define SETUP_VCCSWITCH COMMANDID(4) 
#define SETUP_CHARGER   COMMANDID(5) 
#define SETUP_KEYMAP    COMMANDID(6) 
#define SETUP_MATRIX    COMMANDID(7) 

#define LED_ENABLE      COMMANDID(9)
#define LED_HELLO       COMMANDID(10)
#define LED_UPDATE      COMMANDID(11)

#define PROCESSS_WDT    COMMANDID(12)
#define PROCESSS_MATRIX COMMANDID(13)
#define UPDATE_KEYS     COMMANDID(14)
#define RENDER_HID      COMMANDID(15)
#define RENDER_SLEEP    COMMANDID(16)
#define UPDATE_UNPAIR   COMMANDID(17)
#define RENDER_UNPAIR   COMMANDID(18)
#define UPDATE_SAVE     COMMANDID(19)
#define RENDER_SAVE     COMMANDID(20)
#define UPDATE_FORMAT   COMMANDID(21)
#define RENDER_FORMAT   COMMANDID(22)
#define UPDATE_REBOOT   COMMANDID(23)
#define RENDER_REBOOT   COMMANDID(24)
#define BATTERY_UPDATE  COMMANDID(25)

#define RUN_COMMAND_QUEUE   COMMANDID(254)
#define CLEAR_COMMAND_QUEUE COMMANDID(255)

#endif
