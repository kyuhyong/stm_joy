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
#define PB0_EXTI0_Pin GPIO_PIN_0
#define PB0_EXTI0_GPIO_Port GPIOB
#define PB0_EXTI0_EXTI_IRQn EXTI0_IRQn
#define PB1_EXTI1_Pin GPIO_PIN_1
#define PB1_EXTI1_GPIO_Port GPIOB
#define PB1_EXTI1_EXTI_IRQn EXTI1_IRQn
#define PB2_EXTI2_Pin GPIO_PIN_2
#define PB2_EXTI2_GPIO_Port GPIOB
#define PB2_EXTI2_EXTI_IRQn EXTI2_IRQn
#define PB3_EXTI3_Pin GPIO_PIN_3
#define PB3_EXTI3_GPIO_Port GPIOB
#define PB3_EXTI3_EXTI_IRQn EXTI3_IRQn
#define PB4_EXTI4_Pin GPIO_PIN_4
#define PB4_EXTI4_GPIO_Port GPIOB
#define PB4_EXTI4_EXTI_IRQn EXTI4_IRQn
#define PB5_EXTI5_Pin GPIO_PIN_5
#define PB5_EXTI5_GPIO_Port GPIOB
#define PB5_EXTI5_EXTI_IRQn EXTI9_5_IRQn
#define PB6_EXTI6_Pin GPIO_PIN_6
#define PB6_EXTI6_GPIO_Port GPIOB
#define PB6_EXTI6_EXTI_IRQn EXTI9_5_IRQn
#define PB7_EXTI7_Pin GPIO_PIN_7
#define PB7_EXTI7_GPIO_Port GPIOB
#define PB7_EXTI7_EXTI_IRQn EXTI9_5_IRQn
#define PB8_EXTI8_Pin GPIO_PIN_8
#define PB8_EXTI8_GPIO_Port GPIOB
#define PB8_EXTI8_EXTI_IRQn EXTI9_5_IRQn
#define PB9_EXTI9_Pin GPIO_PIN_9
#define PB9_EXTI9_GPIO_Port GPIOB
#define PB9_EXTI9_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
