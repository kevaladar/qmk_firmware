#pragma once
#include QMK_KEYBOARD_H

/* ------ File Includes ---------- */
// Base Layout
// #include "layout.h"

// Features
#include "features/mod_lock.h"
#include "features/nshot_mod.h"
#include "features/smart_layer.h"
#include "features/override_keys.h"
#include "features/swapper.h"
// gboards combos
#ifdef COMBO_ENABLE
#include "g/keymap_combo.h"
#endif
