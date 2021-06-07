#define MASTER_RIGHT
#define THUMB_6
#define _10
#define TRACKBALL_RIGHT

#ifdef TRACKBALL_LEFT
    #define PIMORONI_TRACKBALL_INVERT_X
    #define PIMORONI_TRACKBALL_INVERT_Y
#endif

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
