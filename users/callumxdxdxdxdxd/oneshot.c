#include "oneshot.h"

/**
 * @brief Cập nhật trạng thái oneshot modifier
 * 
 * @param state Con trỏ đến trạng thái hiện tại của oneshot mod
 * @param mod Keycode của mod được áp dụng (ví dụ: KC_LSFT)
 * @param trigger Keycode custom kích hoạt oneshot (ví dụ: OS_SHFT)
 * @param keycode Keycode của phím đang được xử lý
 * @param record Bản ghi sự kiện phím
 * 
 * Hàm này xử lý toàn bộ logic oneshot modifier:
 * - Kích hoạt modifier khi nhấn phím trigger
 * - Tự động hủy modifier khi nhấn phím khác
 * - Quản lý các trạng thái khác nhau của oneshot mod
 */
void update_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    // Xử lý sự kiện của chính phím trigger
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Khi nhấn phím trigger
            if (*state == os_up_unqueued) {
                // Nếu mod chưa được kích hoạt, đăng ký mod
                register_code(mod);
            }
            // Chuyển sang trạng thái "đã nhấn nhưng chưa sử dụng"
            *state = os_down_unused;
        } else {
            // Khi thả phím trigger
            switch (*state) {
            case os_down_unused:
                // Nếu mod chưa được sử dụng khi giữ phím trigger
                // Chuyển sang trạng thái "chờ hủy sau khi thả phím tiếp theo"
                *state = os_up_queued;
                break;
                
            case os_down_used:
                // Nếu mod đã được sử dụng khi giữ phím trigger
                // Hủy kích hoạt mod và reset trạng thái
                *state = os_up_unqueued;
                unregister_code(mod);
                break;
                
            default:
                break;
            }
        }
    } else {
        // Xử lý các phím không phải trigger
        if (record->event.pressed) {
            // Khi nhấn phím khác
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
                // Nếu là phím hủy oneshot (như layer key)
                // Ngay lập tức hủy oneshot mod
                *state = os_up_unqueued;
                unregister_code(mod);
            }
        } else {
            // Khi thả phím khác
            if (!is_oneshot_ignored_key(keycode)) {
                // Chỉ xử lý với phím không nằm trong danh sách bỏ qua
                switch (*state) {
                case os_down_unused:
                    // Khi thả phím thường, đánh dấu mod đã được sử dụng
                    *state = os_down_used;
                    break;
                    
                case os_up_queued:
                    // Hủy mod đang chờ sau khi phím được thả
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    break;
                    
                default:
                    break;
                }
            }
        }
    }
}