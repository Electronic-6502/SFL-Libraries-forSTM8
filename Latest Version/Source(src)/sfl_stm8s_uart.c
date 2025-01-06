/**
 * @file    sfl_stm8s_uart.c
 * @author  HS6502
 * @date    12-Sep-2024 @date Updated 15-Dec-2024
 * @version 1.4
 * @brief   Fast and Simplified UART Library for STM8
 */

#include "sfl_stm8s_uart.h"

void UART_Reset (void){
  UART1->SR = 0xC0;
  //(void)UART1->DR;
  UART1->BRR2 = 0x00;
  UART1->BRR1 = 0x00;
  UART1->CR1 = 0x00;
  UART1->CR2 = 0x00;
  UART1->CR3 = 0x00;
  UART1->CR4 = 0x00;
  UART1->CR5 = 0x00;
  UART1->GTR = 0x00;
  UART1->PSCR = 0x00;
}

void UART_Begin (uint32_t BaudRate){
    uint32_t BDR_MNTS = 0, BDR_MNTS100 = 0;
    UART_Reset();      
    /* Set the UART1 BaudRates in BRR1 and BRR2 registers according to UART1_BaudRate value */
    BDR_MNTS = ((uint32_t)CLK_GetMasterFreq() / (BaudRate << 4));
    BDR_MNTS100 = (((uint32_t)CLK_GetMasterFreq() * 100) / (BaudRate << 4));
    UART1->BRR2 |= (uint8_t)((uint8_t)(((BDR_MNTS100 -       // Set the fraction of UART1DIV
                 (BDR_MNTS * 100)) << 4) / 100) & (uint8_t)0x0F);  
    UART1->BRR2 |= (uint8_t)((BDR_MNTS >> 4) & (uint8_t)0xF0); /* Set the MSB mantissa of UART1DIV  */  
    UART1->BRR1 = (uint8_t)BDR_MNTS;                  /* Set the LSB mantissa of UART1DIV  */  
          
    UART1->CR2 = 0x0C;                          // Enable RX and TX ( Full Duplex Mode )
    CLK->PCKENR1 |= 0x04;                       // Enable UART Clock
}

void UART_Direction (UART_Direction_TypeDef Mode){
  UART1->CR2 &= 0xF3;             // Clear RX-TX Mode Bytes
  UART1->CR2 |= Mode;             // Set RX Only,TX Only or RXTX Mode
}

void UART_Interrupt (UART_Interrupt_TypeDef ITR_Name){
  UART1->CR2 &= (ITR_Name | 0x9F);     // Keep Byte 0 to 4 and 7, Write Byte 5 and 6 with New Value
}

void UART_Peripheral (bool P_Status){
  if(P_Status){
    UART1->CR1 &= 0xDF;           /* Enable UART Perpheral */
    CLK->PCKENR1 |= 0x04;         /* Enable UART Clock */
  }
  else{
    UART1->CR1 |= 0x20;           /* Disable UART Peripheral */
    CLK->PCKENR1 &= 0xFB;         /* Disable UART Clock */
  }
}

void UART_Write (uint8_t Data){
  while((UART1->SR & 0x80) == 0);  /* Wait for Transmitt Register Empty */
  UART1->DR = Data;                // Send Data to UART         
}

uint8_t UART_Read (void){
  return ((uint8_t)UART1->DR);
}

void UART_Print (uint8_t String[]){                        
  uint16_t i,Length;
  Length = strlen(String);          /* Get String Length ( in Bit ) */
  for(i=0;i<Length;i++){
    UART_Write(String[i]);
  }
}
