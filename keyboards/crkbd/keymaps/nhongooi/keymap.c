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
#include "config.h"
#include "nhongooi.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_fifi_wrapper(
    QWERTY_1,
    QWERTY_2,
    QWERTY_3,
    QWERTY_T

  ),
  [_LOWER] = LAYOUT_fifi_wrapper(
    I3_1,    NUM_1,
    I3_2,    NUM_2,
    I3_3,    NUM_3,
    TRANS_S, NUM_T
  ),
  [_RAISE] = LAYOUT_fifi_wrapper(
    FUCT_1,  RASSIT_1,
    FUCT_2,  RASSIT_2,
    FUCT_3,  RASSIT_3,
    TRANS_W
  ),
  [_LMISC] = LAYOUT_fifi_wrapper(
    LMISC_1,
    LMISC_2,
    LMISC_3,
    TRANS_W

  ),
  [_RPG] = LAYOUT_fifi_wrapper(
    RPG_1,
    RPG_2,
    RPG_3,
    TRANS_S, RPG_T
  ),
  [_MEDIA] = LAYOUT_fifi_wrapper(
    MEDIA_1,
    MEDIA_2,
    MEDIA_3,
    TRANS_S, MEDIA_T
  ),
  [_ADJUST] = LAYOUT_fifi_wrapper(
    ADJ_1,
    ADJ_2,
    ADJ_3,
    TRANS_W
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _LOWER:
            DRV_pulse(buzz_60);
            break;
        case _RAISE:
            DRV_pulse(pulsing_medium_80);
            break;
        case _MEDIA:
            DRV_pulse(transition_click_40);
            break;
        case _RPG:
            DRV_pulse(transition_hum_60);
            break;
        case _LMISC:
            DRV_pulse(lg_dblsharp_tick);
            break;
    }
    return state;
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
