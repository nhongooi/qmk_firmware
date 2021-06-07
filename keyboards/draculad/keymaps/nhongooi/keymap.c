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

#include QMK_KEYBOARD_H
#include "pimoroni_trackball.h"
#include "pointing_device.h"
#include "nhongooi.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] =  LAYOUT_wrapper(
        QWERTY_1,
        QWERTY_2,
        QWERTY_3,
        CONMENU, CGUI(KC_M),
        TD(MS_BT),    TABLM,    SPCLW, _______, RETRS, KC_BSPC
    ),
    [_LOWER] =  LAYOUT_wrapper(
        I3_1,    NUM_1,
        I3_2,    NUM_2,
        I3_3,    NUM_3,
        CLEANTERM, TERMPASTE,
        TRANS_S, NUM_T
    ),
    [_RAISE] =  LAYOUT_wrapper(
        FUCT_1,  RASSIT_1,
        FUCT_2,  RASSIT_2,
        FUCT_3,  RASSIT_3,
        CLEANAFTER, _______,
        TRANS_W
    ),
    [_LMISC] =  LAYOUT_wrapper(
        LMISC_1,
        LMISC_2,
        LMISC_3,
        _______, _______,
        TRANS_W
    ),
    [_ADJUST] =  LAYOUT_wrapper(
        ADJ_1,
        ADJ_2,
        ADJ_3,
        XXXXXXX, XXXXXXX,
        TRANS_W
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
      switch (get_highest_layer(layer_state)) {
        case _LOWER:
          register_code(KC_LCTL);
          clockwise?tap_code(KC_RIGHT):tap_code(KC_LEFT);
          unregister_code(KC_LCTL);
          break;
        case _RAISE:
          register_code(KC_LALT);
          clockwise?tap_code(KC_F):tap_code(KC_B);
          unregister_code(KC_LALT);
          break;
        default:
          clockwise?tap_code(KC_DOWN):tap_code(KC_UP);
          break;
      }
    }
    else if (index == 2) {
      switch (get_highest_layer(layer_state)) {
        case _LOWER:
            register_code(KC_LCTL);
            register_code(KC_LGUI);
            clockwise?tap_code(KC_RIGHT):tap_code(KC_LEFT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LGUI);
            break;
        default:
            clockwise?tap_code(KC_PGDN):tap_code(KC_PGUP);
            break;
      }
    }
}
#endif
