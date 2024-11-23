/**
 * @file : sfl_stm8_beep.c
 * @author : HS6502
 * @version : 1.0
 * @date : 2-Nov-2024   Updated : 7-Nov-2024
 * @brief : SFL STM8 Beeper Peripheral Library
 */
#include "sfl_stm8_beep.h"

void BEEP_Freq (BP_FREQ Frequency){
    BEEP_Register &= 0x20;         // Clear The Frequency Divider Bits
    BEEP_Register |= (uint8_t)Frequency;
}

void BEEP_Enable (void){
    BEEP_Register |= 0x20;
}

void BEEP_Disable (void){
    BEEP_Register &= 0xDF;
}