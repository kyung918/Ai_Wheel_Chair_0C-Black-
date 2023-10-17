/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
#include <string.h>
#include "gpio.h"

// Can Baud  50K bps Prescaler 40
// Can Baud  100K bps Prescaler 20
// Can Baud  125K bps Prescaler 16
// Can Baud  250K bps Prescaler  8
// Can Baud  500K bps Prescaler  4
// Can Baud 1000K bps Prescaler  2

CAN_FilterTypeDef  sFilterConfig;   // ?��?�� ?��?�� 구조�??????? �????????��
CAN_RxHeaderTypeDef   RxHeader;
CAN_TxHeaderTypeDef   TxHeader;
uint8_t               TxData[8];
uint8_t               RxData[8];
uint32_t              TxMailbox;
uint8_t 			  Txpos;
CAN_DATA Can_RxD;
CAN_QUEUE Can_RxQ;
CAN_COMMAND Can_Cmd;
void Can_Initial(void);
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 40;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_15TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_TX_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

//--------------------------------------------------------------------
// Can_Initial
//--------------------------------------------------------------------
void Can_Initial(void)
{
	//CAN Filter
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;              			// 0x00000000 = ID
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;

	if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
	{
	  Error_Handler();	//Filter configuration Error
	}
	if (HAL_CAN_Start(&hcan1) != HAL_OK)
	{
	  Error_Handler();
	}

	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)	//Activate CAN RX notification
	{
	  Error_Handler();
	}
	Can_RxQ.wptr=0;	//Queue write counter clear
	Can_RxQ.rptr=0;	//Queue read counter clear
}
//--------------------------------------------------------------------
// CanTxDataProcess - 보내�???????
//--------------------------------------------------------------------
void CanTxDataProcess(void)
{
	int val;
	/*
	if(utim.cantx)return;

	switch(Txpos)
	{
		case 0://DCIN VOLTAGE
			TxHeader.StdId = 0x01;   	// Standard Identifier, 0 ~ 0x7FF
  			TxHeader.RTR = CAN_RTR_DATA;            		//
  			TxHeader.IDE = CAN_ID_STD;              		// ?��?��?��?�� 메세�????????�� ?��별자 ???��, STD or EXT
  			TxHeader.DLC = 8;                       		// ?��?�� ?��?��?�� 길이, 0 ~ 8 byte
  			//val = (int)(ad.ADC_cal[ADC_DCIN]*10);
  			TxData[0] = gpio.id+0x30;
  			TxData[1] = 0;
  			TxData[2] = val /100+0x30;
  			TxData[3] = val /10%10+0x30;
  			TxData[4] = '.';
  			TxData[5] = val %10+0x30;
  			TxData[6] = 0;
  			TxData[7] = 0;
  			Txpos++;
			break;
	}

	if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	{
		Error_Handler();
	}
	utim.cantx=20;
*/
}
//--------------------------------------------------------------------
// Can_EmptyRxQ
//--------------------------------------------------------------------
char Can_EmptyRxQ(void)
{
	if(Can_RxQ.rptr == Can_RxQ.wptr)return(1);
	else	return(0);
}
//--------------------------------------------------------------------
// Can_RxQRead
//--------------------------------------------------------------------
int Can_RxQRead(void)
{
	if(Can_EmptyRxQ())return -1;
	if(Can_RxQ.rptr >= CAN_MAXQ) Can_RxQ.rptr = 0;
	return Can_RxQ.rptr++;
}
//--------------------------------------------------------------------
// DataFlowProcess
//--------------------------------------------------------------------
void DataFlowProcess(void)
{
	TxHeader.StdId = Can_RxD.StdId[Can_RxQ.rptr-1];	// Standard Identifier, 0 ~ 0x7FF
	//TxHeader.StdId = 0x01;
	TxHeader.RTR = CAN_RTR_DATA;            		//
	TxHeader.IDE = CAN_ID_STD;              		// ?��?��?��?�� 메세�????????�� ?��별자 ???��, STD or EXT
	TxHeader.DLC = Can_RxD.DLC[Can_RxQ.rptr -1];                       		// ?��?�� ?��?��?�� 길이, 0 ~ 8 byte
	//TxHeader.DLC = 8;
	memcpy(TxData, Can_RxD.Data[Can_RxQ.rptr -1], Can_RxD.DLC[Can_RxQ.rptr -1]);
/*
	TxData[0] = 0xCF;
	TxData[1] = 0x01;
	TxData[2] = 0x07;
	TxData[3] = 0xd0;
	TxData[4] = 0x01;
	TxData[5] = 0x07;
	TxData[6] = 0xd0;
	TxData[7] = 0x00;
*/
	if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	{
		Error_Handler();
	}

	Can_RxD.StdId[Can_RxQ.rptr-1]=0;
	memset(Can_RxD.Data[Can_RxQ.rptr-1],0,8);

}
//--------------------------------------------------------------------
// SerialToCanSendProcess
//--------------------------------------------------------------------
void SerialToCanSendProcess(uint8_t *cVal){


	TxHeader.StdId = cVal[2];	// Standard Identifier, 0 ~ 0x7FF
	TxHeader.RTR = CAN_RTR_DATA;            		//
	TxHeader.IDE = CAN_ID_STD;              		// ?��?��?��?�� 메세�????????�� ?��별자 ???��, STD or EXT
	TxHeader.DLC = cVal[4];                       		// ?��?�� ?��?��?�� 길이, 0 ~ 8 byte
	TxData[0] = cVal[3];
	memcpy(TxData + 1, cVal + 5, (uint8_t)cVal[4]);


/*	TxData[1] = 0x01;
	TxData[2] = 0x07;
	TxData[3] = 0xd0;
	TxData[4] = 0x01;
	TxData[5] = 0x07;
	TxData[6] = 0xd0;
	TxData[7] = 0x00;
*/
	if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	{
		Error_Handler();
	}


	//Can_RxD.StdId[Can_RxQ.rptr-1]=0;
	//memset(Can_RxD.Data[Can_RxQ.rptr-1],0,8);
}
//--------------------------------------------------------------------
// CanDataGetFlowProcess
//--------------------------------------------------------------------
void CanDataGetFlowProcess(void)
{
	int rcvdata;

	rcvdata = Can_RxQRead();

	if(rcvdata != -1)
	{
		DataFlowProcess();
	}
}
//--------------------------------------------------------------------
// HAL_CAN_RxFifo0MsgPendingCallback
//--------------------------------------------------------------------
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan1)
{

	if (HAL_CAN_GetRxMessage(hcan1, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
	{
	  Error_Handler();
	}


	Can_RxD.StdId[Can_RxQ.wptr]=RxHeader.StdId;
	Can_RxD.ExtId[Can_RxQ.wptr]=RxHeader.ExtId;
	Can_RxD.IDE  [Can_RxQ.wptr]=RxHeader.IDE;
	Can_RxD.RTR  [Can_RxQ.wptr]=RxHeader.RTR;
	Can_RxD.DLC  [Can_RxQ.wptr]=RxHeader.DLC;
	memcpy(Can_RxD.Data[Can_RxQ.wptr],RxData,sizeof(RxData));
	//printf("StdID: %04lx, IDE: %ld, DLC: %ld\r\n", RxHeader.StdId, RxHeader.IDE, RxHeader.DLC);
	//printf("Data: %d %d %d %d %d %d %d %d\r\n", Can_RxD.Data[Can_RxQ.wptr][0], Can_RxD.Data[Can_RxQ.wptr][1], Can_RxD.Data[Can_RxQ.wptr][2], Can_RxD.Data[Can_RxQ.wptr][3], Can_RxD.Data[Can_RxQ.wptr][4], Can_RxD.Data[Can_RxQ.wptr][5], Can_RxD.Data[Can_RxQ.wptr][6], Can_RxD.Data[Can_RxQ.wptr][7]);

	if(Can_RxQ.wptr >= CAN_MAXQ) Can_RxQ.wptr = 0;	// write ptr clr
	Can_RxQ.wptr++;

}
/* USER CODE END 1 */
