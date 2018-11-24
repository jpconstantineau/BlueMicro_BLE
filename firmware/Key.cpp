#include "Key.h"

//should be called with the keycode of the default layer
Key::Key(uint32_t activation) 
{
    activations[0][0] = static_cast<uint16_t>(activation & 0x0000FFFF); 
    durations[0][0] = static_cast<uint8_t>((activation & 0x00FF0000) >> 16);
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

/*
uint16_t Key::getActivation(uint8_t layer) const 
{
    switch(state.getState()) 
    {
        case KeyState::State::PRESSED:
            return activations[layer][0];
            break;
        case KeyState::State::MT_TAPPED:
            return activations[layer][1];
            break;
        case KeyState::State::MT_HELD:
            return activations[layer][2];
            break;
        case KeyState::State::DT_TAPPED:
            return activations[layer][3];
            break;
        case KeyState::State::DT_DOUBLETAPPED:
            return activations[layer][4];
            break;
        default:
            return 0;
    }
}

uint8_t Key::getDuration(uint8_t layer, uint8_t method) const 
{
    return durations[layer][method];
}
*/
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
     * TODO: layer changes aren't included here 
     */
    if (lastMethod == 0 || method != lastMethod)
    {
        lastMethod = method;
        return std::make_pair(activations[layer][method], durations[layer][method]);
    }
    else 
    {
        return std::make_pair(0, 0);
    }
}

