/*
 * API_debounce.h
 *
 *  Created on: 26-03-2022
 *      Author: nhasbun
 */

#ifndef API_INC_MAG_BUTTON_H_
#define API_INC_MAG_BUTTON_H_

#include <stdbool.h>

void mag_debounce_button_init();
void mag_btn_debounce_update();
bool read_btn_press();
bool read_long_press();


#endif /* API_INC_MAG_BUTTON_H_ */
