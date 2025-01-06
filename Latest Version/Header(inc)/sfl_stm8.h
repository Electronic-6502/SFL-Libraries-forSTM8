/**
 * @file    sfl_stm8.h
 * @author  HS6502
 * @date    2-Nov-2024   Updated : 24-Dec-2024
 * @version V1.3
 * @brief   This Header file need to Include to Your Project
 * @brief   Source code for Using the SFL Libraries
 */
/*********** Full Supported Devices ***********
 * STM8S003 Series
 * STM8S103 Series
 **********************************************/
#ifndef __SFL_STM8_CONFIG_H
#define __SFL_STM8_CONFIG_H

#include "stm8s.h"

#ifndef SFL_IS_USED
    #define SFL_IS_USED
#endif 

#include "sfl_common.h"
#include "sfl_stm8s_adc.h"
#include "sfl_stm8_beep.h"
#include "sfl_stm8s_clk.h"
#include "sfl_stm8s_eeprom.h"
#include "sfl_stm8_i2c.h"
#include "sfl_stm8_tim2.h"
#include "sfl_stm8s_uart.h"

#endif
/*-----End of File-----*/