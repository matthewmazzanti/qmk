/* Copyright 2019 Thomas Baart
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define LAYOUT_ortho_3x4( \
	k00, k01, k02, k03, \
	k04, k05, k06, k07, \
	k08, k09, k10, k11  \
) { \
	{k08, k04, k00}, \
	{k09, k05, k01}, \
	{k10, k06, k02}, \
	{k11, k07, k03} \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_3x4( /* Base */
		KC_Q, KC_W, KC_E, KC_O,
		KC_F, KC_G, KC_K, KC_L,
		KC_X, KC_C, KC_COMM, KC_DOT
	),
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_90;
}


void oled_task_user(void) {
	oled_write_P(PSTR("abcdefghijklmnopqrstuvwxyz"), false);
}
#endif

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code16(KC_A);
    } else {
        tap_code16(KC_V);
    }
}
#endif
