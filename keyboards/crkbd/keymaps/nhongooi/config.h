/*
Copyright 2021 @mangoiv

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

#define MASTER_RIGHT
#define THUMB_6
#define _10

// trackball
#define USE_SERIAL

#define LAYOUT_split_3x5_3( \
  L00, L01, L02, L03, L04,           R00, R01, R02, R03, R04, \
  L10, L11, L12, L13, L14,           R10, R11, R12, R13, R14, \
  L20, L21, L22, L23, L24,           R20, R21, R22, R23, R24, \
                 L30, L31, L32, R30, R31, R32 \
  ) \
  { \
    { KC_NO, L00, L01, L02, L03, L04 }, \
    { KC_NO, L10, L11, L12, L13, L14 }, \
    { KC_NO, L20, L21, L22, L23, L24 }, \
    { KC_NO, KC_NO, KC_NO, L30, L31, L32 }, \
    { KC_NO, R04, R03, R02, R01, R00 }, \
    { KC_NO, R14, R13, R12, R11, R10 }, \
    { KC_NO, R24, R23, R22, R21, R20 }, \
    { KC_NO, KC_NO, KC_NO, R32, R31, R30 } \
  }

#define LAYOUT_fifi_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

/* Haptic Driver initialization settings
 * Feedback Control Settings */
#define FB_ERM_LRA 1 /* For ERM:0 or LRA:1*/
#define FB_BRAKEFACTOR 6 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#define FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */
/* default 2V LRA voltage and library */
#if FB_ERM_LRA == 1
#define RATED_VOLTAGE 2
#define V_RMS 2.0
#define V_PEAK 2.85
#define F_LRA 200
/* Library Selection */
#define LIB_SELECTION 6 /* For Empty:0' TS2200 library A to D:1-5, LRA Library: 6 */
#define DRV_GREETING alert_750ms
#endif
