#include "rolling_mod_tap.h"

void rolling_mod_tap(
  uint16_t keycode,
  keyrecord_t *record,
  int mod_tap_keycode,
  rolling_mod_tap_state_t *state
) {
  if (keycode == mod_tap_keycode) {
    if(record->event.pressed) {
      state->pressed = true;
      // For now it is a tap
      state->tapped = true;
    } else {
      state->pressed = false;
    }
  } else {
    // Another key have been pressed, no longer a tap
    state->tapped = false;
  }
}