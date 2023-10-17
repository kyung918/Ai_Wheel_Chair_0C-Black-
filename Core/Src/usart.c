/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    usart.c
 * @brief   This file provides code for the configuration
 *          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
#include <string.h>
#include <stdio.h>

#include "tim.h"
#include "gpio.h"

uint8_t buff;

UART_QUEUE UART_RxQ[MAX_USART_CHANNEL];
COMM_BUF GS_Rev1Buf, GS_Rev2Buf, GS_Rev3Buf, GS_Rev4Buf, GS_Rev5Buf;

char cPid;
char r_cPid;
// int nPacketLen;
bool bAutoMode_Usart = false;
bool bLocalMode_Usart = false;
bool bSerialType_Usart = false;
int nRPM_L, nRPM_R;
RPM _rpm;
float fV, fw;
double _pi = 3.1415926535897931;
// 100ms * 20cycle = 2000ms
int nSendFail = 20;
// motor gear rate
float _fGearRate = 26;

// Velocity Constant
float _fVEL = 9.5492743;

//?? mini
float _fWidth_mini = 0.7;
//?? black
float _fWidth_black = 0.7;
//?? gold
float _fWidth_gold = 0.6;
// tire radius
// float _fWheel = 0.1525;
float _fWheel = 0.180;
// sbus
uint8_t sbus_data[25] = {0x0f, 0x01, 0x04, 0x20, 0x00, 0xff, 0x07, 0x40, 0x00, 0x02, 0x10, 0x80, 0x2c, 0x64, 0x21, 0x0b, 0x59, 0x08, 0x40, 0x00, 0x02, 0x10, 0x80, 0x00, 0x00};
int16_t channels[18] = {1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 0, 0};
uint8_t failsafe_status = SBUS_SIGNAL_FAILSAFE;

// ibus
uint8_t ibus_Data[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint16_t ibus_Ch[16] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};

/* USER CODE END 0 */

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

/* UART4 init function */
void MX_UART4_Init(void)
{

	/* USER CODE BEGIN UART4_Init 0 */

	/* USER CODE END UART4_Init 0 */

	/* USER CODE BEGIN UART4_Init 1 */

	/* USER CODE END UART4_Init 1 */
	huart4.Instance = UART4;
	huart4.Init.BaudRate = 57600;
	huart4.Init.WordLength = UART_WORDLENGTH_9B;
	huart4.Init.StopBits = UART_STOPBITS_1;
	huart4.Init.Parity = UART_PARITY_EVEN;
	huart4.Init.Mode = UART_MODE_TX_RX;
	huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart4.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart4) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN UART4_Init 2 */

	/* USER CODE END UART4_Init 2 */
}
/* UART5 init function */
void MX_UART5_Init(void)
{

	/* USER CODE BEGIN UART5_Init 0 */

	/* USER CODE END UART5_Init 0 */

	/* USER CODE BEGIN UART5_Init 1 */

	/* USER CODE END UART5_Init 1 */
	huart5.Instance = UART5;
	huart5.Init.BaudRate = 57600;
	huart5.Init.WordLength = UART_WORDLENGTH_8B;
	huart5.Init.StopBits = UART_STOPBITS_1;
	huart5.Init.Parity = UART_PARITY_NONE;
	huart5.Init.Mode = UART_MODE_RX;
	huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart5.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart5) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN UART5_Init 2 */

	/* USER CODE END UART5_Init 2 */
}
/* USART1 init function */

void MX_USART1_UART_Init(void)
{

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_9B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */
}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

	/* USER CODE BEGIN USART3_Init 0 */

	/* USER CODE END USART3_Init 0 */

	/* USER CODE BEGIN USART3_Init 1 */

	/* USER CODE END USART3_Init 1 */
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 115200;
	huart3.Init.WordLength = UART_WORDLENGTH_9B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart3) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART3_Init 2 */

	/* USER CODE END USART3_Init 2 */
}

void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if (uartHandle->Instance == UART4)
	{
		/* USER CODE BEGIN UART4_MspInit 0 */

		/* USER CODE END UART4_MspInit 0 */
		/* UART4 clock enable */
		__HAL_RCC_UART4_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		/**UART4 GPIO Configuration
		PC10     ------> UART4_TX
		PC11     ------> UART4_RX
		*/
		GPIO_InitStruct.Pin = MotorRs485Txd_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(MotorRs485Txd_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = MotorRs485Rxd_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(MotorRs485Rxd_GPIO_Port, &GPIO_InitStruct);

		/* UART4 interrupt Init */
		HAL_NVIC_SetPriority(UART4_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(UART4_IRQn);
		/* USER CODE BEGIN UART4_MspInit 1 */

		/* USER CODE END UART4_MspInit 1 */
	}
	else if (uartHandle->Instance == UART5)
	{
		/* USER CODE BEGIN UART5_MspInit 0 */

		/* USER CODE END UART5_MspInit 0 */
		/* UART5 clock enable */
		__HAL_RCC_UART5_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		/**UART5 GPIO Configuration
		PC12     ------> UART5_TX
		PD2     ------> UART5_RX
		*/
		GPIO_InitStruct.Pin = PcRs485Txd_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(PcRs485Txd_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = PcRs485Rxd_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(PcRs485Rxd_GPIO_Port, &GPIO_InitStruct);

		/* UART5 interrupt Init */
		HAL_NVIC_SetPriority(UART5_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(UART5_IRQn);
		/* USER CODE BEGIN UART5_MspInit 1 */

		/* USER CODE END UART5_MspInit 1 */
	}
	else if (uartHandle->Instance == USART1)
	{
		/* USER CODE BEGIN USART1_MspInit 0 */

		/* USER CODE END USART1_MspInit 0 */
		/* USART1 clock enable */
		__HAL_RCC_USART1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART1 GPIO Configuration
		PA9     ------> USART1_TX
		PA10     ------> USART1_RX
		*/
		GPIO_InitStruct.Pin = DebugTxd_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(DebugTxd_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = DebugRxd_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(DebugRxd_GPIO_Port, &GPIO_InitStruct);

		/* USART1 interrupt Init */
		HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		/* USER CODE BEGIN USART1_MspInit 1 */

		/* USER CODE END USART1_MspInit 1 */
	}
	else if (uartHandle->Instance == USART3)
	{
		/* USER CODE BEGIN USART3_MspInit 0 */

		/* USER CODE END USART3_MspInit 0 */
		/* USART3 clock enable */
		__HAL_RCC_USART3_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**USART3 GPIO Configuration
		PB10     ------> USART3_TX
		PB11     ------> USART3_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = SBUS_RXD_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(SBUS_RXD_GPIO_Port, &GPIO_InitStruct);

		/* USART3 interrupt Init */
		HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART3_IRQn);
		/* USER CODE BEGIN USART3_MspInit 1 */

		/* USER CODE END USART3_MspInit 1 */
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle)
{

	if (uartHandle->Instance == UART4)
	{
		/* USER CODE BEGIN UART4_MspDeInit 0 */

		/* USER CODE END UART4_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_UART4_CLK_DISABLE();

		/**UART4 GPIO Configuration
		PC10     ------> UART4_TX
		PC11     ------> UART4_RX
		*/
		HAL_GPIO_DeInit(GPIOC, MotorRs485Txd_Pin | MotorRs485Rxd_Pin);

		/* UART4 interrupt Deinit */
		HAL_NVIC_DisableIRQ(UART4_IRQn);
		/* USER CODE BEGIN UART4_MspDeInit 1 */

		/* USER CODE END UART4_MspDeInit 1 */
	}
	else if (uartHandle->Instance == UART5)
	{
		/* USER CODE BEGIN UART5_MspDeInit 0 */

		/* USER CODE END UART5_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_UART5_CLK_DISABLE();

		/**UART5 GPIO Configuration
		PC12     ------> UART5_TX
		PD2     ------> UART5_RX
		*/
		HAL_GPIO_DeInit(PcRs485Txd_GPIO_Port, PcRs485Txd_Pin);

		HAL_GPIO_DeInit(PcRs485Rxd_GPIO_Port, PcRs485Rxd_Pin);

		/* UART5 interrupt Deinit */
		HAL_NVIC_DisableIRQ(UART5_IRQn);
		/* USER CODE BEGIN UART5_MspDeInit 1 */

		/* USER CODE END UART5_MspDeInit 1 */
	}
	else if (uartHandle->Instance == USART1)
	{
		/* USER CODE BEGIN USART1_MspDeInit 0 */

		/* USER CODE END USART1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART1_CLK_DISABLE();

		/**USART1 GPIO Configuration
		PA9     ------> USART1_TX
		PA10     ------> USART1_RX
		*/
		HAL_GPIO_DeInit(GPIOA, DebugTxd_Pin | DebugRxd_Pin);

		/* USART1 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART1_IRQn);
		/* USER CODE BEGIN USART1_MspDeInit 1 */

		/* USER CODE END USART1_MspDeInit 1 */
	}
	else if (uartHandle->Instance == USART3)
	{
		/* USER CODE BEGIN USART3_MspDeInit 0 */

		/* USER CODE END USART3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART3_CLK_DISABLE();

		/**USART3 GPIO Configuration
		PB10     ------> USART3_TX
		PB11     ------> USART3_RX
		*/
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10 | SBUS_RXD_Pin);

		/* USART3 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART3_IRQn);
		/* USER CODE BEGIN USART3_MspDeInit 1 */

		/* USER CODE END USART3_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */
UART_QUEUE UART_RxQ[MAX_USART_CHANNEL];
//------------------------------------------------------------------
// Ring buffer empty ??.
//------------------------------------------------------------------
char Uart_EmptyRxQ(char port)
{
	if (UART_RxQ[port].rptr == UART_RxQ[port].wptr)
		return (1);
	else
		return (0);
}
//------------------------------------------------------------------
// Read Rxd data.
//------------------------------------------------------------------
int Uart_RxQRead(char port)
{
	if (Uart_EmptyRxQ(port))
		return -1;
	if (UART_RxQ[port].rptr == UART_MAXQ - 1)
		UART_RxQ[port].rptr = 0;

	return (UART_RxQ[port].buff[UART_RxQ[port].rptr++]);
}
//------------------------------------------------------------------
//?????? ???????????????????????? ???????? ????????? ???????????????????????????
//------------------------------------------------------------------
//?????????????????????????? : ????? ??????????????????????????? ??? ???????? ????????????????????????????????? ????????.
//????? ????????????????????????????????? ?????????????????????????????? -1??? ????????
//------------------------------------------------------------------
int CommGetChar(unsigned char ch)
{
	return Uart_RxQRead(ch);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	switch ((uint32_t)huart->Instance)
	{

	case (uint32_t)USART1:
		__HAL_UART_CLEAR_OREFLAG(&huart1);
		HAL_UART_Receive_IT(&huart1, &buff, 1); // 1????T ????
		if (UART_RxQ[COM1].wptr == UART_MAXQ - 1)
			UART_RxQ[COM1].wptr = 0; // write ptr clr
		UART_RxQ[COM1].buff[UART_RxQ[COM1].wptr++] = buff;

		break;

	case (uint32_t)USART2:
		/*			__HAL_UART_CLEAR_OREFLAG(&huart2);
					HAL_UART_Receive_IT(&huart2, &buff, 1); // 1????T ????
					//if(UART_RxQ[COM2].wptr == UART_MAXQ) UART_RxQ[COM2].wptr = 0;	// write ptr clr
					//UART_RxQ[COM2].buff[UART_RxQ[COM2].wptr++] = buff;
					*/
		break;

	case (uint32_t)USART3:
		__HAL_UART_CLEAR_OREFLAG(&huart3);
		HAL_UART_Receive_IT(&huart3, &buff, 1); // 1????T ????
		if (UART_RxQ[COM3].wptr == UART_MAXQ)
			UART_RxQ[COM3].wptr = 0; // write ptr clr
		UART_RxQ[COM3].buff[UART_RxQ[COM3].wptr++] = buff;
		break;

	case (uint32_t)UART4:
		__HAL_UART_CLEAR_OREFLAG(&huart4);
		HAL_UART_Receive_IT(&huart4, &buff, 1); // 1????T ????
		if (UART_RxQ[COM4].wptr == UART_MAXQ)
			UART_RxQ[COM4].wptr = 0; // write ptr clr
		UART_RxQ[COM4].buff[UART_RxQ[COM4].wptr++] = buff;
		break;

	case (uint32_t)UART5:
		__HAL_UART_CLEAR_OREFLAG(&huart5);
		HAL_UART_Receive_IT(&huart5, &buff, 1); // 1????T ????
		if (UART_RxQ[COM5].wptr == UART_MAXQ)
			UART_RxQ[COM5].wptr = 0; // write ptr clr
		UART_RxQ[COM5].buff[UART_RxQ[COM5].wptr++] = buff;
		break;
		/*
		case (uint32_t)USART6:
			__HAL_UART_CLEAR_OREFLAG(&huart6);
			HAL_UART_Receive_IT(&huart6, &buff, 1); // 1????T ????
			//if(UART_RxQ[COM6].wptr == UART_MAXQ) UART_RxQ[COM6].wptr = 0;	// write ptr clr
			//UART_RxQ[COM6].buff[UART_RxQ[COM6].wptr++] = buff;
		break;
		*/
	}
}
//------------------------------------------------------------------
//?????.
//------------------------------------------------------------------
void Usart_Init(void)
{
	COMM_BUF *ptr;

	ptr = &GS_Rev1Buf;
	ptr->Buf[0] = 0;
	ptr->Ctr = 0;
	ptr->Len = 0;
	ptr->RxCompletion = 0;

	ptr = &GS_Rev2Buf;
	ptr->Buf[0] = 0;
	ptr->Ctr = 0;
	ptr->Len = 0;
	ptr->RxCompletion = 0;

	ptr = &GS_Rev3Buf;
	ptr->Buf[0] = 0;
	ptr->Ctr = 0;
	ptr->Len = 0;
	ptr->RxCompletion = 0;

	ptr = &GS_Rev4Buf;
	ptr->Buf[0] = 0;
	ptr->Ctr = 0;
	ptr->Len = 0;
	ptr->RxCompletion = 0;

	ptr = &GS_Rev5Buf;
	ptr->Buf[0] = 0;
	ptr->Ctr = 0;
	ptr->Len = 0;
	ptr->RxCompletion = 0;

	PC_RS485_DIR_RXD;
	MOTOR_RS485_DIR_RXD;

	cPid = 0;
	r_cPid = 0;

	// Disconnection Timer = 1000
	discontim.discon = 200;
	nRPM_L, nRPM_R = 0;
	// AutoMode 1: auto / 0: Manual
	// bAutoMode = false;
	// G_DataGetPort   =   0;   /* DataGerProcess??? ???????????????????????????????? ?????????????????????????? ??? port */
	// G_DataFlowPort   =   0;   /* DataFlowProcess??? ???????????????????????????????? ?????????????????????????? ??? port */

	//   ClearScreen();
}

void CommBufClear(unsigned char port)
{
	COMM_BUF *ptr;

	switch (port)
	{
	case COM1:
		ptr = &GS_Rev1Buf;
		break;
	case COM2:
		ptr = &GS_Rev2Buf;
		break;
	case COM3:
		ptr = &GS_Rev3Buf;
		break;
	case COM4:
		ptr = &GS_Rev4Buf;
		break;
	case COM5:
		ptr = &GS_Rev5Buf;
		break;
	}
	memset(ptr->Buf, 0, COMM_MAX_BUF);
	ptr->Ctr = 0;
	ptr->flag = 0;
	ptr->RxCompletion = 0;
	nSendFail--;
	if (nSendFail == 0)
		nSendFail = 20;
}
//------------------------------------------------------------------
//????????? ???????????????????????????????? ???????????????????????????? ????????? ?? ?????????????????????????????????????? ???????????? ?????????????????????????????????? ???????????????????????????????? ?????.
//------------------------------------------------------------------

void DataGetFlowProcess(unsigned char port)
{

	COMM_BUF *ptr;
	int m_nPacketLen = 0;
	switch (port)
	{
	case COM1:
		ptr = &GS_Rev1Buf;
		break;
	case COM2:
		ptr = &GS_Rev2Buf;
		break;
	case COM3:
		ptr = &GS_Rev3Buf;
		break;
	case COM4:
		ptr = &GS_Rev4Buf;
		break;
	case COM5:
		ptr = &GS_Rev5Buf;
		break;
	default:
		return;
	}

	bAutoMode_Usart = autoremotemode.bAutoRemoteMode;
	bLocalMode_Usart = localmode.bLocalMode;
	bSerialType_Usart = serialtype.bSerialType;

	while (1)
	{

		ptr->rtn = CommGetChar(port);
		if (ptr->rtn == D_EMPTY)
			break;

		switch (port)
		{
			// Debug
		case COM1:
		case COM4:
		case COM5:
			ptr->Buf[ptr->Ctr++] = ptr->rtn;
			ptr->RxCompletion = 1;
			// Serial Event Timer
			utim.uart_get[port] = 1;
			// utim.uart_get[port]=2;

			if (ptr->Buf[5] == 0xb7)
			{
				CommBufClear(port);
				break;
			}
			else if (ptr->Ctr >= 40)
			{
				CommBufClear(port);
				break;
			}
			else if (ptr->Ctr >= UART_MAXQ - 1)
			{ // ?? ??????? ??
				CommBufClear(port);
				break;
			}

			break;
		case COM3:

			if (ptr->Buf[0] != 0x20)
			{
				if (ptr->rtn == 0x20)
				{
					ptr->Ctr = 0;
				}
				else
				{
					// printf("%c",ptr->rtn);
					break;
				}
			}

			ptr->Buf[ptr->Ctr++] = ptr->rtn;
			if ((ptr->Buf[0] == 0x20) && (ptr->Ctr == 32))
			{

				memcpy(ibus_Data, ptr->Buf, 32);
				if (ibus_read(&ibus_Data))
				{

					// -1.5 ~ 1.5 m/s
					fV = (((ibus_Ch[2] - 1500) * 3.0) / 1000);
					// fw = (((ibus_Ch[0] - 1500) * 1.6) / 1000);
					//  -5 ~ 5 rad/s
					// fw = ((ibus_Ch[0] - 1500) / 100);
					fw = (((ibus_Ch[0] - 1500) * 3.0) / 1000);

					CalcRPM(1);

					/*CursorPosition(0,0);
					printf("CH0: %04d\r\n",ibus_Ch[0]);
					printf("CH2: %04d\r\n",ibus_Ch[2]);
					printf("CH4: %04d\r\n",ibus_Ch[4]);
					printf("CH5: %04d\r\n",ibus_Ch[5]);
					printf("Vel %0.3f\r\n", fV);
					printf("Ang Vel %f\r\n", fw);
					printf("RPM_L %04d\r\n", nRPM_L);
					printf("RPM_R %04d\r\n", nRPM_R);
			*/
					// AutoManual Switch - Remote -> H/W Switch change
					/*if(ibus_Ch[4] == 1000){
						bAutoMode_Usart = false;
					}
					else{
						bAutoMode_Usart = true;
					}*/

					// All Brake / Tq off / ?? ?????? S/W
					//  320      / 1000   / 2000
					if (ibus_Ch[5] == 1500)
					{
						r_cPid = 0xae;
					}
					else if (ibus_Ch[5] == 1000)
					{
						r_cPid = 0xaf;
					}
					else if (ibus_Ch[5] == 2000)
					{
						r_cPid = 0xcf;
					}
					// bAutoMode = (channels[8] == 0 ? true : false);
					// r_cPid = (channels[9] == 1000 ? 0xae : (channels[9] == 306 ? 0xaf : 0xcf));

					// pid 174(ae/ Tq Off) or 175(af / All Break)
					if ((r_cPid == 0xae) || (r_cPid == 0xaf))
						m_nPacketLen = 9;
					// pid 207(cf / Velocity)
					else
						m_nPacketLen = 13;

					// if(bAutoMode == false){
					// if(autoremotemode.bAutoRemoteMode==true){
					if (bAutoMode_Usart)
					{
						// id, ?????
						DataSendToMotor(0x01, r_cPid, m_nPacketLen);
						// Message Success Timer Reset

						r_cPid = 0x00;
						if ((fw == 0) && (fV == 0))
							DataSendToMotor(0x01, 0xae, 9);
					}
					else
					{
						if ((fw == 0) && (fV == 0))
							DataSendToMotor(0x01, 0xae, 9);
						// DataSendToMotor(0x01, 0xae, 9);
					}

					// printf("%d",ibus_Ch[0]);
					CommBufClear(port);

					break;
				}
				else
				{
					CommBufClear(port);

					break;
				}
			}

			if (ptr->Ctr >= UART_MAXQ - 1)
			{ // ?? ??????? ??
				CommBufClear(port);
				break;
			}

			break;
		}
	}

	if (utim.uart_get[port] == 0)
	{

		if (ptr->RxCompletion == 1)
		{

			switch (port)
			{
				// Debug
			case COM1:
				/* ptr->RxCompletion=0;
					//printf("%d\n", ptr->Ctr);
				if((ptr->Buf[ptr->Ctr-1] == 0x0d) ||(ptr->Buf[ptr->Ctr-1] ==0x0a)){

					printf("%s\n",ptr->Buf);
				}
				CommBufClear(port);*/
				break;
			case COM2:

				break;
				// sbus
			case COM3:

				break;
				// Motor
			case COM4:
				ptr->RxCompletion = 0;

				// printf("%s\n",ptr->Buf);
				// if((ptr->Buf[ptr->Ctr-1] == 0x0d) || (ptr->Buf[ptr->Ctr-1] ==0x0a)){
				if ((ptr->Buf[0] == 0xb7) || (ptr->Buf[1] == 0xb8))
				{
					//??????, Tq off, Brake????????? Motor Drive?????? ?? ??????
				}
				CommBufClear(port);
				break;
				// PC
			case COM5:
				ptr->RxCompletion = 0;

				// printf("%02d\r\n", ptr->Ctr);
				//			printf("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\r\n",
				//									ptr->Buf[0],ptr->Buf[1],ptr->Buf[2],ptr->Buf[3],ptr->Buf[4],ptr->Buf[5],ptr->Buf[6],
				//									ptr->Buf[7],ptr->Buf[8],ptr->Buf[9],ptr->Buf[10],ptr->Buf[11],ptr->Buf[12]);
				// if((ptr->Buf[ptr->Ctr-1] == 0x0d) || (ptr->Buf[ptr->Ctr-1] ==0x0a)){
				if ((ptr->Buf[0] == 0xb7) && (ptr->Buf[1] == 0xac))
				{

					// if((ptr->Buf[0] == 0xb7) || (ptr->Buf[1] == 0xb8)){

					// pid ?? ????????? ??????????????????????? ?????????????????????? ??????????????????????????
					cPid = ptr->Buf[3];

					// pid 174(ae) or 175(af)
					if ((cPid == 0xae) || (cPid == 0xaf))
						m_nPacketLen = 9;
					// pid 207
					else if (cPid == 0xcf)
						m_nPacketLen = 13;
					else
					{

						CommBufClear(port);
						break;
					}
					// pintf("cPid%02d\r\n",cPid);
					// Default RS485 -> Dip S/W || AutoMode : true
					// if(localmode.bLocalMode==true){
					if (bLocalMode_Usart)
					{

						// if ((serialtype.bSerialType) || (bAutoMode)){
						// if ((serialtype.bSerialType) || (autoremotemode.bAutoRemoteMode == false)){
						if ((bSerialType_Usart) || (!bAutoMode_Usart))
						{

							if (m_nPacketLen > 0)
							{
								//???????????? ?????? ??? ????????????????????????????? Bypass ??????

								MOTOR_RS485_DIR_TXD;
								HAL_Delay(10);
								// CursorPosition(0,0);
								// printf("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\r\n",
								// ptr->Buf[0],ptr->Buf[1],ptr->Buf[2],ptr->Buf[3],ptr->Buf[4],ptr->Buf[5],ptr->Buf[6],
								// ptr->Buf[7],ptr->Buf[8],ptr->Buf[9],ptr->Buf[10],ptr->Buf[11],ptr->Buf[12]);
								if (!(ptr->Buf[11] == 0x00))
								{
									if (!(ptr->Buf[12] == 0x00))
									{
										if (!(ptr->Buf[5] == 0x00))
										{
											if (ptr->Buf[6] == 0xff)
												ptr->Buf[6] = 0xfe;
											if (ptr->Buf[9] == 0xff)
												ptr->Buf[9] = 0xfe;
											printf("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\r\n",
												   ptr->Buf[0], ptr->Buf[1], ptr->Buf[2], ptr->Buf[3], ptr->Buf[4], ptr->Buf[5], ptr->Buf[6],
												   ptr->Buf[7], ptr->Buf[8], ptr->Buf[9], ptr->Buf[10], ptr->Buf[11], ptr->Buf[12]);
											HAL_NVIC_DisableIRQ(UART4_IRQn); // Rx Callback ?????? Disable
											HAL_UART_Transmit(&huart4, ptr->Buf, m_nPacketLen, 1000);
											HAL_NVIC_EnableIRQ(UART4_IRQn); // Rx callback ?????? enable
											// Message Success Timer Reset
											discontim.discon = 200;
											HAL_Delay(10);
											MOTOR_RS485_DIR_RXD;
										}
									}
								}
								//????????????????????????????? ?????
								m_nPacketLen = 0;
								cPid = 0x00;
								// printf("Send OK!\r\n");
							}
						}
						// Serial ????????????????? ????? Can???????????????????? ??????
						// else if((serialtype.bSerialType == false) || (bAutoMode)) {
						// else if((serialtype.bSerialType == false) || (autoremotemode.bAutoRemoteMode == false)) {
						else if ((!bSerialType_Usart) || (!bAutoMode_Usart))
						{
							SerialToCanSendProcess(ptr->Buf);
						}
					}
					CommBufClear(port);
					break;
				}
				else
				{
					CommBufClear(port);
					break;
				}

				CommBufClear(port);
				break;
			default:
				return;
			} // switch
			// CursorPosition(0,0);
			// printf("discon Time %04d\r\n", discontim.discon);
			// printf("SendFail %04d\r\n", nSendFail);

		} // rx-Complecation
		if (bLocalMode_Usart)
		{

			if (discontim.discon == 0)
			{
				CommBufClear(port);

				DataSendToMotor(0x01, 0xae, 9);
				discontim.discon = 200;
			} // discon
		}	  // localmode
	}		  // Timer 0
}

bool DataSendToMotor(int nid, char cPid, int nPacketLen)
{

	unsigned char ucSendData[nPacketLen];

	// RMID
	ucSendData[0] = 0xb7;
	// TMID
	ucSendData[1] = 0xac;
	// ucSendData[1] = 0xb8;
	// id
	ucSendData[2] = (char)nid;
	// pid
	ucSendData[3] = cPid;
	// Len
	ucSendData[4] = (char)(nPacketLen - 6);

	/*for(int i = 5; i < nPacketLen; i++){
		ucSendData[i] = 0x00;
	}*/

	if (cPid == 0xcf)
	{
		ucSendData[5] = 0x01;

		IByte cbuf;

		cbuf = Int2Byte((short)_rpm.nRPM_L);
		ucSendData[6] = cbuf.byLow;
		ucSendData[7] = cbuf.byHigh;

		ucSendData[8] = 0x01;
		cbuf = Int2Byte((short)_rpm.nRPM_R);
		ucSendData[9] = cbuf.byLow;
		ucSendData[10] = cbuf.byHigh;

		ucSendData[11] = 0x00;
		ucSendData[12] = (char)GetCheckSum(12, ucSendData);
	}
	else
	{
		ucSendData[5] = 0x05;
		ucSendData[6] = 0x01;
		ucSendData[7] = 0x01;
		ucSendData[8] = (char)GetCheckSum(8, ucSendData);
	}

	// Motor ??? ????????? ???????????????????
	// Motor LED Lamp On
	MOTOR_RS485_DIR_TXD;
	 HAL_Delay(2);

	HAL_NVIC_DisableIRQ(UART4_IRQn); // Rx Callback ?????? Disable
	HAL_UART_Transmit(&huart4, ucSendData, nPacketLen, 1000);
	HAL_NVIC_EnableIRQ(UART4_IRQn); // Rx callback ?????? enable

	 HAL_Delay(2);
	// Motor LED Lamp On
	MOTOR_RS485_DIR_RXD;

	return true;
}

short IsChkSumOK(char *byArray, short nPacketSize)
{
	short i;
	char cbySum;
	cbySum = 0;
	for (i = 0; i < nPacketSize; i++)
	{
		cbySum += *(byArray + i);
	}
	if (cbySum == 0)
		return 1;
	else
		return 0;
}
// From the input array, return the chksum
char GetCheckSum(short nPacketSize, char *byArray)
{
	char byTmp = 0;
	short i;
	for (i = 0; i < nPacketSize; i++)
		byTmp += *(byArray + i);
	return (~byTmp + 1);
}
// Make interger from two bytes
short Byte2Int(char byLow, char byHigh)
{
	return (byLow | (short)byHigh << 8);
}
// Make long type data from four bytes
int Byte2LInt(char byData1, char byData2, char byData3, char byData4)
{
	return ((int)byData1 | (int)byData2 << 8 | (int)byData3 << 16 | (int)byData4 << 24);
}

// Get the low and high byte from interger
IByte Int2Byte(short nIn)
{
	IByte Ret;
	Ret.byLow = nIn & 0xff;
	Ret.byHigh = nIn >> 8 & 0xff;
	return Ret;
}
// Get the bytes from long type data
LByte LInt2Byte(int nIn)
{
	LByte Ret;
	Ret.byData[0] = nIn & 0xff;
	Ret.byData[1] = nIn >> 8 & 0xff;
	Ret.byData[2] = nIn >> 16 & 0xff;
	Ret.byData[3] = nIn >> 24 & 0xff;
	return Ret;
}

void update_channels(uint8_t *buf)
{
	// Read all received data and calculate channel data
	uint8_t i;
	for (i = 1; i < 24; i++)
	{
		sbus_data[i] = 0;
	}

	//??????????????????? ?????????????????? ??
	memcpy(sbus_data + 1, buf + 1, 25);
	//?? ?????
	for (i = 0; i < 16; i++)
	{
		channels[i] = 0;
	}

	// reset counters
	uint8_t byte_in_sbus = 1;
	uint8_t bit_in_sbus = 0;
	uint8_t ch = 0;
	uint8_t bit_in_channel = 0;

	// process actual sbus data
	for (i = 0; i < 176; i++)
	{
		if (sbus_data[byte_in_sbus] & (1 << bit_in_sbus))
		{
			channels[ch] |= (1 << bit_in_channel);
		}
		bit_in_sbus++;
		bit_in_channel++;

		if (bit_in_sbus == 8)
		{
			bit_in_sbus = 0;
			byte_in_sbus++;
		}
		if (bit_in_channel == 11)
		{
			bit_in_channel = 0;
			ch++;
		}
	}
	// DigiChannel 1
	if (sbus_data[23] & (1 << 0))
	{
		channels[16] = 1;
	}
	else
	{
		channels[16] = 0;
	}
	// DigiChannel 2
	if (sbus_data[23] & (1 << 1))
	{
		channels[17] = 1;
	}
	else
	{
		channels[17] = 0;
	}

	// channels[1] = ??????(??????) / channels[2] = ?????
	//?????? ?????????????????? ???????????????? 320 ~ 999 ~ 1694
	//?????? =  (???? / 10) - 100(??????????????????) *(float)(????????? ?????????????????????? / ?????????????????????? ??????????????????????) * 0.1(????????????????????)
	fV = round(((channels[1] / 10) - 100) * (float)(30.0 / 138.0) * 0.1);
	fw = round(((channels[0] / 10) - 100) * (float)(16.0 / 138.0) * 0.1);

	/*
			fV = round(((((channels[1] / 10) - 30) *  (float)(30.0 / 138.0) - 15) * 0.1) *10) / 10;

			fw = round(((((channels[0] / 10) - 16) *  (float)(16.0 / 138.0) - 8) * -0.1) *10) / 10;

			fV = (round(round((channels[1] - 1000) / 10 ) * 3.42857) * 10);
			fw = (round(round((channels[0] - 1000) / 10 ) * 0.64285) * 10);
	*/
	// Motor ??? ????????? RPM ??
	CalcRPM(0);

	/*	CursorPosition(0,0);
		printf("CH0: %04d\r\n",channels[0]);
		printf("CH1: %04d\r\n",channels[1]);
		printf("CH6: %04d\r\n",channels[6]);
		printf("CH8: %04d\r\n",channels[8]);
		printf("Vel %f\r\n", fV);
		printf("Ang Vel %f\r\n", fw);
		printf("RPM_L %04d\r\n", nRPM_L);
		printf("RPM_R %04d\r\n", nRPM_R);
*/
	// Failsafe
	failsafe_status = SBUS_SIGNAL_OK;
	if (sbus_data[23] & (1 << 2))
	{
		failsafe_status = SBUS_SIGNAL_LOST;
	}
	if (sbus_data[23] & (1 << 3))
	{
		failsafe_status = SBUS_SIGNAL_FAILSAFE;
	}
}
void CalcRPM(int nType)
{

	//?????????????????????????
	float fV_L, fV_R;
	float fWidth;
	/*
		//???????????????????????? ??????????????????????????? ???????? ???????????????? ???????? ????????_Ver1.0.pptx ??
		fV_L = fV + ((0.5 * fWidth) * fw);
		fV_R = fV - ((0.5 * fWidth) * fw);


		nRPM_L = fV_L * 26 * 60 * (1 /( 2.0 * 3.14 * fWheel));

		nRPM_R = -fV_R * 26 * 60 * (1 /( 2.0 * 3.14 * fWheel));
	*/
	// platform Type : black
	if (nType == 0)
	{
		fWidth = _fWidth_black;
	}
	// platform Type : gold
	else if (nType == 1)
	{
		fWidth = _fWidth_gold;
	}
	//	fV_adc_L = (fV_adc*-1) + (fw_adc * fWidth_adc / 2);
	// fV_adc_R = fV_adc - ((fw_adc * fWidth_adc / 2) *-1);
	fV_L = fV + (fw * fWidth / 2);
	fV_R = fV - (fw * fWidth / 2);

	// fV_L, fV_R < MotorMaxRPM
	// nRPM_L = MotorMaxRPM(fV_L);
	// nRPM_R = (MotorMaxRPM(fV_R) * -1);
	_rpm.nRPM_L = MotorMaxRPM(fV_L);
	_rpm.nRPM_R = (MotorMaxRPM(fV_R));
}

//------------------------------------------------------------------
//	CursorPosition
//------------------------------------------------------------------
void CursorPosition(int x, int y)
{
	int ch;

	ch = 0x1b; // clear screen
	printf("%c", ch);
	printf("[%d;%dH", x, y);
}

bool ibus_read(uint16_t *ibus_data)
{
	if (!ibus_is_valid())
		return false;

	if (!ibus_checksum())
		return false;

	ibus_update(ibus_data);
	return true;
}

/* Sub Functions */
bool ibus_is_valid()
{
	// is it ibus?
	return (ibus_Data[0] == IBUS_LENGTH && ibus_Data[1] == IBUS_COMMAND40);
}

bool ibus_checksum()
{
	uint16_t checksum_cal = 0xffff;
	uint16_t checksum_ibus;

	for (int i = 0; i < 30; i++)
	{
		checksum_cal -= ibus_Data[i];
	}

	checksum_ibus = ibus_Data[31] << 8 | ibus_Data[30]; // checksum value from ibus
	return (checksum_ibus == checksum_cal);
}

void ibus_update()
{
	for (int ch_index = 0, bf_index = 2; ch_index < IBUS_USER_CHANNELS; ch_index++, bf_index += 2)
	{
		ibus_Ch[ch_index] = ibus_Data[bf_index + 1] << 8 | ibus_Data[bf_index];
	}
}

float MotorMaxRPM(float fVal)
{
	float fResult = 0.0;

	fResult = fVal * _fVEL / _fWheel * _fGearRate;

	if (fResult <= -2700)
	{
		fResult = -2700;
	}
	else if (fResult > 2700)
	{
		fResult = 2700;
	}

	return fResult;
}

/* USER CODE END 1 */
