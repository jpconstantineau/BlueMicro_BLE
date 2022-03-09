// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include "keystate.h"
#include "advanced_keycodes.h"
#include "hid_keycodes.h"
#include <array>
#include <utility>

#ifndef KEY_H
#define KEY_H

#ifndef MAX_NO_LAYERS
#define MAX_NO_LAYERS 10 //6
#endif

typedef struct   {
  uint16_t activations;
  Duration durations __attribute__((packed)); 
} KeyDefinition; 

using KeyDefinitionArray =  std::array<std::array<KeyDefinition, 5>, MAX_NO_LAYERS>;

class Key {
public:
  // cppcheck-suppress noExplicitConstructor     // cannot make this an explicit constructor as we are relying on conversion of keycodes to uint32_t
  Key(uint32_t activation);

  void press(unsigned long currentMillis);
  void clear(unsigned long currentMillis);
  void addActivation(const uint8_t layer, const Method method, const uint32_t activation);
  KeyDefinition getActiveActivation(uint8_t layer);

private:
  Method lastMethod;
  KeyDefinition lastActivation;
  KeyState state;
  KeyDefinitionArray keydefs;
};

#endif /* KEY_H */
