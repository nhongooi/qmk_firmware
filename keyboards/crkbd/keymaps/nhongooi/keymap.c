#include QMK_KEYBOARD_H
#ifdef POINTING_DEVICE_ENABLE
#include "pointing_device.h"
#endif

#ifdef PIMORONI_TRACKBALL_ENABLE
#include "pimoroni_trackball.h"
#endif

#include "config.h"
#include "nhongooi.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_fifi_wrapper(
    QWERTY_1,
    QWERTY_2,
    QWERTY_3,
    QWERTY_T
  ),
  [_LOWER] = LAYOUT_fifi_wrapper(
    I3_1,    NUM_1,
    I3_2,    NUM_2,
    I3_3,    NUM_3,
    TRANS_S, NUM_T
  ),
  [_RAISE] = LAYOUT_fifi_wrapper(
    FUCT_1,  RASSIT_1,
    FUCT_2,  RASSIT_2,
    FUCT_3,  RASSIT_3,
    TRANS_W
  ),
  [_LMISC] = LAYOUT_fifi_wrapper(
    LMISC_1,
    LMISC_2,
    LMISC_3,
    TRANS_W

  ),
  [_RPG] = LAYOUT_fifi_wrapper(
    RPG_1,
    RPG_2,
    RPG_3,
    TRANS_S, RPG_T
  ),
  [_MEDIA] = LAYOUT_fifi_wrapper(
    MEDIA_1,
    MEDIA_2,
    MEDIA_3,
    TRANS_S, MEDIA_T
  ),
  [_ADJUST] = LAYOUT_fifi_wrapper(
    ADJ_1,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,        KC_ACL0,  KC_ACL1, KC_ACL2, XXXXXXX, XXXXXXX,
    ADJ_3,
    TRANS_W
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


#ifdef PIMORONI_TRACKBALL_ENABLE
void pointing_device_task() {
  report_mouse_t mouse_report = pointing_device_get_report();

  if (is_keyboard_master()) {
      process_mouse(&mouse_report);
  }

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
          trackball_set_rgbw(0,0,0,0);
  }


  if (layer_state_is(_RAISE)) {
      trackball_set_scrolling(true);
  } else {
      trackball_set_scrolling(false);
  }

  pointing_device_set_report(mouse_report);
  pointing_device_send();
}
#endif

// https://gist.github.com/trd86/03aaa969253ae8c64252d1ca17068b9a
//  trd86/mouse-tap-sample.c
#ifdef TAP_DANCE_ENABLE
#define ACTION_TAP_DANCE_MOUSE_LAYER(kc1, layer) \
  { .fn = {mousekey_tap, mousekey_finished, mousekey_reset}, .user_data = (void *)&((qk_tap_dance_pair_t){kc1, layer}),  }

// Tap Dance declarations
enum {
    TD_MB_CMD,
    TD_MB_L1,
    TD_RMB_L2
};

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD,
    IGNORE_TAP,
    SHIFTED_ON_INITAL
};

static tap mtap_state = {
  .is_press_action = true,
  .state = 0,
  .layer = -1
};

void mousekey_tap (qk_tap_dance_state_t *state, void *user_data);
void mousekey_finished (qk_tap_dance_state_t *state, void *user_data);
void mousekey_reset (qk_tap_dance_state_t *state, void *user_data);

// https://gist.github.com/trd86/03aaa969253ae8c64252d1ca17068b9a
//  trd86/mouse-tap-sample.c

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_MB_CMD] = { .fn = {mousekey_tap, mousekey_finished, mousekey_reset}, .user_data = NULL },
  [TD_MB_L1] = ACTION_TAP_DANCE_MOUSE_LAYER(KC_MS_BTN1, 1),
  [TD_RMB_L2] = ACTION_TAP_DANCE_MOUSE_LAYER(KC_MS_BTN2, 2)
}

void mousekey_tap (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    mtap_state.layer = -1;
  }

  if (user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    mtap_state.layer = pair->kc2;
  }
}

void mousekey_finished (qk_tap_dance_state_t *state, void *user_data) {
  uint16_t mouse_key = KC_MS_BTN1;
  int layer = -1;

  if (user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    mouse_key = pair->kc1;
    layer = pair->kc2;
  }

  uint8_t st = SINGLE_TAP;

  if (state->count == 1) {
      if (!state->pressed) {
        st = SINGLE_TAP;
      } else {
        st = SINGLE_HOLD;
      }
  } else if (state->count == 2) {
      if (state->pressed) st = DOUBLE_HOLD; else st = DOUBLE_TAP;
  } if (state->count == 3) {
      if (state->interrupted || !state->pressed) st = TRIPLE_TAP;
      else st = DOUBLE_SINGLE_TAP;
  }

  mtap_state.state = st;
  switch (mtap_state.state) {
    case SINGLE_HOLD: if (layer > -1) layer_on(layer); else register_code(KC_LGUI); break;
    case SINGLE_TAP: if (get_oneshot_mods() & MOD_MASK_GUI) register_code(KC_LGUI); tap_key(mouse_key); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_LGUI); break;
    case TRIPLE_TAP:
    case DOUBLE_HOLD: if (get_oneshot_mods() & MOD_MASK_GUI) { clear_oneshot_mods(); unregister_code(KC_LGUI); register_code(KC_LALT); }; register_code(mouse_key); break;
    case DOUBLE_TAP: tap_key(mouse_key); tap_key(mouse_key); break;
  }
}

void mousekey_reset (qk_tap_dance_state_t *state, void *user_data) {
  uint16_t mouse_key = KC_MS_BTN1;
  int layer = -1;

  if (user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    mouse_key = pair->kc1;
    layer = pair->kc2;
  }

  switch (mtap_state.state) {
    case SINGLE_HOLD: if (layer > -1) layer_off(layer); else unregister_code(KC_LGUI); break;
    case DOUBLE_SINGLE_TAP: unregister_code(KC_LGUI); break;
    case DOUBLE_TAP: clear_oneshot_mods(); break;
    case SINGLE_TAP: clear_oneshot_mods();
    case DOUBLE_HOLD: unregister_code(KC_LALT); unregister_code(mouse_key); clear_oneshot_mods(); break;
  }
  mtap_state.state = 0;
}
#endif
