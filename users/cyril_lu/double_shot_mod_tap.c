#include "double_shot_mod_tap.h"

bool double_shot_mod_tap(
  uint16_t keycode, keyrecord_t *record,
  uint8_t mod, uint16_t double_tap
) {
  if (keycode == OSM(mod)
    && record->event.pressed
    && (get_oneshot_mods() & mod)
  ) {
    clear_oneshot_mods();
    tap_code(double_tap);
    return false;
  } else {
    return true;
  }
}