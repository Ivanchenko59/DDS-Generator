/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "printf.h"
#include "encoder.h"
#include "AD9833.h"
#include "st7735.h"
#include "fonts.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
Color_TypeDef text_color = {ST7735_WHITE, ST7735_BLACK, ST7735_BLACK, ST7735_YELLOW};
Selector_TypeDef Menu_Selector = Main_Menu;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t curr_time = 0;
uint32_t freq = 100;
int8_t edit_pos = 2;
int8_t waveform_select = 2;
int8_t encoder_status;
uint8_t button_status;
uint16_t MHz, kHz, Hz;
char Str_Buffer[10];
uint8_t short_press_flag = 0;
uint8_t hide_apply_flag = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  ST7735_Init();
  Encoder_Init();
  AD9833_Init(wave_sine, freq, 0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  ST7735_FillScreen(ST7735_BLACK);
  ST7735_FillRectangle(25, 70, 12, 2, ST7735_DARKGREY);
  ST7735_FillRectangle(49, 70, 35, 2, ST7735_DARKGREY);
  ST7735_FillRectangle(97, 70, 35, 2, ST7735_DARKGREY);
  ST7735_WriteString(10, 4, "AD9833 DDS GENERATOR", Font_7x10, ST7735_DARKGREY, ST7735_BLACK);
  ST7735_WriteString(21, 75, "MHz  kHz    Hz", Font_7x10, ST7735_DARKGREY, ST7735_BLACK);
  SineIcon(18, 92, ST7735_YELLOW);
  SquareIcon(63, 92, ST7735_LIGHTGREY);
  TriangleIcon(108, 92, ST7735_LIGHTGREY);

  MHz = freq / 1000000;
  kHz = freq / 1000 % 1000;
  Hz = freq % 1000;
  sprintf_(Str_Buffer, "%1d,%03d,%03d", MHz, kHz, Hz);

  while (1)
  {
	  //TODO: Stop counting Encoder Tim because its influences to position
	  button_status = Button_Get_Status();

	  switch(Menu_Selector) {
		  case Main_Menu:
			  ST7735_WriteString(25, 50, Str_Buffer, Font_12x18, ST7735_WHITE, ST7735_BLACK);
			  if((HAL_GetTick() - curr_time > APPLY_SHOW_TIME) && hide_apply_flag) {
				  ST7735_WriteString(30, 30, "               ", Font_7x10, ST7735_DARKGREY, ST7735_BLACK);
				  hide_apply_flag = 0;
			  }
			  if (button_status == Short_Press) Menu_Selector = Change_Frequency;
			  if (button_status == Long_Press) Menu_Selector = Change_Wave_Form;
			  break;

		  case Change_Wave_Form:
			  ST7735_WriteString(30, 30, "Change Waveform", Font_7x10, ST7735_DARKGREY, ST7735_BLACK);
			  ST7735_WriteString(25, 50, Str_Buffer, Font_12x18, ST7735_WHITE, ST7735_BLACK);
			  Change_Position(&waveform_select, MAX_WAVEFORM);
			  if (waveform_select == wave_sine) {
				  SineIcon(18, 92, ST7735_YELLOW);
				  SquareIcon(63, 92, ST7735_LIGHTGREY);
				  TriangleIcon(108, 92, ST7735_LIGHTGREY);
			  }
			  else if (waveform_select == wave_square) {
				  SineIcon(18, 92, ST7735_LIGHTGREY);
				  SquareIcon(63, 92, ST7735_YELLOW);
				  TriangleIcon(108, 92, ST7735_LIGHTGREY);
			  }
			  else if (waveform_select == wave_triangle) {
				  SineIcon(18, 92, ST7735_LIGHTGREY);
				  SquareIcon(63, 92, ST7735_LIGHTGREY);
				  TriangleIcon(108, 92, ST7735_YELLOW);
			  }

			  if (button_status == Short_Press) {
				  AD9833_SetWaveform(waveform_select);
				  Menu_Selector = Main_Menu;
				  ST7735_WriteString(30, 30, "    Apply!     ", Font_7x10, ST7735_DARKGREY, ST7735_BLACK);
				  hide_apply_flag = 1;
				  curr_time = HAL_GetTick();
			  }
			  if (button_status == Long_Press) {
//				  Menu_Selector = Main_Menu;
//				  or something else?
			  }
			  break;

		  case Change_Frequency:
			  ST7735_WriteString(30, 30, "Edit Frequency ", Font_7x10, ST7735_DARKGREY, ST7735_BLACK);
			  (short_press_flag) ? Edit_Frequency(edit_pos, &freq) : Change_Position(&edit_pos, MAX_DIGITS);

			  MHz = freq / 1000000;
			  kHz = freq / 1000 % 1000;
			  Hz = freq % 1000;

			  sprintf_(Str_Buffer, "%1d,%03d,%03d", MHz, kHz, Hz);
			  ST7735_WriteStringWithSelect(25, 50, Str_Buffer, Font_12x18, edit_pos, text_color);

			  if (button_status == Short_Press) {
				  short_press_flag = !short_press_flag;
			  }
			  if (button_status == Long_Press) {
				  AD9833_SetFrequency(freq);
				  ST7735_WriteString(30, 30, "    Apply!    ", Font_7x10, ST7735_DARKGREY, ST7735_BLACK);
				  hide_apply_flag = 1;
				  curr_time = HAL_GetTick();
				  Menu_Selector = Main_Menu;
				  short_press_flag = 0;
			  }
			  break;

		  case Sweep_Mode:
			  //TODO: Sweep

			  break;

		  default:
			  break;
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
  {
  }

  /* HSI configuration and activation */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_1, 8, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_Enable();
  LL_RCC_PLL_EnableDomain_SYS();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  }

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Sysclk activation on the main PLL */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(64000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void Edit_Frequency(int8_t position, uint32_t* const p_freq)
{
	uint32_t pos_to_Hz = int_pow(10, position);
	uint32_t edit_value = *p_freq / pos_to_Hz;

	switch(Encoder_Get_Status()) {
		  case Incremented:
			  edit_value++;
			  break;
		  case Decremented:
			  if(edit_value > 0)
				  edit_value--;
			  break;
		  case Neutral:
			  break;
	  }

	uint32_t edited_freq = edit_value * pos_to_Hz + *p_freq % pos_to_Hz;

	if (edited_freq <= MAX_FREQ_VALUE)
		*p_freq = edited_freq;
}

void Change_Position(int8_t* const edit_pos, uint8_t MAX_POS)
{
	switch(Encoder_Get_Status()) {
		case Incremented:
			(*edit_pos)--;
			if (*edit_pos < 0) *edit_pos = MAX_POS - 1;
			break;
		case Decremented:
			(*edit_pos)++;
			if (*edit_pos >= MAX_POS) *edit_pos = 0;
			break;
		case Neutral:
			break;
	}
}

uint32_t int_pow(uint32_t base, uint8_t exp)
{
    uint32_t result = 1;
    while (exp) {
        if (exp % 2)
           result *= base;
        exp /= 2;
        base *= base;
    }
    return result;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
