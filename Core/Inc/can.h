/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
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
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#define CAN_MAXQ		80

/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan1;

/* USER CODE BEGIN Private defines */

typedef struct
{
	uint8_t mode[2];
	uint8_t status[2];
	uint8_t ch;
	uint8_t ch_old;
	uint8_t pos1;
	uint8_t pos2;
	uint8_t cnt1;
	uint8_t cnt2;
}CAN_COMMAND;


typedef struct
{
  uint32_t StdId[CAN_MAXQ+1];
  uint32_t ExtId[CAN_MAXQ+1];
  uint8_t IDE[CAN_MAXQ+1];
  uint8_t RTR[CAN_MAXQ+1];
  uint8_t DLC[CAN_MAXQ+1];
  uint8_t Data[CAN_MAXQ+1][8];
  uint8_t FMI[CAN_MAXQ+1];
}CAN_DATA;


typedef struct
{
    int   wptr;     /* write pointer */
    int   rptr;     /* read pointer */
}CAN_QUEUE;
/* USER CODE END Private defines */

void MX_CAN1_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

