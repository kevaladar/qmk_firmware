#include QMK_KEYBOARD_H
#include "oneshot.h"   // Custom oneshot mod implementation
#include "swapper.h"   // Window/language switching functionality

// Macros for common key combinations
#define HOME G(KC_LEFT)      // Cmd+Left - Move to start of line
#define END G(KC_RGHT)       // Cmd+Right - Move to end of line
#define FWD G(KC_RBRC)       // Cmd+] - Forward browser history
#define BACK G(KC_LBRC)      // Cmd+[ - Back browser history
#define TABL G(S(KC_LBRC))   // Cmd+Shift+[ - Move to left tab
#define TABR G(S(KC_RBRC))   // Cmd+Shift+] - Move to right tab
#define SPCL A(G(KC_LEFT))   // Alt+Cmd+Left - Move to prev word
#define SPC_R A(G(KC_RGHT))  // Alt+Cmd+Right - Move to next word

// Layer toggle keys
#define LA_SYM MO(SYM)  // Momentarily activate SYM layer
#define LA_NAV MO(NAV)  // Momentarily activate NAV layer

// Layer definitions
enum layers {
    DEF,  // Default layer (base typing layer)
    SYM,  // Symbols layer
    NAV,  // Navigation/media layer
    NUM,  // Numbers/function keys layer (activated when both SYM+NAV are on)
};

// Custom keycodes
enum keycodes {
    // Custom oneshot mod implementation with no timers
    OS_SHFT = SAFE_RANGE,  // Oneshot shift
    OS_CTRL,               // Oneshot control
    OS_ALT,                // Oneshot alt
    OS_CMD,                // Oneshot command
    
    // Custom swapper keys
    SW_WIN,   // Switch windows (Cmd+Tab)
    SW_LANG,  // Switch input language (Ctrl+Space)
};

// Keymap definition
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Default layer (Colemak-DH like layout)
    [DEF] = LAYOUT_split_3x5_2(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                                   LA_NAV,  KC_LSFT, KC_SPC,  LA_SYM   // Thumb keys
    ),

    // Navigation/media layer
    [NAV] = LAYOUT_split_3x5_2(
        KC_TAB,  SW_WIN,  TABL,    TABR,    KC_VOLU, QK_BOOT, HOME,    KC_UP,   END,     KC_DEL,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_VOLD, KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
        SPCL,    SPC_R,   BACK,    FWD,     KC_MPLY, XXXXXXX, KC_PGDN, KC_PGUP, SW_LANG, KC_ENT,
                                   _______, _______, _______, _______  // Blank thumb keys
    ),

    // Symbols layer
    [SYM] = LAYOUT_split_3x5_2(
        KC_ESC,  KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD, KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV,
        KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,  KC_HASH, OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
        KC_PLUS, KC_PIPE, KC_AT,   KC_BSLS, KC_PERC, XXXXXXX, KC_AMPR, KC_SCLN, KC_COLN, KC_EXLM,
                                   _______, _______, _______, _______  // Blank thumb keys
    ),

    // Numbers/function keys layer (activated when both SYM+NAV are on)
    [NUM] = LAYOUT_split_3x5_2(
        KC_7,    KC_5,    KC_3,    KC_1,    KC_9,    KC_8,    KC_0,    KC_2,    KC_4,    KC_6,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_F11,  KC_F10,  OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
        KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F9,   KC_F8,   KC_F12,  KC_F2,   KC_F4,   KC_F6,
                                   _______, _______, _______, _______  // Blank thumb keys
    ),
};

// Determine if a key should cancel oneshot mods
bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:  // Sym layer key
    case LA_NAV:  // Nav layer key
        return true;  // These keys cancel oneshot mods
    default:
        return false;
    }
}

// Determine if a key should be ignored for oneshot purposes
bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:   // Sym layer key
    case LA_NAV:   // Nav layer key
    case KC_LSFT:  // Regular shift
    case OS_SHFT:  // Oneshot shift
    case OS_CTRL:  // Oneshot control
    case OS_ALT:   // Oneshot alt
    case OS_CMD:   // Oneshot command
        return true;  // These keys don't trigger oneshot mod release
    default:
        return false;
    }
}

// State variables for window/language switching
bool sw_win_active = false;   // Track window switcher state
bool sw_lang_active = false;  // Track language switcher state

// State variables for oneshot mods
oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

// Main key processing function
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Handle window switching (Cmd+Tab)
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );
    
    // Handle language switching (Ctrl+Space)
    update_swapper(
        &sw_lang_active, KC_LCTL, KC_SPC, SW_LANG,
        keycode, record
    );

    // Update oneshot mod states
    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_cmd_state, KC_LCMD, OS_CMD, keycode, record);

    return true;
}

// Layer state handler - enables NUM layer when both SYM and NAV are active
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}