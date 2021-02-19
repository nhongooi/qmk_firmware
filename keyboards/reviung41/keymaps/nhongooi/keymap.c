/* Copyright 2020 gtips
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
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
    _RPG
};

#define LOWER     MO(_LOWER)
#define RAISE     MO(_RAISE)
#define ADJUST    MO(_ADJUST)
#define RPG       TG(_RPG)
#define MOUSE     LT(_MOUSE, KC_MINS)
#define MEDIA     TG(_MEDIA)
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
  [_BASE] = LAYOUT_reviung41(
    LCTL_T(KC_TAB),  KC_Q,             KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_QUOT,
    KC_BSPC,         KC_A,             KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_MINS,
    KC_LSFT,         LALT_T(KC_Z),     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_ENT,
                                                           KC_LGUI,   LOWER,    KC_SPC,   RAISE,    RSFT_T(KC_RCBR)
  ),
  [_LOWER] = LAYOUT_reviung41(
    LCTL(KC_TAB), KC_1,       KC_2,       KC_3,       KC_4,          KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_EQL,
    RCS(KC_TAB),  LGUI(KC_J), LGUI(KC_K), LGUI(KC_L), LGUI(KC_SCLN), LCA(KC_DEL),        KC_LCBR,  KC_RCBR,  _______,  _______,  _______,  _______,
    _______,      LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4),    LGUI(KC_5),         _______,  _______,  _______,  _______,  _______,  _______,
                                                      _______,       _______,    KC_ENT, _______,  _______
  ),
  [_RAISE] = LAYOUT_reviung41(
    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,              KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,  KC_F12,
    _______,  _______,  _______,  _______,  _______,   _______,            KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______, KC_GESC,
    _______,  _______,  _______,  _______,  _______,   _______,            KC_END,   KC_PGDN,  KC_DEL,   _______,  RPG,     KC_PIPE,
                                            _______,   _______,  _______,  _______,  _______
  ),
  [_RPG] = LAYOUT_reviung41(
    _______,  _______,  _______,  _______,  _______,   _______,            _______,  _______,  KC_UP,    _______,  _______,   _______,
    _______,  _______,  _______,  _______,  _______,   _______,            KC_X,     KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,   KC_Z,
    _______,  _______,  _______,  _______,  _______,   _______,            _______,  _______,  _______,  _______,  _______,   KC_RSFT,
                                            _______,   _______,  KC_ENT,   _______,  RPG
  ),
    [_MEDIA] = LAYOUT(
     _______,  _______, _______, _______, _______,  _______,        MPVDEL,     KC_LT,       KC_I,       KC_GT,      KC_Q,    MEDIA,
     _______,  _______, _______, _______, _______,  _______,        MPVRATIO,   NARCHIVE,    KC_UP,      PARCNIVE,   KC_DEL,  _______,
     _______,  _______, _______, _______, _______,  _______,        KC_HOME,    KC_LEFT,     KC_DOWN,    KC_RIGHT,   KC_END,  _______,
                                          _______,  _______,        _______,    _______
  ),
  [_ADJUST] = LAYOUT_reviung41(
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                            _______,   _______,  XXXXXXX,  _______,  _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _RAISE:
        rgblight_sethsv_noeeprom(HSV_GOLD);
        break;
    case _LOWER:
        rgblight_sethsv_noeeprom (HSV_TEAL);
        break;
    case _ADJUST:
        rgblight_sethsv_noeeprom (HSV_PINK);
        break;
    case _RPG:
        rgblight_sethsv_noeeprom (HSV_ORANGE);
        break;
    default:
        rgblight_sethsv_noeeprom (HSV_PURPLE);
        break;
    }
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

uint8_t mod_state;
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
