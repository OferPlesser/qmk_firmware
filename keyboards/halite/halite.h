#ifndef HALITE_H
#define HALITE_H

#include "quantum.h"

inline void halite_fn1_led_off(void) 	{ DDRB |= (1<<5); PORTB &= ~(1<<5); }
inline void halite_fn1_led_on(void) 	{ DDRB |= (1<<5); PORTB |= (1<<5); }
inline void halite_fn0_led_off(void) 	{ DDRF |= (1<<0); PORTF &= ~(1<<0); }
inline void halite_fn0_led_on(void) 	{ DDRF |= (1<<0); PORTF |= (1<<0); }

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, \
    k12, k13, k14, k15, k16, k17, k18, k19, k20, k22, k23, k24, \
    k25, k26, k27, k28, k29, k30, k31, k32, k33, k34, k35, k36, \
    		k37, k38, 					k49, k40 \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11 }, \
    { k12, k13, k14, k15, k16, k17, k18, k19, k20, k22, k23, k24 }, \
    { k25, k26, k27, k28, k29, k30, k31, k32, k33, k34, k35, k36, }, \
    { KC_NO, KC_NO, k37, k38, KC_NO, KC_NO, KC_NO, KC_NO, k39, k40, KC_NO, KC_NO } \
}

#endif
