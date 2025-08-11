#include "keymap_defs.h"

// Layers
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
        KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
        KC_LCTL,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
                                KC_LGUI,   MO(_FIRST),  KC_SPC,  KC_ENT,   MO(_SECOND), KC_RALT
    ),
    [_FIRST] = LAYOUT_split_3x6_3(
        KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,     KC_9,     KC_0,    KC_BSPC,
        KC_LSFT, KC_NUHS, KC_BSLS, KC_NUBS, KC_LBRC, KC_RBRC,      KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,  KC_PSCR, KC_HOME,
        KC_LCTL, KC_CAPS, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_Z), KC_PMNS, KC_PPLS, KC_VOLU, KC_VOLD, KC_MUTE, LCTL(KC_F),
                                KC_LGUI, MO(_BASE),  KC_SPC,  KC_ENT, MO(_SECOND), KC_RALT
    ),
    [_SECOND] = LAYOUT_split_3x6_3(
        KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
        KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
                                KC_LGUI, MO(_BASE),  KC_SPC,  KC_ENT, MO(_FIRST), KC_RALT
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_BASE]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
  [_FIRST]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
  [_SECOND] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) }
};
#endif

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
        0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9,
        0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9,
        0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4,
        0x00
    };
    oled_write_P(qmk_logo, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return is_keyboard_master() ? OLED_ROTATION_270 : OLED_ROTATION_180;
}

static void oled_render_separator(void) {
    oled_write(PSTR("-----"), false);
}

static void render_layer_state(void) {
    oled_write_ln(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:   oled_write_ln(PSTR("BASE "), false); break;
        case _FIRST:  oled_write_ln(PSTR("FIRST"), false); break;
        case _SECOND: oled_write_ln(PSTR("SEC  "), false); break;
        default:      oled_write_ln(PSTR("UNK  "), false); break;
    }
}

static void render_wpm(void) {
    oled_write_ln(PSTR("WPM"), false);
    char wpm_str[4];
    snprintf(wpm_str, sizeof(wpm_str), "%03d", get_current_wpm());
    oled_write_ln(wpm_str, false);
}

static void render_caps_status(void) {
    oled_write(PSTR("CAPS"), false);
    oled_write_ln(PSTR(host_keyboard_led_state().caps_lock ? "+" : "-"), false);
}

static void render_num_status(void) {
    oled_write(PSTR("NUM"), false);
    oled_write_ln(PSTR(host_keyboard_led_state().num_lock ? "+" : "-"), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_clear();
        render_layer_state();
        oled_render_separator();
        render_caps_status();
        render_num_status();
        oled_render_separator();
        render_wpm();
    } else {
        render_logo();
    }
    return false;
}
#endif
