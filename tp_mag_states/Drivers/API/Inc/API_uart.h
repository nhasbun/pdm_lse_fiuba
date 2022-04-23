/*
 * API_uart.h
 *
 *  Created on: 02-04-2022
 *      Author: nhasbun
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "stm32f4xx_nucleo_144.h"
#include "stm32f4xx_hal_uart.h"

typedef bool bool_t;

#define println(str1) uartsendString((uint8_t *) str1 "\r\n")

bool_t uartinit();
void uartsendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

#endif /* API_INC_API_UART_H_ */
