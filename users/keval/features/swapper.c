#include "swapper.h"

void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(tabish);
        } else {
            unregister_code(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (*active) {
        unregister_code(cmdish);
        *active = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SW_TAB:
            if (record->event.pressed) {
                // Implement tab switching logic here
                // Example: Hold CMD and tap TAB
                register_code(KC_LGUI); // CMD key
                tap_code(KC_TAB);
                unregister_code(KC_LGUI);
            }
            break;
        case SW_WIN:
            if (record->event.pressed) {
                // Implement window switching logic here
                // Example: Hold ALT and tap TAB
                register_code(KC_LALT); // ALT key
                tap_code(KC_TAB);
                unregister_code(KC_LALT);
            }
            break;
    }
    return true;
}
