
#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"


enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _MEDIA,
  _LMISC,
  _RPG,
  _ADJUST
};


// Control GUI modifier
#define CGUI(kc) (QK_LGUI | QK_LCTL | (kc))
// modifiers QWERTY
#define LGUIA     LGUI_T(KC_A)
#define LALTF     LALT_T(KC_F)
#define LCTLD     LCTL_T(KC_D)
#define LSHFS     LSFT_T(KC_S)
#define RGUICOL   RGUI_T(KC_SCLN)
#define RALTJ     RALT_T(KC_J)
#define RCTLK     RCTL_T(KC_K)
#define RSHFL     RSFT_T(KC_L)
#define RSHFENT   RSFT_T(KC_ENT)
// layer taps
#define SPCLW     LT(_LOWER, KC_SPACE)
#define RETRS     LT(_RAISE, KC_ENT)
#define TABLM     LT(_LMISC, KC_TAB)
#define LMLW      LM(_LOWER, MOD_LSFT)
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
#define COPY      RCTL(KC_C)
#define CUT       RCTL(KC_X)
#define PASTE     RCTL(KC_V)
#define LTAB      RCS(KC_TAB)
#define RTAB      RCTL(KC_TAB)
#define WBACK     LALT(KC_LEFT)
#define WFORWARD  LALT(KC_RIGHT)
#define BWORD     LCTL(KC_LEFT)
#define NWORD     LCTL(KC_RIGHT)
#define RMTAB     LCTL(KC_W)
#define RESTAB    RCS(KC_T)
#define CONEMU    LCTL(KC_1)
#define NEWTAB    LCTL(KC_T)
#define TERMB     LALT(KC_B)
#define TERMF     LALT(KC_F)
#define TERMDEL   LALT(KC_D)
#define CONMENU        LALT(KC_SPC)
#define CLEANTERM      LCTL(KC_U)
#define CLEANAFTER     LALT(KC_D)
#define TERMPASTE      RCS(KC_V)



#if defined _10

#define QWERTY_1    KC_Q,  KC_W,   KC_E,   KC_R,   KC_T,  KC_Y,  KC_U,  KC_I,    KC_O,   KC_P
#define QWERTY_2    LGUIA, LSHFS,  LCTLD,  LALTF,  KC_G,  KC_H,  RALTJ, RCTLK,   RSHFL,  RGUICOL
#define QWERTY_3    KC_Z,  KC_X,   KC_C,   KC_V,   KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLSH
#define I3_1        DMENU,   BWORD,   _______, NWORD,    _______
#define I3_2        WINTOG,  FCSL,    FCSD,    FCSU,     FCSR
#define I3_3        QUIT,    WORK1,   WORK2,   WORK3,    WORK4
#define NUM_1       KC_LBRC, KC_7,    KC_8,    KC_9,     KC_RBRC
#define NUM_2       KC_QUOT, KC_4,    KC_5,    KC_6,     KC_EQL
#define NUM_3       KC_MINUS,KC_1,    KC_2,    KC_3,     KC_BSLASH
#define RASSIT_1    KC_PGUP, KC_HOME, KC_CUT,  KC_COPY,  KC_PSTE
#define RASSIT_2    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  KC_BSLASH
#define RASSIT_3    KC_PGDN, KC_END,  KC_DEL,   _______, KC_GRAVE
#define FUCT_1      KC_ESC,  KC_F1,   KC_F2,   KC_F3,    KC_F4
#define FUCT_2      _______, KC_F5,   KC_F6,   KC_F7,    KC_F8
#define FUCT_3      _______, KC_F9,   KC_F10,  KC_F11,   KC_F12
#define RPG_1       _______, _______, _______, _______,  _______,        KC_LCTL,  KC_X,     KC_UP,    KC_S,    KC_RSFT
#define RPG_2       _______, _______, _______, _______,  _______,        KC_SPC,   KC_LEFT,  KC_DOWN,  KC_RGHT,  _______
#define RPG_3       _______, _______, _______, _______,  _______,        KC_ENT,   _______,  _______,  _______,  RPG
#define MEDIA_1     _______, _______, _______, _______,  _______,        MPVDEL,   KC_F,    KC_I,     KC_SPC,   KC_Q
#define MEDIA_2     _______, _______, _______, _______,  _______,        MPVRATIO, KC_9,    KC_UP,    KC_0,     KC_DEL
#define MEDIA_3     _______, _______, _______, _______,  _______,        KC_HOME,  KC_LEFT, KC_DOWN,  KC_RIGHT, KC_END
#define ADJ_1       XXXXXXX, MOVE1,   MOVE2,   MOVE3,    MOVE4,          RPG,      MEDIA,   XXXXXXX,  XXXXXXX,  XXXXXXX
#define ADJ_2       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,        BWORD,    XXXXXXX, XXXXXXX,  NWORD,    XXXXXXX
#define ADJ_3       RESET,   XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,        XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX
#define LMISC_1     RESTAB,  LTAB,    RMTAB,   RTAB,    NEWTAB,          KC_LCBR,  KC_AMPR, KC_ASTR,  KC_LPRN,  KC_RCBR
#define LMISC_2     UNDO,    CUT,     COPY,    PASTE,   REDO,            KC_DQT,   KC_DLR,  KC_PERC,  KC_CIRC,  KC_PLUS
#define LMISC_3     _______, TERMB,   TERMDEL, TERMF,   CONEMU,          KC_UNDS,  KC_EXLM, KC_AT,    KC_HASH,  KC_PIPE
#elif defined _12

#define QWERTY_1    CTLTAB,   KC_Q,  KC_W,   KC_E,   KC_R,   KC_T,  KC_Y,  KC_U,  KC_I,    KC_O,   KC_P,    KC_QUOT
#define QWERTY_2    GUIDEL,   LGUIA, LSHFS,  LCTLD,  LALTF,  KC_G,  KC_H,  RALTJ, RCTLK,   RSHFL,  RGUICOL, KC_MINS
#define QWERTY_3    KC_LSFT,  KC_Z,  KC_X,   KC_C,   KC_V,   KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLSH, RSHFENT
#define I3_1        DMENU,    _______, _______, _______,  _______, _______
#define I3_2        WINTOG,   FCSL,    FCSD,     FCSU,    FCSR, _______
#define I3_3        QUIT,     WORK1,   WORK2,   WORK3,   WORK4, _______
#define NUM_1       KC_LBRC,  KC_7,  KC_8,  KC_9,  KC_RBRC, _______
#define NUM_2       KC_QUOT,  KC_4,  KC_5,  KC_6,  KC_EQL, _______
#define NUM_3       KC_MINUS, KC_1,  KC_2,  KC_3,  KC_BSLASH, _______
#define RASSIT_1    KC_PGUP,  KC_HOME,  KC_CUT,   KC_COPY,  KC_PSTE, _______
#define RASSIT_2    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_BSLASH, _______
#define RASSIT_3    KC_PGDN,  KC_END,   KC_DEL,   _______,  KC_GRAVE, _______
#define FUCT_1      _______,  KC_ESC, KC_F1,   KC_F2,   KC_F3,   KC_F4
#define FUCT_2      _______, _______, KC_F5,   KC_F6,   KC_F7,   KC_F8
#define FUCT_3      _______, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12
#define RPG_1       _______, _______, _______, _______,  _______,        KC_LCTL,  KC_X,     KC_UP,    KC_S,     KC_RSFT
#define RPG_2       _______, _______, _______, _______,  _______,        KC_SPC,   KC_LEFT,  KC_DOWN,  KC_RGHT,  _______
#define RPG_3       _______, _______, _______, _______,  _______,        KC_RET,   _______,  _______,  _______,  RPG
#define MEDIA_1     _______, _______, _______, _______,  _______,        MPVDEL,     KC_F,  KC_I,    KC_SPC,    KC_Q
#define MEDIA_2     _______, _______, _______, _______,  _______,        MPVRATIO,   KC_9,     KC_UP,   KC_0,      KC_DEL
#define MEDIA_3     _______, _______, _______, _______,  _______,        KC_HOME,    KC_LEFT,  KC_DOWN, KC_RIGHT,  KC_END
#define ADJ_1       XXXXXXX, MOVE1,   MOVE2,   MOVE3,    MOVE4,          RPG,      MEDIA,   XXXXXXX, XXXXXXX, XXXXXXX
#define ADJ_2       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ADJ_3       RESET,   XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define LMISC_1     RESTAB,  LTAB,    RMTAB,   RTAB,    NEWTAB,          KC_LCBR,  KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR
#define LMISC_2     UNDO,    CUT,     COPY,    PASTE,   REDO,            KC_DQT,   KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS
#define LMISC_3     _______, TERMB,   TERMDEL, TERMF,   CONEMU,          KC_DQT,  KC_EXLM, KC_AT,   KC_HASH, KC_PIPE


#endif

#if defined THUMB_6

#define QWERTY_T    LMLW,    TABLM,    SPCLW, RETRS, KC_BSPC,  KC_GESC
#define NUM_T       _______, KC_DOT,   KC_0
#define RPG_T       KC_ENT,  _______,  RPG
#define MEDIA_T     _______, KC_LT,    MEDIA
#define TRANS_S     _______, _______,  _______
#define TRANS_W     _______, _______,  _______,  _______, _______,  _______

#elif defined THUMB_4

#define QWERTY_T    TABLM,   SPCLW, RETRS, KC_BSPC
#define NUM_T       KC_DOT,  KC_0
#define RPG_T       KC_Z,  KC_X
#define MEDIA_T     _______, MEDIA
#define LMISC_T     _______, KC_RPRN
#define TRANS_S     _______, _______
#define TRANS_W     _______, _______,  _______, _______

#endif

#endif
