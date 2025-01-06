/**
 * @file    sfl_common.h
 * @author  HS6502
 * @date    27-Oct-2024 // Updated : 24-Dec-2024
 * @version 0.9 Beta
 * @brief   Common Used Functions in SFL STM8 Libraries
 */
#ifndef __SFL_COMMON_H
#define __SFL_COMMON_H

#include "stm8s.h"

void TimeOut (uint16_t T_Value);

// Cosmic Compiler is not Supported "strlen" Function by Default
#ifdef COSMIC         
uint16_t strlen (uint8_t String[]);
#endif

uint16_t Check_Parameter (uint16_t Value, uint16_t Max_Allowed, uint16_t Min_Allowed);


uint16_t POW (uint8_t Base, uint8_t Exponent );

#endif  /* End of File */