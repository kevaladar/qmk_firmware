USER_NAME := keval
# Cấu hình OLED cho SH1107
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
OLED_TRANSPORT = i2c

# LTO_ENABLE = yes          # Giảm kích thước firmware
REPEAT_KEY_ENABLE = yes     # Phím lặp
CAPS_WORD_ENABLE = yes      # Caps cho từng từ
TRI_LAYER_ENABLE = yes      # Ba lớp cùng lúc
COMBO_ENABLE = yes          # Tổ hợp phím
WPM_ENABLE = yes            # Enable word per minute counter


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