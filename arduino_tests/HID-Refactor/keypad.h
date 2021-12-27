#ifndef KEYPAD_H
#define KEYPAD_H
#include <Arduino.h>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <iterator>


#ifdef NRF52840_XXAA
#define gpioIn_inv (((uint64_t)(NRF_P1->IN)^0xffffffff)<<32)|(NRF_P0->IN)^0xffffffff
#else
#define gpioIn_inv (NRF_GPIO->IN)^0xffffffff
#endif

#ifdef NRF52840_XXAA
#define gpioIn (((uint64_t)NRF_P1->IN)<<32)|(NRF_P0->IN)
#else
#define gpioIn NRF_GPIO->IN
#endif

#ifdef NRF52840_XXAA
#define PINDATATYPE uint64_t
#else
#define PINDATATYPE uint32_t
#endif

//#define DEBOUNCECOUNT 10

typedef void (*eventActionCallback)();

typedef struct {
  uint32_t timestamp;
  int8_t key_number;
  bool pressed;
} KeyEvent;


typedef struct {
  int8_t key_number;
  eventActionCallback pressed_cb;
  eventActionCallback released_cb;
} KeyEventMap;

class Keypad {
  public:
    virtual ~Keypad()=0;
    virtual void scan(uint32_t timestamp)=0;
    void setupKeymap(std::vector<KeyEventMap>& keymap);
    void process();
    KeyEvent getEvent();
    bool anyEvent();
  protected:
    void press(uint8_t key, uint32_t timestamp);
    void release(uint8_t key, uint32_t timestamp);
  private:
    void updatekeystate(uint8_t key, uint32_t timestamp, bool pressed);
    std::vector<KeyEvent> _events;
    std::vector<KeyEvent> _state;
    std::vector<KeyEventMap> _event_map;
};

class Keys : public Keypad
{
  public:
    void setupPins(std::vector<uint8_t>& pins);
    void setupPins(std::vector<uint8_t>& pins, bool state);
    void setupActiveState(bool state);
    void scan(uint32_t timestamp);
  private:
    std::vector<uint8_t> _pins;
    bool _active_state;
    bool _initialized;
};


#endif /* KEYPAD_H */
