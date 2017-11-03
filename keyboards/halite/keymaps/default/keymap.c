#include "halite.h"

#define XXXXXXX     KC_NO
#define _______     KC_TRNS

/*** LAYERS ***/

#define _QWERTY     0
#define _SYMBOLS    1
#define _NUMBERS    2
#define _META       3

/*** ACTIONS ***/

#define SFT_TAB     MT(MOD_LSFT, KC_TAB)
#define SFTNTAB     LSFT(KC_TAB)
#define ENT_ALT     MT(MOD_LALT, KC_ENT)
#define GUI_DOT     MT(MOD_LGUI, KC_PDOT)
#define MS_ON       M(0)
#define MS_OFF      M(1)

/*** LEDS ***/

#define FN_0_LED    F0
#define FN_1_LED    B5

/*** META ***/

#define EXIT_MT     TO(_QWERTY)
#define META_LAYER_COMBO_INDEX  0

/*** TAP DANCE ***/

#define BRCS        TD(TD_SQUARE_BRACKETS)
#define CBRCS       TD(TD_CURLY_BRACKETS)
#define PARENS      TD(TD_PARENTHESES)
#define CHEVRS      TD(TD_CHEVRONS)
#define QUOTS       TD(TD_QUOTES)

enum {
    TD_SQUARE_BRACKETS,
    TD_CURLY_BRACKETS,
    TD_PARENTHESES,
    TD_CHEVRONS,
    TD_QUOTES,
};


/*** KEYMAPS ***/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = { /* Base */
    { KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_FN1,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P    },
    { KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    SFT_TAB, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN },
    { KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    ENT_ALT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_FN0  },
    { XXXXXXX, KC_LCTL, KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  KC_RGUI, XXXXXXX }},

[_SYMBOLS] = {
    { KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_INS,  KC_ESC,  QUOTS,   PARENS,  CBRCS,   BRCS,    CHEVRS  },
    { KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,  _______, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,  KC_PIPE },
    { KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_QUES, _______ },
    { XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX }},

[_NUMBERS] = {
    { KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, _______, KC_PAST, KC_P7,   KC_P8,   KC_P9,    KC_PMNS },
    { KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_SLCK, SFTNTAB, KC_PSLS, KC_P4,   KC_P5,   KC_P6,    KC_PPLS },
    { KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PAUS, _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,    KC_BSLS },
    { XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, GUI_DOT,  XXXXXXX }},

[_META] = {
    { BL_TOGG, MS_ON,   XXXXXXX, XXXXXXX, XXXXXXX, EXIT_MT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX },
    { BL_INC,  MS_OFF,  XXXXXXX, XXXXXXX, XXXXXXX, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX },
    { BL_DEC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX },
    { XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX }}
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_TAP_KEY(_SYMBOLS, KC_SLSH),
    [1] = ACTION_LAYER_TAP_TOGGLE(_NUMBERS),
};


qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SQUARE_BRACKETS] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
    [TD_CURLY_BRACKETS]  = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
    [TD_PARENTHESES]     = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
    [TD_CHEVRONS]        = ACTION_TAP_DANCE_DOUBLE(KC_LABK, KC_RABK),
    [TD_QUOTES]          = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
};

void matrix_init_user(void) {
    LED_INIT(B5);
    LED_INIT(F0);
}    

void matrix_scan_user(void) {
    if (LAYER_ON(_META)) {
        LED_ON(FN_1_LED);
        LED_ON(FN_0_LED);
        return;
    }

    BIND_LED_TO_LAYER(FN_1_LED, _NUMBERS);
    BIND_LED_TO_LAYER(FN_0_LED, _SYMBOLS);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void led_set_user(uint8_t usb_led) {

}