/**
 * @file    sfl_stm8s_adc.h
 * @author  HS6502
 * @version 1.7
 * @date    20-Sep-2024 @date Updated : 29-Nov-2024
 * @brief   Header File for sfl_stm8s.c Library
 */
#ifndef __SFL_STM8S_ADC_H
#define __SFL_STM8S_ADC_H

#include "stm8s.h"

#define Sample_Num  10

/* Reset ADC Registers to Default Value */
void ADC_Reset (void);

/* Initialize ADC Peripheral */
void ADC_Begin(void);	

/* Read Current ADC Value from Selected Channel */				
uint16_t ADC_Read (uint8_t Channel_Number);

/* Read Average Value of Selected ADC Channel */			
uint16_t ADC_Read_Average (uint8_t Channel_Number);	

/*================ Analog Watch Dog (AWD) ================*/

/* Reset AWD Registers to Default Status */
void ADC_AWD_Reset (void);

/* Enable Selected Channel Analog Watchdog */
void ADC_AWD_Begin (uint8_t Channel_);

/* Enable or Disable AWD Interrupt */
void ADC_AWD_Interrupt (bool New_Status);

/* Set High Threshold Value of AWD */
void ADC_AWD_HighThreshold (uint16_t Hth_Value);

/* Set Low Threshold Value of AWD */
void ADC_AWD_LowThreshold (uint16_t Lth_Value);

/* Get AWD Status ( Occured or Not Occured )*/
bool ADC_AWD_GetStatus (void);

#endif /* End of File */