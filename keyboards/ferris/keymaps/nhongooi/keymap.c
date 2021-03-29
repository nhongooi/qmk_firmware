// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum ferris_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};


#define KC_CTSC RCTL_T(KC_SCLN)
#define KC_CTLA LCTL_T(KC_A)
#define KC_LSHZ LSFT_T(KC_Z)
#define KC_RLSH RSFT_T(KC_SLSH)
#define KC_SPM1 LT(_LOWER, KC_SPC)
#define KC_BSM2 LT(_RAISE, KC_BSPC)
#define ALTTAB  LALT_T(KC_TAB)
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( /* QWERTY */
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,  KC_I,    KC_O,   KC_P,
    KC_CTLA, KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,  KC_K,    KC_L,   KC_SCLN,
    KC_LSHZ, KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M,  KC_COMM, KC_DOT, KC_RLSH,
                               KC_LGUI, KC_SPM1,         KC_BSM2, ALTTAB
  ),
  [_LOWER] = LAYOUT( /* [> LOWER <] */
    KC_1,   KC_2,   KC_3,   KC_4,    KC_5,            KC_6,    KC_7,    KC_8,     KC_9,    KC_0,
    MOVEL,  MOVED,  MOVEU,  MOVER,   KC_ENT,          KC_QUOT, KC_MINS, KC_EQL,   KC_PLUS, KC_GRAVE,
    WORK1,  WORK2,  WORK3,  WORK4,   KC_ESC,          KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_PIPE,
                            KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS
  ),
  [_RAISE] = LAYOUT( /* [> RAISE <] */
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_TRNS,        KC_HOME,  KC_PGUP,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_TRNS,        KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_PIPE,
    KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,        KC_END,   KC_PGDN,  KC_DEL,   KC_LBRC,  KC_RBRC,
                               KC_TRNS, KC_ENT,         KC_TRNS,  KC_TRNS
  ),
   [_ADJUST] = LAYOUT( /* [> RAISE <] */
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                KC_TRNS, KC_TRNS,         KC_TRNS,  KC_TRNS
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
