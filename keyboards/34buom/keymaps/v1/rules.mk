# comment line 9-11 for SPACE SAVERS WHEN NOT DEBUGGING	
USER_NAME = uv1
# Sweep But Actually Hypergarlic
RGBLIGHT_ENABLE 		= no    # Enable keyboard RGB underglow

BOOTLOADER = rp2040

# Enable debugging
CONSOLE_ENABLE = yes
DEBUG_ENABLE = yes

# Cấu hình OLED cho 0.91in
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
OLED_TRANSPORT = i2c

# additional source file
SRC += features/oled.c
SRC += features/override_keys.c