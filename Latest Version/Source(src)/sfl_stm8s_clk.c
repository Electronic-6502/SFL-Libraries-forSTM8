/**
 * @file    sfl_stm8_clk.c
 * @author  HS6502
 * @version 1.0.1
 * @date    8-Nov-2024  Updated : 16-Nov-2024
 * @brief   Clock Manage Library for STM8 Microcontroller 
 */
#include "sfl_stm8s_clk.h"

const uint8_t HSIDivFactor[4] = {1, 2, 4, 8};

uint32_t CLK_GetMasterFreq(void){
  uint32_t clockfrequency = 0;
  CLK_Source_TypeDef clocksource = CLK_SOURCE_HSI;
  uint8_t tmp = 0, presc = 0;
  
  /* Get CLK source. */
  clocksource = (CLK_Source_TypeDef)CLK->CMSR;
  
  if (clocksource == CLK_SOURCE_HSI)
  {
    tmp = (uint8_t)(CLK->CKDIVR & CLK_CKDIVR_HSIDIV);
    tmp = (uint8_t)(tmp >> 3);
    presc = HSIDivFactor[tmp];
    clockfrequency = HSI_VALUE / presc;
  }
  else if ( clocksource == CLK_SOURCE_LSI)
  {
    clockfrequency = 128000;    // LSI Frequency Value
  }
  else
  {
    clockfrequency = HSE_VALUE;
  }
  
  return((uint32_t)clockfrequency);
}
/*
uint32_t CLK_GetCPUFreq (void){
  return (CLK_GetMasterFreq() / (CLK->CKDIVR & 0x07));
}*/

void CLK_CCO_Begin (CCO_Source_TypeDef CCO_Source){
  CLK->CCOR &= CCO_Source;
}

void CLK_CCO (bool Status){
  CLK->CCOR &= 0xFE;    // Clear Bit 0 of Register
  CLK->CCOR |= Status;  // Write New Value
}