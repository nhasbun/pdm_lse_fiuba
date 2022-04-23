/**
 * Module for detecting and debouncing user button actions under Nucleo-F429ZI
 * developer board.
 */

#include "mag_button.h"
#include "API_delay.h"
#include "stm32f4xx_nucleo_144.h"

#define DEFAULT_DELAY_T {0, 0, false}

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
	BUTTON_LONG_DOWN,
	BUTTON_LONG_RAISING
} debounceState_t;

// Parameters
static const tick_t debounce_valid_time = 40;
static const tick_t long_press_time = 3000;

// Private static variables
static delay_t debounce_timeout = DEFAULT_DELAY_T;
static delay_t long_press_timeout = DEFAULT_DELAY_T;
static debounceState_t button_state = BUTTON_UP;
static bool pressed_key = false;
static bool long_pressed_key = false;

// Private methods
static bool button_press_detected();

/**
 * Initialize debounce system.
 *
 * Configuring board for button input and setting initial state.
 */
void mag_debounce_button_init() {
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	button_state = BUTTON_UP;
}


/**
 * Continuously check for user input and apply a debounce filter based on time.
 *
 * Waits for 40ms before declaring a valid button state change and reporting key as pressed.
 *
 * Also checks if button was down for more than 5s for declaring a long press.
 */
void mag_btn_debounce_update() {

	switch (button_state) {

		case BUTTON_UP:
			if (button_press_detected()) {
				button_state = BUTTON_FALLING;
				delayInit(&debounce_timeout, debounce_valid_time);
			}

			break;

		case BUTTON_FALLING:
			if (!button_press_detected()) button_state = BUTTON_UP;

			else if (delayRead(&debounce_timeout)) {
				button_state = BUTTON_DOWN;
				delayInit(&long_press_timeout, long_press_time);
			}

			break;

		case BUTTON_DOWN:
			if (!button_press_detected()) {
				button_state = BUTTON_RAISING;
				delayInit(&debounce_timeout, debounce_valid_time);
			}

			if (delayRead(&long_press_timeout)) {
				button_state = BUTTON_LONG_DOWN;
				long_pressed_key = true;
			}

			break;

		case BUTTON_RAISING:
			if (button_press_detected()) button_state = BUTTON_DOWN;

			else if (delayRead(&debounce_timeout)) {
				button_state = BUTTON_UP;
				pressed_key = true;
			}

			break;

		case BUTTON_LONG_DOWN:
			if (!button_press_detected()) {
				button_state = BUTTON_LONG_RAISING;
				delayInit(&debounce_timeout, debounce_valid_time);
			}

			break;

		case BUTTON_LONG_RAISING:
			if (button_press_detected()) button_state = BUTTON_LONG_DOWN;

			else if (delayRead(&debounce_timeout)) {
				button_state = BUTTON_UP;
			}

		default:
			button_state = BUTTON_UP;
			break;
	}
}

/**
 * Checks for user button pressed after applying internal debounce filter.
 *
 * @return true if detected user button pressed, false otherwise
 */
bool read_btn_press() {
	bool pressed_key_old = pressed_key;
	pressed_key = false;
	return pressed_key_old;
}

/**
 * Checks for user button long press.
 *
 * @return true if detected user button long pressed, false otherwise
 */
bool read_long_press() {
	bool long_press_old = long_pressed_key;
	long_pressed_key = false;
	return long_press_old;
}

/**
 * First electrical detection of button pressed.
 *
 * @return A positive logic response of button reading, 1 when pressed
 * 		   and 0 when free.
 */
static bool button_press_detected() {
	return BSP_PB_GetState(BUTTON_USER);
}
