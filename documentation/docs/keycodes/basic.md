---
id: keycodes_basic
title: Basic Keycodes
slug: /keycodes_basic
---

These keycodes are based on [Universal Serial Bus HID Usage Tables](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf) Document Version 1.12
Chapter 10: Keyboard/Keypad Page(0x07) - Page 53



| Usage ID (HEX) | Usage Name              | Keycode Identifiers        |
| -------------- | ----------------------- | -------------------------- |
| 00             | Reserved (No Event)     | KC_NO        XXXXXXX       |
| 01             | Keyboard ErrorRollOver  | KC_ROLL_OVER   KC_TRANSPARENT   \_\_\_\_\_\_\_   KC_TRNS   |
| 02             | Keyboard PostFail       | KC_POST_FAIL               |
| 03             | Keyboard ErrorUndefined | KC_UNDEFINED               |
| 04             | Keyboard a and A        | KC_A                       |
| 05             | Keyboard b and B        | KC_B                       |
| 06             | Keyboard c and C        | KC_C                       |
| 07             | Keyboard d and D        | KC_D                       |
| 08             | Keyboard e and E        | KC_E                       |
| 09             | Keyboard f and F        | KC_F                       |
| 0A             | Keyboard g and G        | KC_G                       |
| 0B             | Keyboard h and H        | KC_H                       |
| 0C             | Keyboard i and I        | KC_I                       |
| 0D             | Keyboard j and J        | KC_J                       |
| 0E             | Keyboard k and K        | KC_K                       |
| 0F             | Keyboard l and L        | KC_L                       |
| 10             | Keyboard m and M        | KC_M                       |
| 11             | Keyboard n and N        | KC_N                       |
| 12             | Keyboard o and O        | KC_O                       |
| 13             | Keyboard p and P        | KC_P                       |
| 14             | Keyboard q and Q        | KC_Q                       |
| 15             | Keyboard r and R        | KC_R                       |
| 16             | Keyboard s and S        | KC_S                       |
| 17             | Keyboard t and T        | KC_T                       |
| 18             | Keyboard u and U        | KC_U                       |
| 19             | Keyboard v and V        | KC_V                       |
| 1A             | Keyboard w and W        | KC_W                       |
| 1B             | Keyboard x and X        | KC_X                       |
| 1C             | Keyboard y and Y        | KC_Y                       |
| 1D             | Keyboard z and Z        | KC_Z                       |
| 1E             | Keyboard 1 and !        | KC_1                       |
| 1F             | Keyboard 2 and @        | KC_2                       |
| 20             | Keyboard 3 and #        | KC_3                       |
| 21             | Keyboard 4 and $        | KC_4                       |
| 22             | Keyboard 5 and %        | KC_5                       |
| 23             | Keyboard 6 and ^        | KC_6                       |
| 24             | Keyboard 7 and &        | KC_7                       |
| 25             | Keyboard 8 and *        | KC_8                       |
| 26             | Keyboard 9 and (        | KC_9                       |
| 27             | Keyboard 0 and )        | KC_0                       |
| 28             | Keyboard ENTER          | KC_ENTER    KC_ENT         |
| 29             | Keyboard ESCAPE         | KC_ESCAPE   KC_ESC         |
| 2A             | Keyboard BACKSPACE      | KC_BSPACE   KC_BSPC        |
| 2B             | Keyboard TAB            | KC_TAB                     |
| 2C             | Keyboard SPACE          | KC_SPACE   KC_SPC          |
| 2D             | Keyboard - and \_       | KC_MINUS   KC_MINS         |
| 2E             | Keyboard = and +        | KC_EQUAL    KC_EQL         |
| 2F             | Keyboard [ and {        | KC_LBRACKET   KC_LBRC      |
| 30             | Keyboard ] and }        | KC_RBRACKET   KC_RBRC      |
| 31             | Keyboard \\ and \|      | KC_BSLASH    KC_BSLS       |
| 32             | Keyboard Non-US # and ~ | KC_NONUS_HASH   KC_NUHS    |
| 33             | Keyboard ; and :        | KC_SCOLON     KC_SCLN      |
| 34             | Keyboard ' and "        | KC_QUOTE     KC_QUOT       |
| 35             | Keyboard \` and Tilde   | KC_GRAVE    KC_GRV         |
| 36             | Keyboard , and <        | KC_COMMA      KC_COMM      |
| 37             | Keyboard . and >        | KC_DOT                     |
| 38             | Keyboard / and ?        | KC_SLASH       KC_SLSH     |
| 39             | Keyboard CAPS LOCK      | KC_CAPSLOCK    KC_CAPS   KC_CLCK     |
| 3A             | Keyboard F1             | KC_F1                       |
| 3B             | Keyboard F2             | KC_F2                       |
| 3C             | Keyboard F3             | KC_F3                       |
| 3D             | Keyboard F4             | KC_F4                       |
| 3E             | Keyboard F5             | KC_F5                       |
| 3F             | Keyboard F6             | KC_F6                       |
| 40             | Keyboard F7             | KC_F7                      |
| 41             | Keyboard F8             | KC_F8                      |
| 42             | Keyboard F9             | KC_F9                      |
| 43             | Keyboard F10            | KC_F10                     |
| 44             | Keyboard F11            | KC_F11                     |
| 45             | Keyboard F12            | KC_F12                     |
| 46             | Keyboard PrintScreen    | KC_PSCREEN                 |
| 47             | Keyboard Scroll Lock    | KC_SCROLLLOCK              |
| 48             | Keyboard Pause          | KC_PAUSE                   |
| 49             | Keyboard Insert         | KC_INSERT                  |
| 4A             | Keyboard Home           | KC_HOME                    |
| 4B             | Keyboard Page Up        | KC_PGUP                    |
| 4C             | Keyboard Delete         | KC_DELETE                  |
| 4D             | Keyboard End            | KC_END                     |
| 4E             | Keyboard Page Down      | KC_PGDOWN                  |
| 4F             | Keyboard Right Arrow    | KC_RIGHT                   |
| 50             | Keyboard Left Arrow     | KC_LEFT                    |
| 51             | Keyboard Down Arrow     | KC_DOWN                    |
| 52             | Keyboard Up Arrow       | KC_UP                      |
| 53             | Keyboard Num Lock       | KC_NUMLOCK                 |
| 54             | Keypad /                | KC_KP_SLASH                |
| 55             | Keypad *                | KC_KP_ASTERISK             |
| 56             | Keypad -                | KC_KP_MINUS                |
| 57             | Keypad +                | KC_KP_PLUS                 |
| 58             | Keypad Enter            | KC_KP_ENTER                |
| 59             | Keypad 1 and End        | KC_KP_1                    |
| 5A             | Keypad 2 and Down Arrow | KC_KP_2                    |
| 5B             | Keypad 3 and Page Down  | KC_KP_3                    |
| 5C             | Keypad 4 and Left Arrow | KC_KP_4                    |
| 5D             | Keypad 5                | KC_KP_5                    |
| 5E             | Keypad 6 and Right Arrow | KC_KP_6                    |
| 5F             | Keypad 7 and Home       | KC_KP_7                    |
| 60             | Keypad 8 and Up Arrow   | KC_KP_8                    |
| 61             | Keypad 9 and PageUp     | KC_KP_9                    |
| 62             | Keypad 0 and Insert     | KC_KP_0                      |
| 63             | Keypad . and Delete     | KC_KP_DOT                 |
| 64             | Keyboard non-US \\      | KC_NONUS_BSLASH                |
| 65             | Keyboard Application    | KC_APPLICATION             |
| 66             | Keyboard Power          | KC_POWER                |
| 67             | Keypad =                | KC_KP_EQUAL                 |
| 68             | Keyboard F13            | KC_F13                |
| 69             | Keyboard F14            | KC_F14                    |
| 6A             | Keyboard F15            | KC_F15                    |
| 6B             | Keyboard F16            | KC_F16                    |
| 6C             | Keyboard F17            | KC_F17                    |
| 6D             | Keyboard F18            | KC_F18                    |
| 6E             | Keyboard F19            | KC_F19                    |
| 6F             | Keyboard F20            | KC_F20                    |
| 70             | Keyboard F21            | KC_F21                    |
| 71             | Keyboard F22            | KC_F22                    |
| 72             | Keyboard F23            | KC_F23                    |
| 73             | Keyboard F24            | KC_F24                    |
| E0             | Keyboard Left Control   | KC_LCTRL                    |
| E1             | Keyboard Left Shift     | KC_LSHIFT                    |
| E2             | Keyboard Left Alt       | KC_LALT                      |
| E3             | Keyboard Left GUI       | KC_LGUI                 |
| E4             | Keypad Right Control    | KC_RCTRL                |
| E5             | Keypad Right Shift      | KC_RSHIFT             |
| E6             | Keypad Right Alt        | KC_RALT                |
| E7             | Keypad Right GUI        | KC_RGUI                 |

Table is still a work in progress.  Refer to `hid_keycodes.h` and `advanced_keycodes.h` for a detailed list of keycodes.