#include "bsp/board.h"
#include "trajectory.h"
#include "tusb.h"

static uint32_t prev_move_ms = 0;
size_t trajectory_pos = 0;

void main() {
  board_init();
  tusb_init();

  for (;;) {
    tud_task();

    if (tud_hid_ready()) {
      uint32_t now_ms = to_ms_since_boot(get_absolute_time());
      if (now_ms - prev_move_ms > trajectory_delay_ms) {
        prev_move_ms = now_ms;
        tud_hid_mouse_report(REPORT_ID_MOUSE, 0x00, trajectory[trajectory_pos][0], trajectory[trajectory_pos][1], 0, 0);
        trajectory_pos = (trajectory_pos + 1) % (sizeof(trajectory) / sizeof(trajectory[0]));
      }
    }
  }
}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen) {
  return 0;
}

void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {}
