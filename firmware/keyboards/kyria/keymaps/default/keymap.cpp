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
              KC_7,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
              KC_8,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
              KC_9,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_N, KC_M,
                                       KC_P,    KC_O,    KC_I,  KC_L, KC_K                      
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

void process_user_layers(uint16_t layermask) 
{

}

#endif


#if KEYBOARD_SIDE == LEFT


std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    KEYMAP2ARRAY(KEYMAP(
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T, \
        KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,\
        KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_BSPC, KC_ESC,\
                                   KC_LGUI, KC_LALT, L_LOWER, KC_SPC,  KC_LCTRL \
    ));

 
void setupKeymap() {


    uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
              KC_GRV,  KC_1,    KC_2,   KC_3,    KC_4,    KC_5,  \
              _______, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC, \
              _______, KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_LSFT, _______,\
                                        _______, _______, _______, _______, _______ \
        );


    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
              _______, KC_INS,    KC_PSCR,   XXXXXXX,   XXXXXXX,   XXXXXXX,\
              _______, KC_LALT,   KC_LCTL,   KC_LSFT,   XXXXXXX,   KC_CAPS,\
              _______, LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V),XXXXXXX, _______, _______,\
                                              _______,  _______,   _______, _______, _______ \
        );
		
    uint32_t adjust[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
              _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  \
              _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
              _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,\
                                         _______, _______, _______, _______, _______ \
        );
    /*
     * add the other layers on the regular presses.
     */
  
ADDLAYER(_LOWER, Method::PRESS , lower);
ADDLAYER(_RAISE, Method::PRESS , raise);
ADDLAYER(_ADJUST, Method::PRESS, adjust);
    // if you want to add Tap/Hold or Tap/Doubletap activations, then you add them below.

// Code below makes sure that the encoder gets configured.

  RotaryEncoder.begin(ENCODER_PAD_A, ENCODER_PAD_B);    // Initialize Encoder
  RotaryEncoder.setCallback(encoder_callback);    // Set callback
  RotaryEncoder.start();    // Start encoder
}

void encoder_callback(int step)
{
  if ( step > 0 )
  {
      switch(KeyScanner::localLayer)
      {
          case _LOWER: break;
          case _RAISE: break;
          default: KeyScanner::add_to_encoderKeys(KC_AUDIO_VOL_DOWN);
      }
  }else
  {
      switch(KeyScanner::localLayer)
      {
          case _LOWER: break;
          case _RAISE: break;
          default: KeyScanner::add_to_encoderKeys(KC_AUDIO_VOL_UP);
      }
  }  
}

void process_user_layers(uint16_t layermask)
{
    KeyScanner::process_for_tri_layers(_LOWER, _RAISE, _ADJUST);
}

#endif  // left



#if KEYBOARD_SIDE == RIGHT


std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    KEYMAP2ARRAY(KEYMAP( \
                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_BSPC, \
                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCOLON, KC_QUOT,\
        KC_RSFT, KC_DEL, KC_N,    KC_M,    KC_COMMA,KC_DOT,  KC_SLSH,   KC_ENT,\
        KC_ENT,  KC_SPC, L_RAISE, KC_RALT, KC_RGUI 
	));

void setupKeymap() {

    uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,\
                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,\
        _______, _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,\
        _______, _______, _______, _______, _______\
        );

    uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
                          KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX, KC_BSPC,\
                          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,  KC_BSPC, \
        _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,\
        _______, _______, _______, _______, _______\
        );
		
    uint32_t adjust[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
                          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,\
                          XXXXXXX, XXXXXXX, XXXXXXX, KC_F11,  KC_F12,  _______,\
        _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,\
        _______, _______, _______, _______, _______\
        );
    /*
     * add the other layers
     */
ADDLAYER(_LOWER, Method::PRESS , lower);
ADDLAYER(_RAISE, Method::PRESS , raise);
ADDLAYER(_ADJUST, Method::PRESS, adjust);
// Code below makes sure that the encoder gets configured.

  RotaryEncoder.begin(ENCODER_PAD_A, ENCODER_PAD_B);    // Initialize Encoder
  RotaryEncoder.setCallback(encoder_callback);    // Set callback
  RotaryEncoder.start();    // Start encoder
}

void encoder_callback(int step)
{
  if ( step > 0 )
  {
      switch(KeyScanner::localLayer)
      {
          case _LOWER: break;
          case _RAISE: break;
          default: KeyScanner::add_to_encoderKeys(KC_PGDN);
      }
  }else
  {
      switch(KeyScanner::localLayer)
      {
          case _LOWER: break;
          case _RAISE: break;
          default: KeyScanner::add_to_encoderKeys(KC_PGUP);
      }
  }  
}

void process_user_layers(uint16_t layermask)
{
    KeyScanner::process_for_tri_layers(_LOWER, _RAISE, _ADJUST);
}
#endif
