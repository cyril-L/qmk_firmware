#pragma once

#include "quantum.h"

// Detects taps regardless of TAPPING_TERM, RETRO_TAPPING, PERMISSIVE_HOLD and friends
// ie. the key it has been released and no other key have pressed.
//
// MOD_TAP Down
// KC_X Down
// MOD_TAP Up
// KC_X Up
//
// The above sequence will never be treated as a tap, avoiding some
// false positives I had with the built-in mod tap.
//
// Typical usage:
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   rolling_mod_tap(keycode, record, FN_SWITCH, &fn_switch_state);
//   if (fn_switch_state.pressed) {
//     layer_on(L_FN);
//   } else {
//     layer_off(L_FN);
//     if (fn_switch_state.tapped) {
//       tap_code(KC_F19);
//     }
//   }
//   …

typedef struct {
  bool pressed;
  bool tapped;
} rolling_mod_tap_state_t;

void rolling_mod_tap(
  uint16_t keycode,
  keyrecord_t *record,
  int mod_tap_keycode,
  rolling_mod_tap_state_t *state
);