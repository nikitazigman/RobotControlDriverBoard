/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define cooler_en_Pin GPIO_PIN_13
#define cooler_en_GPIO_Port GPIOC
#define encoder_pr_ch2_Pin GPIO_PIN_1
#define encoder_pr_ch2_GPIO_Port GPIOA
#define encoder_pr_ch1_Pin GPIO_PIN_5
#define encoder_pr_ch1_GPIO_Port GPIOA
#define encoder_st_ch1_Pin GPIO_PIN_6
#define encoder_st_ch1_GPIO_Port GPIOA
#define encoder_st_ch2_Pin GPIO_PIN_7
#define encoder_st_ch2_GPIO_Port GPIOA
#define temp_propulsion_Pin GPIO_PIN_8
#define temp_propulsion_GPIO_Port GPIOC
#define temp_steering_Pin GPIO_PIN_9
#define temp_steering_GPIO_Port GPIOC
#define emergency_btn_Pin GPIO_PIN_8
#define emergency_btn_GPIO_Port GPIOA
#define COM_TX_Pin GPIO_PIN_9
#define COM_TX_GPIO_Port GPIOA
#define COM_RX_Pin GPIO_PIN_10
#define COM_RX_GPIO_Port GPIOA
#define propulsion_forward_enable_Pin GPIO_PIN_12
#define propulsion_forward_enable_GPIO_Port GPIOC
#define propulsion_is_Pin GPIO_PIN_3
#define propulsion_is_GPIO_Port GPIOB
#define propulsion_backward_enable_Pin GPIO_PIN_4
#define propulsion_backward_enable_GPIO_Port GPIOB
#define steering_forward_enable_Pin GPIO_PIN_5
#define steering_forward_enable_GPIO_Port GPIOB
#define propulsion_PWM_Pin GPIO_PIN_6
#define propulsion_PWM_GPIO_Port GPIOB
#define steering_PWM_Pin GPIO_PIN_7
#define steering_PWM_GPIO_Port GPIOB
#define steering_is_Pin GPIO_PIN_8
#define steering_is_GPIO_Port GPIOB
#define steering_backward_enable_Pin GPIO_PIN_9
#define steering_backward_enable_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
