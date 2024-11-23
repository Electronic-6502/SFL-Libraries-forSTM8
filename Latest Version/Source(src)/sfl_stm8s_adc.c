/**
 * @file    sfl_stm8s_adc.h
 * @author  HS6502
 * @version 1.5.0
 * @date    20-September-2024
 * @brief   Library for STM8 ADC Peripheral , from 
 * @brief   SFL Series Library
 */
#ifndef SFL_STM8S_ADC_C
#define SFL_STM8S_ADC_C

#include <stm8s.h>
#include <sfl_stm8s_adc.h>

void ADC_Init(void){
	ADC1->CSR =  Reset_Value;			// Start of DeInit
    ADC1->CR1 =  Reset_Value;
    ADC1->CR2 =  Reset_Value;
    ADC1->CR3 =  Reset_Value;
    ADC1->TDRH = Reset_Value;
    ADC1->TDRL = Reset_Value;
    ADC1->HTRH = HTRH_Reset_Value;
    ADC1->HTRL = HTRL_Reset_Value;
    ADC1->LTRH = Reset_Value;
    ADC1->LTRL = Reset_Value;
    ADC1->AWCRH = Reset_Value;
    ADC1->AWCRL = Reset_Value;	    	// End of DeInit

	CLK->PCKENR2 |= CLK_PCKENR2_ADC;	// Enable ADC Clock
	//ADC1->TDRL = Channel;				// ADC Schemitt Trigger Channel
	ADC1->CR1 = ADC_Clock;          	// ADC Clock Division
	ADC1->CR2 = ADC_RIGHT_ALIGN;		// ADC Data Aligment
	ADC1->CR1 |= ADC1_CR1_ADON;			// ADC Enable
}

uint16_t Read_ADC(uint8_t channel){
	uint16_t ADC_Result;
	
	ADC1->CSR = channel;					// Channel Selecting**
	ADC1->CR1 |= ADC1_CR1_ADON;				// Enable ADC and Start Conversion
	while(!(ADC1->CSR & ADC1_CSR_EOC));		// while to end conversion
	ADC_Result = ADC1->DRL;                 // ADC Data Register Low
	ADC_Result |= ADC1->DRH << 8;		    
	return ADC_Result;
}

uint16_t Read_ADC_Average(uint8_t Channel){
    uint8_t i;
    uint16_t Avg=0;
    for(i=0;i < Sample_Num;i++){
        Avg += Read_ADC(Channel);
    }
    Avg = Avg / Sample_Num;
    return Avg;
}
#endif