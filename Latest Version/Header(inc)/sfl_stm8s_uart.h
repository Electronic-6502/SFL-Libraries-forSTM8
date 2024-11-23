/**
 * @file : sfl_stm8s_uart.h
 * @author : HS6502
 * @date : 12-Oct-2024 @date Updated 21-Nov-2024
 * @version : 1.3
 * @brief : Macro File for Library
 */
// Include Guard
#ifndef __SFL_STM8S_UART_H
#define __SFL_STM8S_UART_H

#include "stm8s.h"
#include "sfl_stm8s_clk.h"
#include <string.h>

typedef enum{
    RX = 0x04,
    TX = 0x08 ,
    RXTX = 0x0C
}UART_Direction_TypeDef;

typedef enum{
    Receive = 0x20,
    Transmitt = 0x40,
    None = 0x00
}UART_Interrupt_TypeDef;

void UART_Reset(void);                           // Reset and Disable UART
void UART_Begin(uint32_t BaudRate);              // Reset and Initialize UART Peripheral for Using
void UART_Direction(UART_Direction_TypeDef Mode); // Select UART Mode: RX,TX and RXTX
void UART_Interrupt(UART_Interrupt_TypeDef ITR); // Enable Selected UART Event Interrupt
void UART_Power(bool Status);                // Turn ON or OFF UART Peripheral
void UART_Write(uint8_t Data);               // Write 1 Byte Data on UART and Transmitt
uint8_t UART_Read(void);                     // Read 1 Byte Data from UART
void UART_Print(uint8_t String[]);           // Print String to UART and Transmitt

// if SyncMode = 0x80 , UART is Clock Synced
#endif
/*-----End of File-----*/