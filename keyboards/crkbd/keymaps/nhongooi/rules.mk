MOUSEKEY_ENABLE = yes       # Mouse keys
TAP_DANCE_ENABLE = yes
POINTING_DEVICE_ENABLE := yes
OPT_DEFS += -DPIMORONI_TRACKBALL_ENABLE
SRC += pimoroni_trackball.c
QUANTUM_LIB_SRC += i2c_master.c
