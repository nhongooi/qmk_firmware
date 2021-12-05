

//#define MASTER_RIGHT
#define THUMB_6
#define _10
#undef TAPPING_TERM
#define TAPPING_TERM 180

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

#ifdef POINTING_DEVICE_ENABLE
#define TRACKBALL_RIGHT

#ifdef TRACKBALL_RIGHT
    #define PIMORONI_TRACKBALL_INVERT_X
    #define PIMORONI_TRACKBALL_INVERT_Y
#endif

#endif

#ifdef HAPTIC_ENABLE
#define FB_ERM_LRA 1
#define FB_BRAKEFACTOR 3 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#define FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */
#define RATED_VOLTAGE 2
#define V_PEAK 2.8
#define V_RMS 2.0
#define F_LRA 205
#endif
