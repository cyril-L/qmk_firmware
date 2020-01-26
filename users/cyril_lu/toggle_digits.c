#include "quantum.h"
#include "cyril_lu.h"
#include "toggle_digits.h"

bool are_digits_toggled = false;
bool are_caps_locked = false;

bool process_toggle_digits(uint16_t keycode, keyrecord_t *record) {
  if (keycode == CL_TOGGLE_DIGITS && record->event.pressed) {
    are_digits_toggled = !are_digits_toggled;
  }
  // Do nothing if num are not toggled
  if (!are_digits_toggled) { return true; }
  // Do nothing if caps are locked
  if (are_caps_locked) { return true; }
  const uint8_t mods_bck = get_mods();
  const uint8_t osmods_bck = get_oneshot_mods();
  // Do nothing if any mod other than shift is active
  if ((mods_bck | osmods_bck) & (~MOD_MASK_SHIFT)) {
  	return true;
  }
  if (KC_1 <= keycode && keycode <= KC_0) {
    if (record->event.pressed) {
      clear_mods();
      clear_oneshot_mods();

      if ((mods_bck | osmods_bck) & MOD_MASK_SHIFT) {
        tap_code(keycode);
      } else {
        tap_code16(LSFT(keycode));
      }

      set_mods(mods_bck);
    }
    return false;
  }
  return true;
}

void led_set_toggle_digits(uint8_t usb_led) {
	are_caps_locked = IS_LED_ON(usb_led, USB_LED_CAPS_LOCK);
}