/**
 * @author : HS6502
 * @date : 27-Oct-2024  
 * @version : 1.0
 * @brief : Header File for SFL STM8 EEPROM Source File
 */

 #ifndef __SFL_STM8S_EEPROM_H
 #define __SFL_STM8S_EEPROM_H

 #define EEPROM_Begin EEPROM_UnLock

 void EEPROM_Write (uint16_t Address, uint8_t Data);
 void EEPROM_WriteArray (uint16_t Start_Address,const uint8_t Array[]);
 uint8_t EEPROM_Read (uint16_t Address);
 void EEPROM_UnLock (void);
 void EEPROM_Lock (void);
 uint16_t Address_Correction (uint16_t Address);

 #endif