
OLED_DRIVER_ENABLE = no     # OLED display
MOUSEKEY_ENABLE    = yes   # Mouse keys
THUMBSTICK_ENABLE  = yes  # Enables analog thumbstick code

ifeq ($(strip $(THUMBSTICK_ENABLE)), yes)
    POINTING_DEVICE_ENABLE = yes
    OPT_DEFS += -DTHUMBSTICK_ENABLE
	SRC += analog.c
	SRC += thumbstick.c
endif
