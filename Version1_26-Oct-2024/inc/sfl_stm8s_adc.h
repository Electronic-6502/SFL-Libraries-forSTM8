/**
 * @file    sfl_stm8s_adc.h
 * @author  HS6502
 * @version 1.5.0
 * @date    20-September-2024
 * @brief   Header File for sfl_stm8s.c Library
 */
#ifndef SFL_STM8S_ADC_H
#define SFL_STM8S_ADC_H

#define Reset_Value 0x00
#define HTRH_Reset_Value 0xFF
#define HTRL_Reset_Value 0x03
#define Sample_Num  10
#define ADC_Clock   ADC1_PRESSEL_FCPU_D2 

// Begin ADC Peripheral
void ADC_Init(void);	

// Read Current ADC Value					
uint16_t Read_ADC(uint8_t Channel);

// Read Average Value of ADC			
uint16_t Read_ADC_Average(uint8_t Channel);	

#endif
