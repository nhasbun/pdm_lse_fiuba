/*
 * API_debounce.h
 *
 *  Created on: 26-03-2022
 *      Author: nhasbun
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "API_delay.h"
#include "stm32f4xx_nucleo_144.h"

void debounceFSM_init();
void debounceFSM_update();
bool_t readKey();


#endif /* API_INC_API_DEBOUNCE_H_ */
