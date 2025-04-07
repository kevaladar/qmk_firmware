# Enable common features
COMBO_ENABLE 		   = yes
MOUSEKEY_ENABLE        = yes
CAPS_WORD_ENABLE       = yes
# LTO_ENABLE             = yes

# Disable unused features
MAGIC_ENABLE	       = yes
CONSOLE_ENABLE         = no
BOOTMAGIC_ENABLE       = no
UNICODE_ENABLE         = no
SPACE_CADET_ENABLE     = no
GRAVE_ESC_ENABLE       = no
AUDIO_ENABLE 	       = no

# Cấu hình OLED cho 0.91in
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
OLED_TRANSPORT = i2c


VPATH += keyboards/gboards/ # using gboards combo code: see https://combos.gboards.ca/
INTROSPECTION_KEYMAP_C = v6.c

# Add custom features
SRC += features/mod_lock.c
SRC += features/nshot_mod.c
SRC += features/smart_layer.c
SRC += features/override_keys.c
SRC += features/oled.c
SRC += features/swapper.c
# Add configuration for built-in features
ifeq ($(strip $(COMBOS_ENABLE)), yes)
	SRC += combos.c
endif
