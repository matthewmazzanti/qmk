#include QMK_KEYBOARD_H

enum layers {
	QWE=0,
	DVK,
	GAM,
	MOD,
	SYM,
	NUM,
	ETC
};

enum custom_keycodes {
	MK_ENCR=SAFE_RANGE,
};

enum encoder_states {
	NOOP=0,
	MAP_BASE,
	MAP_MODS,
};

uint8_t encoder_right = NOOP;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[QWE] = LAYOUT(

KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,     KC_DEL,
KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN,  KC_ENT,
KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    TG(DVK), TG(GAM),    KC_3,    KC_4,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH,  KC_BSPC,
                           KC_A,    KC_LALT, KC_LGUI, KC_LCTL, KC_LALT,    MO(NUM), MO(SYM), KC_SPC,  MO(ETC), MK_ENCR
), [DVK] = LAYOUT(

_______, KC_DQUO, KC_COMM, KC_DOT,  KC_P,    KC_Y,                                           KC_F,    KC_G,    KC_C,    KC_R,   KC_L,     KC_DEL,
_______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                                           KC_D,    KC_H,    KC_T,    KC_N,   KC_S,     KC_ENT,
_______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    _______, _______,    _______, _______, KC_B,    KC_M,    KC_W,    KC_V,   KC_Z,     KC_BSPC,
                           _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______

), [GAM] = LAYOUT(

_______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
                           KC_F1,   KC_LALT, KC_SPC,  KC_LCTL, KC_F2,      _______, _______, _______, _______, _______

), [SYM] = LAYOUT(

_______, KC_GRV,  KC_PERC, KC_AT,   KC_HASH, KC_CIRC,                                        KC_DLR,  KC_UNDS, KC_PMNS, KC_PPLS, _______, _______,
_______, KC_QUOT, KC_LT,   KC_LPRN, KC_LCBR, KC_LBRC,                                        KC_RBRC, KC_RCBR, KC_RPRN, KC_GT,   KC_DQUO, _______,
_______, KC_BSLS, KC_TILD, KC_PSLS, KC_PAST, KC_PIPE, _______, _______,    KC_PGUP, KC_PGDN, KC_AMPR, KC_EXLM, KC_COMM, KC_DOT,  KC_EQL,  _______,
                           _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______

), [NUM] = LAYOUT(

_______, KC_GRV,  KC_PERC, KC_AT,   KC_HASH, KC_CIRC,                                        KC_DLR,  KC_UNDS, KC_PMNS, KC_PPLS, _______, _______,
_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
_______, KC_BSLS, KC_TILD, KC_PSLS, KC_PAST, KC_PIPE, _______, _______,    KC_NLCK, _______, KC_AMPR, KC_EXLM, KC_COMM, KC_DOT,  KC_EQL,  _______,
                           _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______

), [ETC] = LAYOUT (

_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
_______, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT,                                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
_______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  _______, _______,    _______, _______, KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
                           _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______

)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case MK_ENCR:
			if (record->event.pressed) {
				if (encoder_right == NOOP) {
					encoder_right = MAP_BASE;
				} else if (encoder_right == MAP_BASE) {
					encoder_right = MAP_MODS;
				} else {
					encoder_right = NOOP;
				}
			}
			return false;
		default:
			return true;
	}
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
	// QMK Logo and version information
	render_qmk_logo();

	// Host Keyboard Layer Status
	switch (get_highest_layer(layer_state)) {
		case SYM:
			oled_write_P(PSTR("SYMBOL "), false);
			break;
		case NUM:
			oled_write_P(PSTR("NUMBER "), false);
			break;
		case ETC:
			oled_write_P(PSTR("ETC    "), false);
			break;
		default:
			// Sym, Num, Etc all take precedence
			if (layer_state_is(DVK)) {
				oled_write_P(PSTR("DVORAK "), false);
			} else {
				oled_write_P(PSTR("QWERTY "), false);
			}
			break;
	}

	if (layer_state_is(GAM)) {
		oled_write_P(PSTR("GAMING\n"), false);
	} else {
		oled_write_P(PSTR("NORMAL\n"), false);
	}

	switch (encoder_right) {
		case NOOP:
			oled_write_P(PSTR("       \n"), false);
			break;
		case MAP_BASE:
			oled_write_P(PSTR("MAP BASE\n"), false);
			break;
		case MAP_MODS:
			oled_write_P(PSTR("MAP MODS\n"), false);
			break;
		default:
			oled_write_P(PSTR("Undefined\n"), false);
	}
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
    } else {
        render_kyria_logo();
    }
}
#endif

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
	if (index == 0) {
                if (clockwise) {
                    tap_code16(KC_LEFT);
                } else {
                    tap_code16(KC_RGHT);
                }
	} else if (index == 1) {
		switch (encoder_right) {
			case MAP_BASE:
				layer_invert(DVK);
				break;
			case MAP_MODS:
				layer_invert(GAM);
				break;
			default:
				if (clockwise) {
				    tap_code16(KC_UP);
				} else {
				    tap_code16(KC_DOWN);
				}
				break;
		}
	}
}
#endif
