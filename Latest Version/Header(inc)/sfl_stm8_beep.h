/**
 * @file : sfl_stm8_beep.h
 * @author : HS6502
 * @version : 1.1
 * @date : 2-Nov-2024 Updated : 6-Nov-2024
 * @brief : SFL Beeper Library Header File for STM8
 */
#ifndef __SFL_STM8_BEEP
#define __SFL_STM8_BEEP
#include "stm8s.h"

#if defined(STM8L050J3) || defined(STM8L051F3) || defined(STM8L052C6) || defined(STM8L052R8) \
      || defined(STM8L151) || defined(STM8L162) || defined(STM8AL31) || defined(STM8AL3L) 
 #define BEEP_Register BEEP->CSR2
#else
 #define BEEP_Register BEEP->CSR
#endif

typedef enum{
    F1K = (uint8_t)0x0E,
    F2K = (uint8_t)0x5E,
    F4K = (uint8_t)0xDE
}BP_FREQ;

void BEEP_Freq (BP_FREQ Frequency);       // Change Beep Frequency
void BEEP_Enable (void);                // Enable Beep
void BEEP_Disable (void);               // Disable Beep

#endif