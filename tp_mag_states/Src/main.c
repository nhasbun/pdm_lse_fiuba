/* Includes ------------------------------------------------------------------*/
#include <mag_button.h>
#include "main.h"
#include "API_uart.h"
#include "API_delay.h"
#include "API_led.h"
#include "API_iic_mag.h"
#include "mag_fsm.h"


/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);
static void mock_mag_calib_pct();

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  HAL_Init();
  SystemClock_Config();

  // Enabling all LEDs
  led_init();

  // Enabling the user button
  mag_debounce_button_init();

  // Enabling UART
  uartinit();

  // Enabling magnetometer state
  mag_fsm_init();

  while (1)
  {
	  mag_btn_debounce_update();
	  mag_fsm_update();

	  if (read_btn_press()) {
		  println("button press");

	  	  // Mock mag calibration pct
	  	  if (get_mag_state() == FULL_CALIB) mock_mag_calib_pct();
	  	  else report_mag_com(ping_mag());
	  }

	  if (read_long_press()) {
		  println("long button press");
	  	  report_long_press();
	  }

	  switch (get_mag_state()) {

	  	  case IDLE:
	  		  led_r();
 	  		  break;

	  	  case WORKING_NO_CALIB:
	  		  led_g();
	  		  break;

	  	  case FULL_CALIB:
	  		  blink_led_g();

	  		  break;

	  	  case WORKING_WITH_CALIB:
	  		  led_b();
	  		  break;

	  	  default:
	  		  break;
	  }
  }
}

/**
 * @brief Mocking calculated calibration percentage
 *
 * Given that we currently don't have i2c connectivity neither calibration
 * algorithm we are mocking fake calculated calibration percentages of compass
 * subsystem.
 *
 * TODO review function when i2c is implemented
 * TODO remove function when calibration algorithm is implemented
 */
static void mock_mag_calib_pct() {
	const uint8_t len_values = 3;
	const float calib_pct[] = {0.1f, 0.91f, 0.995f};

	static uint8_t index = 0;

	char buf[2] = "";
	sprintf(buf, "%d", index);
	char msg[30] = "Reporting mock mag calib: ";
	char break_line[] = "\r\n";
	strcat(msg, buf);
	strcat(msg, break_line);
	uartsendString((uint8_t*)msg);

	report_calibration_pct(calib_pct[index]);
	index++;
	if (index == len_values) index = 0;
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED2);
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
