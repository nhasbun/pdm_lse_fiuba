/*
 * mag_fsm.h
 *
 *  Created on: 09-04-2022
 *      Author: nhasbun
 */

#ifndef API_INC_MAG_FSM_H_
#define API_INC_MAG_FSM_H_

#include <stdbool.h>

/**
 * Possible states for magnetometer.
 */
typedef enum {
	IDLE,                // when starts or no communication with magnetometer
	WORKING_NO_CALIB,    // working without calibration
	WORKING_WITH_CALIB,  // working with calibration
	FULL_CALIB           // full calibration taking place
} mag_state_t;

/**
 * Starting magnetometer FSM.
 */
void mag_fsm_init();

/**
 * @brief Keep FSM updated
 *
 * Internally looks for calibration timeout and checks last information about
 * reported external info (like i2c communication status, user button long press
 * or calibration percentage status).
 */
void mag_fsm_update();

/**
 * @brief reports to FSM about magnetometer communications
 * @param com_available true when communication with magnetometer is present
 * 		  else false.
 */
void report_mag_com(bool com_available);

/**
 * Reports to FSM about long press button user action.
 */
void report_long_press();

/**
 * Reports calculated calibration percentage for magnetometer
 * @param pct float from 0.0f to 1.0f representing 0-100% calibration. Out of
 * 		  range numbers will be capped.
 */
void report_calibration_pct(float pct);

/**
 * Exposing magnetometer state
 * @return Actual magnetometer FSM state
 */
mag_state_t get_mag_state();

#endif /* API_INC_MAG_FSM_H_ */
