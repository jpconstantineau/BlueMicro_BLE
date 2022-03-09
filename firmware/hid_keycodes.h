// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

/*
These keycodes are based on Universal Serial Bus HID Usage Tables Document 
Version 1.12
Chapter 10: Keyboard/Keypad Page(0x07) - Page 53
https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
 */

#ifndef HID_KEYCODES_H
#define HID_KEYCODES_H

/*
 * Short names for ease of definition of keymap
 */
#define KC_LCTL KC_LCTRL
#define KC_RCTL KC_RCTRL
#define KC_LSFT KC_LSHIFT
#define KC_RSFT KC_RSHIFT
#define KC_ESC  KC_ESCAPE
#define KC_BSPC KC_BSPACE
#define KC_ENT  KC_ENTER
#define KC_DEL  KC_DELETE
#define KC_INS  KC_INSERT
#define KC_CAPS KC_CAPSLOCK
#define KC_CLCK KC_CAPSLOCK
#define KC_RGHT KC_RIGHT
#define KC_PGDN KC_PGDOWN
#define KC_PSCR KC_PSCREEN
#define KC_SLCK KC_SCROLLLOCK
#define KC_PAUS KC_PAUSE
#define KC_BRK  KC_PAUSE
#define KC_NLCK KC_NUMLOCK
#define KC_SPC  KC_SPACE
#define KC_MINS KC_MINUS
#define KC_EQL  KC_EQUAL
#define KC_GRV  KC_GRAVE
#define KC_RBRC KC_RBRACKET
#define KC_LBRC KC_LBRACKET
#define KC_COMM KC_COMMA
#define KC_BSLS KC_BSLASH
#define KC_SLSH KC_SLASH
#define KC_SCLN KC_SCOLON
#define KC_QUOT KC_QUOTE
#define KC_APP  KC_APPLICATION
#define KC_NUHS KC_NONUS_HASH
#define KC_NUBS KC_NONUS_BSLASH
#define KC_LCAP KC_LOCKING_CAPS
#define KC_LNUM KC_LOCKING_NUM
#define KC_LSCR KC_LOCKING_SCROLL
#define KC_ERAS KC_ALT_ERASE
#define KC_CLR  KC_CLEAR
/* Japanese specific */
#define KC_ZKHK KC_GRAVE
#define KC_RO   KC_INT1
#define KC_KANA KC_INT2
#define KC_JYEN KC_INT3
#define KC_HENK KC_INT4
#define KC_MHEN KC_INT5
/* Korean specific */
#define KC_HAEN KC_LANG1
#define KC_HANJ KC_LANG2
/* Keypad */
#define KC_P1   KC_KP_1
#define KC_P2   KC_KP_2
#define KC_P3   KC_KP_3
#define KC_P4   KC_KP_4
#define KC_P5   KC_KP_5
#define KC_P6   KC_KP_6
#define KC_P7   KC_KP_7
#define KC_P8   KC_KP_8
#define KC_P9   KC_KP_9
#define KC_P0   KC_KP_0
#define KC_PDOT KC_KP_DOT
#define KC_PCMM KC_KP_COMMA
#define KC_PSLS KC_KP_SLASH
#define KC_PAST KC_KP_ASTERISK
#define KC_PMNS KC_KP_MINUS
#define KC_PPLS KC_KP_PLUS
#define KC_PEQL KC_KP_EQUAL
#define KC_PENT KC_KP_ENTER
/* Unix function key */
#define KC_EXEC KC_EXECUTE
#define KC_SLCT KC_SELECT
#define KC_AGIN KC_AGAIN
#define KC_PSTE KC_PASTE
/* Mousekey */
#define KC_MS_U KC_MS_UP
#define KC_MS_D KC_MS_DOWN
#define KC_MS_L KC_MS_LEFT
#define KC_MS_R KC_MS_RIGHT
#define KC_BTN1 KC_MS_BTN1
#define KC_BTN2 KC_MS_BTN2
#define KC_BTN3 KC_MS_BTN3
#define KC_BTN4 KC_MS_BTN4
#define KC_BTN5 KC_MS_BTN5
#define KC_WH_U KC_MS_WH_UP
#define KC_WH_D KC_MS_WH_DOWN
#define KC_WH_L KC_MS_WH_LEFT
#define KC_WH_R KC_MS_WH_RIGHT
#define KC_ACL0 KC_MS_ACCEL0
#define KC_ACL1 KC_MS_ACCEL1
#define KC_ACL2 KC_MS_ACCEL2

/* Transparent */
#define KC_TRANSPARENT  1
#define KC_TRNS KC_TRANSPARENT
/* GUI key aliases */
#define KC_LCMD KC_LGUI
#define KC_LWIN KC_LGUI
#define KC_RCMD KC_RGUI
#define KC_RWIN KC_RGUI
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define  KC_LABK KC_LT
#define  KC_RABK KC_GT

/* USB HID Keyboard/Keypad Usage(0x07) */
enum hid_keyboard_keypad_usage {
    KC_NO               = 0x00,
    KC_ROLL_OVER,       // this is equivalent to KC_TRANSPARENT
    KC_POST_FAIL,       
    KC_UNDEFINED,       
    KC_A,
    KC_B,
    KC_C,
    KC_D,
    KC_E,
    KC_F,
    KC_G,
    KC_H,
    KC_I,
    KC_J,
    KC_K,
    KC_L,
    KC_M,               /* 0x10 */
    KC_N,
    KC_O,
    KC_P,
    KC_Q,
    KC_R,
    KC_S,
    KC_T,
    KC_U,
    KC_V,
    KC_W,
    KC_X,
    KC_Y,
    KC_Z,
    KC_1,
    KC_2,
    KC_3,               /* 0x20 */
    KC_4,
    KC_5,
    KC_6,
    KC_7,
    KC_8,
    KC_9,
    KC_0,
    KC_ENTER,
    KC_ESCAPE,
    KC_BSPACE,
    KC_TAB,
    KC_SPACE,
    KC_MINUS,
    KC_EQUAL,
    KC_LBRACKET,
    KC_RBRACKET,        /* 0x30 */
    KC_BSLASH,          /* \ (and |) */
    KC_NONUS_HASH,      /* Non-US # and ~ (Typically near the Enter key) */
    KC_SCOLON,          /* ; (and :) */
    KC_QUOTE,           /* ' and " */
    KC_GRAVE,           /* Grave accent and tilde */
    KC_COMMA,           /* , and < */
    KC_DOT,             /* . and > */
    KC_SLASH,           /* / and ? */
    KC_CAPSLOCK,
    KC_F1,
    KC_F2,
    KC_F3,
    KC_F4,
    KC_F5,
    KC_F6,
    KC_F7,              /* 0x40 */
    KC_F8,
    KC_F9,
    KC_F10,
    KC_F11,
    KC_F12,
    KC_PSCREEN,
    KC_SCROLLLOCK,
    KC_PAUSE,
    KC_INSERT,
    KC_HOME,
    KC_PGUP,
    KC_DELETE,
    KC_END,
    KC_PGDOWN,
    KC_RIGHT,
    KC_LEFT,            /* 0x50 */
    KC_DOWN,
    KC_UP,
    KC_NUMLOCK,
    KC_KP_SLASH,
    KC_KP_ASTERISK,
    KC_KP_MINUS,
    KC_KP_PLUS,
    KC_KP_ENTER,
    KC_KP_1,
    KC_KP_2,
    KC_KP_3,
    KC_KP_4,
    KC_KP_5,
    KC_KP_6,
    KC_KP_7,
    KC_KP_8,            /* 0x60 */
    KC_KP_9,
    KC_KP_0,
    KC_KP_DOT,
    KC_NONUS_BSLASH,    /* Non-US \ and | (Typically near the Left-Shift key) */
    KC_APPLICATION,
    KC_POWER,
    KC_KP_EQUAL,
    KC_F13,
    KC_F14,
    KC_F15,
    KC_F16,
    KC_F17,
    KC_F18,
    KC_F19,
    KC_F20,
    KC_F21,             /* 0x70 */
    KC_F22,
    KC_F23,
    KC_F24,
    KC_EXECUTE,
    KC_HELP,
    KC_MENU,
    KC_SELECT,
    KC_STOP,
    KC_AGAIN,
    KC_UNDO,
    KC_CUT,
    KC_COPY,
    KC_PASTE,
    KC_FIND,
    KC_MUTE,
    KC_VOLUP,          /* 0x80 */
    KC_VOLDOWN,
    KC_LOCKING_CAPS,    /* locking Caps Lock */
    KC_LOCKING_NUM,     /* locking Num Lock */
    KC_LOCKING_SCROLL,  /* locking Scroll Lock */
    KC_KP_COMMA,
    KC_KP_EQUAL_AS400,  /* equal sign on AS/400 */
    KC_INT1,
    KC_INT2,
    KC_INT3,
    KC_INT4,
    KC_INT5,
    KC_INT6,
    KC_INT7,
    KC_INT8,
    KC_INT9,
    KC_LANG1,           /* 0x90 */
    KC_LANG2,
    KC_LANG3,
    KC_LANG4,
    KC_LANG5,
    KC_LANG6,
    KC_LANG7,
    KC_LANG8,
    KC_LANG9,
    KC_ALT_ERASE,
    KC_SYSREQ,
    KC_CANCEL,
    KC_CLEAR,
    KC_PRIOR,
    KC_RETURN,
    KC_SEPARATOR,
    KC_OUT,             /* 0xA0 */
    KC_OPER,
    KC_CLEAR_AGAIN,
    KC_CRSEL,
    KC_EXSEL,           /* 0xA4 */

    KC_RESERVED_A5, /*0xA5 to 0xAF - RESERVED*/ // Used as macro identifier
    KC_RESERVED_A6,                             // this is used for special keyboard functions
    KC_RESERVED_A7,
    KC_RESERVED_A8,
    KC_RESERVED_A9,
    KC_RESERVED_AA,
    KC_RESERVED_AB,
    KC_RESERVED_AC,
    KC_RESERVED_AD,
    KC_RESERVED_AE,
    KC_RESERVED_AF,
#if 0
    /* NOTE: Following codes(0xB0-DD) are not used but are in the HID Document. Leaving them for reference. */
    KC_KP_00            = 0xB0,
    KC_KP_000,
    KC_THOUSANDS_SEPARATOR,
    KC_DECIMAL_SEPARATOR,
    KC_CURRENCY_UNIT,
    KC_CURRENCY_SUB_UNIT,
    KC_KP_LPAREN, KC_KP_RPAREN,
    KC_KP_LCBRACKET,    /* { */
    KC_KP_RCBRACKET,    /* } */
    KC_KP_TAB,
    KC_KP_BSPACE,
    KC_KP_A,
    KC_KP_B,
    KC_KP_C,
    KC_KP_D,
    KC_KP_E,            /* 0xC0 */
    KC_KP_F,
    KC_KP_XOR,
    KC_KP_HAT,
    KC_KP_PERC,
    KC_KP_LT,
    KC_KP_GT,
    KC_KP_AND,
    KC_KP_LAZYAND,
    KC_KP_OR,
    KC_KP_LAZYOR,
    KC_KP_COLON,
    KC_KP_HASH,
    KC_KP_SPACE,
    KC_KP_ATMARK,
    KC_KP_EXCLAMATION,
    KC_KP_MEM_STORE,    /* 0xD0 */
    KC_KP_MEM_RECALL,
    KC_KP_MEM_CLEAR,
    KC_KP_MEM_ADD,
    KC_KP_MEM_SUB,
    KC_KP_MEM_MUL,
    KC_KP_MEM_DIV,
    KC_KP_PLUS_MINUS,
    KC_KP_CLEAR,
    KC_KP_CLEAR_ENTRY,
    KC_KP_BINARY,
    KC_KP_OCTAL,
    KC_KP_DECIMAL,
    KC_KP_HEXADECIMAL,  /* 0xDD */
#endif

    /* Modifiers */
    KC_LCTRL            = 0xE0,
    KC_LSHIFT,
    KC_LALT,
    KC_LGUI,
    KC_RCTRL,
    KC_RSHIFT,
    KC_RALT,
    KC_RGUI,

  
};

#define LAYER_0      0xF0
#define LAYER_1      0xF1
#define LAYER_2      0xF2
#define LAYER_3      0xF3
#define LAYER_4      0xF4
#define LAYER_5      0xF5
#define LAYER_6      0xF6
#define LAYER_7      0xF7
#define LAYER_8      0xF8
#define LAYER_9      0xF9
#define LAYER_A      0xFA
#define LAYER_B      0xFB
#define LAYER_C      0xFC
#define LAYER_D      0xFD
#define LAYER_E      0xFE
#define LAYER_F      0xFF

#define RESET               KB(KC_A)   
#define DEBUG               KB(KC_B)
#define EEPROM_RESET        KB(KC_C)
#define EEP_RST             EEPROM_RESET
#define DFU                 KB(KC_D)
#define SERIAL_DFU          KB(KC_E)
#define UF2_DFU             KB(KC_ESC)
#define CLEAR_BONDS         KB(KC_F)

#define BL_TOGG             KB(KC_G)
#define BL_STEP             KB(KC_H)
#define BL_ON               KB(KC_I)
#define BL_OFF              KB(KC_J)
#define BL_INC              KB(KC_K)
#define BL_DEC              KB(KC_L)
#define BL_BRTG             KB(KC_M)
#define BL_REACT            KB(KC_N)
#define BL_STEPINC          KB(KC_O)
#define BL_STEPDEC          KB(KC_P)

#define OUT_AUTO            KB(KC_Q)
#define OUT_USB             KB(KC_R)
#define OUT_BT              KB(KC_S) 

#define RGB_TOG             KB(KC_T) 
#define RGB_MODE_FORWARD    KB(KC_U) 
#define RGB_MOD             RGB_MODE_FORWARD
#define RGB_MODE_REVERSE	KB(KC_V) 
#define RGB_RMOD            RGB_MODE_REVERSE
#define RGB_HUI             KB(KC_W) 
#define RGB_HUD             KB(KC_X) 
#define RGB_SAI             KB(KC_Y) 
#define RGB_SAD             KB(KC_Z) 
#define RGB_VAI             KB(KC_1) 
#define RGB_VAD             KB(KC_2) 
#define RGB_MODE_PLAIN      KB(KC_3) 
#define RGB_M_P             RGB_MODE_PLAIN
#define RGB_MODE_BREATHE    KB(KC_4) 
#define RGB_M_B             RGB_MODE_BREATHE
#define RGB_MODE_RAINBOW    KB(KC_5) 
#define RGB_M_R             RGB_MODE_RAINBOW 
#define RGB_MODE_SWIRL      KB(KC_6) 
#define RGB_M_SW            RGB_MODE_SWIRL
#define RGB_MODE_SNAKE      KB(KC_7) 
#define RGB_M_SN            RGB_MODE_SNAKE
#define RGB_MODE_KNIGHT     KB(KC_8) 
#define RGB_M_K             RGB_MODE_KNIGHT
#define RGB_MODE_XMAS       KB(KC_9) 
#define RGB_M_X             RGB_MODE_XMAS
#define RGB_MODE_GRADIENT   KB(KC_0) 
#define RGB_M_G             RGB_MODE_GRADIENT
#define RGB_MODE_RGBTEST    KB(KC_F1) 
#define RGB_M_T             RGB_MODE_RGBTEST
#define RGB_SPI             KB(KC_F2) 
#define RGB_SPD             KB(KC_F3) 

#define PRINT_BATTERY       KB(KC_F4)
#define PRINT_INFO          KB(KC_F5)
#define PRINT_BLE           KB(KC_F6)
#define PRINT_HELP          KB(KC_F7)
#define BLEPROFILE_1        KB(KC_F8)       
#define BLEPROFILE_2        KB(KC_F9)
#define BLEPROFILE_3        KB(KC_F10)
#define SLEEP_NOW           KB(KC_F11)
#define HELP_MODE           KB(KC_F12)

#define BATTERY_CALC_DEFAULT  KB(KC_F13)
#define BATTERY_CALC_TEST     KB(KC_F14)
#define BATTERY_CALC_FILTERED KB(KC_F15) // TODO: bring the akudaikon filtered method for switching between USB connected/not connected.

// Power Control
#define KC_SYSTEM_POWER      MK(KC_A) //HID_USAGE_CONSUMER_POWER  
#define KC_SYSTEM_RESET      MK(KC_B) //HID_USAGE_CONSUMER_RESET          
#define KC_SYSTEM_SLEEP	     MK(KC_C) //HID_USAGE_CONSUMER_SLEEP    

// Screen Brightness
#define KC_DISPLAY_BRIGHTI   MK(KC_D) //HID_USAGE_CONSUMER_BRIGHTNESS_INCREMENT
#define KC_DISPLAY_BRIGHTD   MK(KC_E) //HID_USAGE_CONSUMER_BRIGHTNESS_DECREMENT

  // These HID usages operate only on mobile systems (battery powered) and
  // require Windows 8 (build 8302 or greater).
#define KC_RADIO_CONTROL     MK(KC_F) //  HID_USAGE_CONSUMER_WIRELESS_RADIO_CONTROLS           
#define KC_RADIO_BUTTONS	 MK(KC_G) //  HID_USAGE_CONSUMER_WIRELESS_RADIO_BUTTONS            
#define KC_RADIO_LED	     MK(KC_H) //  HID_USAGE_CONSUMER_WIRELESS_RADIO_LED                
#define KC_RADIO_SWITCH	     MK(KC_I) //  HID_USAGE_CONSUMER_WIRELESS_RADIO_SLIDER_SWITCH      

// Media Control
#define KC_MEDIA_PLAY_PAUSE	 MK(KC_K) //HID_USAGE_CONSUMER_PLAY_PAUSE  
#define KC_MEDIA_NEXT_TRACK  MK(KC_L) //HID_USAGE_CONSUMER_SCAN_NEXT         
#define KC_MEDIA_PREV_TRACK  MK(KC_M) //HID_USAGE_CONSUMER_SCAN_PREVIOUS    
#define KC_MEDIA_STOP	     MK(KC_N) //HID_USAGE_CONSUMER_STOP
#define KC_AUDIO_VOL         MK(KC_O) //HID_USAGE_CONSUMER_VOLUME   
#define KC_AUDIO_MUTE	     MK(KC_P) //HID_USAGE_CONSUMER_MUTE  
#define KC_AUDIO_BASS        MK(KC_Q) //HID_USAGE_CONSUMER_BASS 
#define KC_AUDIO_TREBLE      MK(KC_R) //HID_USAGE_CONSUMER_TREBLE 
#define KC_AUDIO_BASS_BOOST  MK(KC_S) //HID_USAGE_CONSUMER_BASS_BOOST           
#define KC_AUDIO_VOL_UP      MR(KC_T) //HID_USAGE_CONSUMER_VOLUME_INCREMENT 
#define KC_AUDIO_VOL_DOWN    MR(KC_U) //HID_USAGE_CONSUMER_VOLUME_DECREMENT  
#define KC_AUDIO_BASS_UP     MR(KC_V) //HID_USAGE_CONSUMER_BASS_INCREMENT      
#define KC_AUDIO_BASS_DOWN   MR(KC_W) //HID_USAGE_CONSUMER_BASS_DECREMENT          
#define KC_AUDIO_TREBLE_UP   MR(KC_X) //HID_USAGE_CONSUMER_TREBLE_INCREMENT           
#define KC_AUDIO_TREBLE_DOWN MR(KC_Y) //HID_USAGE_CONSUMER_TREBLE_DECREMENT     

 // Application Launcher  
#define KC_MSEL              MK(KC_Z) //HID_USAGE_CONSUMER_AL_CONSUMER_CONTROL_CONFIGURATION 
#define KC_WWW               MK(KC_1) //HID_USAGE_CONSUMER_AL_EMAIL_READER   
#define KC_MAIL              KC_WWW   // not sure about this one...
#define KC_CALCULATOR        MK(KC_2) //HID_USAGE_CONSUMER_AL_CALCULATOR    
#define KC_MYCM              MK(KC_3) //HID_USAGE_CONSUMER_AL_LOCAL_BROWSER  

// Browser/Explorer Specific
#define KC_WWW_SEARCH	     MK(KC_4) //HID_USAGE_CONSUMER_AC_SEARCH         
#define KC_WWW_HOME	         MK(KC_5) //HID_USAGE_CONSUMER_AC_HOME          
#define KC_WWW_BACK	         MK(KC_6) //HID_USAGE_CONSUMER_AC_BACK          
#define KC_WWW_FORWARD	     MK(KC_7) //HID_USAGE_CONSUMER_AC_FORWARD     
#define KC_WWW_STOP	         MK(KC_8) //HID_USAGE_CONSUMER_AC_STOP      
#define KC_WWW_REFRESH	     MK(KC_9) //HID_USAGE_CONSUMER_AC_REFRESH     
#define KC_WWW_FAVORITES     MK(KC_0) //HID_USAGE_CONSUMER_AC_BOOKMARKS     

 // Mouse Horizontal scroll
#define KC_AC_PAN            MK(KC_F1) //HID_USAGE_CONSUMER_AC_PAN 

#define KC_PWR 	            KC_SYSTEM_POWER
#define KC_SLEP             KC_SYSTEM_SLEEP
#define KC_MUTE             KC_AUDIO_MUTE
#define KC_VOLU             KC_AUDIO_VOL_UP
#define KC_VOLD             KC_AUDIO_VOL_DOWN
#define KC_MNXT             KC_MEDIA_NEXT_TRACK 
#define KC_MPRV             KC_MEDIA_PREV_TRACK
#define KC_MSTP             KC_MEDIA_STOP
#define KC_MPLY             KC_MEDIA_PLAY_PAUSE
#define KC_CALC             KC_CALCULATOR
#define KC_WSCH             KC_WWW_SEARCH
#define KC_WHOM             KC_WWW_HOME
#define KC_WBAK             KC_WWW_BACK
#define KC_WFWD             KC_WWW_FORWARD
#define KC_WSTP             KC_WWW_STOP
#define KC_WREF             KC_WWW_REFRESH
#define KC_WFAV             KC_WWW_FAVORITES


// Mouse keycodes...
#define KC_MS_OFF    MS(KC_A)
#define KC_MS_UP     MS(KC_B)
#define KC_MS_DOWN   MS(KC_C)
#define KC_MS_LEFT   MS(KC_D)
#define KC_MS_RIGHT  MS(KC_E)
#define KC_MS_BTN1   MS(KC_F)
#define KC_MS_BTN2   MS(KC_G)
#define KC_MS_BTN3   MS(KC_H)
#define KC_MS_BTN4   MS(KC_I)
#define KC_MS_BTN5   MS(KC_J)
#define KC_MS_WH_UP     MS(KC_K)
#define KC_MS_WH_DOWN   MS(KC_L)
#define KC_MS_WH_DN             KC_MS_WH_DOWN
#define KC_MS_WH_LEFT   MS(KC_M)
#define KC_MS_WH_RIGHT  MS(KC_N)
#define KC_MS_ACCEL0  MS(KC_O)  // Slow speed = 1
#define KC_MS_ACCEL1  MS(KC_P)  // normal speed = #define MOVE_STEP   8; you can redefine it in your keyboard_config.h
#define KC_MS_ACCEL2  MS(KC_Q)  // fast speed = 2*MOVE_STEP


// these international characters work on windows
#define WIN_A_GRAVE    KI(KC_A) //Alt 0224 a grave
#define WIN_A_ACUTE    KI(KC_B) //Alt 0225 a acute
#define WIN_A_CIRCU    KI(KC_C) //Alt 0226 a circumflex
#define WIN_A_TILDE    KI(KC_D) //Alt 0227 a tilde
#define WIN_A_UMLAU    KI(KC_E) //Alt 0228 a umlaut

#define WIN_A_GRAVE_CAP    KI(KC_F) //Alt 0192 A grave
#define WIN_A_ACUTE_CAP    KI(KC_G) //Alt 0193 A acute
#define WIN_A_CIRCU_CAP    KI(KC_H) //Alt 0194 A circumflex
#define WIN_A_TILDE_CAP    KI(KC_I) //Alt 0195 A tilde
#define WIN_A_UMLAU_CAP    KI(KC_J) //Alt 0196 A umlaut

#define WIN_C_CEDIL        KI(KC_K) //Alt 0231 c cedilla
#define WIN_C_CEDIL_CAP    KI(KC_L) //Alt 0199 C cedilla

#define WIN_E_GRAVE    KI(KC_M) //Alt 0232 e grave
#define WIN_E_ACUTE    KI(KC_N) //Alt 0233 e acute
#define WIN_E_CIRCU    KI(KC_O) //Alt 0234 e circumflex
#define WIN_E_UMLAU    KI(KC_P) //Alt 0235 e umlaut

#define WIN_E_GRAVE_CAP    KI(KC_Q) //Alt 0200 E grave
#define WIN_E_ACUTE_CAP    KI(KC_R) //Alt 0201 E acute
#define WIN_E_CIRCU_CAP    KI(KC_S) //Alt 0202 E circumflex
#define WIN_E_UMLAU_CAP    KI(KC_T) //Alt 0203 E umlaut

#define WIN_I_GRAVE    KI(KC_U) //Alt 0236 i grave
#define WIN_I_ACUTE    KI(KC_V) //Alt 0237 i acute
#define WIN_I_CIRCU    KI(KC_W) //Alt 0238 i circumflex
#define WIN_I_UMLAU    KI(KC_X) //Alt 0239 i umlaut

#define WIN_I_GRAVE_CAP    KI(KC_Y) //Alt 0204 I grave
#define WIN_I_ACUTE_CAP    KI(KC_Z) //Alt 0205 I acute
#define WIN_I_CIRCU_CAP    KI(KC_DOT) //Alt 0206 I circumflex
#define WIN_I_UMLAU_CAP    KI(KC_COMMA) //Alt 0207 I umlaut

#define WIN_N_TILDE        KI(KC_SPACE) //Alt 164 n tilde
#define WIN_N_TILDE_CAP    KI(KC_BSPACE) //Alt 165 N tilde

#define WIN_O_GRAVE    KI(KC_1) //Alt 0242 o grave
#define WIN_O_ACUTE    KI(KC_2) //Alt 0243 o acute
#define WIN_O_CIRCU    KI(KC_3) //Alt 0244 o circumflex
#define WIN_O_TILDE    KI(KC_4) //Alt 0245 o tilde
#define WIN_O_UMLAU    KI(KC_5) //Alt 0246 o umlaut

#define WIN_O_GRAVE_CAP    KI(KC_6) //Alt 0210 O grave
#define WIN_O_ACUTE_CAP    KI(KC_7) //Alt 0211 O acute
#define WIN_O_CIRCU_CAP    KI(KC_8) //Alt 0212 O circumflex
#define WIN_O_TILDE_CAP    KI(KC_9) //Alt 0213 O tilde
#define WIN_O_UMLAU_CAP    KI(KC_0) //Alt 0214 O umlaut

#define WIN_S_CARON        KI(KC_MINUS) //Alt 0154 s caron
#define WIN_S_CARON_CAP    KI(KC_EQUAL) //Alt 0138 S caron

#define WIN_U_GRAVE    KI(KC_F1) //Alt 0249 u grave
#define WIN_U_ACUTE    KI(KC_F2) //Alt 0250 u acute
#define WIN_U_CIRCU    KI(KC_F3) //Alt 0251 u circumflex
#define WIN_U_UMLAU    KI(KC_F4) //Alt 0252 u umlaut

#define WIN_U_GRAVE_CAP    KI(KC_F5) //Alt 0217 U grave
#define WIN_U_ACUTE_CAP    KI(KC_F6) //Alt 0218  U acute
#define WIN_U_CIRCU_CAP    KI(KC_F7) //Alt 0219 U circumflex
#define WIN_U_UMLAU_CAP    KI(KC_F8) //Alt 0220 U umlaut

#define WIN_Y_ACUTE        KI(KC_F9) //Alt 0253 y acute
#define WIN_Y_UMLAU        KI(KC_F10) //Alt 0255 y umlaut

#define WIN_Y_ACUTE_CAP    KI(KC_F11) //Alt 0221 Y tilde
#define WIN_Y_UMLAU_CAP    KI(KC_F12) //Alt 0159 Y umlaut

#define WIN_Z_CARON        KI(KC_F13) //Alt 0154 z caron
#define WIN_Z_CARON_CAP    KI(KC_F14) //Alt 0138 Z caron

#define SYM_DEGREE         KI(KC_F15) //alt 0176 degree symbol

#define EXPAND_ALT_CODE(CODE1, CODE2, CODE3, CODE4)  addKeycodeToQueue(CODE1,BIT_LALT); addKeycodeToQueue(CODE2,BIT_LALT); addKeycodeToQueue(CODE3,BIT_LALT); addKeycodeToQueue(CODE4,BIT_LALT);

#endif /* HID_KEYCODES_H */

