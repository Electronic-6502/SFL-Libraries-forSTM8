/**
 * @file    sfl_common.c
 * @author  HS6502
 * @date    27-Oct-2024 // Updated : 24-Dec-2024
 * @version 0.9 Beta
 * @brief   Common Used Functions in SFL STM8 Libraries
 */
#include "sfl_common.h"

void TimeOut (uint16_t T_Value){
    uint16_t i;
    for(i=0;i<T_Value;i++);
}
// Cosmic Compiler is not Supported "strlen" Function by Default
#ifdef COSMIC         
uint16_t strlen (uint8_t String[]){
    uint16_t Length = 0;
    uint8_t Temp;
    while(Temp != '\0'){       
        Temp = String [Length];
        Length ++;
    }
    return Length;
}
#endif

uint16_t Check_Parameter (uint16_t Value, uint16_t Max_Allowed, uint16_t Min_Allowed){
    if(Value > Max_Allowed){
        Value = Max_Allowed;
    }
    else if (Value < Min_Allowed){
        Value = Min_Allowed;
    }
    return Value;
}

uint16_t POW (uint8_t Base, uint8_t Exponent ){
    uint8_t i;
    uint16_t Result = 1;
    for(i=0; i<Exponent; i++){
        Result *= Base;
    }
    return Result;
}