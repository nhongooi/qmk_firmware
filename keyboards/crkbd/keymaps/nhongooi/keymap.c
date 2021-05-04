#include QMK_KEYBOARD_H
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
    TRANS3,  NUM_T
  ),
  [_RAISE] = LAYOUT_fifi_wrapper(
    FUCT_1,  RASSIT_1,
    FUCT_2,  RASSIT_2,
    FUCT_3,  RASSIT_3,
    TRANS6
  ),
  [_LMISC] = LAYOUT_fifi_wrapper(
    _______, _______, _______, _______,  _______,       _______, _______, _______, _______,  _______,
    REDO,    CUT,     COPY,    PASTE,    UNDO,          _______, _______, _______, _______,  _______,
    _______, _______, _______, _______,  _______,       _______, _______, _______, _______,  _______,
                      _______, _______,  _______,       _______, _______,  _______

  ),
  [_RPG] = LAYOUT_fifi_wrapper(
    RPG_1,
    RPG_2,
    RPG_3,
    TRANS3, RPG_T
  ),
  [_MEDIA] = LAYOUT_fifi_wrapper(
    MEDIA_1,
    MEDIA_2,
    MEDIA_3,
    TRANS3, MEDIA_T
  ),
  [_ADJUST] = LAYOUT_fifi_wrapper(
    ADJ_1,
    ADJ_2,
    ADJ_3,
    TRANS6
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
