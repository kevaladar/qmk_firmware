
# Cấu hình OLED cho SH1107
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
OLED_TRANSPORT = i2c

# Các tính năng cơ bản
# NKRO_ENABLE = yes           # Nhiều phím cùng lúc
# # LTO_ENABLE = yes            # Giảm kích thước firmware
# REPEAT_KEY_ENABLE = yes     # Phím lặp
# CAPS_WORD_ENABLE = yes      # Caps cho từng từ
# # DEFERRED_EXEC_ENABLE = yes  # Xử lý sự kiện trì hoãn
# TRI_LAYER_ENABLE = yes      # Ba lớp cùng lúc
# COMBO_ENABLE = yes          # Tổ hợp phím
# # DEBOUNCE_TYPE = asym_eager_defer_pk  # Loại bỏ nhiễu phím

# Add custom features
SRC += features/mod_lock.c
SRC += features/nshot_mod.c
SRC += features/smart_layer.c
SRC += features/override_keys.c

# Add configuration for built-in features
ifeq ($(strip $(COMBOS_ENABLE)), yes)
	SRC += combos.c
endif