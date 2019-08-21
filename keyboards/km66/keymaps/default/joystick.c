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

#define STICK_MAX_X 834
#define STICK_MAX_Y 788
#define STICK_MIN_X 247
#define STICK_MIN_Y 249
#define STICK_CENTER_X 504
#define STICK_CENTER_Y 507
#define X_AXIS_DEADZONE 20
#define Y_AXIS_DEADZONE 20

void joystick_init(void) {
	print("Setting up ADC\n");
  	// Turn on the ADC for reading the joystick
  	ADC_Init(ADC_SINGLE_CONVERSION | ADC_PRESCALE_32);
  	ADC_SetupChannel(JOYSTICK_X_ADC_ID);
  	ADC_SetupChannel(JOYSTICK_Y_ADC_ID);
}

static joystick_mode_t joystickMode = MOVE;

void joystick_toggle_mode(void) {

  if (joystickMode == MOVE)
    joystickMode = SCROLL;
  else
    joystickMode = MOVE;

  // Clear state to avoid getting stuck if the mode is changed
  // while the stick is not centered
  report_mouse_t newReport = {0, 0, 0, 0 };
  pointing_device_set_report(newReport);
}

// Map a value from [in_min..in_max] to another value in the range of [out_min..out_max]
int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max) {
  return out_min + (x - in_min) * (out_max - out_min) / (in_max - in_min);
}

static int16_t joystick_read(uint32_t chanmask, uint16_t high, uint16_t low, uint16_t center, uint8_t deadzone)
{
  uint16_t analogValue = ADC_GetChannelReading(ADC_REFERENCE_AVCC | chanmask);

  uprintf("Analog value %u %u\n", analogValue, chanmask);

  if (joystickMode == SCROLL) deadzone *= 2;

  // If the current value is too clone to the deadzone, do not move the mouse.
  if (abs((int)analogValue - center) <= deadzone)
    return 0;

  // We dont want scrolling to be fine. It leads to crazy 2-axis scrolling at the same time.
  // Only register it if the joystick moved significantly
  if (joystickMode == SCROLL)
  {
      return analogValue > center ? 1 : -1; // We only need +/- 1 because we're using QMK's mouse wheel emulation.
  }

  // Map the analog read value from 0 to 1024 to between -127 and 127 so that it can be fed to
  // mouseReport.
  // But in reality we never reach 0 and 1024 because the joystick is not that precise, so just
  // map from the empiric range. (Note that these values as specific to your joystick, if you want finer control
  // you need to adjust the defines to fit your readings).
  int32_t vMapped = map(
      (int)analogValue,
      low,
      high,
      -127,
      127);

  return vMapped * 1/8;
}

static int32_t joystick_read_x(void)
{
  return joystick_read(JOYSTICK_X_ADC, STICK_MAX_X, STICK_MIN_X, STICK_CENTER_X, X_AXIS_DEADZONE);
}

static int32_t joystick_read_y(void)
{
  return joystick_read(JOYSTICK_Y_ADC, STICK_MAX_Y, STICK_MIN_Y, STICK_CENTER_Y, Y_AXIS_DEADZONE);
}

void joystick_process(void)
{
  int8_t x = -joystick_read_x();
  int8_t y = joystick_read_y();

  uprintf("Joystick %d %d\n", x, y);

  if (x || y) {

    if (joystickMode == MOVE)
    {
      report_mouse_t currentReport = pointing_device_get_report();
      currentReport.x = -x; // mounted left-side right
      currentReport.y = y;
      currentReport.v = 0;
      currentReport.h = 0;
      pointing_device_set_report(currentReport);
    }
    else
    {
      if (y > 0) // Up
      {
        register_code(KC_WH_U);
        unregister_code(KC_WH_U);
      }
      else // Down
      {
        register_code(KC_WH_D);
        unregister_code(KC_WH_D);
      }

      if (x > 0)
      {
        register_code(KC_WH_R);
        unregister_code(KC_WH_R);
      }
      else
      {
        register_code(KC_WH_L);
        unregister_code(KC_WH_L);
      }

    }
  }
}