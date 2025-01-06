/**
 * @file    sfl_stm8_tim2.c
 * @author  HS6502
 * @date    29-Nov-2024 Update : 30-Nov-2024
 * @version 1.0 Stable
 * @brief   SFL Timer 2 Library for STM8
 */
#include "sfl_stm8_tim2.h"

void TIM2_PWM1_Begin (void){
    CLK->PCKENR1 |= 0x20;               /* Enable TIM2 Peripheral Clock */
    TIM2->CCER1 |= 0x01;                /* Enable PWM */
    TIM2->CCMR1 |= 0x60;                /* PWM Mode 1 */
    TIM2->ARRH = 0x03;                  /* Autoreload Value MSB */
    TIM2->ARRL = 0xE7;                  /* Autoreload Value LSB */
    TIM2->PSCR = 0x01;                  /* Set Prescaler Value */    
    TIM2->CR1 |= 0x01;                  /* Enable Timer 2 Counter  */
}

/*void TIM2_PWM1_Freq (uint16_t Frequency){
    
}*/

void TIM2_PWM1_Duty (uint16_t DutyCycle){
    TIM2->CCR1H = (DutyCycle >> 8);     /* Set Timer 2 Capture/Compare1 MSB */
    TIM2->CCR1L = DutyCycle;            /* Set Timer 2 Capture/Compare1 LSB */   
}