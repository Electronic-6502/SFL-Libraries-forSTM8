/**
 * @file    sfl_stm8_clk.h
 * @author  HS6502
 * @version 1.0.0
 * @date    8-Nov-2024
 * @brief   SFL STM8 Clock Manage Header File
 */
 // Include Guard
#ifndef __SFL_STM8S_CLK_H
#define __SFL_STM8S_CLK_H

#include "stm8s.h"

typedef enum {
  CLK_SOURCE_HSI    = (uint8_t)0xE1, /*!< Clock Source HSI. */
  CLK_SOURCE_LSI    = (uint8_t)0xD2, /*!< Clock Source LSI. */
  CLK_SOURCE_HSE    = (uint8_t)0xB4 /*!< Clock Source HSE. */
} CLK_Source_TypeDef;

typedef enum{
  HSIDIV = 0x00,
  LSI = 0x01,
  HSE = 0x02,
  CPU = 0x04,
  CPU2 = 0x05,
  CPU4 = 0x06,
  CPU8 = 0x07,
  CPU16 = 0x08,
  CPU32 = 0x09,
  CPU64 = 0x0A,
  HSI = 0x0B,
  MASTER = 0x0C,
}CCO_Source_TypeDef;

uint32_t CLK_GetMasterFreq(void);     // Return Master Clock Frequency
void CLK_CCO_Begin(CCO_Source_TypeDef CCO_Source);   // Initialize CCO Source
void CLK_CCO(bool Status);        // Enable or Disable CCO

#endif