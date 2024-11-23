/**
 * @file    sfl_stm8s_adc.h
 * @author  HS6502
 * @version 1.6.1
 * @date    20-Sep-2024 @date Updated : 8-Nov-2024
 * @brief   Header File for sfl_stm8s.c Library
 */
#ifndef __SFL_STM8S_ADC_H
#define __SFL_STM8S_ADC_H

#define Reset_Value 0x00
#define HTRH_Reset_Value 0xFF
#define HTRL_Reset_Value 0x03
#define ADC_RIGHT_ALIGN 0x08
#define ADC_Clock   0x00
#define Sample_Num  10

// Begin ADC Peripheral
void ADC_Init(void);	

// Read Current ADC Value					
uint16_t Read_ADC(uint8_t Channel);

// Read Average Value of ADC			
uint16_t Read_ADC_Average(uint8_t Channel);	

#endif
