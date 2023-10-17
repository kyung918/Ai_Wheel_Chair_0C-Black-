/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define OPER					HAL_GPIO_TogglePin(LED_OPER_GPIO_Port, LED_OPER_Pin)

#define MOTOR_RS485_DIR_TXD		HAL_GPIO_WritePin(MOTOR_RS485_DIR_GPIO_Port, MOTOR_RS485_DIR_Pin, GPIO_PIN_SET)
#define MOTOR_RS485_DIR_RXD		HAL_GPIO_WritePin(MOTOR_RS485_DIR_GPIO_Port, MOTOR_RS485_DIR_Pin, GPIO_PIN_RESET)
#define PC_RS485_DIR_TXD		HAL_GPIO_WritePin(PC_RS485_DIR_GPIO_Port, PC_RS485_DIR_Pin, GPIO_PIN_SET)
#define PC_RS485_DIR_RXD		HAL_GPIO_WritePin(PC_RS485_DIR_GPIO_Port, PC_RS485_DIR_Pin, GPIO_PIN_RESET)
#define EMERGENCY_EN			HAL_GPIO_WritePin(Emergency_En_GPIO_Port, Emergency_En_Pin, GPIO_PIN_SET)
#define EMERGENCY_DIS			HAL_GPIO_WritePin(Emergency_En_GPIO_Port, Emergency_En_Pin, GPIO_PIN_RESET)

//SW On = false / SW Off = true -> Normal True
#define SW01				HAL_GPIO_ReadPin(SW01_GPIO_Port, SW01_Pin)
#define SW02				HAL_GPIO_ReadPin(SW02_GPIO_Port, SW02_Pin)
#define SW03			    HAL_GPIO_ReadPin(SW03_GPIO_Port, SW03_Pin)
#define SW04				HAL_GPIO_ReadPin(SW04_GPIO_Port, SW04_Pin)

//Digital Input
#define DI01				HAL_GPIO_ReadPin(DI01_GPIO_Port, DI01_Pin)
#define DI02				HAL_GPIO_ReadPin(DI02_GPIO_Port, DI02_Pin)
#define DI03			    HAL_GPIO_ReadPin(DI03_GPIO_Port, DI03_Pin)
#define DI04				HAL_GPIO_ReadPin(DI04_GPIO_Port, DI04_Pin)

//Digital Output
#define DO01				HAL_GPIO_ReadPin(DO01_GPIO_Port, DO01_Pin)
#define DO02				HAL_GPIO_ReadPin(DO02_GPIO_Port, DO02_Pin)
#define DO03			    HAL_GPIO_ReadPin(DO03_GPIO_Port, DO03_Pin)
#define DO04				HAL_GPIO_ReadPin(DO04_GPIO_Port, DO04_Pin)


/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

