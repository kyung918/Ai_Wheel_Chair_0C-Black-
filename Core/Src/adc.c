/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
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
#include "adc.h"

/* USER CODE BEGIN 0 */
#include <string.h>
#include <stdio.h>

#include "tim.h"
#include "gpio.h"
#include "usart.h"

//int ADC_data[4];
int vout[4];
float temp[4];
//ADTIM adctim;
ADC adc;

bool bLocalMode_ADC= false;
bool bAutoMode_ADC = false;
bool bSerialType_ADC = false;

int nRPM_adc_L, nRPM_adc_R;
float fV_adc = 0;
float fw_adc = 0;
double _pi_adc = 3.1415926535897931;

//motor gear rate
float _fGearRate_adc = 26;

//Velocity Constant
float _fVEL_adc = 9.5492743;

//
//차폭 mini
float _fWidth_adc_mini = 0.7;
//차폭 black
float _fWidth_adc_black = 0.7;
//차폭 gold
float _fWidth_adc_gold = 0.6;
//tire radius
//float _fWheel_adc = 0.1525;
float _fWheel_adc = 0.180;

/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = ENABLE;
  hadc1.Init.NbrOfDiscConversion = 1;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 4;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */
	adctim.adc_get[0]=2;
	uint8_t icnt;
   
	for(icnt=0;icnt<4;icnt++){
		
		adc.ADC_data[icnt]=0;
   }
	
  /* USER CODE END ADC1_Init 2 */

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    PA1     ------> ADC1_IN1
    PA2     ------> ADC1_IN2
    PA3     ------> ADC1_IN3
    */
    GPIO_InitStruct.Pin = AI01_Pin|AI02_Pin|AI03_Pin|AI04_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    PA1     ------> ADC1_IN1
    PA2     ------> ADC1_IN2
    PA3     ------> ADC1_IN3
    */
    HAL_GPIO_DeInit(GPIOA, AI01_Pin|AI02_Pin|AI03_Pin|AI04_Pin);

  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void GetADCFlowProcess(){

	//adc Timer
   uint8_t icnt;
   
	bAutoMode_ADC = autoremotemode.bAutoRemoteMode;
	bLocalMode_ADC = localmode.bLocalMode;
	
  if(adctim.adc_get[0]!=0)return;
  adctim.adc_get[0] = 1;
   //printf("3");
   for(icnt=0;icnt<4;icnt++){
      HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1,1);
			adc.ADC_data[icnt] = 0;
		  adc.ADC_data[icnt]=HAL_ADC_GetValue(&hadc1);
   }
   HAL_ADC_Stop(&hadc1);
   
	 
		if((adc.ADC_data[0] < 300) && (adc.ADC_data[1] < 300)){
			if(adc.ADC_data[0] == 0) {
				fV_adc = 0;
			}
			if(adc.ADC_data[1] == 0) {
				fw_adc = 0;
			}
		}
		else{
			// -1.5 ~ 1.5 m/sec
			fV_adc = (((int)((adc.ADC_data[0] - 1800)/100) * 100 * 1.04) / 4000); //rotation
			// -5 ~ 5 rad/s
			fw_adc = (((int)((adc.ADC_data[1] - 1800)/100) * 100 * 3.45) / 2000); //direction
				
			CalcRPM_ADC(1);
			if(!bLocalMode_ADC){
				if(!bAutoMode_ADC){
					//printf("1");
					DataSendToMotor(0x01, 0xcf, 13);
					//printf("2");
					if((fw_adc == 0)&&(fV_adc == 0))DataSendToMotor(0x01, 0xae, 9);
				}
				else{
					if((fw_adc == 0)&&(fV_adc == 0))DataSendToMotor(0x01, 0xae, 9);
				}
			}
			else{
				//if(!bAutoMode_ADC)DataSendToMotor(0x01, 0xae, 9);
			}
		}


		/*CursorPosition(0,0);
    printf("ch1 = %4d\r\n",adc.ADC_data[ 0]);
    printf("Ch2 = %4d\r\n",adc.ADC_data[ 1]);
	  printf("FV = %4f\r\n",fV_adc);
    printf("FW = %4f\r\n",fw_adc);
	  printf("RPM_L = %4d\r\n",nRPM_adc_L);
    printf("RPM_R = %4d\r\n",nRPM_adc_R);
	  printf("LM = %d\r\n",localmode.bLocalMode);
	  printf("AR = %d\r\n",autoremotemode.bAutoRemoteMode);
    */
	 
    /*printf("Cu2 = %d,\r\n",ADC_data[ 9]);
    printf("Cu1 = %d,\r\n",ADC_data[11]);*/
}

void CalcRPM_ADC(int nType){


	//?��?���????????????????��
	float fV_adc_L, fV_adc_R;
	float fWidth_adc;
/*
	//�????????????????��?��?? 모터?��?��?���??????????????? 초기?��?�� �??????????????? ?��?��보드 ?��구사?��_Ver1.0.pptx 참조
	fV_L = fV + ((0.5 * fWidth) * fw);
	fV_R = fV - ((0.5 * fWidth) * fw);


	nRPM_L = fV_L * 26 * 60 * (1 /( 2.0 * 3.14 * fWheel));

	nRPM_R = -fV_R * 26 * 60 * (1 /( 2.0 * 3.14 * fWheel));
*/
	//platform Type : black
	if(nType == 0){
		fWidth_adc = _fWidth_adc_black;
	}
	//platform Type : gold
	else if (nType ==1 ){
		fWidth_adc = _fWidth_adc_gold;
	}
	fV_adc_L = (fV_adc*-1) + (fw_adc * fWidth_adc / 2);
	fV_adc_R = fV_adc - ((fw_adc * fWidth_adc / 2) *-1);

	//fV_L, fV_R < MotorMaxRPM 
	//nRPM_adc_L = MotorMaxRPM_adc(fV_adc_L);
	//nRPM_adc_R = (MotorMaxRPM_adc(fV_adc_R) * -1);
	_rpm.nRPM_L = MotorMaxRPM_adc(fV_adc_L);
	_rpm.nRPM_R = (MotorMaxRPM_adc(fV_adc_R));

}
float MotorMaxRPM_adc (float fVal_adc){
	float fResult_adc = 0.0;

	fResult_adc = fVal_adc * _fVEL_adc / _fWheel_adc * _fGearRate_adc;

	if(fResult_adc <= -2700){
		fResult_adc = -2700;
	}
	else if (fResult_adc > 2700){
		fResult_adc = 2700;
	}

	return fResult_adc;
}
/* USER CODE END 1 */
