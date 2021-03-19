#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

#ifdef OLED_DRIVER_ENABLE
#include <stdio.h>

#endif


extern uint8_t is_master;

enum layer_number {
  _QWERTY = 0,
  _LOWER  = 1,
  _MEDIA  = 2,
  _IDEA = 3
};

enum custom_kc{
    LSLTR = SAFE_RANGE,
    GREP,
    MVN,
    JWB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//prob want a third layer and stack up lower for more useful keys
  [_QWERTY] = LAYOUT(
    KC_GESC,         KC_1,          KC_2,  KC_3,  KC_4,     KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
    KC_TAB,          KC_Q,          KC_W,  KC_E,  KC_R,     KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
    KC_BSPC,         KC_A,          KC_S,  KC_D,  KC_F,     KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_MINS,
    LSFT_T(KC_LCBR), LALT_T(KC_Z),  KC_X,  KC_C,  KC_V,     KC_B,    KC_PGDN, KC_HOME, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_RCBR),
                                           MO(1), KC_LCTRL, KC_LGUI, KC_SPC,  KC_ENT,  MO(1),   MO(3),   RGUI(KC_RCTRL)),
  [_LOWER] = LAYOUT(
    KC_F1,       KC_F2,      KC_F3,      KC_F4,      KC_F5,         KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______,     _______,    _______,    _______,    _______,       _______,                   _______, _______, _______, _______, _______, TG(2),
    LCA(KC_DEL), LGUI(KC_J), LGUI(KC_K), LGUI(KC_L), LGUI(KC_SCLN), _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_BSLS,
    _______,     _______,    _______,    _______,    _______,       _______, KC_ENT,  _______, _______, _______, _______, _______, _______, _______,
                                         _______,    _______,       _______, _______, _______, _______, _______, _______),
  [_MEDIA] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                     LCTL(KC_DEL), _______,       KC_I,    _______,       _______, KC_Q,
    _______, _______, _______, _______, _______, _______,                     LSFT(KC_A),   LSFT(KC_PGUP), KC_UP,   LSFT(KC_PGDN), _______, _______,
    _______, _______, _______, _______, _______, _______,                     KC_DEL,       KC_HOME,       KC_DOWN, KC_END,        _______, _______,
    _______, _______, _______, _______, _______, _______,  _______, KC_PAUS,  KC_LT,        KC_GT,         _______, _______,       _______, TG(2),
                               _______, _______, _______,  _______, _______,  _______,      _______,       _______),
  [_IDEA] = LAYOUT(
    _______, _______, _______,     _______, _______, _______,                        _______,   _______,     _______,      _______,    _______,       _______,
    _______, _______, _______,     _______, _______, _______,                        RCS(KC_A), RALT(KC_F7), RALT(KC_ENT), _______,    _______,       _______,
    _______, _______, RCS(KC_DEL), _______, _______, _______,                        JWB,       _______,     _______,      LCA(KC_L),  _______,       _______,
    _______, _______, _______,     _______, _______, _______,  _______, MEH(KC_T),   GREP,      MVN,         LSLTR,        _______,    RCTL(KC_SLSH), _______,
                                   _______, _______, _______,  _______, RCS(KC_ENT), _______,   _______,     _______)
};

// https://github.com/foureight84/qmk_firmware/blob/sofle_foureight84/keyboards/sofle/keymaps/foureight84/keymap.c
#ifdef OLED_DRIVER_ENABLE
/* Animation bit by j-inc https://github.com/qmk/qmk_firmware/tree/master/keyboards/kyria/keymaps/j-inc */
// WPM-responsive animation stuff here
#define IDLE_FRAMES 5
#define IDLE_SPEED 40 // below this wpm value your animation will idle

// #define PREP_FRAMES 1 // uncomment if >1

#define TAP_FRAMES 2
#define TAP_SPEED 60 // above this wpm value typing animation to triggere

#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
// #define SLEEP_TIMER 60000 // should sleep after this period of 0 wpm, needs fixing
#define ANIM_SIZE 320 // number of bytes in array, mini          mize for adequate firmware size, max is 1024

#define MIN_WALK_SPEED 10
#define MIN_RUN_SPEED 40

// advanced settings
#define ANIM_LUNA_SIZE 96 // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
uint8_t current_idle_frame = 0;
// uint8_t current_prep_frame = 0; // uncomment if PREP_FRAMES >1
uint8_t current_tap_frame = 0;

// current frame
uint8_t current_frame = 0;

// status variables
int current_wpm = 0;

bool isSneaking = false;
bool isJumping = false;
bool showedJump = true;
bool isWoof = false;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

static void print_status_narrow(void) {
    oled_set_cursor(0,0);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write("QWRTY", false);
            break;
        default:
            oled_write("UNDEF", false);
    }

    oled_set_cursor(0,2);
    oled_write("LAYER", false);
    oled_set_cursor(0,3);
    oled_write("-----", false);
    oled_set_cursor(0,5);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write("QWRTY", false);
            break;
        case _LOWER:
            oled_write("Lower", false);
            break;
        case _MEDIA:
            oled_write("Media", false);
            break;
        case _IDEA:
            oled_write("IDEA", false);
            break;
        default:
            oled_write("Undef", false);
    }
}

static void print_logo_narrow(void) {

    // wpm counter
    char wpm_str[8];
    oled_set_cursor(0,12);
    sprintf(wpm_str, " %03d", current_wpm);
    oled_write(wpm_str, false);

    oled_set_cursor(0,15);
    oled_write(" WPM", false);
}

void oled_task_user(void) {
    current_wpm = get_current_wpm();
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        print_logo_narrow();
    }
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
        case KC_HOME:{
            static bool homekey_registered;
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_END);
                homekey_registered = true;
                set_mods(mod_state);
                return false;
                }
            } else {
                if (homekey_registered) {
                unregister_code(KC_END);
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
        case LSLTR:
            if (record->event.pressed) {SEND_STRING("ls -ltr");}
            break;
        case GREP:
            if (record->event.pressed) {SEND_STRING("| grep ");}
            break;
        case MVN:
            if (record->event.pressed) {SEND_STRING("mvn clean ");}
            break;
        case JWB:
            if (record->event.pressed) {SEND_STRING("JWBIII");}
            break;
        case KC_SPC:
            if (record->event.pressed) {
                isJumping = true;
                showedJump = false;
            } else { isJumping = false; }
            break;
        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) { isSneaking = true; }
            else { isSneaking = false; }
            break;
        case KC_ENT:
            if (record->event.pressed) { isWoof= true; }
            else { isWoof = false; }
            break;
    }
    return true;
};

#endif
