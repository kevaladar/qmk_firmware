# Disable RGB lighting to save space and processing power
RGBLIGHT_ENABLE = no  # Tắt đèn RGB để tiết kiệm tài nguyên firmware

# Add custom source files to the build
SRC += callum.c    # File keymap chính chứa bố cục phím và xử lý sự kiện
SRC += oneshot.c   # Triển khai oneshot modifiers không dùng timer
SRC += swapper.c   # Chức năng chuyển đổi cửa sổ/ngôn ngữ