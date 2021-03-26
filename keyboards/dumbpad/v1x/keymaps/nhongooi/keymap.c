#include QMK_KEYBOARD_H

#define _BASE   0
#define _CONT   1
#define _EMOTE  2

enum emoticons {
    LMAO,
    SMILE,
    MEH,
    SHRUG,
    SURPRISE,
    HELLO,
    SWEATING,
    WHAT,
    SIGH,
    OHNO,
    EXCITED,
    TABLE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
                   KC_7,        KC_8,    KC_9,     KC_BSPC,
                   KC_4,        KC_5,    KC_6,     KC_TAB,
                   KC_1,        KC_2,    KC_3,     KC_ENTER,
    KC_ENTER,      TT(_EMOTE),  KC_0,    KC_DOT,   TT(_CONT)
  ),
  [_CONT] = LAYOUT(
                 _______,     _______,     _______,      KC_KP_PLUS,
                 _______,     _______,     _______,      KC_KP_MINUS,
                 _______,     _______,     _______,      KC_KP_PLUS,
    _______,     _______,     _______,     _______,      KC_KP_SLASH
  ),
  [_EMOTE] = LAYOUT(
                LMAO,    TABLE,    SMILE,     RESET,
                MEH,     SHRUG,    SURPRISE,  _______,
                HELLO,   SWEATING, WHAT,      _______,
    _______,    SIGH,    OHNO,     EXCITED,   _______
  ),
};

void matrix_init_user(void) {
    set_unicode_input_mode(UC_LNX);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void keyboard_post_init_user(void) {
}



void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    switch (biton32(layer_state)) {
      case _BASE:
        if (clockwise) {
          tap_code(KC_TAB);
        } else {
          tap_code16(LSFT(KC_TAB));
        }
        break;
      case _CONT:
         if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;
    }
  }
}
