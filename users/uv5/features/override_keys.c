#include "override_keys.h"
// sau này sửa lại l184 layer_off(5) thành layer_off(_SYM)

/*1. Tổng quan về file

File này định nghĩa các hàm callback (callbacks) được sử dụng trong QMK để "ghi đè" (override) hành vi mặc định của các phím. Các hàm này thường được gọi trong file keymap (thường là keymap.c) thông qua cấu trúc process_record_user để xử lý các sự kiện phím (key events). Mỗi hàm nhận tham số keyrecord_t *record, chứa thông tin về trạng thái phím (nhấn hoặc thả), và một số hàm cũng nhận thêm các tham số như is_shifted (có đang trong trạng thái Shift không), keycode (mã phím), v.v.

Các tính năng chính trong file bao gồm:

    Ghi đè hành vi của phím khi Shift được kích hoạt.
    Xử lý hành vi hold của mod tap (phím vừa là modifier vừa là keycode thông thường).
    Tự động ghép cặp ký tự (autopair) như dấu ngoặc.
    Gửi chuỗi ký tự hoặc thực hiện các hành động phức tạp dựa trên điều kiện.

Bây giờ, mình sẽ giải thích từng hàm một cách chi tiết.*/

/*a. override_shift

Mục đích: Ghi đè hành vi của một phím khi Shift được kích hoạt, thay thế keycode mặc định bằng một keycode khác (shift_override) khi Shift được bật.

Tham số:

    is_shifted: Boolean, true nếu Shift đang được kích hoạt.
    keycode: Keycode mặc định của phím.
    shift_override: Keycode sẽ được sử dụng thay thế khi Shift được bật.
    record: Thông tin sự kiện phím.

Hoạt động:

    Khi phím được nhấn (record->event.pressed là true):
        Nếu is_shifted là true (Shift đang bật), hàm sẽ:
            Lưu trạng thái modifier hiện tại (mod_state).
            Xóa trạng thái Shift (clear_shift).
            Gửi keycode thay thế (shift_override).
            Khôi phục trạng thái modifier ban đầu.
        Nếu is_shifted là false, chỉ gửi keycode mặc định (keycode).
    Khi phím được thả (record->event.pressed là false), hàm hủy cả shift_override và keycode.

Ví dụ sử dụng: Nếu bạn muốn phím "1" trở thành "!" khi Shift được bật, bạn có thể gọi override_shift(true, KC_1, S(KC_1), record).*/
bool override_shift( bool is_shifted,
    uint16_t keycode,
    uint16_t shift_override,
    keyrecord_t *record) {
    if (record->event.pressed) {
        if (is_shifted) {
            uint8_t mod_state = get_mods();
            clear_shift(is_shifted);

            register_code16(shift_override);

            set_mods(mod_state);
        } else {
            register_code16(keycode);
        }
        return false;
    }
    else {
        unregister_code16(shift_override);
        unregister_code16(keycode);
    }

    return true;
}

/*b. override_th_hold

Mục đích: Xử lý hành vi hold của một phím mod tap (phím vừa là modifier vừa là keycode thông thường, ví dụ: phím Shift khi hold và chữ cái khi tap). Hàm này gửi một keycode tùy chỉnh khi phím được hold.

Tham số:

    hold_keycode: Keycode sẽ được gửi khi phím được hold.
    record: Thông tin sự kiện phím.

Hoạt động:

    Nếu phím được hold (không tap, !record->tap.count là true) và được nhấn (record->event.pressed là true), hàm gửi hold_keycode bằng tap_code16.
    Nếu không, hàm trả về true, cho phép QMK xử lý tiếp.

Ví dụ sử dụng: Dùng cho các phím như home row mods, nơi hold gửi một modifier (ví dụ: Ctrl) và tap gửi một ký tự (ví dụ: "a").*/
// Send custom keycode on hold for mod tap
// from https://github.com/filterpaper/qmk_userspace/blob/main/filterpaper.c
bool override_th_hold(uint16_t hold_keycode, keyrecord_t *record) {
    if (!record->tap.count && record->event.pressed) {
        tap_code16(hold_keycode);
        return false;
    }
    return true;
}

/*c. send_alternate_key

Mục đích: Gửi một keycode thay thế (alt_keycode) hoặc keycode mặc định (default_keycode) dựa trên một điều kiện (use_alternate).

Tham số:

    default_keycode: Keycode mặc định.
    alt_keycode: Keycode thay thế.
    use_alternate: Boolean, true để dùng keycode thay thế, false để dùng mặc định.
    record: Thông tin sự kiện phím.

Hoạt động:

    Khi phím được nhấn, nếu use_alternate là true, gửi alt_keycode; nếu không, gửi default_keycode.

Ví dụ sử dụng: Chuyển đổi giữa hai hành vi khác nhau dựa trên trạng thái layer hoặc modifier.*/
bool send_alternate_key(
  uint16_t default_keycode,
  uint16_t alt_keycode,
  bool use_alternate,
  keyrecord_t *record) {
  if (record->event.pressed){
    tap_code16(use_alternate ? alt_keycode : default_keycode);
  }
  return false;
}

/*d. send_autopair (), {}, [], "", <>, ''   

Mục đích: Tự động ghép cặp ký tự, ví dụ: khi nhấn "(", tự động thêm ")" và di chuyển con trỏ về giữa.

Tham số:

    keycode: Keycode của ký tự đầu tiên (ví dụ: KC_LPRN cho "(").
    pair_keycode: Keycode của ký tự ghép cặp (ví dụ: KC_RPRN cho ")").
    record: Thông tin sự kiện phím.

Hoạt động:

    Khi phím được nhấn:
        Lưu và xóa trạng thái modifier (mod_state và clear_shift).
        Gửi cả keycode và pair_keycode (ví dụ: "(" và ")").
        Di chuyển con trỏ về trái một lần (tap_code(KC_LEFT)).
        Khôi phục trạng thái modifier.

Ví dụ sử dụng: Nhấn "(" sẽ tự động tạo "(|)" với con trỏ "|" ở giữa.*/
bool send_autopair(
  uint16_t keycode,
  uint16_t pair_keycode,
  keyrecord_t *record  ) {
    if(record->event.pressed) {
		// clear mods before moving left
		uint8_t mod_state = get_mods();
		clear_shift(true);

      // Tap the base keycode regardless of shift state
      tap_code16(keycode);
      tap_code16(pair_keycode);


		// move left and reset mod state
      tap_code(KC_LEFT);
      set_mods(mod_state);
    }
    return false;
}

/*e. send_autopair_on_shift

Mục đích: Tương tự send_autopair, nhưng chỉ hoạt động khi Shift được bật, và tắt layer SYM (symbol) sau khi hoàn tất.

Tham số:

    is_shifted: Boolean, true nếu Shift được bật.
    left_keycode: Keycode của ký tự bên trái (ví dụ: "(").
    right_keycode: Keycode của ký tự bên phải (ví dụ: ")").
    keycode: Keycode mặc định khi không Shift.
    record: Thông tin sự kiện phím.

Hoạt động:

    Nếu Shift được bật, gọi send_autopair với left_keycode và right_keycode, sau đó tắt layer SYM.
    Nếu không, chỉ gửi keycode mặc định.

Ví dụ sử dụng: Khi Shift được bật, nhấn một phím tạo cặp ngoặc, khi không Shift, chỉ gửi ký tự bình thường.*/
bool send_autopair_on_shift(
    bool is_shifted,
    uint16_t left_keycode,
    uint16_t right_keycode,
    uint16_t keycode,
    keyrecord_t *record) {
    if (record->event.pressed) {
        if (is_shifted) {
			send_autopair(left_keycode, right_keycode, record);
            layer_off(5);
        } else {
            tap_code16(keycode);
        }
    }
    return false;
}

/*f. send_double_on_shift

Mục đích: Gửi một ký tự hai lần khi Shift được bật, ví dụ: dấu chấm (.) trở thành "..".

Tham số:

    is_shifted: Boolean, true nếu Shift được bật.
    keycode: Keycode của ký tự.
    record: Thông tin sự kiện phím.

Hoạt động:

    Nếu Shift được bật, xóa trạng thái Shift, gửi keycode hai lần, rồi khôi phục trạng thái Shift.
    Nếu không, không làm gì.

Ví dụ sử dụng: Nhấn Shift + "." sẽ gửi "..".*/
bool send_double_on_shift(
	bool is_shifted,
	uint16_t keycode,
	keyrecord_t *record ) {
    if(record ->event.pressed) {
        // If shifted, double these common punctuation marks.
        if(is_shifted){
            uint8_t mod_state = get_mods();

            clear_shift(is_shifted);

            tap_code16(keycode);
            tap_code16(keycode);

            // restore previous shift state
            set_mods(mod_state);
            return false;
        }
    }
    return true;
}
/*g. send_string_c_function

Mục đích: Gửi một chuỗi cố định ("(){" khi Shift được bật.

Tham số:

    is_shifted: Boolean, true nếu Shift được bật.
    keycode: Keycode (không dùng trong hàm này).
    record: Thông tin sự kiện phím.

Hoạt động:

    Nếu Shift được bật, lưu và xóa trạng thái modifier, gửi chuỗi "(){", rồi khôi phục trạng thái.

Ví dụ sử dụng: Dùng để nhanh chóng nhập mã lập trình.*/
bool send_string_c_function(
    bool is_shifted,
    uint16_t keycode,
    keyrecord_t *record) {
    if (is_shifted){
        if (record->event.pressed) {
            uint8_t mod_state = get_mods();
			clear_shift(is_shifted);
            SEND_STRING("(){");

            set_mods(mod_state);
        }
        return false;
    }
    return true;
}

/*h. send_string_version

Mục đích: Gửi chuỗi "V" theo trạng thái Shift hiện tại, sau đó gửi một số (number keycode) mà không bị ảnh hưởng bởi Shift.

Tham số:

    is_shifted: Boolean, true nếu Shift được bật.
    number_keycode: Keycode của số (ví dụ: KC_1).
    record: Thông tin sự kiện phím.

Hoạt động:

    Gửi "V" (theo trạng thái Shift).
    Xóa Shift, sau đó gửi number_keycode.

Ví dụ sử dụng: Nhập phiên bản như "V1", "V2", v.v.*/
bool send_string_version(
    bool is_shifted,
    uint8_t number_keycode,
    keyrecord_t *record) {
    if(record->event.pressed){
        // Tap V in whatever shift format is present
        tap_code(KC_V);

        // Remove shift before pressing the number
        if(is_shifted){
            del_oneshot_mods(MOD_MASK_SHIFT);
            del_mods(MOD_MASK_SHIFT);
        }

        tap_code(number_keycode);
    }
    return false;
}

/*i. send_string_vi_yiw

Mục đích: Gửi chuỗi lệnh cho Vim ("yiw" hoặc "diw") dựa trên trạng thái Shift và các tham số.

Tham số:

    is_shifted: Boolean, true nếu Shift được bật.
    is_yank: Boolean, true nếu là yank (sao chép), false nếu là delete.
    movement: Keycode cho chuyển động (ví dụ: KC_A hoặc KC_I).
    is_word: Boolean, true nếu thao tác trên từ (word).
    record: Thông tin sự kiện phím.

Hoạt động:

    Đảm bảo chữ thường (ensure_lowercase).
    Nếu là yank, gửi "y".
    Gửi chuyển động (movement).
    Nếu là từ, gửi "w" hoặc "W" (dựa trên Shift).

Ví dụ sử dụng: Tạo phím tắt cho Vim như "yiw" (yank inner word).*/
bool send_string_vi_yiw(
	bool is_shifted,
	bool is_yank,
	uint8_t movement,
	bool is_word,
	keyrecord_t *record) {
  	if (record->event.pressed){
		ensure_lowercase(is_shifted);

		// when yanking, add the y
    	if(is_yank){
      		tap_code(KC_Y);
    	}

		// Movement is either a or i
    	tap_code(movement);

		// and if there's a word, add the w or W.
    	if(is_word)
    	{
	  		uint16_t word_code = is_shifted ? S(KC_W) : KC_W;
	    	tap_code16(word_code);
    	}
	}
	return false;
}

/*. send_string_markdown_link

Mục đích: Gửi chuỗi "" cho liên kết Markdown, với con trỏ ở giữa.

Tham số:

    record: Thông tin sự kiện phím.

Hoạt động:

    Gửi "", sau đó di chuyển con trỏ trái ba lần (triple_tap(KC_LEFT)).

Ví dụ sử dụng: Nhanh chóng tạo liên kết Markdown.*/
bool send_string_markdown_link(
    keyrecord_t *record) {
        if (record->event.pressed) {
            uint8_t mod_state = get_mods();
            del_mods(MOD_MASK_SHIFT);

            SEND_STRING("[]()");
            triple_tap(KC_LEFT);

            set_mods(mod_state);
        }
        return false;
}

/*k. Các hàm phụ trợ

    triple_tap: Gửi một keycode ba lần.
    clear_caps: Tắt Caps Lock nếu đang bật.
    clear_shift: Xóa trạng thái Shift (oneshot và thường).
    ensure_lowercase: Đảm bảo tất cả chữ thường bằng cách tắt Caps Lock và Shift.*/
void triple_tap(uint16_t keycode) {
    tap_code16(keycode);
    tap_code16(keycode);
    tap_code16(keycode);
}

void clear_caps(void) {
	if(host_keyboard_led_state().caps_lock){
  		tap_code(KC_CAPS);
	}
#ifdef CAPS_WORD_ENABLE
	caps_word_off();
#endif
}
void clear_shift(bool is_shifted) {
	if(is_shifted) {
    	del_oneshot_mods(MOD_MASK_SHIFT);
    	del_mods(MOD_MASK_SHIFT);
	}
}
void ensure_lowercase(bool is_shifted) {
    clear_caps();
    clear_shift(is_shifted);
}
