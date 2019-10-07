#pragma once

#include "quantum.h"

// Momentary switches to layer while mod_tap_keycode is pressed
// Returns true if mod_tap_keycode has be tapped,
// ie. it has been released and no other key have pressed.
//
// Typical usage:
//
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   if (rolling_mod_tap(keycode, record, FN_TAP, L_FN)) {
//     tap_code(KC_F19);
//   }
//   …
//
// It allows to trigger the layer behavior with a sequence like this:
// MOD_TAP Down
// KC_X Down
// MOD_TAP Up
// KC_X Up
//
// Instead of this:
// MOD_TAP Down
// KC_X Down
// KC_X Up
// MOD_TAP Up
//
// I didn’t manage to get this simple behavior by tweaking
// TAPPING_TERM, RETRO_TAPPING, PERMISSIVE_HOLD and friends

bool rolling_mod_tap(
	uint16_t keycode,
	keyrecord_t *record,
	int mod_tap_keycode,
	uint8_t layer);