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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY1_Pin GPIO_PIN_3
#define KEY1_GPIO_Port GPIOE
#define KEY0_Pin GPIO_PIN_4
#define KEY0_GPIO_Port GPIOE
#define ROW3_Pin GPIO_PIN_3
#define ROW3_GPIO_Port GPIOC
#define WK_UP_Pin GPIO_PIN_0
#define WK_UP_GPIO_Port GPIOA
#define LED0_Pin GPIO_PIN_4
#define LED0_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_5
#define LED1_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_6
#define LED2_GPIO_Port GPIOA
#define ROW2_Pin GPIO_PIN_7
#define ROW2_GPIO_Port GPIOA
#define ROW1_Pin GPIO_PIN_5
#define ROW1_GPIO_Port GPIOC
#define LCD_BL_Pin GPIO_PIN_0
#define LCD_BL_GPIO_Port GPIOB
#define ROW0_Pin GPIO_PIN_1
#define ROW0_GPIO_Port GPIOB
#define COL3_Pin GPIO_PIN_11
#define COL3_GPIO_Port GPIOF
#define COL2_Pin GPIO_PIN_13
#define COL2_GPIO_Port GPIOF
#define COL1_Pin GPIO_PIN_15
#define COL1_GPIO_Port GPIOF
#define LCD_RS_Pin GPIO_PIN_0
#define LCD_RS_GPIO_Port GPIOG
#define COL0_Pin GPIO_PIN_1
#define COL0_GPIO_Port GPIOG
#define LCD_RD_Pin GPIO_PIN_4
#define LCD_RD_GPIO_Port GPIOD
#define LCD_WR_Pin GPIO_PIN_5
#define LCD_WR_GPIO_Port GPIOD
#define LCD_CS_Pin GPIO_PIN_12
#define LCD_CS_GPIO_Port GPIOG
#define BEEP_Pin GPIO_PIN_8
#define BEEP_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
