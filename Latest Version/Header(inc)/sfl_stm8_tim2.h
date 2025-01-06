/**
 * @file    sfl_stm8_tim2.h
 * @author  HS6502
 * @date    29-Nov-2024 Update : 30-Nov-2024
 * @version 1.0 Stable
 * @brief   SFL Timer 2 Library Header file for STM8
 */

#ifndef __SFL_STM8_TIM2_H
#define __SFL_STM8_TIM2_H

#include "sfl_stm8.h"

/* Initialize Timer2 PWM1 Output */
void TIM2_PWM1_Begin (void);

/* Set Timer2 PWM 1 Output DutyCycle */
void TIM2_PWM1_Duty (uint16_t DutyCycle);

#endif