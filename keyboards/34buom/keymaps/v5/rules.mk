USER_NAME := uv5
# Cấu hình OLED cho 0.91in
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
OLED_TRANSPORT = i2c
TRI_LAYER_ENABLE = yes      # Ba lớp cùng lúc

# additional source file
SRC += features/oled.c
SRC += features/override_keys.c