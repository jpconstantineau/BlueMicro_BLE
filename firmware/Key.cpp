#include "Key.h"

//should be called with the keycode of the default layer
Key::Key(uint32_t activation) 
{
    activations[0][0] = static_cast<uint16_t>(activation & 0x0000FFFF); 
    durations[0][0] = static_cast<uint8_t>((activation & 0x00FF0000) >> 16);

    //last method is the "release" method
    lastMethod = 5;
}

//should be called with 
void Key::addActivation(const uint8_t layer, const uint8_t method, const uint32_t activation) 
{
    activations[layer][method] = static_cast<uint16_t>(activation & 0x0000FFFF);
    durations[layer][method] = static_cast<uint8_t>((activation & 0x00FF0000) >> 16);

    /*
     * tell the state to make sure to look for the added
     * activation
     */
    state.addMethod(method);
}

void Key::press(const unsigned long currentMillis) 
{
    state.press(currentMillis);
}

void Key::clear(const unsigned long currentMillis) 
{
    state.clear(currentMillis);
}

std::pair<uint16_t, uint8_t> Key::getPair(uint8_t layer)
{
    uint8_t method;

    switch(state.getState()) 
    {
        case KeyState::State::PRESSED:
            method = 0;
            break;
        case KeyState::State::MT_TAPPED:
            method = 1;
            break;
        case KeyState::State::MT_HELD:
            method = 2;
            break;
        case KeyState::State::DT_TAPPED:
            method = 3;
            break;
        case KeyState::State::DT_DOUBLETAPPED:
            method = 4;
            break;
        default:
            lastMethod = 5;
            return std::make_pair(0, 0);
    }

    /*
     * check that the last method is different from 
     * the current one, unless it was press
     *
     * this is to make sure that mt/dt activations
     * are only read once - important when toggling
     */
    if ((lastMethod == 0 && durations[layer][method] != 1) || method != lastMethod)
    {
        lastMethod = method;
        return std::make_pair(activations[layer][method], durations[layer][method]);
    }
    else 
    {
        return std::make_pair(0, 0);
    }
}

