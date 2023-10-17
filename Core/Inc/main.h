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
#include <stdbool.h>
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
#define LED_OPER_Pin GPIO_PIN_13
#define LED_OPER_GPIO_Port GPIOC
#define AI01_Pin GPIO_PIN_0
#define AI01_GPIO_Port GPIOA
#define AI02_Pin GPIO_PIN_1
#define AI02_GPIO_Port GPIOA
#define AI03_Pin GPIO_PIN_2
#define AI03_GPIO_Port GPIOA
#define AI04_Pin GPIO_PIN_3
#define AI04_GPIO_Port GPIOA
#define AO01_Pin GPIO_PIN_4
#define AO01_GPIO_Port GPIOA
#define AO02_Pin GPIO_PIN_5
#define AO02_GPIO_Port GPIOA
#define SW04_Pin GPIO_PIN_4
#define SW04_GPIO_Port GPIOC
#define SW03_Pin GPIO_PIN_5
#define SW03_GPIO_Port GPIOC
#define SW02_Pin GPIO_PIN_0
#define SW02_GPIO_Port GPIOB
#define SW01_Pin GPIO_PIN_1
#define SW01_GPIO_Port GPIOB
#define SBUS_RXD_Pin GPIO_PIN_11
#define SBUS_RXD_GPIO_Port GPIOB
#define DI04_Pin GPIO_PIN_12
#define DI04_GPIO_Port GPIOB
#define DI03_Pin GPIO_PIN_13
#define DI03_GPIO_Port GPIOB
#define DI02_Pin GPIO_PIN_14
#define DI02_GPIO_Port GPIOB
#define DI01_Pin GPIO_PIN_15
#define DI01_GPIO_Port GPIOB
#define DO04_Pin GPIO_PIN_6
#define DO04_GPIO_Port GPIOC
#define DO03_Pin GPIO_PIN_7
#define DO03_GPIO_Port GPIOC
#define DO02_Pin GPIO_PIN_8
#define DO02_GPIO_Port GPIOC
#define DO01_Pin GPIO_PIN_9
#define DO01_GPIO_Port GPIOC
#define DebugTxd_Pin GPIO_PIN_9
#define DebugTxd_GPIO_Port GPIOA
#define DebugRxd_Pin GPIO_PIN_10
#define DebugRxd_GPIO_Port GPIOA
#define MotorRs485Txd_Pin GPIO_PIN_10
#define MotorRs485Txd_GPIO_Port GPIOC
#define MotorRs485Rxd_Pin GPIO_PIN_11
#define MotorRs485Rxd_GPIO_Port GPIOC
#define PcRs485Txd_Pin GPIO_PIN_12
#define PcRs485Txd_GPIO_Port GPIOC
#define PcRs485Rxd_Pin GPIO_PIN_2
#define PcRs485Rxd_GPIO_Port GPIOD
#define MOTOR_RS485_DIR_Pin GPIO_PIN_5
#define MOTOR_RS485_DIR_GPIO_Port GPIOB
#define PC_RS485_DIR_Pin GPIO_PIN_6
#define PC_RS485_DIR_GPIO_Port GPIOB
#define Emergency_En_Pin GPIO_PIN_9
#define Emergency_En_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
typedef struct {

	bool bSerialType;

} SerialType;

extern SerialType serialtype;

typedef struct {

	bool bRemoteType;

} RemoteType;

extern RemoteType remotetype;

typedef struct {

	bool bLocalMode;

} LocalMode;

extern LocalMode localmode;

typedef struct {

	bool bAutoRemoteMode;

} AutoRemoteMode;

extern AutoRemoteMode autoremotemode;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
