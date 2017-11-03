#include "halite.h"


void matrix_init_kb(void) {
	// runs once when the firmware starts up
	matrix_init_user();
}

void matrix_scan_kb(void) {
	// runs every cycle (a lot)
	matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	// runs for every action, just before processing by the firmware

	return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
	led_set_user(usb_led);
}
