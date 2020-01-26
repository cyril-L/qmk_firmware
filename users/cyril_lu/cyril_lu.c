#include "quantum.h"
#include "cyril_lu.h"
#include "rolling_mod_tap.h"
#include "double_shot_mod_tap.h"

rolling_mod_tap_state_t fn_switch_state = {false, false};
rolling_mod_tap_state_t code_switch_state = {false, false};

bool process_record_cyril_lu(uint16_t keycode, keyrecord_t *record) {
  // FN layer as modifier, F19 when taped
  rolling_mod_tap(keycode, record, CL_FN_SWITCH, &fn_switch_state);
  if (fn_switch_state.pressed) {
    layer_on(L_FN);
  } else {
    layer_off(L_FN);
    if (fn_switch_state.tapped) {
      tap_code(KC_F19);
    }
  }
  // Code layer as modifier, esc when taped
  rolling_mod_tap(keycode, record, CL_CODE_SWITCH, &code_switch_state);
  if (code_switch_state.pressed) {
    layer_on(L_CODE);
  } else {
    layer_off(L_CODE);
    if (code_switch_state.tapped) {
      tap_code(KC_ESC);
    }
  }
  // Caps lock as double shift
  if(!double_shot_mod_tap(keycode, record, MOD_LSFT, KC_CAPS)) {
    return false;
  }

  // TODO custom sendstring lut not implemented
  switch (keycode) {
    case CL_SQUOTS:
      if (record->event.pressed) { SEND_STRING("--"SS_TAP(X_LEFT)); }
      break;
    case CL_DQUOTS:
      if (record->event.pressed) { SEND_STRING(SS_LSFT("--")SS_TAP(X_LEFT)); }
      break;
    case CL_PARENS:
      if (record->event.pressed) { SEND_STRING("56"SS_TAP(X_LEFT)); }
      break;
    case CL_BRCKTS:
      if (record->event.pressed) { SEND_STRING(SS_RALT("56")SS_TAP(X_LEFT)); }
      break;
    case CL_BRACES:
      if (record->event.pressed) { SEND_STRING(SS_RALT("ty")SS_TAP(X_LEFT)); }
      break;
  }
  return true;
}