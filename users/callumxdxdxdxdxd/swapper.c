#include "swapper.h"

/*
 * @brief Cập nhật trạng thái swapper (chuyển đổi cửa sổ/ngôn ngữ)
 * 
 * @param active Con trỏ đến biến trạng thái swapper
 * @param cmdish Phím modifier (ví dụ: KC_LGUI cho Cmd)
 * @param tabish Phím hành động (ví dụ: KC_TAB)
 * @param trigger Keycode custom kích hoạt swapper
 * @param keycode Keycode của phím đang xử lý
 * @param record Bản ghi sự kiện phím
 * 
 * Hàm này xử lý:
 * - Cơ chế giữ phím modifier khi swapper active
 * - Tự động hủy khi phím khác được nhấn
 * - Phù hợp cho cả Window switcher và Language switcher
 */
void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        // Xử lý sự kiện của chính phím trigger
        if (record->event.pressed) {
            // Khi nhấn phím trigger
            if (!*active) {
                // Nếu swapper chưa active
                *active = true;          // Đánh dấu active
                register_code(cmdish);   // Nhấn phím modifier (Cmd/Ctrl)
            }
            register_code(tabish);       // Nhấn phím hành động (Tab/Space)
        } else {
            // Khi thả phím trigger
            unregister_code(tabish);     // Thả phím hành động ngay lập tức
            // Giữ nguyên modifier (cmdish) cho đến khi phím khác được nhấn
        }
    } else if (*active) {
        // Khi phím khác được nhấn và swapper đang active
        unregister_code(cmdish);  // Thả phím modifier
        *active = false;          // Đánh dấu không còn active
    }
}