/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6465
#define DEVICE_VER      0x0001
#define MANUFACTURER    none
#define PRODUCT         isotkl_split
#define DESCRIPTION     test board for qmk

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

#define DIODE_DIRECTION COL2ROW

#define MATRIX_COL_PINS { B9, B10, B11, B12, A14, A13, A15, A8, A7, A6, B0, B1, B2, B3, B4, B5, B6 }
#define MATRIX_ROW_PINS { A2, A1, A0, B7, A10, A9 }
#define UNUSED_PINS

// #define BACKLIGHT_PIN           B8
// #define BACKLIGHT_PWM_DRIVER    PWMD4
// #define BACKLIGHT_PWM_CHANNEL   3
// #define BACKLIGHT_PAL_MODE      2

// #define RGB_DI_PIN A1

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

#define TAPPING_TERM 500

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
