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
#include "cyril_lu.h"
#include "toggle_digits.h"
#include "joystick.h"

enum custom_keycodes {
  OOOO = CL_SAFE_RANGE,
  J_TOGGLE
};

#define OSX_DEL_LINE LGUI(KC_BSPC)
#define OSX_DEL_WORD LALT(KC_BSPC)
#define OSX_FDEL_LINE LGUI(KC_DELETE)
#define OSX_FDEL_WORD LALT(KC_DELETE)
#define OSX_TAB_NEXT  LCTL(KC_TAB)
#define OSX_TAB_PREV  LCTL(LSFT(KC_TAB))

bool is_layer_on(layer_id_t layer) {
  return layer_state & (1UL << (layer));
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Layer 0: Default Layer
   * ,---------------------------.          ,-------------------------------.
   * | ` |  1|  2|  3|  4|  5|  6|          |  7|  8|  9|  0|  -|  =|   Bksp|
   * |---------------------------'        ,---------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|          |  Y|  U|  I|  O|  P|  [|  ]|     |
   * |--------------------------.         `---------------------------------|
   * |Esc   |  A|  S|  D|  F|  G|          |  H|  J|  K|  L|  ;|  '|   Enter|
   * |----------------------------. ,---. ,`--------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B| | ↑ | |   |  N|  M|  ,|  .|  /|    Shift|
   * |----------------------------------------------------------------------|
   * |Ctrl |     |Alt |Cmd |Spc | ← | ↓ | → |  Fn| Alt| Cmd|          | Ctrl|
   * `-----'     `-----------------------------------------'          `-----'
   */
  [L_BASE] = LAYOUT( /* Base */
    KC_GRV,        KC_1,   KC_2,    KC_3,    KC_4,   KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
    KC_TAB,        KC_Q,   KC_W,    KC_E,    KC_R,   KC_T,    KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_NUHS, \
    CL_CODE_SWITCH,        KC_A,   KC_S,    KC_D,    KC_F,   KC_G,             KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
    OSM(MOD_LSFT),  KC_Z,   KC_X,    KC_C,    KC_V,   KC_B,    KC_UP,   KC_NUBS,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OSM(MOD_RSFT), \
    KC_LCTL,               KC_LALT, KC_LGUI, KC_SPC, KC_LEFT, KC_DOWN, KC_RIGHT, CL_FN_SWITCH,  OSM(MOD_RALT), OSL(L_RCMD),                   KC_RCTL \
  ),
  [L_NF_G1_L1] = LAYOUT( /* French NF from QWERTY group 1 level 1  */
    S(KC_2),     XXXX, XXXX, XXXX, XXXX, S(KC_9), S(KC_0), XXXX, XXXX, XXXX, S(KC_QUOT), KC_QUOT, S(KC_6), ____, \
    ____, KC_A, KC_Z, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS, S(KC_EQL), S(KC_8), \
    ____, KC_Q, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_M, KC_SLSH, ____, \
    OSL(L_NF_G1_L2), KC_W, KC_X, KC_C, KC_V, KC_B, ____, S(KC_COMM), KC_N, KC_DOT, KC_COMM, S(KC_SCLN), KC_SCLN, OSL(L_NF_G1_L2), \
    ____, ____, ____, ____, ____, ____, ____, ____, OSL(L_NF_G2_L1), ____, ____ \
  ),
  [L_NF_G1_L2] = LAYOUT( /* French NF from QWERTY group 1 level 2  */
    S(KC_3), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, S(KC_QUOT), XXXX, ____, \
    ____, S(KC_A), S(KC_Z), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), XXXX, XXXX, XXXX, \
    ____, S(KC_Q), S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), S(KC_M), KC_BSLS, ____, \
    ____, S(KC_W), S(KC_X), S(KC_C), S(KC_V), S(KC_B), ____, S(KC_DOT), S(KC_N), S(KC_SLSH), S(KC_1), XXXX, KC_EQL, ____, \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____ \
  ),
  [L_NF_G2_L1] = LAYOUT( /* French NF from QWERTY group 2 level 1  */
    XXXX, XXXX, XXXX, KC_GRV, S(KC_7), KC_LBRC, KC_RBRC, XXXX, S(KC_MINS), XXXX, XXXX, XXXX, XXXX, ____, \
    ____, XXXX, XXXX, XXXX, XXXX, S(KC_LBRC), S(KC_RBRC), XXXX, XXXX, XXXX, S(KC_5), XXXX, XXXX, XXXX, \
    ____, XXXX, XXXX, S(KC_4), XXXX, XXXX, XXXX, XXXX, XXXX, S(KC_BSLS), XXXX, XXXX, ____, \
    ____, XXXX, XXXX, XXXX, XXXX, XXXX, ____, XXXX, S(KC_GRV), XXXX, XXXX, XXXX, XXXX, ____, \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____ \
  ),
  [L_FN] = LAYOUT( /* Fn, mostly used for navigation and window management */
    KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DELETE, \
    TG(L_NF_G1_L1), HYPR(KC_Q), HYPR(KC_W), HYPR(KC_E), HYPR(KC_R), HYPR(KC_T), KC_HOME, KC_PGDN, KC_PGUP, KC_END, ____, ____, ____, ____, \
    ____, HYPR(KC_A), HYPR(KC_S), HYPR(KC_D), HYPR(KC_F), HYPR(KC_G), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, ____, ____, ____, \
    ____, HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_V), HYPR(KC_B), KC_UP, KC_NUBS, OSX_DEL_LINE, OSX_DEL_WORD, OSX_FDEL_WORD, OSX_FDEL_LINE, ____, KC_NLCK, \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____ \
  ),
  [L_CODE] = LAYOUT( /* Mostly used for code */
    MEH(KC_GRV), MEH(KC_1), MEH(KC_2), MEH(KC_3), MEH(KC_4), MEH(KC_5), MEH(KC_6), MEH(KC_7), MEH(KC_8), MEH(KC_9), MEH(KC_0), MEH(KC_MINS), MEH(KC_EQL), MEH(KC_BSPC), \
    MEH(KC_TAB), KC_Q, MEH(KC_W), MEH(KC_E), MEH(KC_R), MEH(KC_T), MEH(KC_Y), CL_SQUOTS, CL_DQUOTS, MEH(KC_O), MEH(KC_P), MEH(KC_LBRC), MEH(KC_RBRC), MEH(KC_NUHS), \
    ____,MEH( KC_A), MEH(KC_S), MEH(KC_D), MEH(KC_F), MEH(KC_G), MEH(KC_H), CL_PARENS, CL_BRCKTS, CL_BRACES, MEH(KC_SCLN), MEH(KC_QUOT), MEH(KC_ENT), \
    CL_TOGGLE_DIGITS, MEH(KC_Z), MEH(KC_X), MEH(KC_C), MEH(KC_V), MEH(KC_B), MEH(KC_UP), MEH(KC_NUBS), MEH(KC_N), MEH(KC_M), MEH(KC_COMM), MEH(KC_DOT), MEH(KC_SLSH), ____, \
    ____,               ____, ____, MEH(KC_SPC), MEH(KC_LEFT), MEH(KC_DOWN), MEH(KC_RIGHT), ____,  ____, ____, ____ \
  ),
  [L_RCMD] = LAYOUT( /*  */
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, OSX_TAB_PREV, OSX_TAB_NEXT, ____, \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____ \
  ),
  [L_MOUSE] = LAYOUT( /* Mouse mode */
    OOOO, OOOO, OOOO, OOOO, OOOO, OOOO,    OOOO,    OOOO,     OOOO,    OOOO,    OOOO, OOOO, OOOO, OOOO, \
    OOOO, OOOO, OOOO, OOOO, OOOO, OOOO,    OOOO,    OOOO,     OOOO,    OOOO,    OOOO, OOOO, OOOO, OOOO, \
    OOOO, OOOO, OOOO, OOOO, OOOO, OOOO,             OOOO,     OOOO,    OOOO,    OOOO, OOOO, OOOO, OOOO, \
    OOOO, OOOO, OOOO, OOOO, OOOO, OOOO,    J_TOGGLE,   OOOO,  OOOO,    OOOO,    OOOO, OOOO, OOOO, OOOO, \
    OOOO,             OOOO, OOOO, OOOO, KC_BTN1, J_TOGGLE, KC_BTN2, OOOO,  OOOO, OOOO,                   OOOO \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(process_record_cyril_lu(keycode, record) == false) {
    return false;
  }
  switch (keycode) {
    case OOOO:
      layer_off(L_MOUSE);
      // Get back to move mode for the next time the joystick is used
      joystick_set_mode(MOVE);
      break;
    case J_TOGGLE:
      if (record->event.pressed) {
        joystick_set_mode(joystick_get_mode() == MOVE ? SCROLL : MOVE);
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {
  joystick_init();
}

// Using F0 to hook up external things for tactile/audio feedback, like relays
// uint8_t matrix_key_count(void);

extern bool are_digits_toggled;
extern bool are_caps_locked;

void matrix_scan_user(void) {
  // Turn on mouse layer if joystick is used
  if (joystick_process()) {
    layer_on(L_MOUSE);
  }
  if (is_layer_on(L_MOUSE) || are_digits_toggled) {
    writePinHigh(F0);
  } else {
    writePinLow(F0);
  }
  // if (matrix_key_count() != 0) {
  //     writePinHigh(F0);
  // } else {
  //     writePinLow(F0);
  // }
  bool shift_pressed = (get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
  if ((are_caps_locked && !shift_pressed) || (shift_pressed && !are_caps_locked)) {
    writePinHigh(F1);
  } else {
    writePinLow(F1);
  }
}

void led_set_user(uint8_t usb_led) {
  led_set_cyril_lu(usb_led);
}
