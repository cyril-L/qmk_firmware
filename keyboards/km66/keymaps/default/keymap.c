/* Copyright 2019 Cyril Lugan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "joystick.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

#define ____ KC_TRNS

#define OSX_DEL_LINE LGUI(KC_BSPC)
#define OSX_DEL_WORD LALT(KC_BSPC)
#define OSX_FDEL_LINE LGUI(KC_DELETE)
#define OSX_FDEL_WORD LALT(KC_DELETE)
#define OSX_TAB_NEXT  LCTL(KC_TAB)
#define OSX_TAB_PREV  LCTL(LSFT(KC_TAB))

enum {
  TD_SHIFT_CAPS = 0
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_SHIFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
// Other declarations would go here, separated by commas, if you have them
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Layer 0: Default Layer
   * ,-----------------------------------------------------------.
   * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| Bksp|
   * |-----------------------------------------------------------|
   * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn0|
   * |-----------------------------------------------------------'
   * |     |Gui|Alt  |         Space         |Alt  |Gui|   |     |
   * `-----------------------------------------------------------'
   */
  [0] = LAYOUT( /* Base */
    KC_GRV,        KC_1,   KC_2,    KC_3,    KC_4,   KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
    KC_TAB,        KC_Q,   KC_W,    KC_E,    KC_R,   KC_T,    KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_NUHS, \
    KC_ESC,        KC_A,   KC_S,    KC_D,    KC_F,   KC_G,             KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
    TD(TD_SHIFT_CAPS), KC_Z,   KC_X,    KC_C,    KC_V,   KC_B,    KC_UP,   KC_NUBS,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    KC_LCTL,               KC_LALT, KC_LGUI, KC_SPC, KC_LEFT, KC_DOWN, KC_RIGHT, OSL(1),  OSM(MOD_RALT), KC_RGUI,                   KC_RCTL \
  ),
  [1] = LAYOUT( /* Fn */
    KC_PWR,  KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DELETE, \
    ____,    HYPR(KC_Q), HYPR(KC_W), HYPR(KC_E), HYPR(KC_R), HYPR(KC_T), KC_HOME, KC_PGDN, KC_PGUP, KC_END,    ____,    OSX_TAB_PREV, OSX_TAB_NEXT, ____, \
    ____,    HYPR(KC_A), HYPR(KC_S), HYPR(KC_D), HYPR(KC_F), HYPR(KC_G),             KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,    ____, ____, ____, \
    ____, HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_V), HYPR(KC_B), KC_UP,   KC_NUBS,  OSX_DEL_LINE, OSX_DEL_WORD, OSX_FDEL_WORD, OSX_FDEL_LINE, ____, KC_NLCK, \
    ____,                ____,       ____,       ____,       ____,       ____,    ____,     ____,         ____,         ____,                               ____ \
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {
  joystick_init();
}

void matrix_scan_user(void) {
  joystick_process();
}

void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinHigh(F0);
    } else {
        writePinLow(F0);
    }
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinHigh(F1);
    } else {
        writePinLow(F1);
    }
}
