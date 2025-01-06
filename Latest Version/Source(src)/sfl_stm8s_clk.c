/**
 * @file    sfl_stm8_clk.c
 * @author  HS6502
 * @version 1.2
 * @date    8-Nov-2024    Updated : 22-Dec-2024
 * @brief   Clock Manage Library for STM8 Microcontroller 
 */
#include "sfl_stm8s_clk.h"

const uint8_t HSIDivFactor[4] = {1, 2, 4, 8};

uint32_t CLK_GetMasterFreq(void){
	uint32_t ClockFreq = 0;
	CLK_Source_TypeDef ClockSource = CLK_SOURCE_HSI;
	uint8_t Temp = 0, Prescaler = 0;
	
	/* Get CLK source. */
	ClockSource = (CLK_Source_TypeDef)CLK->CMSR;
	
	if (ClockSource == CLK_SOURCE_HSI){
		Temp = (uint8_t)(CLK->CKDIVR & CLK_CKDIVR_HSIDIV);
		Temp = (uint8_t)(Temp >> 3);
		Prescaler = HSIDivFactor[Temp];
		ClockFreq = HSI_VALUE / Prescaler;
	}
	else if ( ClockSource == CLK_SOURCE_LSI){
		ClockFreq = 128000;   		 	/* LSI Frequency */
	}
	else{
		ClockFreq = HSE_VALUE;
	}
	
	return((uint32_t)ClockFreq);
}

uint32_t CLK_GetCPUFreq (void){
	uint8_t Temp;
	Temp = CLK->CKDIVR & 0x07;
	return (CLK_GetMasterFreq() / POW(2,Temp));
}

void CLK_CCO_Begin (CCO_Source_TypeDef CCO_Source){
	CLK->CCOR = (CCO_Source << 1);    	 /* Set CCO Source */
  	CLK->CCOR |= 0x01;                	 /* Enable CCO Output */
}

void CLK_CCO (bool Status){
  	CLK->CCOR &= 0xFE;   			   	 /* Clear Bit 0 of Register */
  	CLK->CCOR |= Status;  			 	 /* Write New Value */
}