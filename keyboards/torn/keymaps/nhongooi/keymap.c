/* Copyright 2020 Richard Titmuss (richard.titmuss@gmail.com)
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

#include QMK_KEYBOARD_H
#include "nhongooi.h"

#define LOWER     MO(_LOWER)
#define LOWERBR   LT(_LOWER, KC_LBRC)
#define RAISE     MO(_RAISE)
#define RAISEBR   LT(_RAISE, KC_RBRC)
#define MOUSE     LT(_MOUSE, KC_MINS)
#define MEDIA     TG(_MEDIA)
#define RPG       TG(_RPG)
#define GUIDEL    LGUI_T(KC_BSPC)
#define CTLTAB    LCTL_T(KC_TAB)
#define SFTTAB    LSFT_T(KC_TAB)
#define ALTZ      LALT_T(KC_Z)
#define MOVEL     LGUI(KC_J)
#define MOVED     LGUI(KC_K)
#define MOVEU     LGUI(KC_L)
#define MOVER     LGUI(KC_SCLN)
#define WORK1     LGUI(KC_1)
#define WORK2     LGUI(KC_2)
#define WORK3     LGUI(KC_3)
#define WORK4     LGUI(KC_4)
#define LTAB      RCS(KC_TAB)
#define RTAB      RCTL(KC_TAB)
#define WBACK     LALT(KC_LEFT)
#define WFORWARD  LALT(KC_RIGHT)
#define RMTAB     LCTL(KC_W)
#define RESTAB    RCS(KC_T)
#define WINTERM   LCTL(KC_1)
#define MPVDEL    LCTL(KC_DEL)
#define MPVRATIO  LSFT(KC_A)
#define NARCHIVE  LSFT(KC_PGUP)
#define PARCNIVE  LSFT(KC_PGDN)

const uint16_t PROGMEM encoder_keymaps[][2][2] = {
    [_QWERTY] =  { { KC_LEFT, KC_RIGHT },     { KC_UP,KC_DOWN} },
    [_LOWER]  =  { { C(S(KC_TAB)), C(KC_TAB) },    { KC__VOLDOWN,   KC__VOLUP } },
    [_RAISE]  =  { { G(KC_LEFT),   G(KC_RGHT) },    { G(KC_TAB),     G(S(KC_TAB)) } },
    [_ADJUST] =  { { KC_TRNS,      KC_TRNS },       { KC_TRNS,       KC_TRNS } },
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_4(
     CTLTAB,    KC_Q,   KC_W,    KC_E,    KC_R,       KC_T,          KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,    KC_QUOT,
     KC_DEL,    KC_A,   KC_S,    KC_D,    KC_F,       KC_G,          KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN, KC_MINS,
     KC_LSFT,   ALTZ,   KC_X,    KC_C,    KC_V,       KC_B,          KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                        _______, KC_LGUI, LOWER,      KC_SPC,        RETRS,    KC_BSPC,  KC_ESC,  _______
  ),
  [_LOWER] = LAYOUT_split_3x6_4(
     _______,   KC_1,   KC_2,   KC_3,   KC_4,     KC_5,           KC_6,       KC_7,     KC_8,     KC_9,     KC_0,       KC_EQL,
     _______,    MOVEL,  MOVED,  MOVEU,  MOVER,    WINTERM,        _______,    _______,  _______,  _______,  _______,    KC_PLUS,
     _______,   WORK1,  WORK2,  WORK3,  WORK4,    KC_ESC,         _______,    _______,  _______,  _______,  KC_GRAVE,   KC_PIPE,
                        _______,  _______, _______,  _______,     _______,  _______,   _______,    _______
  ),
  [_RAISE] = LAYOUT_split_3x6_4(
     _______,  KC_F9, KC_F10, KC_F11, KC_F12,  _______,       KC_HOME,  KC_PGUP,  _______, _______,  _______,  _______,
     _______,  KC_F5, KC_F6,  KC_F7,  KC_F8,   _______,       KC_LEFT,  KC_DOWN,  KC_UP,   KC_RGHT,  KC_LBRC,  KC_RBRC,
     _______,  KC_F1, KC_F2,  KC_F3,  KC_F4,   _______,       KC_END,   KC_PGDN,  KC_DEL,  _______,  _______,  _______,
                          _______,  _______,             _______, _______,     _______,  _______,   _______,  _______
  ),
  [_RPG] = LAYOUT_split_3x6_4(
     _______,  _______, _______, _______, _______,  _______,        _______,  KC_X,     KC_UP,    KC_S,     _______,   RPG,
     _______,  _______, _______, _______, _______,  _______,        _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,   KC_Z,
     _______,  _______, _______, _______, _______,  _______,        KC_ENT,   _______,  _______,  _______,  _______,   KC_RSFT,
                                 _______,  _______,          _______,  _______,      _______,  _______,  _______,  _______
  ),
  [_MEDIA] = LAYOUT_split_3x6_4(
     _______,  _______, _______, _______, _______,  _______,        MPVDEL,     KC_LT,       KC_I,       KC_GT,      KC_Q,    MEDIA,
     _______,  _______, _______, _______, _______,  _______,        MPVRATIO,   NARCHIVE,    KC_UP,      PARCNIVE,   KC_DEL,  _______,
     _______,  _______, _______, _______, _______,  _______,        KC_HOME,    KC_LEFT,     KC_DOWN,    KC_RIGHT,   KC_END,  _______,
                                  _______,  _______,         _______,  _______,     _______,  _______,   _______,    _______
  ),
  [_ADJUST] = LAYOUT_split_3x6_4(
    XXXXXXX, XXXXXXX, RESET,   XXXXXXX, XXXXXXX,XXXXXXX,      MEDIA,   RPG,     XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
                               _______,  _______,        _______, _______,    _______,  _______,    _______,  _______
  )
};
