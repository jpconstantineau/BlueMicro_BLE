/*
Copyright 2018-2020 <Pierre Constantineau, Julian Komaromy>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include "Key.h"

//should be called with the keycode of the default layer
Key::Key(uint32_t activation) 
{
    activations[0][0] = static_cast<uint16_t>(activation & 0x0000FFFF); 
    durations[0][0] = static_cast<Duration>((activation & 0x00FF0000) >> 16);

    //last method is the "release" method
    lastMethod = Method::NONE;
}

//should be called with 
void Key::addActivation(const uint8_t layer, const Method method, const uint32_t activation) 
{
    auto keycode = static_cast<uint16_t>(activation & 0x0000FFFF);
    auto methodIndex = static_cast<int>(method);
 
    /*
     * if the activation is transparent,
     * look for the first non transparent activation
     * in the layers below
     */
    uint8_t tempLayer = layer;
    while (keycode == KC_TRNS) 
    {
        /*
         * if the default layer has been reached
         * and that's transparent as well, the key
         * doesn't do anything
         */
        if (tempLayer == 0) {
            keycode = KC_NO;
            break;
        }

        keycode = activations[--tempLayer][methodIndex];
    }

    activations[layer][methodIndex] = keycode;
    durations[layer][methodIndex] = static_cast<Duration>((activation & 0x00FF0000) >> 16);

    /*
     * tell the state to make sure to look for the added
     * activation
     */
    if (keycode  != XXXXXXX)// need to check if there is an actual keycode to send with this method.  We only activate the method if there is a keycode...
    {
       state.addMethod(method);
    }
    
}

void Key::press(const unsigned long currentMillis) 
{
    state.press(currentMillis);
}

void Key::clear(const unsigned long currentMillis) 
{
    state.clear(currentMillis);
}

std::pair<uint16_t, Duration> Key::getActiveActivation(uint8_t layer)
{
    Method method;

    switch(state.getState()) 
    {
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
            lastActivation = std::make_pair(0, Duration::MOMENTARY);
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
    if (method != lastMethod)
    {
        lastMethod = method;
        lastActivation = std::make_pair(activations[layer][methodIndex], durations[layer][methodIndex]);
        return lastActivation;
    }
    /*
     * for momentary durations, make sure to return
     * the keycode of the selected layer at press time,
     * as long as it remains pressed, so that releasing
     * the layer key doesn't change the meaning of a key
     * inside that layer
     */
    else if ((lastMethod == Method::PRESS || lastMethod == Method::MT_HOLD) && lastActivation.second != Duration::TOGGLE)
  // else if ((lastMethod == Method::PRESS ) && lastActivation.second != Duration::TOGGLE)
    {
        return lastActivation;
    }
    else 
    {
        return std::make_pair(0, Duration::MOMENTARY);
    }
}

