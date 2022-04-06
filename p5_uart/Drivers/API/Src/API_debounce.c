/**
 * Module for detecting and debouncing user button actions under Nucleo-F429ZI
 * developer board.
 */

#include "API_debounce.h"
#include "API_uart.h"

#define DEFAULT_DELAY_T {0, 0, false}

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

// Parameters
static const tick_t debounce_valid_time = 40;

// Private static variables
static delay_t debounce_timeout = DEFAULT_DELAY_T;
static debounceState_t button_state = BUTTON_UP;
static bool_t pressed_key = false;


/**
 * Initialize debounce system.
 *
 * Configuring board for button input and setting initial state.
 */
void debounceFSM_init() {
	// Enabling the user button
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	button_state = BUTTON_UP;
}


/**
 * Continuously check for user input and apply a debounce filter based on time.
 *
 * Waits for 40ms before declaring a valid button state change and reporting key as pressed.
 */
void debounceFSM_update() {
	// button value works with positive logic, 1 when pressed 0 when released.
	uint8_t button_value = BSP_PB_GetState(BUTTON_USER) ? 0 : 1;

	switch (button_state) {

		case BUTTON_UP:
			if (button_value == 0) {
				button_state = BUTTON_FALLING;
				uartsendString((uint8_t*) "button falling\r\n");
				delayInit(&debounce_timeout, debounce_valid_time);
			}
			else button_state = BUTTON_UP;
			break;

		case BUTTON_FALLING:
			if (button_value == 1) button_state = BUTTON_UP;
			else if (delayRead(&debounce_timeout)) {
				button_state = BUTTON_DOWN;
				pressed_key = true;
			}
			break;

		case BUTTON_DOWN:
			if (button_value == 0) button_state = BUTTON_DOWN;
			else {
				button_state = BUTTON_RAISING;
				uartsendString((uint8_t*) "button raising\r\n");
				delayInit(&debounce_timeout, debounce_valid_time);
			}
			break;

		case BUTTON_RAISING:
			if (button_value == 0) button_state = BUTTON_DOWN;
			else if (delayRead(&debounce_timeout)) button_state = BUTTON_UP;

			break;

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
bool_t readKey() {
	bool_t pressed_key_old = pressed_key;
	pressed_key = false;
	return pressed_key_old;
}
