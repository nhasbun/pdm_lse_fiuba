/*
 * API_uart.c
 *
 * Wrapper module for easy send/receive uart messages.
 *
 *  Created on: 02-04-2022
 *      Author: nhasbun
 */

#include "API_uart.h"

#define BAUDRATE 9600
#define break_line(str1) #str1 "\r\n"

static UART_HandleTypeDef UartHandle;

/**
 * Initializes UART configuration.
 *
 * @return true if start is successful false otherwise.
 */
bool_t uartinit() {
	UartHandle.Instance        = USART3;

	UartHandle.Init.BaudRate   = BAUDRATE;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = UART_PARITY_ODD;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode       = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&UartHandle) != HAL_OK)
	{
		return false;

	} else {

		char baudrate_str[8] = "";
		char init_msg[50] = "";
		char break_line[] = "\r\n";

		sprintf(baudrate_str, "%d", BAUDRATE);

		strcat(init_msg, "\n\n\nStarting UART with baudrate: ");
		strcat(init_msg, baudrate_str);
		strcat(init_msg, break_line);

		uartsendString((uint8_t*)init_msg);

		return true;
	}
}

/**
 * Sends a standard C string.
 *
 * @param pstring A C string (must include a NUL terminator \0).
 */
void uartsendString(uint8_t * pstring) {

	if (pstring == NULL) return;

	uint16_t char_count = 0;
	uint8_t * pstring_start = pstring;

	for(;;) {
		if (*pstring == '\0'){
			break;
		}

		pstring++;
		char_count++;
	}

	uartSendStringSize(pstring_start, char_count);
}

/**
 * Sends a substring from original string with pre-defined size.
 *
 * @param pstring Original full C string
 * @param size Amount of characters to send
 */
void uartSendStringSize(uint8_t * pstring, uint16_t size) {

	if (pstring == NULL) return;
	if (size == 0) return;

	HAL_UART_Transmit(&UartHandle, pstring, size, 0xFFFF);
}
