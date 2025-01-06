/**
 * @file    sfl_stm8s_uart.h
 * @author  HS6502
 * @date    12-Oct-2024 @date Updated 15-Dec-2024
 * @version 1.4
 * @brief   Macro File for Library
 */
// Include Guard
#ifndef __SFL_STM8S_UART_H
#define __SFL_STM8S_UART_H

#include "stm8s.h"
#include "sfl_stm8s_clk.h"

#if defined (SDCC) || defined (__SDCC)
    #include <string.h>
#elif defined (COSMIC)
    #include "sfl_common.h" /* COSMIC Compiler is NOT Supported "strlen" Function */
#endif

typedef enum{
    UART_RX_Only = 0x04,
    UART_TX_Only = 0x08 ,
    UART_RXTX = 0x0C
}UART_Direction_TypeDef;

typedef enum{
    UART_Receive = 0x20,
    UART_Transmitt = 0x40,
    UART_None = 0x00
}UART_Interrupt_TypeDef;

/* Reset UART Registers and Disable UART */
void UART_Reset(void);                   

/* Reset, Initialize and Enable UART Peripheral for Using */
void UART_Begin(uint32_t BaudRate);              

/* Select UART Mode: RX Only,TX Only or RXTX (Full Duplex) */
void UART_Direction(UART_Direction_TypeDef Mode); 

/* Enable Selected UART Event Interrupt */
void UART_Interrupt(UART_Interrupt_TypeDef ITR_Name);

/* Enable or Disable UART Peripheral */
void UART_Peripheral(bool Status);  

/* Write 1 Byte Data to UART and Transmitt */
void UART_Write(uint8_t Data);  

/* Read 1 Byte Data from UART */
uint8_t UART_Read(void);  

/* Write String to UART and Transmitt */
void UART_Print(uint8_t String[]);  

// if SyncMode = 0x80 , UART is Clock Synced
#endif  /*-----End of File-----*/