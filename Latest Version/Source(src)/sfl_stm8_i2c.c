/**
 * @file    sfl_stm8s_i2c.h
 * @author  HS6502
 * @version 1.1.1
 * @date    11-Sep-2024  @date Updated : 13-Nov-2024
 * @brief   SFL I2C Library for STM8s Microcontrollers
 */
#include "sfl_stm8_i2c.h"

void I2C_Reset (void){                // Reset I2C Registers to Default
    I2C->CR1 = 0x00;
    I2C->CR2 = 0x00;
    I2C->FREQR = 0x00;
    I2C->OARL = 0x00;
    I2C->OARH = 0x00;
    I2C->ITR = 0x00;
    I2C->CCRL = 0x00; // This Value in Reference Manual 0x0B !
    I2C->CCRH = 0x00;
    I2C->TRISER = 0x02;  
}

void I2C_Begin (uint32_t CLK_Freq){     // Enable I2C & Init I2C Peripheral & Set CLK Pin Freq
    uint8_t I2C_InputClock;
    uint16_t Result;
    I2C_Reset();
    I2C_InputClock = CLK_GetMasterFreq()/1000000;
    Result = (uint16_t)((I2C_InputClock * 1000000) / (CLK_Freq << (uint8_t)1));

    CLK->PCKENR1 |= 0x01;                              // Enable I2C Peripheral Clock
    I2C->CR1 = 0x00;                                   // I2C Disable For Config
    I2C->CR2  = Default_ACK ;                          // Enable Acknowledge
    I2C->FREQR = I2C_InputClock;                       // I2C Peripheral Clock Value
    I2C->TRISER = I2C_InputClock + 1;                  // Maximum Rise Time   
    I2C->CCRL = Result;                                // Clock Control Register LSB
    I2C->CCRH = ((Result >> 8) & 0x0F);                // Clock Control Register MSB
    I2C_OwnAddress(Default_OwnAddress);    
    I2C->CR1 = 0x01;        // Enable I2C
}

void I2C_OwnAddress (uint16_t OwnAddress){
    I2C->OARL = OwnAddress;                   // Set STM8 Own Address LSB       
    I2C->OARH = ((uint8_t)(Address_Mode | 0x40) | ((OwnAddress >> 7) & 0x06));   
}

/**
 * @brief Write Slave Address and Data Direction to I2C Bus
 * @param Address 7bit Slave Device Address in I2C Bus 
 * @param Direction Data Direction, Rx= Receive , Tx= Transmitt
 */
void I2C_WriteAddress(uint8_t Address,I2C_Direction_TypeDef Direction){  
  while(!(I2C->SR1 & 0x80));
  Address &= (uint8_t)0xFE ;                        // Clear Bit 0 ( Direction Bit )
  I2C->DR = (uint8_t)(Address | (uint8_t)Direction);
 // while(!Check_Event((uint16_t)0x0782));            // While Master_Transmitter_Mode_Selected==0 
}

void I2C_WriteData (uint8_t W_Data){                // Function for Write Data only on I2C
  while(!(I2C->SR1 & 0x80));
  I2C->DR = W_Data;                                 // Send Data to I2C Bus
  //while(!Check_Event((uint16_t)0x0784));            // while Master_Byte_Transmitted==0
}

/**
 * @brief Write Slave Address,Data Direction,Data to I2C Bus
 * @param Address : Slave Device Address
 * @param DataDirection : Data Direction, Rx or Tx
 * @param W_Data 
 *//*
void I2C_Write (uint8_t Address,uint8_t Direction,uint8_t W_Data){  
  I2C_Start();                               // Generate I2C Start Command                      
  I2C_WriteAddress(Address,Direction);       // Write Address and Data Direction
  I2C_WriteData(W_Data);                     // Write Data to I2C Bus
  I2C_Stop();                                // Generate I2C Stop Command
}*/

uint8_t I2C_Read (void){                     // Read Data from I2C Bus
  while(I2C_Busy());                         // Wait to BUS BUSY
  return ((uint8_t)I2C->DR);                 // Return the Collected Data
}

void I2C_Acknowledge (bool ACK_Status){
  I2C->CR2 &= 0xFB;          // Clear Bit 2
  I2C->CR2 |= ACK_Status << 2;
}

void I2C_Enable (void){      // Turn ON or OFF I2C Peripheral
  I2C->CR1 = 1; 
}

void I2C_Disable (void){
  I2C->CR1 = 0;
}

void I2C_Start (void){        // Generate Start Command on I2C Bus
  I2C->CR2 |= 0x01;
  while(!Check_Event((uint16_t)0x0301));   // while Event_Master_Mode_Selected==0
}

void I2C_Stop (void){         // Generate Stop Command on I2C Bus
  I2C->CR2 |= 0x02;
}

_Bool Check_Event (uint16_t Event_Code){

  volatile uint16_t Last_Event = 0x00; 
  uint8_t Flag1 = 0x00;
  uint8_t Flag2 = 0x00;
  _Bool Status = 0;

  Flag1 = I2C->SR1;
  Flag2 = I2C->SR3;
  Last_Event = ((uint16_t)((uint16_t)Flag2 << (uint16_t)8) | (uint16_t)Flag1);
  if (((uint16_t)Last_Event & (uint16_t)Event_Code) == (uint16_t)Event_Code){
    Status = 1;
  }
  else{
    Status = 0;
  }

  return Status;
}

_Bool I2C_Busy (void){     // Function for Checking I2C Bus Busy  
  return (I2C->SR3 & 0x02);
}
/*--------------End of File----------------*/