#include "quantum.h"
#include "cyril_lu.h"

#define LAYOUT(\
  K000, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013,       K014, K015, K016, \
  K100, K101, K001, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K113, K114, K115, K116, \
  K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K313, K214, K215, K216, \
  K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, \
  K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411,       K412,       K415, \
  K500, K501, K502,       K504, K505,       K507,       K509, K510, K511, K512, K513, K514, K515, K516 \
) \
{ \
    { K000, K001, K002, K003,  K004, K005, K006,  K007, K008,  K009, K010, K011, K012,  K013,  K014,  K015,  K016 }, \
    { K100, K101, K102, K103,  K104, K105, K106,  K107, K108,  K109, K110, K111, KC_NO, K113,  K114,  K115,  K116 }, \
    { K200, K201, K202, K203,  K204, K205, K206,  K207, K208,  K209, K210, K211, K212,  KC_NO, K214,  K215,  K216 }, \
    { K300, K301, K302, K303,  K304, K305, K306,  K307, K308,  K309, K310, K311, K312,  K313,  KC_NO, KC_NO, KC_NO }, \
    { K400, K401, K402, K403,  K404, K405, K406,  K407, K408,  K409, K410, K411, K412,  KC_NO, KC_NO, K415,  KC_NO }, \
    { K500, K501, K502, KC_NO, K504, K505, KC_NO, K507, KC_NO, K509, K510, K511, K512,  K513,  K514,  K515,  K516 }  \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_BASE] = LAYOUT(
      RESET, KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,   KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12,            KC_PSCR, KC_CAPS, KC_PAUS, \
      KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,    KC_6,   KC_7,   KC_8,   KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC,  KC_INS,  KC_HOME, KC_PGUP, \
      KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_ENT,   KC_DEL,  KC_END,  KC_PGDN, \
      KC_ESC, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,    KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_QUOT, KC_BSLS, \
      OSM(MOD_LSFT),KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,    KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT,  KC_SLSH,          OSM(MOD_RSFT),            KC_UP, \
      KC_LCTL, KC_LGUI, KC_LALT,                KC_LCTL, KC_SPC, CL_FN_SWITCH, OSM(MOD_RALT),        KC_RGUI, KC_RALT, KC_RCTL, KC_MENU, KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [L_FN] = LAYOUT(
      ____, ____,   ____,  ____,  ____,  ____,   ____,  ____,  ____,  ____,  ____,  ____,  ____, ____, ____, ____, \
      ____, ____,   ____,   ____,   ____,   ____,    ____,   ____,   ____,   ____,   ____,    ____, ____,  ____,  ____,  ____, ____, \
      KC_TAB, HYPR(KC_Q), HYPR(KC_W), HYPR(KC_E), HYPR(KC_R), HYPR(KC_T), KC_HOME, KC_PGDN, KC_PGUP, KC_END, ____, ____, ____, ____,   ____,  ____,  ____, \
      KC_ESC, HYPR(KC_A), HYPR(KC_S), HYPR(KC_D), HYPR(KC_F), HYPR(KC_G), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,   ____, ____, ____, \
      KC_LSFT,KC_NUBS,HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_V), HYPR(KC_B),   ____,   ____,   ____,____,  ____,          ____,            ____, \
      ____, ____, ____,                ____, ____, ____, ____,        ____, ____, ____, ____, ____, ____, ____ \
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(process_record_cyril_lu(keycode, record) == false) {
    return false;
  }
  return true;
}