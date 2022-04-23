/**
 * API Led for Nucleo F429ZI.
 */

#include "API_led.h"
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include "API_delay.h"


// Parameters
static const tick_t blink_period = 250;


// File scope variables
static delay_t blink_delay = {0};


void led_init() {
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);

	delayInit(&blink_delay, blink_period);
}

void leds_off() {
	BSP_LED_Off(LED1);
	BSP_LED_Off(LED2);
	BSP_LED_Off(LED3);
}

void led_r() {
	BSP_LED_Off(LED1);
	BSP_LED_Off(LED2);
	BSP_LED_On(LED3);
}

void led_g() {
	BSP_LED_On(LED1);
	BSP_LED_Off(LED2);
	BSP_LED_Off(LED3);
}

void led_b() {
	BSP_LED_Off(LED1);
	BSP_LED_On(LED2);
	BSP_LED_Off(LED3);
}

void blink_led_g() {
	BSP_LED_Off(LED2);
	BSP_LED_Off(LED3);

	if (delayRead(&blink_delay))
		BSP_LED_Toggle(LED1);
}


