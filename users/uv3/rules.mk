
# Enable common features
COMBO_ENABLE 		   = yes
CAPS_WORD_ENABLE       = yes
# LTO_ENABLE             = yes
OLED_ENABLE            = yes
REPEAT_KEY_ENABLE = yes     # Phím lặp
TRI_LAYER_ENABLE = yes      # Ba lớp cùng lúc
ONE_SHOT_ENABLE = yes


# Cấu hình OLED cho 0.91in
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
OLED_TRANSPORT = i2c


# Disable unused features
UNICODE_ENABLE         = no
SPACE_CADET_ENABLE     = no
GRAVE_ESC_ENABLE       = no
AUDIO_ENABLE 	       = no

ifndef GRAVE_ESC_ENABLE
    GRAVE_ESC_ENABLE = no
endif
ifndef MAGIC_ENABLE
    MAGIC_ENABLE = yes
endif
ifndef SPACE_CADET_ENABLE
    SPACE_CADET_ENABLE = no
endif
