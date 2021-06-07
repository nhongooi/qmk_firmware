/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "pimoroni_trackball.h"
#include "i2c_master.h"
#include "nhongooi.h"


static uint8_t scrolling      = 0;
static int16_t x_offset       = 0;
static int16_t y_offset       = 0;
static int16_t h_offset       = 0;
static int16_t v_offset       = 0;
static float   precisionSpeed = 1;

static uint16_t i2c_timeout_timer;
static bool mouse_bt1_registered;

#ifndef I2C_TIMEOUT
#    define I2C_TIMEOUT 100
#endif
#ifndef I2C_WAITCHECK
#    define I2C_WAITCHECK 1000
#endif
#ifndef MOUSE_DEBOUNCE
#    define MOUSE_DEBOUNCE 5
#endif
#ifndef BT1_DEBOUNCE
#    define BT1_DEBOUNCE 200
#endif

// TAP DANCE SECTION


/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */

 // Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

void mouse_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:  register_code(KC_BTN2); break;
        case TD_SINGLE_HOLD: register_code(KC_BTN1); mouse_bt1_registered = true; break;
        case TD_DOUBLE_TAP:  register_code(KC_BTN3); break;
        case TD_DOUBLE_HOLD: register_code(KC_LCTL); register_code(KC_C); break;
        case TD_TRIPLE_TAP:  register_code(KC_LCTL); register_code(KC_X); break;
        default: ;
    }
}

void mouse_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:  unregister_code(KC_BTN2); break;
        case TD_SINGLE_HOLD: unregister_code(KC_BTN1); mouse_bt1_registered = false; break;
        case TD_DOUBLE_TAP:  unregister_code(KC_BTN3); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LCTL); unregister_code(KC_C); break;
        case TD_TRIPLE_TAP:  unregister_code(KC_LCTL); unregister_code(KC_X); break;
        default: ;
    }
    xtap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [MS_BT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mouse_finished, mouse_reset)
};


// TAP DANCE ENDS

void trackball_set_rgbw(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
    uint8_t data[] = {0x00, red, green, blue, white};
    i2c_transmit(TRACKBALL_WRITE, data, sizeof(data), I2C_TIMEOUT);
}

int16_t mouse_offset(uint8_t positive, uint8_t negative, int16_t scale) {
    int16_t offset    = (int16_t)positive - (int16_t)negative;
    int16_t magnitude = (int16_t)(scale * offset * offset * precisionSpeed);
    return offset < 0 ? -magnitude : magnitude;
}

void update_member(int8_t* member, int16_t* offset) {
    if (*offset > 127) {
        *member = 127;
        *offset -= 127;
    } else if (*offset < -127) {
        *member = -127;
        *offset += 127;
    } else {
        *member = *offset;
        *offset = 0;
    }
}

// enabling left and right tab swipe action
void macro_mouse(int16_t* xoffset, int16_t* yoffset) {
    if (*xoffset > 127 && mouse_bt1_registered) {
        register_code(KC_LCTL); register_code(KC_TAB);
        unregister_code(KC_LCTL); unregister_code(KC_TAB);
        *xoffset = 0;
    } else if (*xoffset < -127 && mouse_bt1_registered) {
        register_code(KC_LCTL); register_code(KC_LSFT); register_code(KC_TAB);
        unregister_code(KC_LCTL); unregister_code(KC_LSFT); unregister_code(KC_TAB);
        *xoffset = 0;
    } else if (*yoffset > 127 && mouse_bt1_registered) {
        register_code(KC_LALT); register_code(KC_LEFT);
        unregister_code(KC_LALT); unregister_code(KC_LEFT);
        *yoffset = 0;
    } else if (*yoffset < -200 && mouse_bt1_registered) {
        register_code(KC_LCTL); register_code(KC_W);
        unregister_code(KC_LCTL); unregister_code(KC_W);
        *yoffset = 0;
    }
}

__attribute__((weak)) void trackball_check_click(bool pressed, report_mouse_t* mouse) {
    if (pressed) {
        mouse->buttons |= MOUSE_BTN1;
    } else {
        mouse->buttons &= ~MOUSE_BTN1;
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (true) {
        xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    }


    if (!process_record_user(keycode, record)) { return false; }

/* If Mousekeys is disabled, then use handle the mouse button
 * keycodes.  This makes things simpler, and allows usage of
 * the keycodes in a consistent manner.  But only do this if
 * Mousekeys is not enable, so it's not handled twice.
 */
#ifndef MOUSEKEY_ENABLE
    if (IS_MOUSEKEY_BUTTON(keycode)) {
        report_mouse_t currentReport = pointing_device_get_report();
        if (record->event.pressed) {
            currentReport.buttons |= 1 << (keycode - KC_MS_BTN1);
        } else {
            currentReport.buttons &= ~(1 << (keycode - KC_MS_BTN1));
        }
        pointing_device_set_report(currentReport);
        pointing_device_send();
    }
#endif

    return true;
}

void trackball_register_button(bool pressed, enum mouse_buttons button) {
    report_mouse_t currentReport = pointing_device_get_report();
    if (pressed) {
        currentReport.buttons |= button;
    } else {
        currentReport.buttons &= ~button;
    }
    pointing_device_set_report(currentReport);
}

float trackball_get_precision(void) { return precisionSpeed; }
void  trackball_set_precision(float precision) { precisionSpeed = precision; }
bool  trackball_is_scrolling(void) { return scrolling; }
void  trackball_set_scrolling(bool scroll) { scrolling = scroll; }


__attribute__((weak)) void pointing_device_init(void) { trackball_set_rgbw(0x80, 0x00, 0x00, 0x00); }

void pointing_device_task(void) {
    static bool     debounce;
    static bool     bt1_debounce;
    static uint16_t debounce_timer;
    static uint16_t bt1_timer;
    uint8_t         state[5] = {};
    if (timer_elapsed(i2c_timeout_timer) > I2C_WAITCHECK) {
        if (i2c_readReg(TRACKBALL_WRITE, 0x04, state, 5, I2C_TIMEOUT) == I2C_STATUS_SUCCESS) {
            if (!state[4] && !debounce) {
                if (scrolling) {
#ifdef PIMORONI_TRACKBALL_INVERT_X
                    h_offset += mouse_offset(state[2], state[3], 1);
#else
                    h_offset -= mouse_offset(state[2], state[3], 1);
#endif
#ifdef PIMORONI_TRACKBALL_INVERT_Y
                    v_offset += mouse_offset(state[1], state[0], 1);
#else
                    v_offset -= mouse_offset(state[1], state[0], 1);
#endif
                } else {
#ifdef PIMORONI_TRACKBALL_INVERT_X
                    x_offset -= mouse_offset(state[2], state[3], 5);
#else
                    x_offset += mouse_offset(state[2], state[3], 5);
#endif
#ifdef PIMORONI_TRACKBALL_INVERT_Y
                    y_offset -= mouse_offset(state[1], state[0], 5);
#else
                    y_offset += mouse_offset(state[1], state[0], 5);
#endif
                }

                if(!bt1_debounce) {
                    macro_mouse(&x_offset, &y_offset);
                    bt1_debounce = true;
                    bt1_timer = timer_read();
                }
            } else {
                if (state[4]) {
                    debounce       = true;
                    debounce_timer = timer_read();
                }
            }
        } else {
            i2c_timeout_timer = timer_read();
        }
    }

    if (timer_elapsed(debounce_timer) > MOUSE_DEBOUNCE) debounce = false;

    if (timer_elapsed(bt1_timer) > BT1_DEBOUNCE) bt1_debounce = false;


    report_mouse_t mouse = pointing_device_get_report();
    trackball_check_click(state[4] & (1 << 7), &mouse);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            trackball_set_rgbw(0,0,0,80);
            break;
        case _RAISE:
            trackball_set_rgbw(0,153,95,0);
            break;
        case _LMISC:
            trackball_set_rgbw(153,113,0,0);
            break;
        case _LOWER:
            trackball_set_rgbw(153,0,153,0);
            break;
        case _ADJUST:
            trackball_set_rgbw(255,0,0,0);
            break;
        default:
            trackball_set_rgbw(0,153,95,0);
    }


    if (layer_state_is(_LOWER)) {
        trackball_set_scrolling(true);
    } else {
        trackball_set_scrolling(false);
    }

    if(!mouse_bt1_registered) {
#ifndef PIMORONI_TRACKBALL_ROTATE
        update_member(&mouse.x, &x_offset);
        update_member(&mouse.y, &y_offset);
        update_member(&mouse.h, &h_offset);
        update_member(&mouse.v, &v_offset);
#else
        update_member(&mouse.x, &y_offset);
        update_member(&mouse.y, &x_offset);
        update_member(&mouse.h, &v_offset);
        update_member(&mouse.v, &h_offset);
#endif
        pointing_device_set_report(mouse);
        pointing_device_send();
    }
}
