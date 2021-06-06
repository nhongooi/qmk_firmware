#include QMK_KEYBOARD_H
#include "nhongooi.h"

#define ZLW     LT(_LOWER, KC_Z)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_2u_space(
        KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,    KC_LBRC,   KC_RBRC,   KC_Y,   KC_U,   KC_I,      KC_O,   KC_P,     KC_BSPC,
        LGUIA,  LSHFS,  LCTLD,  LALTF,  KC_G,    KC_QUOT,  KC_MINUS,   KC_H,   RALTJ,  RCTLK,     RSHFL,  RGUICOL,  KC_ENT,
        ZLW,    KC_X,   KC_C,   KC_V,   KC_B,    LT(_RAISE, KC_SPC),   KC_N,   KC_M,   KC_COMM,   KC_DOT, KC_SLSH
    ),
    [_LOWER] = LAYOUT_2u_space(
        DMENU,   BWORD,   _______,  NWORD,  _______,    KC_LPRN, KC_RPRN, KC_LCBR,   KC_7,    KC_8,    KC_9,    KC_LCBR,   KC_DEL,
        WINTOG,  FCSL,    FCSD,     FCSU,   FCSR,       KC_DQT,  KC_DQT,  KC_QUOT,   KC_4,    KC_5,    KC_6,    KC_EQL,    _______,
        _______, WORK1,   WORK2,    WORK3,  WORK4,           _______,     KC_MINUS,  KC_1,    KC_2,    KC_3,    KC_BSLASH
    ),
    [_RAISE] = LAYOUT_2u_space(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    _______, _______,  KC_PGUP,  KC_HOME,  KC_CUT,   KC_COPY,  KC_PSTE,   _______,
        _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,    _______,  _______, KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_BSLASH, _______,
        _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,        _______,      KC_PGDN,  KC_END,   KC_DEL,   _______,  KC_GRAVE
    ),
    [_ADJUST] = LAYOUT_2u_space(
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
