/**
 * @author : HS6502
 * @date : 25-Oct-2024  @date Updated : 27-Oct-2024
 * @version : 1.0
 * @brief : Library for Using STM8 Internal EEPROM
 */
#include "stm8s.h"
#include "sfl_stm8s_eeprom.h"
#include <string.h>


void EEPROM_Write (uint16_t ByteAddress, uint8_t Data){
    ByteAddress = Address_Correction(ByteAddress);
    (*(uint8_t*)(ByteAddress)) = Data;  
}

void EEPROM_WriteArray (uint16_t Start_Address,char Array[]){
    uint16_t i,Length;
    EEPROM_UnLock();
    Length = strlen(Array);
    for(i=0;i<Length;i++){
        EEPROM_Write(Start_Address + i,Array[i]);
    }
    EEPROM_Lock();
}

uint8_t EEPROM_Read (uint16_t ByteAddress){
    ByteAddress= Address_Correction(ByteAddress);
    return (*(uint8_t *)ByteAddress);
}

void EEPROM_UnLock (void){
    if((FLASH->IAPSR >> 3) == 0){ // if EEPROM Locked, Unlock EEPROM
    FLASH->DUKR = 0xAE;
    FLASH->DUKR = 0x56;
    }
}
void EEPROM_Lock (void){
    FLASH->IAPSR &= 0xF7;         // Lock EEPROM
}

uint16_t Address_Correction (uint16_t Address){
    if(Address < 0x4000){
        Address += 0x4000;
    }
    return Address;
}

