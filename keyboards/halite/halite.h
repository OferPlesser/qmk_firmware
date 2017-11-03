#ifndef HALITE_H
#define HALITE_H

#include "quantum.h"

#define LED_INIT(led_pin) \
do { \
    _SFR_IO8((led_pin >> 4) + 1) |= _BV(led_pin & 0xF); \
    _SFR_IO8((led_pin >> 4) + 2) &= ~_BV(led_pin & 0xF); \
} while(0)

#define LED_ON(led_pin)     _SFR_IO8((led_pin >> 4) + 2) |= _BV(led_pin & 0xF)

#define LED_OFF(led_pin)    _SFR_IO8((led_pin >> 4) + 2) &= ~_BV(led_pin & 0xF)

#define LAYER_ON(layer)     ((1<<layer) & layer_state)

#define BIND_LED_TO_LAYER(led_pin, layer) \
do { \
    if (LAYER_ON(layer)) { \
         LED_ON(led_pin); \
    } else { \
        LED_OFF(led_pin); \
    } \
} while(0)

#endif
