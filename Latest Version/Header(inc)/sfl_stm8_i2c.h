/**
 * @file    sfl_stm8_i2c.h
 * @author  HS6502
 * @version 1.2.1
 * @date    11-Sep-2024 @date Updated 21-Nov-2024
 * @brief   SFL I2C Header File
 */
 // Include Guard
#ifndef __SFL_STM8_I2C_H  
#define __SFL_STM8_I2C_H

#include "stm8s.h"
#include "sfl_stm8s_clk.h"

#define Default_OwnAddress  0x98
#define Address_Mode 0x00       // Addressing Mode,0x00=7bit ,0x80=10bit;
#define Default_ACK  0x04       // Default Acnowledge,0x00=Disable ,0x04=Enable

typedef enum{
    I2C_Receive = 0x01,
    I2C_Transmitt = 0x00
}I2C_Direction_TypeDef;

void I2C_Reset(void);
void I2C_Begin (uint32_t CLK_Freq);
void I2C_OwnAddress(uint16_t OwnAddress);
void I2C_WriteAddress(uint8_t Address,I2C_Direction_TypeDef Direction);
void I2C_WriteData (uint8_t W_Data);
//void I2C_Write (uint8_t Address,uint8_t Direction,uint8_t W_Data);
uint8_t I2C_Read (void);
void I2C_Acknowledge (bool ACK_Status);     // Enable or Disable Acknowledge
void I2C_Enable (void);
void I2C_Disable(void);
void I2C_Start(void);
void I2C_Stop(void);
_Bool Check_Event(uint16_t Event_Code);
_Bool I2C_Busy (void);

#endif