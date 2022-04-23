/*
 * API_mag.h
 *
 *  Created on: 16-04-2022
 *      Author: nhasbun
 */

#ifndef API_INC_API_IIC_MAG_H_
#define API_INC_API_IIC_MAG_H_

#include <stdbool.h>


/**
 * Ping magnetometer MPU9250 device to check availability
 * @return true if present false otherwise
 */
bool ping_mag();


#endif /* API_INC_API_IIC_MAG_H_ */
