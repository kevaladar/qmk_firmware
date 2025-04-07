#include "v6.h"
#include "features/oled.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DHORF] = LAYOUT_34key_w(HRM(LAYER_DHORF))

    ,[_ALT] = LAYOUT_34key_w(HRM(LAYER_ALT))

    ,[_QWERTY] = LAYOUT_34key_w(HRM(LAYER_QWERTY))

    ,[_COMBOREF] = LAYOUT_34key_w(LAYER_COMBOREF)

    ,[_NAV] = LAYOUT_34key_w(LAYER_NAV)

    ,[_SYM] = LAYOUT_34key_w(LAYER_SYM)

    ,[_MERG] = LAYOUT_34key_w(LAYER_MERG)

    ,[_NUML] = LAYOUT_34key_w(LAYER_NUML)

    ,[_NUMR] = LAYOUT_34key_w(LAYER_NUMR)

    ,[_FUN] = LAYOUT_34key_w(LAYER_FUN)
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
};
