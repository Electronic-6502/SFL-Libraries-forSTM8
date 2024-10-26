/**
 * @author : HS6502
 * @date : 12-Sep-2024 @date Updated 25-Oct-2024
 * @version : 1.0
 * @brief : Fast and Simplified UART Library for STM8
 */
#include <stm8s.h>
#include <string.h>
#include <stm8s_clk.h>
#include <sfl_stm8s_uart.h>

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
    UART1->BRR1 &= (uint8_t)(~UART1_BRR1_DIVM);  /* Clear the LSB mantissa of UART1DIV  */  
    UART1->BRR2 &= (uint8_t)(~UART1_BRR2_DIVM);  /* Clear the MSB mantissa of UART1DIV  */ 
    UART1->BRR2 &= (uint8_t)(~UART1_BRR2_DIVF);  /* Clear the Fraction bits of UART1DIV */ 
    /* Set the UART1 BaudRates in BRR1 and BRR2 registers according to UART1_BaudRate value */
    BDR_MNTS = ((uint32_t)CLK_GetClockFreq() / (BaudRate << 4));
    BDR_MNTS100 = (((uint32_t)CLK_GetClockFreq() * 100) / (BaudRate << 4));
    UART1->BRR2 |= (uint8_t)((uint8_t)(((BDR_MNTS100 -       // Set the fraction of UART1DIV
                 (BDR_MNTS * 100)) << 4) / 100) & (uint8_t)0x0F);  
    UART1->BRR2 |= (uint8_t)((BDR_MNTS >> 4) & (uint8_t)0xF0); /* Set the MSB mantissa of UART1DIV  */  
    UART1->BRR1 |= (uint8_t)BDR_MNTS;                  /* Set the LSB mantissa of UART1DIV  */  
         
    UART1->CR2 &= (uint8_t)~(UART1_CR2_TEN | UART1_CR2_REN);    // Disable Receiver and Transmitter 
    UART1->CR2 |= 0x0C;                          // Enable RX and TX ( Receive and Transmitt )
}

void UART_Mode (MODE_TPDF Mode){
  UART1->CR2 &= 0xF3;             // Clear RX-TX Mode Bytes
  UART1->CR2 |= Mode;             // Set RX Only,TX Only or RXTX Mode
}

void UART_Power (bool P_Status){
  if(P_Status){
    UART1->CR1 &= 0xDF;           // Enable UART Perpheral
  }
  else{
    UART1->CR1 |= 0x20;           // Disable UART Peripheral
  }
}

void UART_Write (uint8_t Data){
  while(!(UART1->SR & 0x80));     // While Transmit Register Empty 
  UART1->DR = Data;               // Send Data to UART         
}

uint8_t UART_Read (void){
  return ((uint8_t)UART1->DR);
}

void UART_Print (uint8_t String[]){                        
  uint16_t i,Length;
  Length = strlen(String);        // Get String Length
  for(i=0;i<Length;i++){
    UART_Write(String[i]);  
  }
}
