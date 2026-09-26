/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Mehdi_Image.h"
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
#define T_CS_RST_Pin GPIO_PIN_8
#define T_CS_RST_GPIO_Port GPIOI
#define FSK_RST_Pin GPIO_PIN_11
#define FSK_RST_GPIO_Port GPIOI
#define FSK_WD_Pin GPIO_PIN_4
#define FSK_WD_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_1
#define LED2_GPIO_Port GPIOB
#define FSK_RT_Pin GPIO_PIN_11
#define FSK_RT_GPIO_Port GPIOB
#define T_SCK_SCL_Pin GPIO_PIN_6
#define T_SCK_SCL_GPIO_Port GPIOH
#define T_PEN_INT_Pin GPIO_PIN_7
#define T_PEN_INT_GPIO_Port GPIOH
#define FSK_CD_Pin GPIO_PIN_8
#define FSK_CD_GPIO_Port GPIOH
#define T_MISO_Pin GPIO_PIN_3
#define T_MISO_GPIO_Port GPIOG
#define T_MOSI_SDA_Pin GPIO_PIN_3
#define T_MOSI_SDA_GPIO_Port GPIOI
#define FSK_MCLK_Pin GPIO_PIN_10
#define FSK_MCLK_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
