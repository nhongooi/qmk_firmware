/* Copyright 2020 Alexander Tulloh
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0xCA49
#define DEVICE_VER 0x0001
#define MANUFACTURER Alexander Tulloh
#define PRODUCT Oddball

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Split Keyboard specific options */
#define USE_I2C
#define SPLIT_USB_DETECT
#define MASTER_RIGHT

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 40

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* optical sensor settings */
#define SCROLL_DIVIDER 9
#define CPI_1 1400
#define CPI_2 1800
#define CPI_3 2200
#define TAPPING_TERM 200
#define AUTO_SHIFT_MODIFIERS
#define AUTO_SHIFT_TIMEOUT 135
#define AUTO_SHIFT_NO_AUTO_REPEAT
#define NO_AUTO_SHIFT_ALPHA
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

/* Bootmagic Lite key configuration */
// #define BOOTMAGIC_LITE_ROW 0
// #define BOOTMAGIC_LITE_COLUMN 0
