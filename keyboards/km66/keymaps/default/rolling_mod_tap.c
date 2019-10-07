#include "rolling_mod_tap.h"

static layer_state_t tap_if_released = 0;

static void bitset(uint8_t layer) {
  tap_if_released = tap_if_released | (1UL << layer);
}

static void bitclear(uint8_t layer) {
  tap_if_released = tap_if_released & ~(1UL << layer);
}

static bool bitget(uint8_t layer) {
  return (tap_if_released & (1UL << layer)) != 0;
}

bool rolling_mod_tap(
  uint16_t keycode,
  keyrecord_t *record,
  int mod_tap_keycode,
  uint8_t layer
) {
  if (keycode != mod_tap_keycode) {
  	// A keycode other than the mod tap trigger have been pressed
  	if (record->event.pressed) {
  	  // This was not a tap
      bitclear(layer);
  	}
  } else {
    if (record->event.pressed) {
  	  // The mod tap trigger have been pressed
      // For now it is a tap
      bitset(layer);
      // Switch layer anyway
      layer_on(layer);
    } else {
      // The mod tap trigger have been released
      // Switch off the layer
      layer_off(layer);
      if (bitget(layer)) {
      	// No other key have been pressed
        return true;
      }
    }
  }
  return false;
}