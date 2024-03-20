#include "tusb.h"

#define CONFIG_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)
#define EPNUM_HID 0x81
#define DESC_STRING_MAX 31

const tusb_desc_device_t desc_device = {
    .bLength = sizeof(tusb_desc_device_t),
    .bDescriptorType = TUSB_DESC_DEVICE,
    .bcdUSB = 0x0110,
    .bDeviceClass = 0x00,
    .bDeviceSubClass = 0x00,
    .bDeviceProtocol = 0x00,
    .bMaxPacketSize0 = 64,
    .idVendor = 0x275d,
    .idProduct = 0x0ba6,
    .bcdDevice = 0x0100,
    .iManufacturer = 0x00,
    .iProduct = 0x01,
    .iSerialNumber = 0x00,
    .bNumConfigurations = 0x01};

uint8_t const desc_hid_report[] = {TUD_HID_REPORT_DESC_MOUSE(HID_REPORT_ID(REPORT_ID_MOUSE))};

uint8_t const desc_configuration[] = {
    // Config number, interface count, string index, total length, attribute, power in mA
    TUD_CONFIG_DESCRIPTOR(1, 1, 0, CONFIG_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),

    // Interface number, string index, protocol, report descriptor len, EP In address, size & polling interval
    TUD_HID_DESCRIPTOR(0, 0, HID_ITF_PROTOCOL_MOUSE, sizeof(desc_hid_report), EPNUM_HID, 5, 10)};

const uint8_t *string_desc_arr[] = {
    (const char[]){0x09, 0x04},  // langid
    "USB OPTICAL MOUSE ",        // iProduct
};

static uint16_t desc_str[DESC_STRING_MAX];

uint8_t const *tud_descriptor_device_cb() {
  return (uint8_t const *)&desc_device;
}

uint8_t const *tud_hid_descriptor_report_cb(uint8_t itf) {
  return desc_hid_report;
}

uint8_t const *tud_descriptor_configuration_cb(uint8_t index) {
  return desc_configuration;
}

uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
  uint8_t chr_count;

  if (index == 0) {
    memcpy(&desc_str[1], string_desc_arr[0], 2);
    chr_count = 1;
  } else {
    if (index >= sizeof(string_desc_arr) / sizeof(string_desc_arr[0])) {
      return NULL;
    }

    const char *str = string_desc_arr[index];
    chr_count = strlen(str);
    if (chr_count > DESC_STRING_MAX) {
      chr_count = DESC_STRING_MAX;
    }
    // convert ASCII to UTF-16
    for (size_t i = 0; i < chr_count; i++) {
      desc_str[i + 1] = str[i];
    }
  }

  // first byte is length (including header), second byte is string type
  desc_str[0] = (TUSB_DESC_STRING << 8) | (2 * chr_count + 2);
  return desc_str;
}
