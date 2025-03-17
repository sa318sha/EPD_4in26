/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32wbxx_hal.h"
#include "stm32wbxx_nucleo.h"
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
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
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Button_1_Pin GPIO_PIN_0
#define Button_1_GPIO_Port GPIOC
#define Button_1_EXTI_IRQn EXTI0_IRQn
#define Button_2_Pin GPIO_PIN_1
#define Button_2_GPIO_Port GPIOC
#define Button_2_EXTI_IRQn EXTI1_IRQn
#define Button_3_Pin GPIO_PIN_2
#define Button_3_GPIO_Port GPIOC
#define Button_3_EXTI_IRQn EXTI2_IRQn
#define Button_4_Pin GPIO_PIN_3
#define Button_4_GPIO_Port GPIOC
#define Button_4_EXTI_IRQn EXTI3_IRQn

/* USER CODE BEGIN Private defines */
#define EPD_4in26_WIDTH 800
#define EPD_4in26_HEIGHT 480

#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

#define RTOS 1
//#define Debug(__info,...) printf("Debug : " __info,##__VA_ARGS__)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
