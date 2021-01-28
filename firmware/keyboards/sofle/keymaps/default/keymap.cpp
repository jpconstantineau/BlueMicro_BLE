/*
Copyright 2018 <Pierre Constantineau>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include "keymap.h"
#include "RotaryEncoder.h"


#if KEYBOARD_SIDE == MASTER
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    KEYMAP2ARRAY(KEYMAP(
              KC_1,  KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
              KC_7,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
              KC_8,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
              KC_9,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
              KC_P,  KC_O,    KC_I,    KC_L,    KC_K,    KC_J                      
    ));

void setupKeymap() {

   // no layers for master keymap
   // this is a keymap that's used for testing that each key is responding properly to key presses
   // flash this keymap to both left and right to test whether each half works properly.
   // once tested, you can flash the left and right to their respective halves.

  // Code below makes sure that the encoder gets configured.  
  RotaryEncoder.begin(ENCODER_PAD_A, ENCODER_PAD_B);    // Initialize Encoder
  RotaryEncoder.setCallback(encoder_callback);    // Set callback
  RotaryEncoder.start();    // Start encoder
}

void encoder_callback(int step)
{
  if ( step > 0 )
  {
    KeyScanner::add_to_encoderKeys(KC_AUDIO_VOL_DOWN);
  }else
  {
    KeyScanner::add_to_encoderKeys(KC_AUDIO_VOL_UP);
  }  
}

#endif


#if KEYBOARD_SIDE == LEFT


std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    KEYMAP2ARRAY(KEYMAP(
        KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,  \
        KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T, \
        KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,\
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,\
         KC_LGUI,KC_LALT,KC_LCTRL, LAYER_1, KC_ENT, KC_MUTE \
    ));

 
void setupKeymap() {


    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
              _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, \
              KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  \
              _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, \
              _______,  KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR,  \
               _______, _______, _______, _______, _______,_______\
        );


    uint32_t layer2[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
               _______, _______ , _______ , _______ , _______ , _______, \
              _______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,\
              _______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX, KC_CAPS,\
              _______,KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, XXXXXXX,  \
               _______, _______, _______, _______, _______,_______ \
        );
    /*
     * add the other layers on the regular presses.
     */
  
ADDLAYER(_L1, Method::PRESS , layer1);
ADDLAYER(_L2, Method::PRESS , layer2);
    // if you want to add Tap/Hold or Tap/Doubletap activations, then you add them below.

// Code below makes sure that the encoder gets configured.

  RotaryEncoder.begin(ENCODER_PAD_A, ENCODER_PAD_B);    // Initialize Encoder
  RotaryEncoder.setCallback(encoder_callback);    // Set callback
  RotaryEncoder.start();    // Start encoder
}

void encoder_callback(int step)
{
  uint8_t layer = keyboardstate.layer;
  if ( step > 0 )
  {
      switch(layer)
      {
          case _L0: KeyScanner::add_to_encoderKeys(KC_AUDIO_VOL_UP); break;
          case _L1: KeyScanner::add_to_encoderKeys(KC_RIGHT); break;
          case _L2: KeyScanner::add_to_encoderKeys(LSFT(KC_RIGHT)); break;
          default: ;
      }
  }else
  {
      switch(layer)
      {
          case _L0: KeyScanner::add_to_encoderKeys(KC_AUDIO_VOL_DOWN); break;
          case _L1: KeyScanner::add_to_encoderKeys(KC_LEFT);break;
          case _L2: KeyScanner::add_to_encoderKeys(LSFT(KC_LEFT));break;
          default: ;
      }
  }  
}

#endif  // left

#if KEYBOARD_SIDE == RIGHT
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    KEYMAP2ARRAY(KEYMAP( \
             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV, \
            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_QUOTE, \
            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCOLON, KC_QUOT,\
            KC_N,    KC_M,    KC_COMMA,KC_DOT,  KC_SLSH,   KC_RSFT,\
            KC_MUTE, KC_SPACE,  LAYER_2, KC_RCTRL, KC_RALT, KC_RGUI ));

void setupKeymap() {
    uint32_t layer1[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
            KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,\
            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12, \
            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,\
            KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,\
            _______, _______, _______, _______, _______, _______\
        );


    uint32_t layer2[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
             _______,  _______  , _______,  _______ ,  _______ ,_______,\
            KC_PGUP, XXXXXXX,   KC_UP, XXXXXXX,XXXXXXX, KC_BSPC,\
            KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC, \
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, _______,\
            _______, _______, _______, _______, _______, _______\
        );
    /*
     * add the other layers
     */
ADDLAYER(_L1, Method::PRESS , layer1);
ADDLAYER(_L2, Method::PRESS , layer2);

// Code below makes sure that the encoder gets configured.

  RotaryEncoder.begin(ENCODER_PAD_A, ENCODER_PAD_B);    // Initialize Encoder
  RotaryEncoder.setCallback(encoder_callback);    // Set callback
  RotaryEncoder.start();    // Start encoder
}

void encoder_callback(int step)
{
  uint8_t layer = keyboardstate.layer;
  if ( step > 0 )
  {
      switch(layer)
      {
          case _L0: KeyScanner::add_to_encoderKeys(KC_AUDIO_VOL_DOWN); break;
          case _L1: KeyScanner::add_to_encoderKeys(KC_LEFT); break;
          case _L2: break;
          default: ;
      }
  }else
  {
      switch(layer)
      {
          case _L0: KeyScanner::add_to_encoderKeys(KC_AUDIO_VOL_UP); break;
          case _L1: KeyScanner::add_to_encoderKeys(KC_RIGHT);break;
          case _L2: break;
          default: ;
      }
  }  
}

#endif

