/**
 * @file    sfl_stm8s_adc.h
 * @author  HS6502
 * @version 1.6
 * @date    20-Sep-2024 Updated : 29-Sep-2024
 * @brief   Library for STM8 ADC Peripheral , from 
 * @brief   SFL ADC Library for STM8
 */
#include "sfl_stm8s_adc.h"

void ADC_Reset (void){
	ADC1->CSR =  0x00;			
    ADC1->CR1 =  0x00;
    ADC1->CR2 =  0x00;
    ADC1->CR3 =  0x00;
    ADC1->TDRH = 0x00;
    ADC1->TDRL = 0x00;
    ADC1->HTRH = 0xFF;
    ADC1->HTRL = 0x03;
    ADC1->LTRH = 0x00;
    ADC1->LTRL = 0x00;
    ADC1->AWCRH = 0x00;
    ADC1->AWCRL = 0x00;	    
}

void ADC_Begin (void){
    ADC_Reset();
	CLK->PCKENR2 |= 0x08;   	    // Enable ADC Clock
	//ADC1->TDRL = Channel;		    // ADC Schemitt Trigger Channel
	ADC1->CR1 = 0x10;          	    // ADC Clock Division to fMaster / 3
	ADC1->CR2 = 0x08;		        // ADC Value Right Alignment
	ADC1->CR1 |= 0x01;			    // ADC Enable
}

uint16_t ADC_Read (uint8_t Channel_Number){
	uint16_t ADC_Result;
	
	ADC1->CSR = Channel_Number;		   // Select ADC Channel for Read
	ADC1->CR1 |= 0x01;				   // Enable ADC and Start Conversion
	while(!(ADC1->CSR & 0x80));		   // Wait to end conversion
	ADC_Result = ADC1->DRL;            // Read LSB Value of ADC 
	ADC_Result |= ADC1->DRH << 8;	   // Read MSB Value of ADC and Shift    
	return ADC_Result;
}

uint16_t ADC_Read_Average (uint8_t Channel_Number_){
    uint8_t i;
    uint16_t Avg=0;
    for(i=0;i < Sample_Num;i++){
        Avg += ADC_Read(Channel_Number_);
    }
    Avg = Avg / Sample_Num;
    return Avg;
}

/*================ Analog Watch Dog (AWD) ================*/

void ADC_AWD_Reset (void){
    ADC_AWD_Interrupt(DISABLE);
    ADC1->AWCRL = 0x00;
    ADC1->TDRL = 0x00;
    ADC1->HTRH = 0xFF;
    ADC1->HTRL = 0x03;
    ADC1->LTRH = 0x00;
    ADC1->LTRL = 0x00;
}

void ADC_AWD_Begin (uint8_t Channel_){
    ADC1->AWCRL |= (0x01 << Channel_);
    ADC1->TDRL |= (0x01 << Channel_);
}

void ADC_AWD_Interrupt (bool New_Status){
    if(New_Status){
        ADC1->CSR |= 0x10;      /* Enable AWD Interrupt */
    }
    else{
        ADC1->CSR &= 0xEF;      /* Disable AWD Interrupt */
    }
}

void ADC_AWD_HighThreshold (uint16_t Hth_Value){
    ADC1->HTRL = Hth_Value;
    ADC1->HTRH = (Hth_Value >> 2);
}

void ADC_AWD_LowThreshold (uint16_t Lth_Value){
    ADC1->LTRL = Lth_Value;
    ADC1->LTRH = (Lth_Value >> 2);
}

bool ADC_AWD_GetStatus (void){
    bool Status;
    Status = ADC1->CSR & 0x40;  /* Read Flag Status from Register */
    ADC1->CSR &= 0xBF;          /* Clear AWD Flag */
    return Status;
}
/* End of File */