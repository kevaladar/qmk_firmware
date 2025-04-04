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

VPATH += keyboards/gboards/ # using gboards combo code: see https://combos.gboards.ca/
INTROSPECTION_KEYMAP_C = keval.c

# Cấu hình OLED cho 0.91in
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
OLED_TRANSPORT = i2c

# Các tính năng cơ bản
REPEAT_KEY_ENABLE = yes     # Phím lặp
TRI_LAYER_ENABLE = yes      # Ba lớp cùng lúc
ONE_SHOT_ENABLE = yes

# Tắt các tính năng không dùng
ifndef GRAVE_ESC_ENABLE
    GRAVE_ESC_ENABLE = no
endif
ifndef MAGIC_ENABLE
    MAGIC_ENABLE = yes
endif
ifndef SPACE_CADET_ENABLE
    SPACE_CADET_ENABLE = no
endif

# Add custom features
SRC += features/mod_lock.c
SRC += features/nshot_mod.c
SRC += features/smart_layer.c
SRC += features/override_keys.c
SRC += features/swapper.c
# Add configuration for built-in features
ifeq ($(strip $(COMBOS_ENABLE)), yes)
	SRC += combos.c
endif