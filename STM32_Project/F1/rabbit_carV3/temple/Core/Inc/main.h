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
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define Encoder_Right_A_Pin GPIO_PIN_0
#define Encoder_Right_A_GPIO_Port GPIOA
#define Encoder_Right_B_Pin GPIO_PIN_1
#define Encoder_Right_B_GPIO_Port GPIOA
#define HW_OUT_1_Pin GPIO_PIN_5
#define HW_OUT_1_GPIO_Port GPIOA
#define HW_OUT_2_Pin GPIO_PIN_7
#define HW_OUT_2_GPIO_Port GPIOA
#define HW_OUT_3_Pin GPIO_PIN_0
#define HW_OUT_3_GPIO_Port GPIOB
#define HW_OUT_4_Pin GPIO_PIN_1
#define HW_OUT_4_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_12
#define OLED_SDA_GPIO_Port GPIOB
#define Motor_AIN1_Pin GPIO_PIN_13
#define Motor_AIN1_GPIO_Port GPIOB
#define Relay_Right_Pin GPIO_PIN_14
#define Relay_Right_GPIO_Port GPIOB
#define Motor_PWMB_Pin GPIO_PIN_8
#define Motor_PWMB_GPIO_Port GPIOA
#define Motor_PWMA_Pin GPIO_PIN_11
#define Motor_PWMA_GPIO_Port GPIOA
#define KEY2_Pin GPIO_PIN_12
#define KEY2_GPIO_Port GPIOA
#define OLED_SCL_Pin GPIO_PIN_15
#define OLED_SCL_GPIO_Port GPIOA
#define Motor_BIN1_Pin GPIO_PIN_3
#define Motor_BIN1_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_4
#define KEY1_GPIO_Port GPIOB
#define Relay_White_Pin GPIO_PIN_5
#define Relay_White_GPIO_Port GPIOB
#define Encoder_Left_A_Pin GPIO_PIN_6
#define Encoder_Left_A_GPIO_Port GPIOB
#define Encoder_Left_B_Pin GPIO_PIN_7
#define Encoder_Left_B_GPIO_Port GPIOB
#define Relay_Yellow_Pin GPIO_PIN_8
#define Relay_Yellow_GPIO_Port GPIOB
#define Relay_Left_Pin GPIO_PIN_9
#define Relay_Left_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
