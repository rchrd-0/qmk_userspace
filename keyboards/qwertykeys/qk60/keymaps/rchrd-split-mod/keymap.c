/*
Copyright 2022 Qwertykeys

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "keycodes.h"
#include QMK_KEYBOARD_H

enum custom_keycodes {
    RHYPR = SAFE_RANGE,
    RMEH,
    RHUH,
    SPC_LAYER,
    LT_TOGGLE_SPC,
};

static bool space_layer_enabled = true;
static uint16_t space_layer_timer = 0;
#define SPACE_LAYER_TIMEOUT 300

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* if (keycode == LT(1, KC_SPC)) { */
    /*     if (!layer_tap_spacebar_toggle) { */
    /*         if (record->event.pressed) { */
    /*             register_code(KC_SPC); */
    /*         } else { */
    /*             unregister_code(KC_SPC); */
    /*         } */
    /*         return false; */
    /*     } */
    /*     return true; */
    /* } */

    switch (keycode) {
        case SPC_LAYER:
            if (space_layer_enabled) {
                if (record->event.pressed) {
                    space_layer_timer = timer_read();
                    layer_on(1);
                } else {
                    layer_off(1);
                    if (timer_elapsed(space_layer_timer) < SPACE_LAYER_TIMEOUT) {
                        tap_code(KC_SPC);
                    }
                }
            } else {
                // Just a normal spacebar
                if (record->event.pressed) {
                    register_code(KC_SPC);
                } else {
                    unregister_code(KC_SPC);
                }
            }
            return false;
        case RHYPR:
            if (record->event.pressed) {
                register_code(KC_RCTL);
                register_code(KC_RSFT);
                register_code(KC_RALT);
                register_code(KC_RGUI);
            } else {
                unregister_code(KC_RCTL);
                unregister_code(KC_RSFT);
                unregister_code(KC_RALT);
                unregister_code(KC_RGUI);
            }
            return false;
        case RMEH:
            if (record->event.pressed) {
                register_code(KC_RCTL);
                register_code(KC_RSFT);
                register_code(KC_RALT);
            } else {
                unregister_code(KC_RCTL);
                unregister_code(KC_RSFT);
                unregister_code(KC_RALT);
            }
            return false;
        case RHUH:
            if (record->event.pressed) {
                register_code(KC_RGUI);
                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RGUI);
                unregister_code(KC_RSFT);
            }
            return false;
        case LT_TOGGLE_SPC:
            if (record->event.pressed) {
                space_layer_enabled = !space_layer_enabled;
            }
            return false;
    }
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_BSPC):
            return 130;
        case LT(1, KC_SPC):
            return 360;
        case MT(MOD_LCTL, KC_ESC):
            return TAPPING_TERM - 50;
        default:
            return TAPPING_TERM;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,     KC_5,    KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
		KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,     KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
		MT(MOD_LCTL, KC_ESC), KC_A,    KC_S,    KC_D,   KC_F,     KC_G,    KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(1),
		KC_LCTL, KC_LALT, KC_LGUI, KC_HYPR,          SPC_LAYER,  KC_SPC,  KC_SPC,    RHUH,   KC_RGUI, KC_RALT, KC_RCTL
	),
	[1] = LAYOUT(
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_DELETE,
		KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_UP, KC_END, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, NK_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_LEFT, KC_RIGHT, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, LT_TOGGLE_SPC, KC_TRNS
	)
};
