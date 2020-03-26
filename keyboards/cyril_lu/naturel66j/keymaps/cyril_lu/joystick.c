#include "joystick.h"
#include QMK_KEYBOARD_H
#include "pointing_device.h"
#include <LUFA/Drivers/Peripheral/ADC.h>
#include <print.h>

#define JOY_X_ADC_ID 5
#define JOY_Y_ADC_ID 6
#define JOY_X_ADC ADC_CHANNEL5
#define JOY_Y_ADC ADC_CHANNEL6

#define JOY_X_CENTER 480
#define JOY_Y_CENTER 480

// Amount of signal change to go from center to max
#define JOY_SENSIBILITY (200.0)

// Ignore signal when ratio with max is lower than deadzone
#define JOY_DEADZONE (0.005)

typedef struct raw_sample_t {
  uint16_t x;
  uint16_t y;
} raw_sample_t;

typedef struct normalized_sample_t {
  float dist;
  float angle;
} normalized_sample_t;

void joystick_init(void) {
  	ADC_Init(ADC_SINGLE_CONVERSION | ADC_PRESCALE_32);
  	ADC_SetupChannel(JOY_X_ADC_ID);
  	ADC_SetupChannel(JOY_Y_ADC_ID);
}

void joystick_read_raw(raw_sample_t * sample) {
  sample->x = ADC_GetChannelReading(ADC_REFERENCE_AVCC | JOY_X_ADC);
  sample->y = ADC_GetChannelReading(ADC_REFERENCE_AVCC | JOY_Y_ADC);
}

// Returns a dist between 0.0 (centered) to 1.0 (maximum deviation)
// Returns an angle between -pi and pi
void joystick_read_normalized(normalized_sample_t * sample) {
  raw_sample_t raw_sample;
  joystick_read_raw(&raw_sample);
  // Log raw data for experiments
  //uprintf("JOY_RAW: %u, %u\n", (unsigned) raw_sample.x, (unsigned) raw_sample.y);
  float x = ((float) raw_sample.x) - JOY_X_CENTER;
  float y = ((float) raw_sample.y) - JOY_Y_CENTER;
  sample->dist = (x * x + y * y) / (JOY_SENSIBILITY * JOY_SENSIBILITY);
  if (sample->dist < JOY_DEADZONE) {
    sample->dist = 0.0;
    return;
  } else if (sample->dist > 1.0) {
    sample->dist = 1.0;
  } else {
    sample->dist -= JOY_DEADZONE;
  }
  sample->angle = atan2(y, x);
  // uprintf("JOY: %d, %d\n", (int) (sample->dist * 100.0), (int)(sample->angle*180.0/M_PI));
}

static joystick_mode_t mode = MOVE;

joystick_mode_t joystick_get_mode() {
  return mode;
}

void joystick_set_mode(joystick_mode_t new_mode) {
  mode = new_mode;

  // Clear state to avoid getting stuck if the mode is changed
  // while the stick is not centered
  report_mouse_t newReport = {0, 0, 0, 0 };
  pointing_device_set_report(newReport);
}

// When scrolling, this allows to send mouse reports with
// a frequency depending on the joystick state.

static uint16_t last_fired = 0;

int32_t get_scroll_ticks(float speed) {
  int wheel_scaler = 128; // slowest speed will be 1 tick every x ms, higher is slower
  uint16_t now = timer_read();
  int32_t ms_period;
  if (speed == 0.0) { // special value used to prevent a big gap when starting to scroll
    last_fired = now;
    return 0;
  } else if (speed > 0) {
    ms_period = round(wheel_scaler * (1.0 - speed));
    if (ms_period == 0) ms_period = 1;
  } else {
    ms_period = round(wheel_scaler * (-1.0 - speed));
    if (ms_period == 0) ms_period = -1;
  }
  uint16_t elapsed = now - last_fired;
  // TODO test that it is ok when timer overflows
  int32_t ticks_count = elapsed / ms_period;
  if (abs(ticks_count) > 0) {
    last_fired = now;
  }
  return ticks_count;
}

bool joystick_process(void)
{
  normalized_sample_t sample;
  joystick_read_normalized(&sample);

  // Apply some non linearity to go slower when the joystick is near the center
  sample.dist = sample.dist * sample.dist;

  int mouse_scaler = 24; // higher is faster

  if (sample.dist > 0.0) {
    float x = sample.dist * cos(sample.angle);
    float y = sample.dist * sin(sample.angle);
    report_mouse_t currentReport = pointing_device_get_report();
    if (mode == MOVE) {
      currentReport.x = mouse_scaler * x;
      currentReport.y = mouse_scaler * y;
      currentReport.v = 0;
      currentReport.h = 0;
      pointing_device_set_report(currentReport);
    } else {
      // Current scrolling speed is way too fast
      // needs to read some doc
      if (fabs(y) > fabs(x)) {
        int32_t ticks = get_scroll_ticks(y);
        if (ticks != 0) {
          currentReport.x = 0;
          currentReport.y = 0;
          currentReport.v = -ticks; // - for "natural" scroll
          currentReport.h = 0;
          pointing_device_set_report(currentReport);
        }
      } else {
        int32_t ticks = get_scroll_ticks(x);
        if (ticks != 0) {
          currentReport.x = 0;
          currentReport.y = 0;
          currentReport.v = 0;
          currentReport.h = ticks;
          pointing_device_set_report(currentReport);
        }
      }
    }
    return true;
  }
  get_scroll_ticks(0); // TODO: uggly needed to reset tick tracker
  return false;
}