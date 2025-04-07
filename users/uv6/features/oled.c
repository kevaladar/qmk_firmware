#include "features/oled.h"
#include "oled_driver.h"
#include "host.h"
#include "quantum.h"

// OLED rotation
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

// OLED task
bool oled_task_user(void) {
    // Line 1: CapsLock / CapsWord
    oled_set_cursor(1, 0);  // x=6px, y=0px
    bool caps = host_keyboard_led_state().caps_lock;
    bool caps_word = is_caps_word_on();

    if (caps || caps_word) {
        oled_write_P(PSTR("CAP"), false);
    } else {
        oled_write_P(PSTR("   "), false);  // clear dòng nếu không bật
    }

    // // Line 2: Layer
    // oled_set_cursor(1, 2);  // y=16px
    // switch (get_highest_layer(layer_state)) {
    //     case 0: oled_write_ln_P(PSTR("DEF"), false); break;
    //     case 1: oled_write_ln_P(PSTR("ALT"), false); break;
    //     case 2: oled_write_ln_P(PSTR("NAV"), false); break;
    //     case 3: oled_write_ln_P(PSTR("SYM"), false); break;
    //     case 4: oled_write_ln_P(PSTR("MERG"), false); break;
    //     case 5: oled_write_ln_P(PSTR("NUM"), false); break;
    //     case 6: oled_write_ln_P(PSTR("FUN"), false); break;
    //     default: oled_write_ln_P(PSTR("???"), false); break;
    // }

// Line 2: Hiển thị tên layer đang hoạt động
oled_set_cursor(1, 2);  // y = 16px

switch (get_highest_layer(layer_state)) {
    case _DHORF:     oled_write_ln_P(PSTR("DHF"), false); break;
    case _ALT:       oled_write_ln_P(PSTR("ALT"), false); break;
    case _QWERTY:    oled_write_ln_P(PSTR("QTY"), false); break;
    case _COMBOREF:  oled_write_ln_P(PSTR("CBR"), false); break;
    case _NAV:       oled_write_ln_P(PSTR("NAV"), false); break;
    case _SYM:       oled_write_ln_P(PSTR("SYM"), false); break;
    case _MERG:      oled_write_ln_P(PSTR("MEG"), false); break;
    case _NUML:      oled_write_ln_P(PSTR("NUM"), false); break;
    case _NUMR:      oled_write_ln_P(PSTR("NUM"), false); break;
    case _FUN:       oled_write_ln_P(PSTR("FUN"), false); break;
    default:         oled_write_ln_P(PSTR("???"), false); break;
}

    // Line 3: Modifier keys 
    oled_set_cursor(0, 4);  // CTL KEY LEFT TOP
    uint8_t mods = get_mods() | get_oneshot_mods();
    oled_write_P((mods & MOD_MASK_CTRL)  ? PSTR("CT") : PSTR("  "), false);

    // SHIFT KEY    
    oled_set_cursor(3, 4);  // SHIFT KEY RIGHT TOP
    oled_write_P((mods & MOD_MASK_SHIFT) ? PSTR("SF") : PSTR("  "), false);

    // ALT KEY
    oled_set_cursor(0, 6);  // ALT KEY LEFT BOTTOM
    oled_write_P((mods & MOD_MASK_ALT)   ? PSTR("AL") : PSTR("  "), false);

    // GUI KEY
    oled_set_cursor(3, 6);  // GUI KEY RIGHT BOTTOM
    oled_write_P((mods & MOD_MASK_GUI)   ? PSTR("GU") : PSTR("  "), false);

    return false;
}
