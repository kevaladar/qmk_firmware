#pragma once

#include "keycodes.h"

// Primary Thumb Keys
#define THM_LH0     NAVMODE
#define THM_LH1     QK_REP

#define THM_RH0     SYMMODE
#define THM_RH1     KC_SPC

// dhorf that keval use
#define LAYER_DHORF \
    KC_V,    KC_L,    KC_H,    KC_K,    KY_QU,   KC_P,    KC_F,    KC_O,    KC_U,    KC_QUOT,  \
    KC_S,    KC_R,    KC_N,    KC_T,    KC_W,    KC_Y,    KC_C,    KC_A,    KC_E,    KC_I,     \
    XXXXXXX, KC_X,    KC_M,    KC_D,    KC_B,    KC_J,    KC_G,    KC_COMM, KC_DOT,  XXXXXXX,  \
                               THM_LH0, THM_LH1, THM_RH1, THM_RH0

// alt can be whatever, night would be good choice
#define LAYER_ALT \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
    XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX,  \
                               THM_LH0, THM_LH1, THM_RH1, THM_RH0

// whatever, i don't know if it needed here
#define LAYER_QWERTY \
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, \
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  XXXXXXX, \
                               THM_LH0, THM_LH1, THM_RH1, THM_RH0

// i don't know if i need this wtf, we just can combo defi in base layer?
#define LAYER_COMBOREF \
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, \
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  XXXXXXX, \
                               KC_ENT,  KC_TAB,  KC_BSPC, KC_SPC

// nav layer that keval use
#define LAYER_NAV \
    SW_WIN,    SW_TAB,     XXXXXXX,    XXXXXXX,    XXXXXXX,     KC_PGUP, KC_HOME, KC_UP, KC_END, KC_DEL, \
    OS_LGUI,   OS_LALT,    OS_LCTL,    OS_LSFT,    XXXXXXX,     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT, \
    LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_Y), KC_F2, KC_BSPC, LCTL(KC_BSPC),	XXXXXXX, LSFT(KC_ENTER),  \
                               _______, _______, _______, _______

// sym that keval use, ofc those not for code
#define LAYER_SYM \
    XXXXXXX, XXXXXXX, XXXXXXX, KC_ASTR, KC_DLR,  KC_PERC, KC_AT,   KC_QUES, KC_EXLM, XXXXXXX, \
    KC_EQL,  KC_GRV,  KC_MINS, KC_SLSH, KC_AMPR, XXXXXXX, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
    KC_PPLS, KC_TILD, KC_UNDS, KC_BSLS, KC_HASH, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                               _______, _______, OSR_SFT, _______

// merg để tạm thế chứ chịu đéo biết
#define LAYER_MERG \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                               _______, _______, _______, _______

// Numpad left
#define LAYER_NUML \
    KC_PAST, KC_9,    KC_8,    KC_7,    KC_PMNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    KC_PSLS, KC_3,    KC_2,    KC_1,    KC_PPLS, KC_BSPC, KC_EQL,  KC_DOT,  KC_PERC, XXXXXXX, \
    XXXXXXX, KC_6,    KC_5,    KC_4,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                               KC_BSPC, KC_SPC,  XXXXXXX, XXXXXXX

// Numpad right
#define LAYER_NUMR \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PMNS, KC_7,    KC_8,    KC_9,    KC_PAST, \
    XXXXXXX, KC_PERC, KC_DOT,  KC_EQL,  KC_BSPC, KC_PPLS, KC_1,    KC_2,    KC_3,    KC_PSLS, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_4,    KC_5,    KC_6,    XXXXXXX, \
                               XXXXXXX, XXXXXXX, KC_SPC,  KC_BSPC

// Functions and Window management. Funcs are organized by number except for the debuggin' ones
#define LAYER_FUN \
    XXXXXXX, KC_VOLU, KC_MUTE,	KC_VOLD, XXXXXXX, XXXXXXX, KC_BRIU,	MS_UP,   KC_BRID, XXXXXXX, \
    QK_RBT,  MS_BTN1, MS_BTN3,	MS_BTN2, KC_WSCH, MS_WHLL, MS_LEFT,	MS_DOWN, MS_RGHT, MS_WHLR, \
    QK_BOOT, KC_MPRV, KC_MPLY,	KC_MNXT, KC_CALC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                THM_LH0, THM_LH1, THM_RH1, THM_RH0


// LAYOUT wrappers for default 34-key layout mapping
#define LAYOUT_34key_w(...) LAYOUT_split_3x5_2(__VA_ARGS__)

// Macros to add inverted-T GACS mods
#define URM_L(k1) LGUI_T(k1)
#define URM_R(k1) RGUI_T(k1)
#define HRM_L(k0, k1, k2, k3) k0,LALT_T(k1),LCTL_T(k2),LSFT_T(k3)
#define HRM_R(k0, k1, k2, k3) RSFT_T(k0),RCTL_T(k1),LALT_T(k2),k3

// Macros to do the same but for mac
#define MAC_URM_L(k1) LCTL_T(k1)
#define MAC_URM_R(k1) RCTL_T(k1)
#define MAC_HRM_L(k0, k1, k2, k3) k0,LALT_T(k1),LGUI_T(k2),LSFT_T(k3)
#define MAC_HRM_R(k0, k1, k2, k3) RSFT_T(k0),RGUI_T(k1),LALT_T(k2),k3

#define HRM(k) HR_MODTAP(k)
#define HR_MODTAP( \
      l01, l02, l03, l04, l05,  r01, r02, r03, r04, r05, \
      l06, l07, l08, l09, l10,  r06, r07, r08, r09, r10, \
      l11, l12, l13, l14, l15,  r11, r12, r13, r14, r15, \
                     l16, l17, r16, r17 \
)\
      l01, l02, URM_L(l03),l04, l05,  r01, r02, URM_R(r03), r04, r05, \
      HRM_L(l06, l07, l08, l09),l10,  r06, HRM_R(r07, r08, r09, r10), \
      l11,       l12, l13, l14, l15,  r11,       r12, r13, r14,  r15, \
                           l16, l17,  r16, r17 

#define MAC_HRM(k) MAC_HR_MODTAP(k)
#define MAC_HR_MODTAP( \
      l01, l02, l03, l04, l05,  r01, r02, r03, r04, r05, \
      l06, l07, l08, l09, l10,  r06, r07, r08, r09, r10, \
      l11, l12, l13, l14, l15,  r11, r12, r13, r14, r15, \
                     l16, l17, r16, r17 \
)\
      l01, l02, MAC_URM_L(l03),l04, l05,  r01, r02, MAC_URM_R(r03), r04, r05, \
      MAC_HRM_L(l06, l07, l08, l09),l10,  r06, MAC_HRM_R(r07, r08, r09, r10), \
      l11,       l12, l13, l14, l15,  r11,       r12, r13, r14,  r15, \
                           l16, l17,  r16, r17 
