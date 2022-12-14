/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include <stdio.h>
//#include <string.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/* USER CODE BEGIN EFP */
uint32_t int_pow(uint32_t base, uint8_t exp);
/*
 * @brief The function edits the value of the digit of the number by its position
 * The position is counted from right to left, that is,
 * from the least significant digit to the most significant
 * @param Position of the digit to be changed
 * @param Pointer to the number
 */
void Edit_Frequency(int8_t position, uint32_t *p_freq);

/*
 * @brief The function changes the value of the pointer to the
 * position using the rotary encoder. Used to select the position of the
 * digit of the frequency value and to select the type of waveform.
 * @param Pointer to the value of the variable that you want to change using the encoder
 * @param Maximum value of elements (for selection looping)
 */
void Change_Position(int8_t *edit_pos, uint8_t MAX_POS);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define AD9833_SCK_Pin GPIO_PIN_8
#define AD9833_SCK_GPIO_Port GPIOB
#define ST7735_RES_Pin GPIO_PIN_0
#define ST7735_RES_GPIO_Port GPIOA
#define ST7735_SCK_Pin GPIO_PIN_1
#define ST7735_SCK_GPIO_Port GPIOA
#define ST7735_SDA_Pin GPIO_PIN_2
#define ST7735_SDA_GPIO_Port GPIOA
#define ST7735_DC_Pin GPIO_PIN_3
#define ST7735_DC_GPIO_Port GPIOA
#define AD9833_DAT_Pin GPIO_PIN_4
#define AD9833_DAT_GPIO_Port GPIOA
#define AD9833_FSYNC_Pin GPIO_PIN_5
#define AD9833_FSYNC_GPIO_Port GPIOA
#define ENC_S1_Pin GPIO_PIN_6
#define ENC_S1_GPIO_Port GPIOA
#define ENC_S2_Pin GPIO_PIN_7
#define ENC_S2_GPIO_Port GPIOA
#define ENC_BTN_Pin GPIO_PIN_0
#define ENC_BTN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

#define MAX_FREQ_VALUE 5000000
#define MAX_DIGITS 7
#define MAX_WAVEFORM 3
#define APPLY_SHOW_TIME 1000

typedef enum {
	Main_Menu,
	Change_Wave_Form,
	Change_Frequency,
	Sweep_Mode,
} Selector_TypeDef;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
