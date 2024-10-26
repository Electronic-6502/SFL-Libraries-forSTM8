/**
 * @file    sfl_stm8s_i2c.h
 * @author  HS6502
 * @version 1.0.0
 * @date    11-Sep-2024
 * @brief   SFL I2C Library for STM8s Microcontrollers
 */
#include <sfl_stm8s_i2c.h>

void I2C_Reset (void){                // Reset I2C Registers to Default
  I2C->CR1 = I2C_CR1_RESET_VALUE;
  I2C->CR2 = I2C_CR2_RESET_VALUE;
  I2C->FREQR = I2C_FREQR_RESET_VALUE;
  I2C->OARL = I2C_OARL_RESET_VALUE;
  I2C->OARH = I2C_OARH_RESET_VALUE;
  I2C->ITR = I2C_ITR_RESET_VALUE;
  I2C->CCRL = I2C_CCRL_RESET_VALUE;
  I2C->CCRH = I2C_CCRH_RESET_VALUE;
  I2C->TRISER = I2C_TRISER_RESET_VALUE;  
}

void I2C_Begin (uint32_t CLK_Freq){     // Enable I2C & Init I2C Peripheral & Set CLK Pin Freq
    uint8_t I2C_InputClock;
    uint16_t Result;
    I2C_InputClock = CLK_GetClockFreq()/1000000;
    Result = (uint16_t)((I2C_InputClock * 1000000) / (CLK_Freq << (uint8_t)1));

    CLK->PCKENR1 |= CLK_PCKENR1_I2C;                   // Enable I2C Peripheral Clock
    I2C->CR1 = 0;                                      // I2C Disable For Config
    I2C->FREQR = I2C_InputClock;                       // I2C Clock Value
    I2C->TRISER = I2C_InputClock+1;                    // Maximum Rise Time   
    I2C->CCRL = (uint8_t)Result;                       // Clock Control Register LSB
    I2C->CCRH = (uint8_t)((uint8_t)(Result >> 8) & I2C_CCRH_CCR);   // Clock Control Register MSB
    I2C->CR2  = ACK ;
    I2C->OARL = (uint8_t)OwnAddress;                   // Set STM8 Own Address LSB       
    I2C->OARH = (uint8_t)((uint8_t)(Address_Mode | I2C_OARH_ADDCONF) | (uint8_t)((OwnAddress & (uint16_t)0x0300) >> (uint8_t)7));      
      
    //I2C->ITR = 1;       // Enable I2C Interrupts
    
    I2C->CR1 = 1;        // Enable I2C
}

/**
 * @brief Write Slave Address and Data Direction to I2C Bus
 * @param Address 7bit Slave Device Address in I2C Bus 
 * @param Direction Data Direction, Rx= Receive , Tx= Transmitt
 */
void I2C_WriteAddress(uint8_t Address,uint8_t Direction){  
  Address &= (uint8_t)0xFE ;                               // Clear Bit 0 ( Direction Bit )
  I2C->DR = (uint8_t)(Address | (uint8_t)Direction);
  while(!Check_Event((uint16_t)0x0782));               // While Master_Transmitter_Mode_Selected==0 
}

void I2C_WriteData (uint8_t W_Data){                // Function for Write Data only on I2C
  I2C->DR = W_Data;                                 // Send Data to I2C Bus
  while(!Check_Event((uint16_t)0x0784));            // while Master_Byte_Transmitted==0
}

/**
 * @brief Write Slave Address,Data Direction,Data to I2C Bus
 * @param Address : Slave Device Address
 * @param DataDirection : Data Direction, Rx or Tx
 * @param W_Data 
 */
void I2C_Write (uint8_t Address,uint8_t Direction,uint8_t W_Data){  
  I2C_Start();                             // Generate I2C Start Command
                        
  I2C_WriteAddress(Address,Direction);       // Write Address and Data Direction
  I2C_WriteData(W_Data);                     // Write Data to I2C Bus

  I2C_Stop();                                // Generate I2C Stop Command
}

uint8_t I2C_Read (void){           // Read Data from I2C Bus
  while(Busy_Flag());                               // while to BUS BUSY
  return ((uint8_t)I2C->DR);                            // Return the Collected Data
}

void I2C_EnableAcknowledge (void){
  I2C->CR2 |= I2C_CR2_ACK;
}

void I2C_DisableAcknowledge (void){
  I2C->CR2 &= (uint8_t)(~I2C_CR2_ACK);
}

void I2C_Enable (void){      // Enable I2C Peripheral
  I2C->CR1 = 1; 
}

void I2C_Disable(void){     // Disable I2C Peripheral
  I2C->CR1 = 0;
}

void I2C_Start (void){        // Generate Start Command on I2C Bus
  I2C->CR2 |= I2C_CR2_START;
  while(!Check_Event((uint16_t)0x0301));   // while Event_Master_Mode_Selected==0
}

void I2C_Stop (void){         // Generate Stop Command on I2C Bus
  I2C->CR2 |= I2C_CR2_STOP;
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

_Bool Busy_Flag (void){     // Function for Checking I2C Bus Busy
   _Bool Status;
   uint8_t Reg ;
   Reg = (uint8_t)I2C->SR3;

   if((Reg & (uint8_t)0x0302) != 0){
     Status = 1;
   }
   else {
    Status = 0;
   }
    Reg = 0;
    return Status;
}
/*--------------End of File----------------*/