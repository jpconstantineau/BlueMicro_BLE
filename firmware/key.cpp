// SPDX-FileCopyrightText: 2018-2022 BlueMicro contributors (https://github.com/jpconstantineau/BlueMicro_BLE/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#include "key.h"

// should be called with the keycode of the default layer
Key::Key(uint32_t activation) {

  keydefs[0][0].activations = static_cast<uint16_t>(activation & 0x0000FFFF);
  keydefs[0][0].durations = static_cast<Duration>((activation & 0x00FF0000) >> 16);

  // last method is the "release" method
  lastMethod = Method::NONE;
}

// should be called with
void Key::addActivation(const uint8_t layer, const Method method, const uint32_t activation) {
  auto keycode = static_cast<uint16_t>(activation & 0x0000FFFF);
  auto methodIndex = static_cast<int>(method);

  /*
   * if the activation is transparent,
   * look for the first non transparent activation
   * in the layers below
   */
  uint8_t tempLayer = layer;
  while (keycode == KC_TRNS) {
    /*
     * if the default layer has been reached
     * and that's transparent as well, the key
     * doesn't do anything
     */
    if (tempLayer == 0) {
      keycode = KC_NO;
      break;
    }

    keycode = keydefs[--tempLayer][methodIndex].activations;
  }

  keydefs[layer][methodIndex].activations = keycode;
  keydefs[layer][methodIndex].durations = static_cast<Duration>((activation & 0x00FF0000) >> 16);

  /*
   * tell the state to make sure to look for the added
   * activation
   */
  if (keycode != XXXXXXX) // need to check if there is an actual keycode to send with this method.  We only activate the method if there is a keycode...
  {
    state.addMethod(method);
  }
}

void Key::press(const unsigned long currentMillis) { state.press(currentMillis); }

void Key::clear(const unsigned long currentMillis) { state.clear(currentMillis); }

KeyDefinition Key::getActiveActivation(uint8_t layer) {
  Method method;

  switch (state.getState()) {
  case KeyState::State::PRESSED:
    method = Method::PRESS;
    break;
  case KeyState::State::MT_TAPPED:
    method = Method::MT_TAP;
    break;
  case KeyState::State::MT_HELD:
    method = Method::MT_HOLD;
    break;
  case KeyState::State::DT_TAPPED:
    method = Method::DT_TAP;
    break;
  case KeyState::State::DT_DOUBLETAPPED:
    method = Method::DT_DOUBLETAP;
    break;
  default:
    lastMethod = Method::NONE;
    lastActivation.activations = 0;
    lastActivation.durations = Duration::MOMENTARY;
    return lastActivation;
  }

  const auto methodIndex = static_cast<int>(method);

  /*
   * only activate if the last method is different from
   * the current one, unless it was press
   *
   * this is to make sure that mt/dt activations
   * are only read once - important when toggling
   */
  if (method != lastMethod) {
    lastMethod = method;
    lastActivation = keydefs[layer][methodIndex];
    return lastActivation;
  }
  /*
   * for momentary durations, make sure to return
   * the keycode of the selected layer at press time,
   * as long as it remains pressed, so that releasing
   * the layer key doesn't change the meaning of a key
   * inside that layer
   */
  else if ((lastMethod == Method::PRESS || lastMethod == Method::MT_HOLD) && lastActivation.durations != Duration::TOGGLE)
  // else if ((lastMethod == Method::PRESS ) && lastActivation.second != Duration::TOGGLE)
  {
    return lastActivation;
  } else {
    KeyDefinition elseActivation;
        elseActivation.activations = 0;
        elseActivation.durations = Duration::MOMENTARY;
    return elseActivation;
  }
}
