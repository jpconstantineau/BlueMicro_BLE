#ifndef HID_QUEUE_H
#define HID_QUEUE_H
#include <cstdint>
#include <vector>
#include <string.h>
#include <arduino.h>
#include "hid_data_structures.h"
#include <bluefruit.h>
#ifdef NRF52840_XXAA  // only the 840 has USB available.
#include "Adafruit_TinyUSB.h"
#endif
#include "hid_utils.h"

#ifdef NRF52840_XXAA  // only the 840 has USB available.
// HID report descriptor using TinyUSB's template
uint8_t const desc_hid_report[] =
{
  TUD_HID_REPORT_DESC_KEYBOARD( HID_REPORT_ID(RID_KEYBOARD) ),
  TUD_HID_REPORT_DESC_MOUSE   ( HID_REPORT_ID(RID_MOUSE) ),
  TUD_HID_REPORT_DESC_CONSUMER( HID_REPORT_ID(RID_CONSUMER_CONTROL) )
};
#endif

class HID_Queues {
    public:
    HID_Queues();
    HID_Queues(BLEHidAdafruit* ble_hid);
    #ifdef NRF52840_XXAA  // only the 840 has USB available.
      HID_Queues(Adafruit_USBD_HID* usb_hid);
      HID_Queues(Adafruit_USBD_HID* usb_hid, BLEHidAdafruit* ble_hid);
    #endif

    
    // keyboard functions to add to queue
    void keyboardReport(HIDKeyboard* report);
    void keyboardReport(uint8_t modifier, uint8_t keycode[6]);
    void keyboardPress(char ch);
    void keyboardRelease();
    void keySequence(const char* str);

    // consumer functions to add to queue
    void consumerReport(HIDConsumer* report);
    void consumerReport(uint16_t usage_code);
    void consumerKeyPress(uint16_t usage_code);
    void consumerKeyRelease();

    // mouse functions to add to queue
    void mouseReport(HIDMouse* report);
    void mouseReport(uint8_t buttons, int8_t x, int8_t y, int8_t wheel, int8_t pan);
    void mouseButtonPress(uint8_t buttons);
    void mouseButtonRelease();
    void mouseMove(int8_t x, int8_t y);
    void mouseScroll(int8_t wheel);
    void mousePan(int8_t pan);

    // gamepad functions to add to queue
    //gamepadreportButtons(uint32_t button_mask);
    //gamepadreportHat(uint8_t hat);
    //gamepadreportJoystick(int8_t x, int8_t y, int8_t z, int8_t rz, int8_t rx, int8_t ry);

    // Functions to retreive from queues
    HIDKeyboard getKeyboardReport();
    HIDMouse getMouseReport();
    HIDConsumer getConsumerReport();
    HIDGamepad getGamepadReport();

    // Functions to see if queue has data
    bool isKeyboardQueueEmpty();
    bool isMouseQueueEmpty();
    bool isConsumerQueueEmpty();
    bool isGamepadQueueEmpty();

    // Empty queues from data
    void clearKeyboardQueue();
    void clearMouseQueue();
    void clearConsumerQueue();
    void clearGamepadQueue();

    #ifdef NRF52840_XXAA  // only the 840 has USB available.
        void processQueuesWithUSB();
    #endif
    void processQueuesWithBLE();
    void processQueues(connectionMode mode);
    
    private:
    void addKeyboardReport(HIDKeyboard* report);
    void addMouseReport(HIDMouse* report);
    void addConsumerReport(HIDConsumer* report);
    void addGamepadReport(HIDGamepad* report);
    connectionState connection;
    
    static std::vector<HIDKeyboard> keycode_queue;
    static std::vector<HIDMouse>    mouse_queue;
    static std::vector<HIDConsumer> consumer_queue;
    static std::vector<HIDGamepad>  gamepad_queue;
    #ifdef NRF52840_XXAA  // only the 840 has USB available.
      Adafruit_USBD_HID* usb_hid_driver;
    #endif
    BLEHidAdafruit* ble_hid_driver;
    };

#endif /* HID_QUEUE_H */
