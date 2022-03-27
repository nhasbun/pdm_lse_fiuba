/*
 * API_delay.h
 *
 *  Created on: 19-03-2022
 *      Author: nhasbun
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>  // For null usage
#include "stm32f4xx_hal.h"  // HAL_GetTick() usage

/*
 * Types used for non-blocking delay.
 */
typedef uint32_t tick_t;
typedef bool bool_t;

/*
 * Struct defines a non-blocking delay object.
 */
typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;


/*
 * Exported function prototypes for delay_t objects.
 */
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );

#endif /* API_INC_API_DELAY_H_ */
