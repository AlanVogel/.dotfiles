#pragma once

#include QMK_KEYBOARD_H

// Layer names
enum layers {
    _BASE,
    _FIRST,
    _SECOND
};

// Keymap declaration
extern const uint16_t PROGMEM keymaps[3][MATRIX_ROWS][MATRIX_COLS];

#ifdef ENCODER_MAP_ENABLE
extern const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS];
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation);
bool oled_task_user(void);
#endif
