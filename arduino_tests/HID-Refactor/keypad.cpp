#include "keypad.h"

/*
KEYPAD PARENT CLASS
*/

Keypad::~Keypad()
 {
  
 }
/*
#define MATRIX_ROWS 5
#define MATRIX_COLS 15
#define MATRIX_ROW_PINS {43,30,2,29,26} 
#define MATRIX_COL_PINS {6,5,8,41,4,12,38,24,22,13,15,17,20,9,10} 
#define DIODE_DIRECTION COL2ROW

uint8_t pins[]    = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31   };
uint8_t pincount = sizeof(pins)/sizeof(pins[0]);
 */


void Keypad::press(uint8_t key, uint32_t timestamp)
{
  //Serial.println("pressed");
  updatekeystate(key, timestamp, true);
}

void Keypad::release(uint8_t key, uint32_t timestamp)
{
  //Serial.println("released");
  updatekeystate(key, timestamp, false);
}

void Keypad::updatekeystate(uint8_t key, uint32_t timestamp, bool pressed)
{
  KeyEvent thiskey;
  thiskey.timestamp = timestamp;
  thiskey.key_number = key;
  thiskey.pressed = pressed;
  auto last_state = std::find_if(begin(_state), end(_state), [thiskey](KeyEvent i){ return i.key_number == thiskey.key_number; });
  if (last_state != std::end(_state))
  {
    if ( last_state->pressed == thiskey.pressed )
    {
      ; // no change in state
    }
    else
    {
      _events.push_back(thiskey);
      std::replace_if(_state.begin(), _state.end(),[thiskey](KeyEvent i){ return i.key_number == thiskey.key_number; },thiskey);  
    }
  }
  else // not in state - this should only run the first scan...
  {
     _state.push_back(thiskey);
  }


        
   // find key in state
  // if not found, add to state and add to event
  // if in state, check pressed
    // if different status, update state and add to event
  ;
}


bool Keypad::anyEvent()
{
  return !_events.empty();
}

KeyEvent Keypad::getEvent()
{
  KeyEvent myevent = _events.back();
  _events.pop_back();
  return myevent;
}

void Keypad::setupKeymap(std::vector<KeyEventMap>& keymap)
{
  std::copy(keymap.begin(), keymap.end(), std::back_inserter(_event_map));
}

void Keypad::process()
{
   while (anyEvent())
   {
    KeyEvent data = getEvent();  
    auto km = std::find_if(begin(_event_map), end(_event_map), [data](KeyEventMap i){ return i.key_number == data.key_number; });
    if (km != std::end(_event_map))
    {
      if (data.pressed)
      {
        km->pressed_cb();
      }
      else
      {
        km->released_cb();
      }
    }
  }
}

/*
KEYS CHILD CLASS
*/
void Keys::setupPins(std::vector<uint8_t>& pins)
{
  std::copy(pins.begin(), pins.end(), std::back_inserter(_pins));
}

void Keys::setupPins(std::vector<uint8_t>& pins, bool state)
{
  setupPins(pins);
  setupActiveState(state);
}

void Keys::setupActiveState(bool state)
{
  _active_state = state;
}



void Keys::scan(uint32_t timestamp)
{
   PINDATATYPE pinreg = 0;
   
   if (!_initialized){

     for(auto pin : _pins)
     {
       pinMode(pin, _active_state ? INPUT_PULLDOWN : INPUT_PULLUP);
     }
     nrfx_coredep_delay_us(1); // need for the GPIO lines to settle down electrically before reading.
     _initialized = true;
   }
   if (_active_state)
   {
     pinreg = gpioIn;    // press is active high regardless of activestate
   }
   else
   {
     pinreg = gpioIn_inv;  // press is active high regardless of activestate
   }
   
   uint8_t keyindex = 0;
   for(auto pin : _pins)
   {
      uint8_t keystatus = (pinreg>>g_ADigitalPinMap[pin])&1;
      if(keystatus)    Keypad::press(keyindex, timestamp);
      else             Keypad::release(keyindex, timestamp);
      keyindex++;
   } 
}

/*
KEYMATRIX CHILD CLASS
*/
