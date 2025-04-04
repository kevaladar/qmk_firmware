#pragma once

#include "quantum.h"


#ifdef OLED_ENABLE

// Hàm khởi tạo OLED (xoay màn hình nếu cần)
oled_rotation_t oled_init_user(oled_rotation_t rotation);

// Hàm hiển thị thông tin OLED (capslock, layer, modifier)
bool oled_task_user(void);

#endif
