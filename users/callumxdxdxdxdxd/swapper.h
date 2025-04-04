#pragma once

#include QMK_KEYBOARD_H

/*
 * @file swapper.h
 * @brief Header for the key swapper functionality (Cmd-Tab/Alt-Tab style behavior)
 * 
 * This implements a generic "hold modifier + tap key" mechanism that:
 * - Activates on a custom trigger key
 * - Maintains the modifier until another key is pressed
 * - Works across layer changes
 */

/*
 * @brief Updates the swapper state machine
 * 
 * @param active Pointer to the active state boolean (should be initialized to false)
 * @param cmdish The modifier keycode to hold (e.g., KC_LGUI for Cmd/Windows key)
 * @param tabish The keycode to tap (e.g., KC_TAB for app switching)
 * @param trigger The custom keycode that activates this swapper
 * @param keycode The keycode currently being processed
 * @param record The key record event data
 * 
 * Typical usage examples:
 * 1. Application switcher (Cmd-Tab behavior):
 *    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record);
 * 
 * 2. Language switcher (Ctrl-Space behavior):
 *    update_swapper(&sw_lang_active, KC_LCTL, KC_SPC, SW_LANG, keycode, record);
 * 
 * Behavior examples:
 * - Trigger, Trigger, A → Cmd down, Tab, Tab, Cmd up, A
 * - Layer key down, Trigger, Layer key up → Layer down, Cmd down, Tab, Cmd up, Layer up
 */
void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
);