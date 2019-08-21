#pragma once

void joystick_init(void);

void joystick_process(void);

typedef enum {
  MOVE,
  SCROLL,
} joystick_mode_t;


void joystick_toggle_mode(void);