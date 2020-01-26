#pragma once

#include "quantum.h"

// When digits are toogled:
//
//  KC_1 -> LSFT(KC_1)
//  LSFT(KC_1) -> KC_1
//
// Typical usage:
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   if(!process_toggle_digits(keycode, record)) {
//     return false;
//   }
//   …
// }

bool process_toggle_digits(uint16_t keycode, keyrecord_t *record);

void led_set_toggle_digits(uint8_t usb_led);