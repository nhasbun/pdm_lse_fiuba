/**
 * Module for i2c abstraction communication with MPU9250 9-axis IMU.
 *
 * We are interested only in magnetometer data acquisition here.
 */

#include "API_iic_mag.h"


static bool mag_available = false;


bool ping_mag() {
	// Mocking i2c connection for now
	// TODO implement i2c interface for nucleo f429zi board
	//      HAL_StatusTypeDef code = HAL_I2C_IsDeviceReady(&hi2c1, 0x29 << 1, 3, 500);
	//      if (code == HAL_OK) device is present.

	mag_available = !mag_available;
	return mag_available;
}
