#pragma once

#include "quantum.h"

void joystick_init(void);

bool joystick_process(void);

typedef enum {
  MOVE,
  SCROLL,
} joystick_mode_t;

void joystick_set_mode(joystick_mode_t mode);

joystick_mode_t joystick_get_mode(void);