#pragma once

#include "quantum.h"

#define ____ KC_TRNS
#define XXXX KC_NO

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes_cyril_lu {
  CL_FN_SWITCH = SAFE_RANGE,
  CL_CODE_SWITCH,
  CL_SQUOTS,
  CL_DQUOTS,
  CL_PARENS,
  CL_BRCKTS,
  CL_BRACES,
  CL_SAFE_RANGE
};

typedef enum {
  L_BASE = 0,
  L_NF_G1_L1,
  L_NF_G1_L2,
  L_NF_G2_L1,
  L_FN,
  L_CODE,
  L_RCMD,
  L_MOUSE
} layer_id_t;

bool process_record_cyril_lu(uint16_t keycode, keyrecord_t *record);