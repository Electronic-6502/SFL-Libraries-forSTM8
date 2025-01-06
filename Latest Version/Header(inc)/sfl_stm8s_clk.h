/**
 * @file    sfl_stm8_clk.h
 * @author  HS6502
 * @version 1.2
 * @date    8-Nov-2024   Update : 22-Dec-2024
 * @brief   SFL STM8 Clock Manage Header File
 */
 // Include Guard
#ifndef __SFL_STM8S_CLK_H
#define __SFL_STM8S_CLK_H

#include "stm8s.h"
#include "sfl_common.h"

typedef enum {
  CLK_SOURCE_HSI    = (uint8_t)0xE1, /*!< Clock Source HSI. */
  CLK_SOURCE_LSI    = (uint8_t)0xD2, /*!< Clock Source LSI. */
  CLK_SOURCE_HSE    = (uint8_t)0xB4 /*!< Clock Source HSE. */
} CLK_Source_TypeDef;

typedef enum{
  CCO_HSIDIV = 0x00,
  CCO_LSI = 0x01,
  CCO_HSE = 0x02,
  CCO_CPU = 0x04,
  CCO_CPUDIV2 = 0x05,
  CCO_CPUDIV4 = 0x06,
  CCO_CPUDIV8 = 0x07,
  CCO_CPUDIV16 = 0x08,
  CCO_CPUDIV32 = 0x09,
  CCO_CPUDIV64 = 0x0A,
  CCO_HSI = 0x0B,
  CCO_MASTER = 0x0C,
}CCO_Source_TypeDef;

/* Return Master Clock Frequency */
uint32_t CLK_GetMasterFreq(void);  

/* Return CPU Clock Frequency */
uint32_t CLK_GetCPUFreq(void);

/* Initialize and Enable CCO */
void CLK_CCO_Begin(CCO_Source_TypeDef CCO_Source);    

/* Enable or Disable CCO */
void CLK_CCO(bool Status);        

#endif    /* End of File */