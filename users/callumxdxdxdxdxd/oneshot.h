#pragma once

#include QMK_KEYBOARD_H

/*
 @file oneshot.h
 @brief Header file for oneshot modifier implementation without timers
 
 This provides a timer-free implementation of oneshot modifiers that:
 - Can be stacked (multiple oneshot mods active together)
 - Can be carried across layers
 - Provides more control than QMK's built-in oneshot
 */

/*
 @enum oneshot_state
 @brief Các trạng thái của một oneshot modifier
 
 Cơ chế oneshot hoạt động như một state machine với 4 trạng thái:
*/

// Represents the four states a oneshot key can be in
typedef enum {
    os_up_unqueued, //< Mod không active và không chờ hủy
    os_up_queued,   //< Mod đã được thả nhưng đang chờ hủy sau phím tiếp theo
    os_down_unused, //< Mod đang active nhưng chưa được sử dụng
    os_down_used,   //< Mod đang active và đã được sử dụng
} oneshot_state;


/*
 * @brief Hàm chính xử lý oneshot modifier
 * 
 * @param state Con trỏ đến biến trạng thái oneshot
 * @param mod Keycode modifier thực tế (ví dụ: KC_LSFT)
 * @param trigger Keycode custom kích hoạt oneshot (ví dụ: OS_SHFT)
 * @param keycode Keycode của phím đang xử lý
 * @param record Bản ghi sự kiện phím
 * 
 * Hàm này cần được gọi từ process_record_user() để hoạt động chính xác
 */

// Custom oneshot mod implementation that doesn't rely on timers. If a mod is
// used while it is held it will be unregistered on keyup as normal, otherwise
// it will be queued and only released after the next non-mod keyup.
void update_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
);

/*
 * @brief Kiểm tra phím hủy oneshot
 * @param keycode Keycode cần kiểm tra
 * @return true Nếu phím này nên hủy oneshot mod
 * 
 * Ví dụ: Các phím chuyển layer thường nên hủy oneshot
 * 
 * Hàm này phải được implement bởi người dùng trong keymap.c
 */

// To be implemented by the consumer. Defines keys to cancel oneshot mods.
bool is_oneshot_cancel_key(uint16_t keycode);

// To be implemented by the consumer. Defines keys to ignore when determining
// whether a oneshot mod has been used. Setting this to modifiers and layer
// change keys allows stacking multiple oneshot modifiers, and carrying them
// between layers.

/*
 * @brief Kiểm tra phím bỏ qua oneshot
 * @param keycode Keycode cần kiểm tra
 * @return true Nếu phím này không nên kích hoạt release oneshot
 * 
 * Ví dụ: Các phím modifier khác hoặc phím layer để cho phép
 * kết hợp nhiều oneshot mod hoặc giữ mod khi chuyển layer
 * 
 * Hàm này phải được implement bởi người dùng trong keymap.c
 */

bool is_oneshot_ignored_key(uint16_t keycode);

