#include "hid_queues.h"

HID_Queues::HID_Queues()
{
  ;
}

HID_Queues::HID_Queues(BLEHidAdafruit* ble_hid)
{
  ble_hid_driver = ble_hid;
}

#ifdef NRF52840_XXAA  // only the 840 has USB available.
HID_Queues::HID_Queues(Adafruit_USBD_HID* usb_hid)
{
  usb_hid_driver = usb_hid;
}

HID_Queues::HID_Queues(Adafruit_USBD_HID* usb_hid, BLEHidAdafruit* ble_hid)
{
  usb_hid_driver = usb_hid;
  ble_hid_driver = ble_hid;
}
#endif

void HID_Queues::keyboardReport(HIDKeyboard* report)
{
  addKeyboardReport(report);
}

void HID_Queues::keyboardReport(uint8_t modifier, uint8_t keycode[6])
{
  HIDKeyboard report =
  {
      .modifier = modifier,
  };
  memcpy(report.keycode, keycode, 6);
  keyboardReport(&report);
}

void HID_Queues::keyboardPress(char ch)
{
  HIDKeyboard report;
  report.keycode[0] = 0;
  report.keycode[1] = 0;
  report.keycode[2] = 0;
  report.keycode[3] = 0;
  report.keycode[4] = 0;
  report.keycode[5] = 0;

  report.modifier = ( hid_ascii_to_keycode[(uint8_t)ch][0] ) ? KEYBOARD_MODIFIER_LEFTSHIFT : 0;
  report.keycode[0] = hid_ascii_to_keycode[(uint8_t)ch][1];
  keyboardReport(&report);
}

void HID_Queues::keyboardRelease()
{
  HIDKeyboard report;
  report.modifier = 0;
  report.keycode[0] = 0;
  report.keycode[1] = 0;
  report.keycode[2] = 0;
  report.keycode[3] = 0;
  report.keycode[4] = 0;
  report.keycode[5] = 0;
  keyboardReport(&report);
}

void HID_Queues::keySequence(const char* str)
{
   // Send each key in sequence
  char ch;
  while( (ch = *str++) != 0 )
  {
    char lookahead = *str;
    keyboardPress(ch);

    /* Only need to empty report if the next character is NULL or the same with
     * the current one, else no need to send */
    if ( lookahead == ch || lookahead == 0 )
    {
      keyboardRelease();
    }
  }
}

void HID_Queues::consumerReport(HIDConsumer* report)
{
  addConsumerReport(report);
}

void HID_Queues::consumerReport(uint16_t usage_code)
{
  HIDConsumer report =
  {
      .usage_code = usage_code,
  };
  consumerReport(&report);
}

void HID_Queues::consumerKeyPress(uint16_t usage_code)
{
  consumerReport(usage_code); 
}

void HID_Queues::consumerKeyRelease()
{
  uint16_t code = 0;
  consumerReport(code); 
}

void HID_Queues::mouseReport(HIDMouse* report)
{
  addMouseReport(report);
}

void HID_Queues::mouseReport(uint8_t buttons, int8_t x, int8_t y, int8_t wheel, int8_t pan)
{
  HIDMouse report;
  report.buttons = buttons;
  report.x = x;
  report.y = y; 
  report.wheel = wheel; 
  report.pan = pan;
  mouseReport(&report); 
}

void HID_Queues::mouseButtonPress(uint8_t buttons)
{
  mouseReport(buttons, 0, 0, 0, 0);
}

void HID_Queues::mouseButtonRelease()
{
 mouseReport(0,0,0,0,0);
}

void HID_Queues::mouseMove(int8_t x, int8_t y)
{
 mouseReport(0,x,y,0,0);
}

void HID_Queues::mouseScroll(int8_t wheel)
{
 mouseReport(0, 0, 0, wheel,0) ;
}

void HID_Queues::mousePan(int8_t pan)
{
  mouseReport(0, 0, 0, 0, pan);
}

HIDKeyboard HID_Queues::getKeyboardReport()
{
    HIDKeyboard reportdata  = keycode_queue.back();
    keycode_queue.pop_back();
    return reportdata;
}

HIDMouse HID_Queues::getMouseReport()
{
    HIDMouse reportdata  = mouse_queue.back();
    mouse_queue.pop_back();
    return reportdata;
}

HIDConsumer HID_Queues::getConsumerReport()
{
    HIDConsumer reportdata  = consumer_queue.back();
    consumer_queue.pop_back();
    return reportdata;
}

HIDGamepad HID_Queues::getGamepadReport()
{
    HIDGamepad reportdata  = gamepad_queue.back();
    gamepad_queue.pop_back();
    return reportdata;
}
    
bool HID_Queues::isKeyboardQueueEmpty()
{
  return keycode_queue.empty();
}

bool HID_Queues::isMouseQueueEmpty()
{
  return mouse_queue.empty();
}

bool HID_Queues::isConsumerQueueEmpty()
{
  return consumer_queue.empty();
}

bool HID_Queues::isGamepadQueueEmpty()
{
  return gamepad_queue.empty();
}

void HID_Queues::clearKeyboardQueue()
{
    keycode_queue.clear();
}

void HID_Queues::clearMouseQueue()
{
    mouse_queue.clear();
}

void HID_Queues::clearConsumerQueue()
{
    consumer_queue.clear();
}

void HID_Queues::clearGamepadQueue()
{
    gamepad_queue.clear();
}
#ifdef NRF52840_XXAA  // only the 840 has USB available.
void HID_Queues::processQueuesWithUSB()
{
  // Remote wakeup
  if (( TinyUSBDevice.suspended() && ((!isMouseQueueEmpty()) || (!isKeyboardQueueEmpty()) || (!isConsumerQueueEmpty())) ))
  {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    TinyUSBDevice.remoteWakeup();
  }
  if ( usb_hid_driver->ready() && !isMouseQueueEmpty())
  {
    HIDMouse ms_report;
    ms_report = getMouseReport();
    usb_hid_driver->mouseReport(RID_MOUSE, ms_report.buttons, ms_report.x, ms_report.y, ms_report.wheel, ms_report.pan);
    delay(10);
  }
  if ( usb_hid_driver->ready() && !isKeyboardQueueEmpty())
  {
    HIDKeyboard kb_report;
    kb_report = getKeyboardReport();
    usb_hid_driver->keyboardReport(RID_KEYBOARD, kb_report.modifier, kb_report.keycode);
    delay(10);
  }
  if ( usb_hid_driver->ready() && !isConsumerQueueEmpty())
  {
    HIDConsumer cs_report;
    cs_report = getConsumerReport();
    usb_hid_driver->sendReport16(RID_CONSUMER_CONTROL, cs_report.usage_code);
    delay(10);
  }
}
#endif

void HID_Queues::processQueuesWithBLE()
{
    if (  !isMouseQueueEmpty())
  {
    HIDMouse ms_report;
    ms_report = getMouseReport();
    ble_hid_driver->mouseReport(ms_report.buttons, ms_report.x, ms_report.y, ms_report.wheel, ms_report.pan);
    delay(10);
  }
  if ( !isKeyboardQueueEmpty())
  {
    HIDKeyboard kb_report;
    kb_report = getKeyboardReport();
    ble_hid_driver->keyboardReport(kb_report.modifier, kb_report.keycode);
    delay(10);
  }
  if ( !isConsumerQueueEmpty())
  {
    HIDConsumer cs_report;
    cs_report = getConsumerReport();
    ble_hid_driver->consumerReport(cs_report.usage_code);
    delay(10);
  }
}
void HID_Queues::processQueues(connectionMode mode)
{
  switch (mode)
  {
    case CONNECTION_MODE_BLE_ONLY:
        connection = CONNECTION_BLE;
    break;
    case CONNECTION_MODE_USB_ONLY:
        connection = CONNECTION_USB;
    break;
    case CONNECTION_MODE_AUTO:
        connection = CONNECTION_NONE;
        // if BLE connected
        if (Bluefruit.connected())
        {
          connection = CONNECTION_BLE;
        }
        // if USB connected
        #ifdef NRF52840_XXAA  // only the 840 has USB available.
        if (TinyUSBDevice.mounted())
        {
        connection = CONNECTION_USB;
        }
        #endif
    break;
    default:
    break;
  }

  switch(connection)
  {
    case CONNECTION_NONE:
    break;
    case CONNECTION_USB:
        #ifdef NRF52840_XXAA  // only the 840 has USB available.
          processQueuesWithUSB();
        #endif
    break;
    case CONNECTION_BLE:
        processQueuesWithBLE();
    break;
    default:
    break;
    
  }
  
}

// PRIVATE FUNCTIONS
void HID_Queues::addKeyboardReport(HIDKeyboard* report)
{
  auto it = keycode_queue.begin();
  it = keycode_queue.insert(it, *report);   
}

void HID_Queues::addMouseReport(HIDMouse* report)
{
  auto it = mouse_queue.begin();
  it = mouse_queue.insert(it, *report);   
}

void HID_Queues::addConsumerReport(HIDConsumer* report)
{
  auto it = consumer_queue.begin();
  it = consumer_queue.insert(it, *report);   
}

void HID_Queues::addGamepadReport(HIDGamepad* report)
{
  auto it = gamepad_queue.begin();
  it = gamepad_queue.insert(it, *report);   
}    


std::vector<HIDKeyboard> HID_Queues::keycode_queue;
std::vector<HIDMouse>    HID_Queues::mouse_queue;
std::vector<HIDConsumer> HID_Queues::consumer_queue;
std::vector<HIDGamepad>  HID_Queues::gamepad_queue;
