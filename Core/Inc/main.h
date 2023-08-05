/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
void TIM4_ISR(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED0_Pin GPIO_PIN_13
#define LED0_GPIO_Port GPIOC
#define S12_Pin GPIO_PIN_5
#define S12_GPIO_Port GPIOA
#define S13_Pin GPIO_PIN_6
#define S13_GPIO_Port GPIOA
#define S14_Pin GPIO_PIN_7
#define S14_GPIO_Port GPIOA
#define S2_Pin GPIO_PIN_0
#define S2_GPIO_Port GPIOB
#define S5_Pin GPIO_PIN_1
#define S5_GPIO_Port GPIOB
#define S3_Pin GPIO_PIN_10
#define S3_GPIO_Port GPIOB
#define S4_Pin GPIO_PIN_11
#define S4_GPIO_Port GPIOB
#define S15_Pin GPIO_PIN_12
#define S15_GPIO_Port GPIOB
#define S16_Pin GPIO_PIN_13
#define S16_GPIO_Port GPIOB
#define S17_Pin GPIO_PIN_14
#define S17_GPIO_Port GPIOB
#define S18_Pin GPIO_PIN_15
#define S18_GPIO_Port GPIOB
#define S6_Pin GPIO_PIN_3
#define S6_GPIO_Port GPIOB
#define S7_Pin GPIO_PIN_4
#define S7_GPIO_Port GPIOB
#define S8_Pin GPIO_PIN_5
#define S8_GPIO_Port GPIOB
#define S9_Pin GPIO_PIN_6
#define S9_GPIO_Port GPIOB
#define S10_Pin GPIO_PIN_7
#define S10_GPIO_Port GPIOB
#define S11_Pin GPIO_PIN_8
#define S11_GPIO_Port GPIOB
#define S1_Pin GPIO_PIN_9
#define S1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
