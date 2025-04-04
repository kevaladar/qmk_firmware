#pragma once

#include QMK_KEYBOARD_H

// ----------------------
// 📌 Layer definitions
// ----------------------
enum layer_names {
    _DEF,   // Default layer
    _ALT,
    _NAV,
    _SYM,
    _MERG,
    _NUM,
    _FUN
};

// ----------------------
// 📌 Combo definitions
// ----------------------
enum combos {
    LH_ESC,
    XM_TAB,
    NT_OSSFT,
    CA_OSSFT,
    REPSPC_FUN,
    XD_ENTER,
    CTLZCTLX_CTRLA,
    LU_CAPS,
    KF_CAPSW,
    LK_WINSHIFTS,
    BRIUP_BRIDN_SLP,
    VOLUP_VOLDN_MUTE,
    XD_M_PRSC
};

// ----------------------
// 📌 Custom keycodes
// ----------------------
enum custom_keycodes {
    M_QU = SAFE_RANGE,
    M_SLINE,
    M_PRSC
};

// ----------------------
// 📌 Function prototypes
// ----------------------

// Process keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record);

// OLED rotation and drawing
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation);
bool oled_task_user(void);
#endif
