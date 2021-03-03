#include QMK_KEYBOARD_H
#include <stdio.h>


#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


extern uint8_t is_master;

enum layer_number {
  _QWERTY = 0,
  _LOWER  = 1,
  _MEDIA  = 2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* QWERTY
  * ,-----------------------------------------.                    ,-----------------------------------------.
  * | GESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  =   |
  * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  '   |
  * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  * |BackSP|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  -   |
  * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
  * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
  * `-----------------------------------------/       /     \      \-----------------------------------------'
  *                   | LT_1 | CTRL | META | /Space  /       \Enter \  | LT_1 | CTRL | HOME |
  *                   | PGUP | PGDN |      |/       /         \      \ |DELETE|      |      |
  *                   `----------------------------'           '------''--------------------'
  */

  [_QWERTY] = LAYOUT( \
    KC_GESC,         KC_1,  KC_2,  KC_3,  KC_4,    KC_5,                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL, \
    LALT_T(KC_TAB),  KC_Q,  KC_W,  KC_E,  KC_R,    KC_T,                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT, \
    KC_BSPC,         KC_A,  KC_S,  KC_D,  KC_F,    KC_G,                    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_MINS, \
    LSFT_T(KC_LBRC), KC_Z,  KC_X,  KC_C,  KC_V,    KC_B,  KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_RBRC), \
                LT(1,KC_PGUP), LCTL_T(KC_PGDN), KC_LGUI, KC_SPC,  KC_ENT,  LT(1,KC_DEL), KC_RCTRL, KC_HOME \
  ),
  /* LOWER
  * ,-----------------------------------------.                    ,-----------------------------------------.
  * |      |      |      |      |      |      |                    | TG 2 |      |      |      |      |      |
  * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
  * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  * |      |      |      |      |      |      |-------.    ,-------| Left | Down |  Up  |Right |      | PIPE |
  * |------+------+------+------+------+------| Enter |    |       |------+------+------+------+------+------|
  * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
  * `-----------------------------------------/       /     \      \-----------------------------------------'
  *                   |      |      |      | /       /       \      \  |      |      |      |
  *                   |      |      |      |/       /         \      \ |      |      |      |
  *                   `----------------------------'           '------''--------------------'
  */
  [_LOWER] = LAYOUT( \
    _______, _______,   _______,    _______,    _______,       _______,                   TG(2), _______, _______,_______, _______, _______,\
    KC_F1,   KC_F2,     KC_F3,      KC_F4,      KC_F5,         KC_F6,                     KC_F7,   KC_F8,   KC_F9, KC_F10,  KC_F11,  KC_F12, \
    _______, LGUI(KC_J),LGUI(KC_K), LGUI(KC_L), LGUI(KC_SCLN), _______,                   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, KC_BSLS, \
    _______, _______,    _______, _______, _______, _______, KC_ENT , _______, _______, _______, _______, _______, _______, _______, \
                              _______, _______, _______, _______, _______,  _______, _______, _______\
  ),
  /* _EDIA
  * ,-----------------------------------------.                    ,-----------------------------------------.
  * |      |      |      |      |      |      |                    |CTLDEL|      |      |      |      |  Q   |
  * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  * |      |      |      |      |      |      |                    |SFT_A |      |      |      |      |      |
  * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  * |      |      |      |      |      |      |-------.    ,-------|DELETE|SFPGUP|KC_UP |SFPGDW|      |      |
  * |------+------+------+------+------+------|       |    | PAUSE |------+------+------+------+------+------|
  * |      |      |      |      |      |      |-------|    |-------|   <  | HOME | DOWN |  END |   >  | TG 2 |
  * `-----------------------------------------/       /     \      \-----------------------------------------'
  *                   |      |      |      | /       /       \      \  |      |      |      |
  *                   |      |      |      |/       /         \      \ |      |      |      |
  *                   `----------------------------'           '------''--------------------'
  */

  [_MEDIA] = LAYOUT( \
    _______, _______, _______, _______, _______, _______,                     LCTL(KC_DEL), _______,       _______, _______,       _______, KC_Q, \
    _______, _______, _______, _______, _______, _______,                     LSFT(KC_A),   LSFT(KC_PGUP), KC_UP,   LSFT(KC_PGDN), _______, _______, \
    _______, _______, _______, _______, _______, _______,                     KC_DEL,       KC_HOME,       KC_DOWN, KC_END,        _______, _______, \
    _______, _______, _______, _______, _______, _______,  _______, KC_PAUS,  KC_LT,        KC_GT,         _______, _______,       _______, TG(2), \
                               _______, _______, _______,  _______, _______,  _______, _______, _______ \
  )
};

uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Store the current modifier state in the variable for later reference
  mod_state = get_mods();
  switch (keycode) {
    case KC_BSPC:
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
      break;
    case KC_HOME:
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
  return true;
};

// Credit: https://github.com/HellSingCoder/qmk_firmware/tree/master/keyboards/sofle/keymaps/HellSingCoder
#ifdef OLED_DRIVER_ENABLE
// KEYBOARD PET START

// settings
#define MIN_WALK_SPEED 10
#define MIN_RUN_SPEED 40

// advanced settings
#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
#define ANIM_SIZE 96 // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

// timers
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;

// current frame
uint8_t current_frame = 0;

// status variables
int current_wpm = 0;
led_t led_usb_state;

bool isSneaking = false;
bool isJumping = false;
bool showedJump = true;

// logic
static void render_luna(int LUNA_X, int LUNA_Y) {

    // Sit
    static const char PROGMEM sit[2][ANIM_SIZE] = {
        // 'sit1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
            0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
            0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },

        // 'sit2', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
            0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
            0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        }
    };

    // Walk
    static const char PROGMEM walk[2][ANIM_SIZE] = {
        // 'walk1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80,
            0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03,
            0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },

        // 'walk2', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
            0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e,
            0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        }
    };

    // Run
    static const char PROGMEM run[2][ANIM_SIZE] = {
        // 'run1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01,
            0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
        },

        // 'run2', 32x22px
        {
            0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
            0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37,
            0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        }
    };

    // Bark
    static const char PROGMEM bark[2][ANIM_SIZE] = {
        // 'bark1', 32x22px
        {
            0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
            0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02,
            0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },

        // 'bark2', 32x22px
        {
            0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
            0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02,
            0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        }
    };

    // Sneak
    static const char PROGMEM sneak[2][ANIM_SIZE] = {
        // 'sneak1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04,
            0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06,
            0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
        },

        // 'sneak2', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04,
            0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04,
            0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
        }
    };

    // animation
    void animation_phase(void) {

        // jump
        if (isJumping || !showedJump) {

            // clear
            oled_set_cursor(LUNA_X,LUNA_Y +2);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X,LUNA_Y -1);

            showedJump = true;
        } else {

            // clear
            oled_set_cursor(LUNA_X,LUNA_Y -1);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X,LUNA_Y);
        }

        // switch frame
        current_frame = (current_frame + 1) % 2;

        // current status
        if(led_usb_state.caps_lock) {
            oled_write_raw_P(bark[abs(1 - current_frame)], ANIM_SIZE);

        } else if(isSneaking) {
            oled_write_raw_P(sneak[abs(1 - current_frame)], ANIM_SIZE);

        } else if(current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[abs(1 - current_frame)], ANIM_SIZE);

        } else if(current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[abs(1 - current_frame)], ANIM_SIZE);

        } else {
            oled_write_raw_P(run[abs(1 - current_frame)], ANIM_SIZE);
        }
    }

    // animation timer
    if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animation_phase();
    }

    // this fixes the screen on and off bug
    if (current_wpm > 0) {
        oled_on();
        anim_sleep = timer_read32();
    } else if(timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
        oled_off();
    }

}

// KEYBOARD PET END

static void print_logo_narrow(void) {
    // wpm counter
    char wpm_str[8];
    oled_set_cursor(0,14);
    sprintf(wpm_str, " %03d", current_wpm);
    oled_write(wpm_str, false);

    oled_set_cursor(0,15);
    oled_write(" wpm", false);
}

static void print_status_narrow(void) {
    oled_set_cursor(0,1);

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write("QWRTY", false);
            break;
        case _LOWER:
            oled_write("LOWER", false);
            break;
        case _MEDIA:
            oled_write("MEDIA", false);
            break;
        default:
            oled_write("UNDEF", false);
    }

    oled_set_cursor(0,5);

    // Print current layer
    oled_write("LAYER", false);

    oled_set_cursor(0,6);
    oled_write("-----", false);
    oled_set_cursor(0,7);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write("Base", false);
            break;
        case _MEDIA:
            oled_write("Media", false);
            break;
        case _LOWER:
            oled_write("lower", false);
            break;
        default:
            oled_write("Undef", false);
    }

    oled_set_cursor(0,8);
    oled_write("-----", false);

    // KEYBOARD PET RENDER START

    render_luna(0,13);

    // KEYBOARD PET RENDER END
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void oled_task_user(void) {

    // KEYBOARD PET VARIABLES START

    current_wpm = get_current_wpm();
    led_usb_state = host_keyboard_led_state();

    // KEYBOARD PET VARIABLES END

    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        print_logo_narrow();
    }
}

#endif
