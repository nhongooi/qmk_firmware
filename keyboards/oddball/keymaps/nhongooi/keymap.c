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

#include QMK_KEYBOARD_H

enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _RPG,
    _MEDIA,
    _MOUSE,
    _ADJUST
};

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
#define COPY      LCTL(KC_C)
#define PASTE     LCTL(KC_V)
#define CUT       LCTL(KC_X)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
     CTLTAB,    KC_Q,   KC_W,    KC_E,    KC_R,       KC_T,          KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,    KC_QUOT,
     GUIDEL,    KC_A,   KC_S,    KC_D,    KC_F,       KC_G,          KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN, MOUSE,
     KC_LSFT,   ALTZ,   KC_X,    KC_C,    KC_V,       KC_B,          KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                                          LOWER,    KC_SPC,        _______,  RAISE
  ),
  [_LOWER] = LAYOUT(
     KC_SCROLL, KC_1,   KC_2,   KC_3,   KC_4,     KC_5,           KC_6,       KC_7,     KC_8,     KC_9,     KC_0,       KC_EQL,
     KC_DEL,    MOVEL,  MOVED,  MOVEU,  MOVER,    WINTERM,        KC_BTN1,    KC_BTN2,  KC_BTN3,  _______,  _______,    KC_PLUS,
     _______,   WORK1,  WORK2,  WORK3,  WORK4,    KC_ESC,         _______,    _______,  _______,  _______,  KC_GRAVE,   KC_PIPE,
                                        _______,  _______,        _______,    _______
  ),
  [_RAISE] = LAYOUT(
     _______,  KC_F9, KC_F10, KC_F11, KC_F12,  _______,       KC_HOME,  KC_PGUP,  _______, _______,  _______,  _______,
     _______,  KC_F5, KC_F6,  KC_F7,  KC_F8,   _______,       KC_LEFT,  KC_DOWN,  KC_UP,   KC_RGHT,  KC_LBRC,  KC_RBRC,
     _______,  KC_F1, KC_F2,  KC_F3,  KC_F4,   _______,       KC_END,   KC_PGDN,  KC_DEL,  _______,  _______,  _______,
                                      _______, _______,       _______,  _______
  ),
  [_RPG] = LAYOUT(
     _______,  _______, _______, _______, _______,  _______,        _______,  KC_X,     KC_UP,    KC_S,     _______,   RPG,
     _______,  _______, _______, _______, _______,  _______,        _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,   KC_Z,
     _______,  _______, _______, _______, _______,  _______,        KC_ENT,   _______,  _______,  _______,  _______,   KC_RSFT,
                                          _______,  _______,        _______,  _______
  ),
  [_MEDIA] = LAYOUT(
     _______,  _______, _______, _______, _______,  _______,        MPVDEL,     KC_LT,       KC_I,       KC_GT,      KC_Q,    MEDIA,
     _______,  _______, _______, _______, _______,  _______,        MPVRATIO,   NARCHIVE,    KC_UP,      PARCNIVE,   KC_DEL,  _______,
     _______,  _______, _______, _______, _______,  _______,        KC_HOME,    KC_LEFT,     KC_DOWN,    KC_RIGHT,   KC_END,  _______,
                                          _______,  _______,        _______,    _______
  ),
  [_MOUSE] = LAYOUT(
     _______,  _______, _______, _______, _______,  _______,        XXXXXXX,  XXXXXXX,  RMTAB,    RESTAB,   KC_SCROLL,   KC_SPC,
     _______,  _______, _______, _______, _______,  _______,        KC_BTN1,  KC_BTN2,  KC_BTN3,  WBACK,    WFORWARD,    XXXXXXX,
     _______,  _______, _______, _______, _______,  _______,        LTAB,     RTAB,     COPY,     PASTE,    CUT,         _______,
                                          _______,  _______,        _______,  _______z
  ),
  [_ADJUST] = LAYOUT(
    XXXXXXX, XXXXXXX, RESET,   XXXXXXX, XXXXXXX,XXXXXXX,      MEDIA,   RPG,     XXXXXXX, XXXXXXX, XXXXXXX,KC_CPI_1,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,KC_CPI_2,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,KC_CPI_3,
                                      _______, _______,        _______,  _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

static uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {
        case KC_BSPC:{
            // Initialize a boolean variable that keeps track
            // of the delete key status: registered or not?
            static bool delkey_registered;
            if (record->event.pressed) {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    // Update the boolean variable to reflect the status of KC_DEL
                    delkey_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            } else { // on release of KC_BSPC
                // In case KC_DEL is still being sent even after the release of KC_BSPC
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
            // Let QMK process the KC_BSPC keycode as usual outside of shift
            break;
        }
        case KC_END:{
            static bool homekey_registered;
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_HOME);
                homekey_registered = true;
                set_mods(mod_state);
                return false;
                }
            } else {
                if (homekey_registered) {
                unregister_code(KC_HOME);
                homekey_registered = false;
                return false;
                }
            }
            break;
        }
        case KC_PGDN:{
            static bool pagekey_registered;
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_PGUP);
                pagekey_registered = true;
                set_mods(mod_state);
                return false;
                }
            } else {
                if (pagekey_registered) {
                unregister_code(KC_PGUP);
                pagekey_registered = false;
                return false;
                }
            }
            break;
        }
    }
    return true;
};
