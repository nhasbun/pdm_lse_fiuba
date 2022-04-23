/*
 * mag_fsm.c
 *
 *  Created on: 22-04-2022
 *      Author: nhasbun
 */

#include <stdio.h>
#include "mag_fsm.h"
#include "API_delay.h"
#include "API_uart.h"

// Parameters
#define DEFAULT_DELAY_T {0, 0, false}
static const tick_t calibration_max_time = 20000;

// File scope variables
static mag_state_t mag_state = 0;
static bool magnetometer_alive = false;
static bool button_long_press_flag = false;
static float calibration_pct = 0.0f;
static delay_t calibration_timeout = DEFAULT_DELAY_T;

// Private functions
static void set_idle();
static void set_no_calib();
static void set_full_calib();
static void set_calibrated();


void mag_fsm_init() {
	set_idle();
}

void mag_fsm_update() {

	switch(mag_state) {

		case IDLE:
			if (magnetometer_alive) set_no_calib();
			button_long_press_flag = false;
			calibration_pct = 0.0f;
			break;

		case WORKING_NO_CALIB:
			if (!magnetometer_alive) set_idle();

			else if (button_long_press_flag) {
				set_full_calib();
				delayInit(&calibration_timeout, calibration_max_time);
				button_long_press_flag = false;
			}
			else if (calibration_pct >= 0.9f) set_calibrated();
			break;

		case FULL_CALIB:
			if (!magnetometer_alive) set_idle();

			else if (calibration_pct >= 0.99f) set_calibrated();
			else if (delayRead(&calibration_timeout)) {

				if (calibration_pct < 0.9f) set_no_calib();
				else set_calibrated();
			}

			break;

		case WORKING_WITH_CALIB:
			if (!magnetometer_alive) set_idle();

			else if (calibration_pct < 0.9f) set_no_calib();

			button_long_press_flag = false;

			break;

		default:
			set_idle();
			break;
	}
}

void report_mag_com(bool com_available) {
	magnetometer_alive = com_available;
}

void report_long_press() {
	button_long_press_flag = true;
}

void report_calibration_pct(float pct) {
	if (pct < 0.0f) pct = 0.0f;
	if (pct > 1.0f) pct = 1.0f;

	calibration_pct = pct;
}

mag_state_t get_mag_state() {
	return mag_state;
}

static void set_idle() {
	mag_state = IDLE;
	println("Magnetometer state IDLE");
}

static void set_no_calib() {
	mag_state = WORKING_NO_CALIB;
	println("Magnetometer state WORKING_NO_CALIB");
}

static void set_full_calib() {
	mag_state = FULL_CALIB;
	println("Magnetometer FULL CALIBRATION in place");
}

static void set_calibrated() {
	mag_state = WORKING_WITH_CALIB;
	println("Magnetometer state WORKING_WITH_CALIB");
}

