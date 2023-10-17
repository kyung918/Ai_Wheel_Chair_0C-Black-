/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart4;

extern UART_HandleTypeDef huart5;

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */

#define MAX_USART_CHANNEL   5
#define COMM_MAX_BUF      2047
#define UART_MAXQ         2047

#define D_FALSE      0
#define D_TRUE      1
#define D_EMPTY      -1

//Com1 Debug
#define COM1   0         // uart1 port
//Com2 Not Used
#define COM2   1         // uart2 port
//Com3 Sbus
#define COM3   2         // uart3 port
//Com4 Motor RS485
#define COM4   3         // uart4 port
//Com5 PC RS485
#define COM5   4         // uart5 port
/* USER CODE END Private defines */

void MX_UART4_Init(void);
void MX_UART5_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */
#define SBUS_SIGNAL_OK          0x00
#define SBUS_SIGNAL_LOST        0x01
#define SBUS_SIGNAL_FAILSAFE    0x03


extern uint8_t buff;

typedef struct {

    uint8_t  buff[UART_MAXQ+1]; // data buffer
    int           wptr;         // write pointer
    int           rptr;         // read pointer
} UART_QUEUE;

typedef struct {

   int             rtn;
   unsigned char   Buf[COMM_MAX_BUF+1];
   unsigned int   Ctr;
   unsigned int    flag;
   int				Len;
   unsigned char   RxCompletion;
}COMM_BUF;

typedef struct{
		int nRPM_L;
		int nRPM_R;
}RPM;
extern RPM _rpm;



typedef struct {
	char byLow;
	char byHigh;
} IByte;
typedef struct {
	char byData[4];
} LByte;
void CursorPosition(int x,int y);
void CalcRPM(int nType);
bool DataSendToMotor(int nid, char cPid, int nPacketLen);


short IsChkSumOK(char *byArray, short nPacketSize);
// From the input array, return the chksum
char GetCheckSum(short nPacketSize, char *byArray);
// Make interger from two bytes
short Byte2Int(char byLow, char byHigh);
// Make long type data from four bytes
int Byte2LInt(char byData1, char byData2, char byData3, char byData4);
// Get the low and high byte from interger
IByte Int2Byte(short nIn);
// Get the bytes from long type data
LByte LInt2Byte(int nIn);
//Calc Motor Max RPM
float MotorMaxRPM (float fVal);


/* User configuration */
#define IBUS_USER_CHANNELS		6		// Use 6 channels - FS-iA6B

/* Defines */
#define IBUS_LENGTH				0x20	// 32 bytes
#define IBUS_COMMAND40			0x40	// Command to set servo or motor speed is always 0x40
#define IBUS_MAX_CHANNLES		14


/* Main Functions */
bool ibus_read();


/* Sub Functions */
bool ibus_is_valid();
bool ibus_checksum();
void ibus_update();
void ibus_soft_failsafe(uint16_t* ibus_data, uint8_t fail_safe_max);
void ibus_reset_failsafe();

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

