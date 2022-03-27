/*
 * API_delay.c
 *
 *  Created on: 19-03-2022
 *      Author: nhasbun
 */

#include "API_delay.h"

static const tick_t max_led_period = 10000;

/**
 * Initial configuration for non-blocking delay object.
 *
 * @param delay: some delay_t type instance
 * @param duration: desired delay duration/period in ms
 */
void delayInit( delay_t * delay, tick_t duration ) {
	delay->startTime = HAL_GetTick();
	delayWrite(delay, duration);
}

/**
 * Starts delay object.
 * If already started it checks for expired delay time.
 *
 * @param delay: some delay_t type instance
 * @return true if expired delay time else false
 */
bool_t delayRead( delay_t * delay ) {

	// Capturing null pointer error
	if (delay == NULL) {
		return false;
	}

	// Continuing regular routine
	if (delay->running == false) {
		delay->running = true;
		delay->startTime = HAL_GetTick();
		return false;
	}

	else {

		tick_t current_time = HAL_GetTick();

		if (current_time - delay->startTime > delay->duration) {
			delay->startTime = current_time;
			return true;
		}

		else return false;
	}
}

/**
 * Overrides delay duration for non-blocking delay object.
 *
 * @param delay: some delay_t type instance
 * @param duration: desired delay duration/period in ms
 */
void delayWrite( delay_t * delay, tick_t duration ) {

	// Capturing null pointer error
	if (delay == NULL) {
		return;
	}

	// Checking for max allowed period
	if (duration > max_led_period) {
		duration = max_led_period;
	}

	delay->duration = duration;
}
