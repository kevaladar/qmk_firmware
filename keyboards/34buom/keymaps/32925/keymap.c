// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keval.h"
// define layers name
enum layer_names {
    _DEF1,	// Layer 0
    _ALT1,	// Layer 1
    _NAV1,	// Layer 2
	_SYM1,	// Layer 3
	_MERG1,	// Layer 4
	_NUM1,	// Layer 5
	_FUN1	// Layer 6
};
/*
// Define combo events
enum combos {
  LH_ESC,             // l + h -> esc
  XM_TAB,             // x + m -> tab
  NT_OSSFT,           // n + t -> oneshot shift
  CA_OSSFT,           // c + a -> oneshot shift
  REPSPC_FUN,         // repeat + space -> MO(_FUN)
  XD_ENTER,           // x + d -> enter
  CTLZCTLX_CTRLA,   // z + x -> ctrl + a
  LU_CAPS,            // l + u -> capslock
  KF_CAPSW,           // k + f -> capsword
  LK_WINSHIFTS,       // l + k -> win + shift + s
  BRIUP_BRIDN_SLP,    // bright up + bright down -> sleep
  VOLUP_VOLDN_MUTE,    // vol+ + vol- -> mute
  XD_M_PRSC 		  // x + d -> prsc
};

// Define key combinations
const uint16_t PROGMEM lh_combo[] = {KC_L, KC_H, COMBO_END};
const uint16_t PROGMEM xm_combo[] = {KC_X, KC_M, COMBO_END};
const uint16_t PROGMEM nt_combo[] = {KC_N, KC_T, COMBO_END};
const uint16_t PROGMEM ca_combo[] = {KC_C, KC_A, COMBO_END};
const uint16_t PROGMEM repspc_combo[] = {QK_REP, KC_SPC, COMBO_END};
const uint16_t PROGMEM xd_combo[] = {KC_X, KC_D, COMBO_END};
const uint16_t PROGMEM ctlzctlx_combo[] = {LCTL(KC_Z), LCTL(KC_X), COMBO_END};
const uint16_t PROGMEM lu_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM kf_combo[] = {KC_K, KC_F, COMBO_END};
const uint16_t PROGMEM lk_combo[] = {KC_L, KC_K, COMBO_END};
const uint16_t PROGMEM briup_bridn_combo[] = {KC_BRIU, KC_BRID, COMBO_END};
const uint16_t PROGMEM volup_voldn_combo[] = {KC_VOLU, KC_VOLD, COMBO_END};



// Map combos to actions
combo_t key_combos[] = {
  [LH_ESC] = COMBO(lh_combo, KC_ESC),
  [XM_TAB] = COMBO(xm_combo, KC_TAB),
  [NT_OSSFT] = COMBO(nt_combo, OSM(MOD_LSFT)),
  [CA_OSSFT] = COMBO(ca_combo, OSM(MOD_LSFT)),
  [REPSPC_FUN] = COMBO(repspc_combo, MO(_FUN1)),
  [XD_ENTER] = COMBO(xd_combo, KC_ENTER),
  [CTLZCTLX_CTRLA] = COMBO(ctlzctlx_combo, LCTL(KC_A)),
  [LU_CAPS] = COMBO(lu_combo, KC_CAPS),
  [KF_CAPSW] = COMBO(kf_combo, CW_TOGG),
  [LK_WINSHIFTS] = COMBO(lk_combo, LGUI(LSFT(KC_S))),
  [BRIUP_BRIDN_SLP] = COMBO(briup_bridn_combo, KC_SLEP),
  [VOLUP_VOLDN_MUTE] = COMBO(volup_voldn_combo, KC_MUTE),
};

define macros name
enum custom_keycodes {
    M_QU = SAFE_RANGE,
    M_SLINE,
    M_PRSC
};

//define macro work
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_QU:
            if (record->event.pressed) {
                // 1. Tap Q, release LShift, Tap U
                tap_code(KC_Q);
                unregister_code(KC_LSFT);  // bỏ shift nếu đang giữ
                tap_code(KC_U);
            }
            return false;

        case M_SLINE:
            if (record->event.pressed) {
                // 2. Tap End, rồi LShift + Home
                tap_code(KC_END);
                register_code(KC_LSFT);
                tap_code(KC_HOME);
                unregister_code(KC_LSFT);
            }
            return false;

        case M_PRSC:
            if (record->event.pressed) {
                // 3. Win + Shift + S
                register_code(KC_LGUI);   // giữ Win
                register_code(KC_LSFT);   // giữ Shift
                tap_code(KC_S);           // nhấn S
                unregister_code(KC_LSFT); // nhả Shift
                unregister_code(KC_LGUI); // nhả Win
            }
            return false;

        default:
            return true;
    }
}
*/

// define layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
    Default layer| Alpha layer | Dhorf by Oxey
    ,---------------------------------------.	,---------------------------------------.
    | V     | L     | H     | K     | Q     |	| P     | F     | O     | U     | '     |
    |-------+-------+-------+-------+-------|	|-------+-------+-------+-------+-------|
    | S     | R     | N     | T     | W     |	| Y     | C     | A     | E     | I     |
    |-------+-------+-------+-------+-------|	|-------+-------+-------+-------+-------|
    |       | X     | M     | D     | B     | 	| J     | G     | ,     | .     |       |
    '-------+-------+-------+-------+-------' 	`-------+-------+-------+-------+-------'
							|  NAV  |  REP  | 	|  SPC  |  SYM  |
							`-------+-------' 	`-------+-------'
*/
    [_DEF1] = LAYOUT_split_3x5_2(
        KC_V,		KC_L,		KC_H,   	KC_K,		KC_TRNS,		KC_P,		KC_F,   	KC_O,		KC_U,		KC_QUOT,
        KC_S,		KC_R,   	KC_N,   	KC_T,		KC_W,			KC_Y,   	KC_C,   	KC_A,		KC_E,   	KC_I,
        KC_NO,		KC_X,   	KC_M,   	KC_D,		KC_B,			KC_J,   	KC_G,		KC_COMM,	KC_DOT,		KC_NO,
											MO(_NAV1),	QK_REP,			KC_SPC, 	MO(_SYM1)
    ),
/*
    Second | Alternative alpha layer
    ,---------------------------------------.	,---------------------------------------.
    |       |       |       |       |       |	|       |       |       |       |       |
    |-------+-------+-------+-------+-------|	|-------+-------+-------+-------+-------|
    | 		| 		|       |       |       |	|       |       |       |       |       |
    |-------+-------+-------+-------+-------|	|-------+-------+-------+-------+-------|
    |       |       |       |       |       | 	|       |       |       |       |       |
    '-------+-------+-------+-------+-------' 	`-------+-------+-------+-------+-------'
							|       |       | 	|       |       |
							`-------+-------' 	`-------+-------'
*/
	[_ALT1] = LAYOUT_split_3x5_2(
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
											KC_TRNS,	KC_TRNS,		KC_TRNS,	KC_TRNS
	),
/*
    Navigation Layer
    ,---------------------------------------. ,---------------------------------------.
    |  TD0  | C-TAB |       |       | PRSC  | | PGUP  | HOME  |  UP   |  END  |  DEL  |
    |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
    |  GUI  |  ALT  | CTRL  | SHIFT | TD1   | | PGDN  | LEFT  | DOWN  | RIGHT | ENT   |
    |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
    |  UNDO |  CUT  | COPY  | PASTE | REDO  | | F2    | BSPC  | C-BSPC| S-ENT |       |
    `-------+-------+-------+-------+-------' `-------+-------+-------+-------+-------'
							|       |       | | BSPC  | SYM   |
							`-------+-------' `-------+-------'
TD0: Windows swap
TD1: Select line
*/
	[_NAV1] = LAYOUT_split_3x5_2(
		TD(0),		LCTL(KC_TAB),	KC_TRNS,	KC_TRNS,	KC_TRNS,		KC_PGUP,	KC_HOME,	KC_UP,			KC_END,		KC_DEL,
		OS_LGUI,	 OS_LALT,		OS_LCTL,	OS_LSFT,	KC_TRNS,		KC_PGDN,	KC_LEFT,	KC_DOWN,		KC_RGHT,	KC_ENT,
		LCTL(KC_Z),	LCTL(KC_X),		LCTL(KC_C),	LCTL(KC_V),	LCTL(KC_Y),		KC_F2,		KC_BSPC,	LCTL(KC_BSPC),	KC_NO,		LSFT(KC_ENTER),
												KC_NO,		KC_NO,			KC_BSPC,	MO(_SYM1)
	),
/*

    Symbol Layer
    ,---------------------------------------. ,---------------------------------------.
    |       |       |       |       |       | | %     | @     | ?     | !     |       |
    |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
    |   =   | 	`	|   -   | 	/   |	&   | |       | LSFT  | LCTL  | LALT  | LGUI  |
    |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
    |   +   | 	~   |   _   |   \   |   #   | |       |       |       |TG_NUM |TG_FUN |
    `-------+-------+-------+-------+-------' `-------+-------+-------+-------+-------'
							| SYM   |       | |       |       |
							`-------+-------' `-------+-------'
*/
	[_SYM1] = LAYOUT_split_3x5_2(
		KC_TRNS,	KC_TRNS,		KC_TRNS,		KC_TRNS,	KC_TRNS,		LSFT(KC_5),	LSFT(KC_2),	LSFT(KC_SLSH),	LSFT(KC_1),	KC_TRNS,
		KC_EQL,		KC_GRV,			KC_MINS,		KC_SLSH,	LSFT(KC_7),		KC_TRNS,	OS_LSFT,	OS_LCTL,		OS_LALT,	OS_LGUI,
		KC_PPLS,	LSFT(KC_GRV),	LSFT(KC_MINS),	KC_NUBS,	LSFT(KC_3),		KC_TRNS,	KC_TRNS,	KC_TRNS,		TG(_NUM1),	TG(_FUN1),
													MO(_SYM1),	KC_TRNS,		KC_TRNS, 	KC_TRNS
	),
/*

    Merge Layer
    ,---------------------------------------. ,---------------------------------------.
    |       |       |       |       |       | | *     | 7     | 8     | 9     | /     |
    |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
    |       |       |       |       |       | | -     | 0     | 1     | 2     | 3     |
    |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
    |       |       |       |       |       | | +     | 4     | 5     | 6     | .     |
    `-------+-------+-------+-------+-------' `-------+-------+-------+-------+-------'
							|       |       | |       |       |
							`-------+-------' `-------+-------'
*/
	[_MERG1] = LAYOUT_split_3x5_2(
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,		LSFT(KC_8),		KC_7,		KC_8,		KC_9,		KC_SLSH,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,		KC_MINS,		KC_0,		KC_1,		KC_2,		KC_3,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,		LSFT(KC_EQL),	KC_4,		KC_5,		KC_6,		KC_DOT,
											KC_NO,		KC_NO,			KC_NO, 			KC_NO
	),	
/*

    Number Layer
    ,---------------------------------------. ,---------------------------------------.
    |       |       |       |       |       | | PGUP  | HOME  | UP    | END   | DEL   |
    |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
    |       |       |       |       |       | | PGDN  | LEFT  | DOWN  | RIGHT |       |
    |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
    |       |       |       |       |       | | F2    | BSPC  | LCTL  | BSPC  |       |
    `-------+-------+-------+-------+-------' `-------+-------+-------+-------+-------'
							|       |       | |       |       |
							`-------+-------' `-------+-------'
*/
	[_NUM1] = LAYOUT_split_3x5_2(
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,		KC_PGUP,	KC_HOME,	KC_UP,		KC_END,		KC_DEL,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,		KC_PGDN,	KC_LEFT,	KC_DOWN,	KC_RGHT,	KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,		KC_F2,		KC_BSPC,	KC_LCTL,	KC_BSPC,	KC_TRNS,
											KC_TRNS,	KC_TRNS,		KC_TRNS,	KC_TRNS
	),
/*

    Function and cursor layer
    ,---------------------------------------. ,---------------------------------------.
    |       | VOLU  | MUTE  | VOLD  |       | | PGUP  | BRIU  | M_UP  | BRID  |       |
    |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
    | RESET | MBTN1 | MBTN3 | MBTN2 | WSCH  | | WHLL  | M_LEFT| M_DOWN| M_RGHT| WHLR  |
    |-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------|
    | BOOT  | MPRV  |       | MNXT  | CALC  | | 	  | 	  | 	  | 	  |       |
    `-------+-------+-------+-------+-------' `-------+-------+-------+-------+-------'
							|       |       | |       |       |
							`-------+-------' `-------+-------'
*/
	[_FUN1] = LAYOUT_split_3x5_2(
		KC_NO,		KC_VOLU,	KC_MUTE,	KC_VOLD,	KC_NO,			KC_NO,		KC_BRIU,	MS_UP,		KC_BRID,	KC_NO,
		QK_RBT,		MS_BTN1,	MS_BTN3,	MS_BTN2,	KC_WSCH,		MS_WHLL,	MS_LEFT,	MS_DOWN,	MS_RGHT,	MS_WHLR,
		QK_BOOT,	KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_CALC,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
											KC_NO,		KC_NO,			KC_NO, 		KC_NO
	)
};

//oled code here
#ifdef OLED_ENABLE

// Rotate OLED
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270; //default rotate is 90 or idk, but my display assem is upside down so I need 270
}

// Draw to OLED
bool oled_task_user() {
    // Set cursor position
    oled_set_cursor(0, 1);

    // Define image array
    static const char image [] PROGMEM = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //this is legendary Tom Platz pose
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x80, 0x80, 0x80, 0x80, 0xC0, 0xC0,
		0xC0, 0x80, 0xC0, 0xC0, 0xC0, 0xC0,
		0xC0, 0x80, 0x80, 0x80, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
		0x80, 0xC0, 0xF0, 0xF8, 0xFC, 0xFE,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7,
		0x8F, 0xFE, 0xF8, 0xC0, 0xC0, 0xF4,
		0xFE, 0xFF, 0xFF, 0xBF, 0xBF, 0x1F,
		0x1F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x00, 0x04, 0xF1, 0xD1, 0x01, 0x03,
		0x03, 0x02, 0x00, 0x40, 0xC0, 0xC0,
		0xC0, 0xC1, 0x80, 0x01, 0x83, 0x03,
		0x03, 0x07, 0x07, 0x0F, 0x0F, 0x0F,
		0x0F, 0x07, 0x03, 0x83, 0x83, 0x01,
		0x09, 0x03, 0x00, 0x80, 0xA0, 0xF0,
		0x70, 0x78, 0x78, 0xB8, 0x38, 0x1E,
		0x78, 0x70, 0x60, 0x40, 0x00, 0x80,
		0x81, 0x80, 0xE0, 0xF0, 0xF0, 0x20,
		0x80, 0x00, 0x00, 0x01, 0x00, 0x01,
		0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF,
		0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0xF0,
		0xD8, 0x01, 0x03, 0x03, 0x07, 0x07,
		0x07, 0x03, 0x03, 0x00, 0x00, 0xC8,
		0xC0, 0x80, 0x00, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
		0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x00,
		0x00, 0x01, 0x03, 0x03, 0x06, 0x02,
		0x00, 0x00, 0x00, 0x00, 0x00, 0xE0,
		0xE8, 0xE1, 0xC7, 0xDF, 0xFF, 0xFF,
		0xFE, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFE, 0xFC, 0xF8, 0xC0, 0xE0,
		0xE0, 0xE0, 0xE0, 0xF8, 0xFC, 0xFE,
		0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x5F, 0x9F, 0xBF, 0x7F, 0x3F, 0x5F,
		0x7F, 0x7F, 0xDF, 0x1F, 0x17, 0x0B,
		0x0F, 0x07, 0x01, 0x01, 0x82, 0x83,
		0x01, 0x05, 0x0F, 0x4F, 0x5F, 0x7F,
		0x7F, 0x7F, 0x3F, 0x3F, 0x7F, 0x7F,
		0x7F, 0x7F, 0x80, 0x01, 0xC1, 0xC0,
		0xE0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF0,
		0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF9,
		0xFD, 0xFD, 0xFF, 0xFC, 0xF8, 0xF8,
		0xF8, 0xB0, 0x80, 0x80, 0x80, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x0F, 0x1F,
		0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFB, 0xFB, 0xFD, 0xFD, 0xF8,
		0xFB, 0xF3, 0x77, 0x17, 0x07, 0x0F,
		0x1F, 0x0F, 0x0F, 0x0F, 0x1F, 0x1F,
		0x1F, 0x1F, 0x0F, 0x1C, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x01, 0x01, 0x01,
		0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
		0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
		0x00, 0x00, 0x1C, 0x0C, 0x1C, 0x1C,
		0x0E, 0x06, 0x06, 0x06, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x01, 0x03, 0x03, 0x83, 0x03,
		0x01, 0x01, 0x01, 0x01, 0x00, 0x18,
		0x18, 0x1C, 0x78, 0x78, 0x78, 0x30,
		0x10, 0x20, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0xC4, 0xE4,
		0xE8, 0xFC, 0xFE, 0xFE, 0xFE, 0xFC,
		0xFC, 0xFC, 0xFC, 0xFD, 0xFC, 0xFE,
		0xFE, 0xFE, 0xFC, 0xFC, 0xFC, 0xF8,
		0xF8, 0xFC, 0xE8, 0xE8, 0xE0, 0xE0,
		0xE8, 0xE0, 0xEC, 0xFE, 0xFE, 0xE2,
    };

    // Draw image to Oled
    oled_write_raw_P(image, sizeof(image));

    return false;
}
#endif