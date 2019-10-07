#include "joystick.h"
#include QMK_KEYBOARD_H
#include "pointing_device.h"
#include <LUFA/Drivers/Peripheral/ADC.h>
#include <print.h>

// Most of this come from
// https://github.com/pyrho/qmk_firmware/blob/joystick/keyboards/gergo/matrix.c

#define JOYSTICK_X_ADC_ID 5
#define JOYSTICK_Y_ADC_ID 6
#define JOYSTICK_X_ADC ADC_CHANNEL5
#define JOYSTICK_Y_ADC ADC_CHANNEL6

#define STICK_MAX_X 780
#define STICK_MAX_Y 734
#define STICK_MIN_X 227
#define STICK_MIN_Y 230
#define STICK_CENTER_X 480
#define STICK_CENTER_Y 480
#define X_AXIS_DEADZONE 50
#define Y_AXIS_DEADZONE 50

void joystick_init(void) {
  	// Turn on the ADC for reading the joystick
  	ADC_Init(ADC_SINGLE_CONVERSION | ADC_PRESCALE_32);
  	ADC_SetupChannel(JOYSTICK_X_ADC_ID);
  	ADC_SetupChannel(JOYSTICK_Y_ADC_ID);
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

static float joystick_read(uint32_t chanmask, uint16_t high, uint16_t low, uint16_t center, uint8_t deadzone)
{
  float value = (float)ADC_GetChannelReading(ADC_REFERENCE_AVCC | chanmask) - center;

  int sign;
  int max;

  if (value >= 0.0) {
    sign = 1;
    max = high - center;
  } else {
    sign = -1;
    value = -value;
    max = center - low;
  }

  if (value <= deadzone || max <= deadzone) {
    return 0;
  }

  // Maps value between 0 and 1
  value = (value - deadzone) / (max - deadzone);
  if (value > 1.0) {
    value = 1.0;
  }

  // Apply some non linearity for progressive movement
  return sign * value * value;

  //uprintf("Analog value %u %u\n", (unsinged) analogValue, (unsinged) chanmask);
}

static float joystick_read_x(void)
{
  return joystick_read(JOYSTICK_X_ADC, STICK_MAX_X, STICK_MIN_X, STICK_CENTER_X, X_AXIS_DEADZONE);
}

static float joystick_read_y(void)
{
  return joystick_read(JOYSTICK_Y_ADC, STICK_MAX_Y, STICK_MIN_Y, STICK_CENTER_Y, Y_AXIS_DEADZONE);
}

static uint16_t last_fired = 0;

int32_t scroll_pwm(int32_t ms_period) {
  uint16_t now = timer_read();
  if (ms_period == 0) { // special value used to prevent a big gap when starting to scroll
    last_fired = now;
    return 0;
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
  float x = joystick_read_x();
  float y = joystick_read_y();

  int mouse_scaler = 24; // higher is faster
  int wheel_scaler = 128; // slowest speed will be 1 tick every x ms, higher is slower

  if (x || y) {

      report_mouse_t currentReport = pointing_device_get_report();
    if (mode == MOVE)
    {
      currentReport.x = mouse_scaler * x;
      currentReport.y = mouse_scaler * y;
      currentReport.v = 0;
      currentReport.h = 0;
    }
    else
    {
      // Current scrolling speed is way too fast
      // needs to read some doc
      if (fabs(y) > fabs(x)) {
        currentReport.x = 0;
        currentReport.y = 0;
        currentReport.v = scroll_pwm(wheel_scaler * (y > 0 ? 1.0 - y : -1.0 - y));
        currentReport.h = 0;
      } else {
        currentReport.x = 0;
        currentReport.y = 0;
        currentReport.v = 0;
        currentReport.h = scroll_pwm(wheel_scaler * (x > 0 ? 1.0 - x : -1.0 - x));
      }
    }
    pointing_device_set_report(currentReport);
    return true; // joystick is moving
  } else {
    scroll_pwm(0);
    return false;
  }
}