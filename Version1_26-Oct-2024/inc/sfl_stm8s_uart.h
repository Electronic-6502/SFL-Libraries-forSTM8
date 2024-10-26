/**
 * @author : HS6502
 * @date : 2024-10-12 @date Updated 20-Oct-2024
 * @version : 1.0
 * @brief : Macro File for Library
 */
#ifndef SFL_STM8S_UART_H
#define SFL_STM8S_UART_H

//#define SyncMode   0x80  // Set SyncMode, 0x80 = Clock Sync Disable

typedef enum{
    RX = 0x04,
    TX = 0x08 ,
    RXTX = 0x0C
}MODE_TPDF;

void UART_Reset(void);                // Reset and Disable UART
void UART_Begin(uint32_t BaudRate);   // Reset and Initialize UART Peripheral for Using
void UART_Mode(MODE_TPDF Mode);       // Select UART Mode: RX,TX and RXTX
void UART_Power(bool Status);         // Turn ON or OFF UART Peripheral
void UART_Write(uint8_t Data);        // Write 1 Byte Data on UART and Transmitt
uint8_t UART_Read(void);              // Read 1 Byte Data from UART
void UART_Print(uint8_t String[]);    // Print String to UART and Transmitt

#endif