#pragma once

#include <quantum.h>
#include "color.h"

#ifndef TRACKBALL_ADDRESS
#    define TRACKBALL_ADDRESS 0x0A
#endif

#ifndef TRACKBALL_ANGLE_OFFSET
#   define TRACKBALL_ANGLE_OFFSET 0
#endif

#define TRACKBALL_WRITE ((TRACKBALL_ADDRESS << 1) | I2C_WRITE)
#define TRACKBALL_READ  ((TRACKBALL_ADDRESS << 1) | I2C_READ)

#define TB_I2C_TIMEOUT 100

#define REG_RED 0x00
#define REG_GREEN 0x01
#define REG_BLUE 0x02
#define REG_WHITE 0x03

#define REG_LEFT 0x04

#define REG_INTERRUPT_PIN 0xF9
#define MASK_INTERRUPT_TRIGGERED 0x01
#define MASK_INTERRUPT_PIN_ENABLE 0x02

#define REG_CTRL 0xFE
#define MSK_CTRL_SLEEP 0b00000001
#define MSK_CTRL_RESET 0b00000010
#define MSK_CTRL_FREAD 0b00000100
#define MSK_CTRL_FWRITE 0b00001000


typedef struct {
    int16_t x;
    int16_t y;
    bool button_down;
    bool button_triggered;
#ifndef TRACKBALL_NO_MATH
    double vector_length;
    double angle_rad;
    int8_t raw_x;
    int8_t raw_y;
#endif
} trackball_state_t;

void trackball_init(void);
bool trackball_get_interrupt(void);
void trackball_set_rgbw(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
void trackball_read_state(uint8_t* data, uint16_t size_of_data);
void trackball_sleep(void);
void trackball_set_brightness(uint8_t brightness);
void trackball_set_hsv(uint8_t hue, uint8_t sat, uint8_t brightness);
void trackball_set_scrolling (bool scroll);

trackball_state_t trackball_get_state(void);

void pointing_device_init(void);
void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y, int16_t h, int16_t v);
void update_member(int8_t* member, int16_t* offset);
bool has_report_changed(report_mouse_t new, report_mouse_t old);
void process_mouse(report_mouse_t* mouse);
void pointing_device_task(void);
void pointing_device_send(void);


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
#endif
