/*
Copyright 2020-2021 <Pierre Constantineau>

3-Clause BSD License

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "usb.h"

extern DynamicState keyboardstate;

// Report ID
enum {
  RID_KEYBOARD = 1,
  RID_MOUSE,
  RID_CONSUMER_CONTROL, // Media, volume etc ..
};

#ifdef TINYUSB_AVAILABLE
// HID report descriptor using TinyUSB's template
// Single Report (no ID) descriptor
uint8_t const desc_hid_report[] = {TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(RID_KEYBOARD)), TUD_HID_REPORT_DESC_MOUSE(HID_REPORT_ID(RID_MOUSE)),
                                   TUD_HID_REPORT_DESC_CONSUMER(HID_REPORT_ID(RID_CONSUMER_CONTROL))};

extern Adafruit_USBD_Device USBDevice;
Adafruit_USBD_HID USBhid;
#endif

void usb_setup() {
#ifdef TINYUSB_AVAILABLE
  USBDevice.setManufacturerDescriptor(MANUFACTURER_NAME);
  USBDevice.setProductDescriptor(DEVICE_NAME);

  USBhid.setPollInterval(2);
  USBhid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  USBhid.setReportCallback(NULL, hid_report_callback);
  USBhid.begin();
#endif
}

bool usb_isConnected() {
#ifdef TINYUSB_AVAILABLE
  return USBhid.ready() && !USBDevice.suspended();
#else
  return false;
#endif
}

void usb_wakeup() {
#ifdef TINYUSB_AVAILABLE
  if (USBDevice.suspended()) {
    // Wake up host if we are in suspend mode and REMOTE_WAKEUP feature is enabled by host
    USBDevice.remoteWakeup();
  }
#endif
}

void usb_sendKeys(std::array<uint8_t, 8> currentReport) {
#ifdef TINYUSB_AVAILABLE
  uint8_t keycode[6];
  uint8_t mods = 0;
  mods = currentReport[0];       // modifiers
  keycode[0] = currentReport[1]; // Buffer
  keycode[1] = currentReport[2]; // Buffer
  keycode[2] = currentReport[3]; // Buffer
  keycode[3] = currentReport[4]; // Buffer
  keycode[4] = currentReport[5]; // Buffer
  keycode[5] = currentReport[6]; // Buffer

  USBhid.keyboardReport(RID_KEYBOARD, mods, keycode);
#endif
}

void usb_sendKeys(uint8_t currentReport[8]) {
#ifdef TINYUSB_AVAILABLE
  uint8_t keycode[6];
  uint8_t mods = 0;

  mods = currentReport[0];       // modifiers
  keycode[0] = currentReport[1]; // Buffer
  keycode[1] = currentReport[2]; // Buffer
  keycode[2] = currentReport[3]; // Buffer
  keycode[3] = currentReport[4]; // Buffer
  keycode[4] = currentReport[5]; // Buffer
  keycode[5] = currentReport[6]; // Buffer

  USBhid.keyboardReport(RID_KEYBOARD, mods, keycode);
#endif
}

void usb_sendMediaKey(uint16_t keycode) {
#ifdef TINYUSB_AVAILABLE
  USBhid.sendReport16(RID_CONSUMER_CONTROL, hid_GetMediaUsageCode(keycode));
#endif
}

#define MOVE_STEP 1
void usb_sendMouseKey(uint16_t keycode) {
#ifdef TINYUSB_AVAILABLE
  switch (keycode) {
  case KC_MS_OFF:
    USBhid.mouseButtonRelease(RID_MOUSE);
    break;
  case KC_MS_BTN1:
    USBhid.mouseButtonPress(RID_MOUSE, MOUSE_BUTTON_LEFT);
    break;
  case KC_MS_BTN2:
    USBhid.mouseButtonPress(RID_MOUSE, MOUSE_BUTTON_RIGHT);
    break;
  case KC_MS_BTN3:
    USBhid.mouseButtonPress(RID_MOUSE, MOUSE_BUTTON_MIDDLE);
    break;
  case KC_MS_BTN4:
    USBhid.mouseButtonPress(RID_MOUSE, MOUSE_BUTTON_BACKWARD);
    break;
  case KC_MS_BTN5:
    USBhid.mouseButtonPress(RID_MOUSE, MOUSE_BUTTON_FORWARD);
    break;
  }
#endif
}

void usb_sendMouseMove(uint16_t keycode, uint16_t steps) {
#ifdef TINYUSB_AVAILABLE
  switch (keycode) {
  case KC_MS_UP:
    USBhid.mouseMove(RID_MOUSE, 0, -steps);
    break;
  case KC_MS_DOWN:
    USBhid.mouseMove(RID_MOUSE, 0, steps);
    break;
  case KC_MS_LEFT:
    USBhid.mouseMove(RID_MOUSE, -steps, 0);
    break;
  case KC_MS_RIGHT:
    USBhid.mouseMove(RID_MOUSE, steps, 0);
    break;

  case KC_MS_WH_UP:
    USBhid.mouseScroll(RID_MOUSE, -1, 0);
    break;
  case KC_MS_WH_DOWN:
    USBhid.mouseScroll(RID_MOUSE, 1, 0);
    break;
  case KC_MS_WH_LEFT:
    USBhid.mouseScroll(RID_MOUSE, 0, -1);
    break;
  case KC_MS_WH_RIGHT:
    USBhid.mouseScroll(RID_MOUSE, 0, 1);
    break;
  }
#endif
}

// Output report callback for LED indicator such as Caplocks
void hid_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {
#ifdef TINYUSB_AVAILABLE
  if (report_id != RID_KEYBOARD)
    return;

  // LED indicator is output report with only 1 byte length
  if (report_type != HID_REPORT_TYPE_OUTPUT)
    return;

  // The LED bit map is as follows: (also defined by KEYBOARD_LED_* )
  // Kana (4) | Compose (3) | ScrollLock (2) | CapsLock (1) | Numlock (0)
  keyboardstate.statuskb = buffer[1];
#endif
}