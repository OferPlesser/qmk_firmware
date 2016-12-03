#include "halite.h"
#include "action_layer.h"

#define XXXXXXX     KC_NO
#define _______     KC_TRNS

#define _QWERTY     0
#define _SYMBOLS    1
#define _NUMBERS    2
#define _META       3

#define KC_3_1      MT(MOD_LSFT, KC_BSPC)
#define KC_2_5      MT(MOD_LALT, KC_ENT)
#define KC_2_10     LT(1, KC_SLSH)
#define KC_0_5      M(0)

#define META_LAYER_TIMEOUT 3000

static uint8_t  number_layer_already_on = 0;
static uint8_t  meta_layer_already_on = 0;
static uint16_t key_timer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = { /* Base */
    { KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_0_5, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P },
    { KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_TAB, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN },
    { KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_2_5, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_2_10 },
    { XXXXXXX, KC_LCTL, KC_3_1, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  KC_RGUI, XXXXXXX }},

[_SYMBOLS] = {
    { KC_PGUP, KC_HOME,   KC_UP,  KC_END,  KC_INS, KC_ESC,  KC_EQL,  KC_LPRN, KC_LCBR, KC_LBRC, KC_QUOT },
    { KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, KC_PIPE, KC_PLUS, KC_RPRN, KC_RCBR, KC_RBRC, KC_DQUO },
    { KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_UNDS, _______ },
    { XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX }},

[_NUMBERS] = {
    { KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, _______, KC_PGUP, KC_7,    KC_8,    KC_9,    KC_ASTR },
    { KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_SLCK, _______, KC_PGDN, KC_4,    KC_5,    KC_6,    KC_PLUS },
    { KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PAUS, _______, KC_0,    KC_1,    KC_2,    KC_3,    KC_BSLS },
    { XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_DOT,  XXXXXXX }},

[_META] = {
    { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
    { _______, _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______ },
    { _______, _______, _______, _______, _______, BL_STEP, _______,    _______, _______, _______, _______ },
    { XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX }}
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        case 0:
            // This macro makes it so the fn1 key is 
            // both momentary and toggleable
            if (record->event.pressed) {
                key_timer = timer_read();
                if (!meta_layer_already_on) {
                    layer_on(_NUMBERS);
                }
            } else {
                if (number_layer_already_on) {
                    layer_off(_NUMBERS);
                    number_layer_already_on = 0;
                } else {
                    if (meta_layer_already_on) {
                        layer_off(_META);
                        breathing_disable();
                        halite_fn1_led_off();
                        halite_fn0_led_off();
                        meta_layer_already_on = 0;
                    } else if (timer_elapsed(key_timer) > META_LAYER_TIMEOUT) {
                        layer_off(_NUMBERS);
                        layer_on(_META);
                        breathing_enable();
                        halite_fn1_led_on();
                        halite_fn0_led_on();
                        meta_layer_already_on = 1;
                    } else {
                        number_layer_already_on = 1;
                    }
                }
            }
        break;
        case 1:
            if (record->event.pressed) {
            } else {
                breathing_toggle();
            }
    }
    return MACRO_NONE;
};


void matrix_init_user(void) {
}

void matrix_scan_user(void) {
    uint32_t layer = layer_state;

    if ((1 << _META) == layer) {
        return;
    }

    if ((1 << _NUMBERS) == layer) {
        halite_fn1_led_on();
    } else {
        halite_fn1_led_off();
    }

    if ((1 << _SYMBOLS) == layer) {
        halite_fn0_led_on();
    } else {
        halite_fn0_led_off();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint32_t layer = layer_state;

    // Now when releasing the function key, the macro will know
    // the function key was used a momentary switch and will disable the layer
    if (((1 << _NUMBERS) == layer) && (keycode != KC_0_5)) {
        number_layer_already_on = 1;
    }

    return true;
}

void led_set_user(uint8_t usb_led) {

}