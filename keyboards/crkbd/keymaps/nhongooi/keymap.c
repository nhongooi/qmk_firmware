// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H
#include "config.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum crkbd_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _MEDIA,
  _RPG,
  _ADJUST
};
// Control GUI modifier
#define CGUI(kc) (QK_LGUI | QK_LCTL | (kc))
// modifiers QWERTY
#define LGUIA     LGUI_T(KC_A)
#define LALTS     LALT_T(KC_S)
#define LCTLD     LCTL_T(KC_D)
#define LSHFF     LSFT_T(KC_F)
#define RGUICOL   RGUI_T(KC_SCLN)
#define RALTL     RALT_T(KC_L)
#define RCTLK     RCTL_T(KC_K)
#define RSHFJ     RSFT_T(KC_J)
#define SHFSLSH   RSFT_T(KC_SLSH)
// layer taps
#define SPCLW     LT(_LOWER, KC_SPACE)
#define RETRS     LT(_RAISE, KC_ENT)
// Toggle layers
#define MEDIA     TG(_MEDIA)
#define RPG       TG(_RPG)
#define MPVDEL    LCTL(KC_DEL)
#define MPVRATIO  LSFT(KC_A)
#define NARCHIVE  LSFT(KC_PGUP)
#define PARCNIVE  LSFT(KC_PGDN)
// i3 specific
#define DMENU     LGUI(KC_SPC)
#define WINTOG    SGUI(KC_SPC)
#define FCSL      LGUI(KC_J)
#define FCSD      LGUI(KC_K)
#define FCSU      LGUI(KC_L)
#define FCSR      LGUI(KC_SCLN)
#define MOVE1     CGUI(KC_1)
#define MOVE2     CGUI(KC_2)
#define MOVE3     CGUI(KC_3)
#define MOVE4     CGUI(KC_4)
#define WORK1     LGUI(KC_1)
#define WORK2     LGUI(KC_2)
#define WORK3     LGUI(KC_3)
#define WORK4     LGUI(KC_4)
#define TERM      LGUI(KC_ENT)
#define QUIT      SGUI(KC_Q)
// special
#define UNDO      RCTL(KC_Z)
#define REDO      RCTL(KC_Y)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x5_3(
    KC_Q,  KC_W,   KC_E,    KC_R,   KC_T,               KC_Y,     KC_U,     KC_I,    KC_O,   KC_P,
    LGUIA, LALTS,  LCTLD,   LSHFF,  KC_G,               KC_H,     RSHFJ,    RCTLK,   RALTL,  RGUICOL,
    KC_Z,  KC_X,   KC_C,    KC_V,   KC_B,               KC_N,     KC_M,     KC_COMM, KC_DOT, SHFSLSH,
                   KC_BSPC, KC_TAB, SPCLW,              RETRS,    KC_BSPC,  KC_GESC
  ),
  [_LOWER] = LAYOUT_split_3x5_3(
    DMENU,   MOVE1,  MOVE2,   MOVE3,   MOVE4,           KC_LBRC,   KC_7,    KC_8,  KC_9,  KC_RBRC,
    WINTOG,  FCSL,   FCSD,    FCSU,    FCSR,            KC_QUOT,   KC_4,    KC_5,  KC_6,  KC_EQL,
    QUIT,    WORK1,  WORK2,   WORK3,   WORK4,           KC_MINUS,  KC_1,    KC_2,  KC_3,  KC_SLSH,
                     _______, _______, _______,         _______,   KC_DOT,  KC_0
  ),
  [_RAISE] = LAYOUT_split_3x5_3(
    _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,           KC_PGUP,  KC_HOME,  KC_CUT,   KC_COPY,  KC_PSTE,
    _______,  KC_F5,   KC_F6,   KC_F7,   KC_F8,           KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_PIPE,
    _______,  KC_F9,   KC_F10,  KC_F11,  KC_F12,          KC_PGDN,  KC_END,   KC_DEL,   UNDO,     REDO,
                       _______, _______, _______,         _______,  _______,  _______
  ),
  [_RPG] = LAYOUT_split_3x5_3(
    _______, _______, _______, _______,  _______,        KC_LCTL,  KC_X,     KC_UP,    KC_S,     KC_RSFT,
    _______, _______, _______, _______,  _______,        KC_SPC,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_Z,
    _______, _______, _______, _______,  _______,        _______,  _______,  _______,  _______,  _______,
                      _______, _______,  _______,        KC_ENT,   _______,   RPG
  ),
  [_MEDIA] = LAYOUT_split_3x5_3(
    _______, _______, _______, _______,  _______,        MPVDEL,     KC_LT,    KC_I,    KC_GT,     KC_Q,
    _______, _______, _______, _______,  _______,        MPVRATIO,   KC_9,     KC_UP,   KC_0,      KC_DEL,
    _______, _______, _______, _______,  _______,        KC_HOME,    KC_LEFT,  KC_DOWN, KC_RIGHT,  KC_END,
                      _______, _______,  _______,        _______,    _______,  MEDIA
  ),
  [_ADJUST] = LAYOUT_split_3x5_3(
    XXXXXXX,  RESET,   XXXXXXX, XXXXXXX, XXXXXXX,        RPG,      MEDIA,   XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                       _______, _______, _______,        _______,  _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
