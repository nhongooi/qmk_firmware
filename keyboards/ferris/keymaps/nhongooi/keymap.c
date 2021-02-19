#include QMK_KEYBOARD_H
#include "config.h"
#include "nhongooi.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_ferris_wrapper(
    QWERTY_1,
    QWERTY_2,
    QWERTY_3,
    QWERTY_T
  ),
  [_LOWER] = LAYOUT_ferris_wrapper(
    I3_1,    NUM_1,
    I3_2,    NUM_2,
    I3_3,    NUM_3,
    TRANS_S, NUM_T
  ),
  [_RAISE] = LAYOUT_ferris_wrapper(
    FUCT_1,  RASSIT_1,
    FUCT_2,  RASSIT_2,
    FUCT_3,  RASSIT_3,
    TRANS_W
  ),
  [_LMISC] = LAYOUT_ferris_wrapper(
    LMISC_1,
    LMISC_2,
    LMISC_3,
    TRANS_S, LMISC_T

  ),
  [_RPG] = LAYOUT_ferris_wrapper(
    RPG_1,
    RPG_2,
    RPG_3,
    TRANS_S, RPG_T
  ),
  [_MEDIA] = LAYOUT_ferris_wrapper(
    MEDIA_1,
    MEDIA_2,
    MEDIA_3,
    TRANS_S, MEDIA_T
  ),
  [_TYPE] = LAYOUT( /* QWERTY */
    KC_Q, KC_W, KC_E, KC_R, KC_T,            KC_Y, KC_U,  KC_I,    KC_O,   KC_P,
    KC_A, KC_S, KC_D, KC_F, KC_G,            KC_H, KC_J,  KC_K,    KC_L,   KC_QUOT,
    KC_Z, KC_X, KC_C, KC_V, KC_B,            KC_N, KC_M,  KC_COMM, KC_DOT, KC_RSHIFT,
                            TYPEL, SPCLW, KC_ENT, KC_BSPC
  ),
  [_ADJUST] = LAYOUT_ferris_wrapper(
    ADJ_1,
    ADJ_2,
    ADJ_3,
    TRANS_W
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
