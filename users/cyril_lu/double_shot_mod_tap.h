#pragma once

#include "quantum.h"

// Like a normal one shot modifier when tapped,
// but sends another keycode when tapped another time
//
// I use it for Shift, used as a one shot modifier when
// tapped once, used as Caps Lock when tapped twice.
// A bit like tap dance without having to mess with TAP_TERM
//
// Returns false when all further processing for this event
// sould be skipped.
//
// Typical usage:
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   if(!double_shot_mod_tap(keycode, record, MOD_LSFT, KC_CAPS)) {
//     return false;
//   }
//   …
// }

bool double_shot_mod_tap(
  uint16_t keycode, keyrecord_t *record,
  uint8_t mod, uint16_t double_tap
);