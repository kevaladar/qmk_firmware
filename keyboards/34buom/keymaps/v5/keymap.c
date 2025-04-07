#include QMK_KEYBOARD_H
#include "features/oled.h"
#include "features/override_keys.h"

// define layers name
enum layer_names {
    _DEF,	// Layer 0
    _ALT,	// Layer 1
    _NAV,	// Layer 2
	_SYM,	// Layer 3
	_MERG,	// Layer 4
	_NUM,	// Layer 5
	_FUN	// Layer 6
};

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
  GCOMM_Q,            // g + , -> q
  DOTCOMM_Z,          // . + comm -> z
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
const uint16_t PROGMEM gcomm_q_combo[] = {KC_G, KC_COMM, COMBO_END};
const uint16_t PROGMEM dotcomm_z_combo[] = {KC_DOT, KC_COMM, COMBO_END};

// Map combos to actions
combo_t key_combos[] = {
  [LH_ESC] = COMBO(lh_combo, KC_ESC),
  [XM_TAB] = COMBO(xm_combo, KC_TAB),
  [NT_OSSFT] = COMBO(nt_combo, OSM(MOD_LSFT)),
  [CA_OSSFT] = COMBO(ca_combo, OSM(MOD_LSFT)),
  [REPSPC_FUN] = COMBO(repspc_combo, MO(_FUN)),
  [XD_ENTER] = COMBO(xd_combo, KC_ENTER),
  [CTLZCTLX_CTRLA] = COMBO(ctlzctlx_combo, LCTL(KC_A)),
  [LU_CAPS] = COMBO(lu_combo, KC_CAPS),
  [KF_CAPSW] = COMBO(kf_combo, CW_TOGG),
  [LK_WINSHIFTS] = COMBO(lk_combo, LGUI(LSFT(KC_S))),
  [BRIUP_BRIDN_SLP] = COMBO(briup_bridn_combo, KC_SLEP),
  [VOLUP_VOLDN_MUTE] = COMBO(volup_voldn_combo, KC_MUTE),
  [GCOMM_Q] = COMBO(gcomm_q_combo, KC_Q),
  [DOTCOMM_Z] = COMBO(dotcomm_z_combo, KC_Z),
};
// test zq  
//define macros name
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


// define layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DEF] = LAYOUT_split_3x5_2(
        KC_V,    KC_L,	KC_H,   KC_K,	M_QU,	KC_P,	KC_F,   KC_O,	KC_U,	KC_QUOT,
        KC_S,    KC_R,  KC_N,   KC_T,	KC_W,	KC_Y,   KC_C,   KC_A,	KC_E,   KC_I,
        XXXXXXX, KC_X,  KC_M,   KC_D,	KC_B,	KC_J,   KC_G,	KC_COMM, KC_DOT, KC_NO,
							MO(_NAV), QK_REP, KC_SPC,   MO(_SYM)
    ),

	[_ALT] = LAYOUT_split_3x5_2(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
    XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX,  \
							  MO(_NAV),  QK_REP, KC_SPC,  MO(_SYM)
    ),

	[_NAV] = LAYOUT_split_3x5_2(
		LALT(KC_TAB), LCTL(KC_TAB),	XXXXXXX,	XXXXXXX,	XXXXXXX,		KC_PGUP,	KC_HOME,	KC_UP,			KC_END,		KC_DEL,
		KC_LGUI,	KC_LALT,		KC_LCTL,	KC_LSFT,	M_SLINE,		KC_PGDN,	KC_LEFT,	KC_DOWN,		KC_RGHT,	KC_ENT,
		LCTL(KC_Z),	LCTL(KC_X),		LCTL(KC_C),	LCTL(KC_V),	LCTL(KC_Y),		KC_F2,		KC_BSPC,	LCTL(KC_BSPC),	XXXXXXX,	LSFT(KC_ENTER),
												KC_NO,		KC_NO,			KC_BSPC,	MO(_NUM)
	),

	[_SYM] = LAYOUT_split_3x5_2(
		XXXXXXX,	XXXXXXX,		XXXXXXX,		XXXXXXX,	XXXXXXX,		LSFT(KC_5),	LSFT(KC_2),	LSFT(KC_SLSH),	LSFT(KC_1),	XXXXXXX,
		KC_EQL,		KC_GRV,			KC_MINS,		KC_SLSH,	LSFT(KC_7),		XXXXXXX,	KC_LSFT,	KC_LCTL,		KC_LALT,	KC_LGUI,
		KC_PPLS,	LSFT(KC_GRV),	LSFT(KC_MINS),	KC_NUBS,	LSFT(KC_3),		XXXXXXX,	XXXXXXX,	XXXXXXX,		TG(_NUM),	TG(_FUN),
													MO(_NUM),	XXXXXXX,		XXXXXXX, 	XXXXXXX
	),

	[_MERG] = LAYOUT_split_3x5_2(
		XXXXXXX,	XXXXXXX,		XXXXXXX,		XXXXXXX,	XXXXXXX,		LSFT(KC_8),		KC_7,		KC_8,		KC_9,		KC_SLSH,
		XXXXXXX,	XXXXXXX,		XXXXXXX,		XXXXXXX,	XXXXXXX,		KC_MINS,		KC_0,		KC_1,		KC_2,		KC_3,
		XXXXXXX,	XXXXXXX,		XXXXXXX,		XXXXXXX,	XXXXXXX,		LSFT(KC_EQL),	KC_4,		KC_5,		KC_6,		KC_DOT,
											KC_NO,		KC_NO,			KC_NO, 			KC_NO
	),	

	[_NUM] = LAYOUT_split_3x5_2(
		XXXXXXX,	XXXXXXX,		XXXXXXX,		XXXXXXX,	XXXXXXX,		LSFT(KC_8),		KC_7,		KC_8,		KC_9,		KC_SLSH,
		XXXXXXX,	XXXXXXX,		XXXXXXX,		XXXXXXX,	XXXXXXX,		KC_MINS,		KC_0,		KC_1,		KC_2,		KC_3,
		XXXXXXX,	XXXXXXX,		XXXXXXX,		XXXXXXX,	XXXXXXX,		LSFT(KC_EQL),	KC_4,		KC_5,		KC_6,		KC_DOT,
											KC_NO,		KC_NO,			KC_NO, 			KC_NO
	),	

	[_FUN] = LAYOUT_split_3x5_2(
		KC_NO,		KC_VOLU,	KC_MUTE,	KC_VOLD,	KC_NO,			KC_NO,		KC_BRID,	MS_UP,		KC_BRIU,	KC_NO,
		QK_RBT,		MS_BTN1,	MS_BTN3,	MS_BTN2,	KC_WSCH,		MS_WHLL,	MS_LEFT,	MS_DOWN,	MS_RGHT,	MS_WHLR,
		QK_BOOT,	KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_CALC,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
											KC_NO,		KC_NO,			KC_NO, 		KC_NO
	)
};
