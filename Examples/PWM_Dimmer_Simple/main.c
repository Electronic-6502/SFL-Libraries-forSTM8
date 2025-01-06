/**
 * @file    main.c
 * @author  HS6502
 * @date    10-Dec-2024
 * @version 1.0
 * @brief   Simple PWM Dimmer using SFL Libraries
 */
/*
- Hardware Connection for STM8S003/103 :
- LED Anode Pin : PORT D4
- Potentiometer Middle Pin : PORT C4
*/

#include "sfl_stm8.h"

int i ;

void Delay (void){
    uint32_t d;
    for(d=0;d<1000;d++);
}

void main (void){
    ADC_Begin();
    TIM2_PWM1_Begin();
    Delay();
    
    while(1){
        TIM2_PWM1_Duty(ADC_Read(2));
        Delay();
    }
}