/*
 * @Description:
 * @Version: 2.0
 * @Author: Dandelion
 * @Date: 2022-05-21 17:50:39
 * @LastEditTime: 2022-07-22 09:26:52
 * @FilePath: \Master_of_2022_C++\Project\User\inc\beep.h
 */
#ifndef _BEEP_H
#define _BEEP_H

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "includes.h"
#define BEEP_OFF() GPIOA->BSRRH = GPIO_Pin_8
#define BEEP_ON() GPIOA->BSRRL = GPIO_Pin_8
#define BEEP_TOGGLE GPIOG->ODR ^= GPIO_Pin_1
#define beep_show(x) beep_on_num += (x)
#define beep_clear() beep_on_num = 0

#ifdef __cplusplus
extern "C"
{
#endif

    extern u16 beep_on_num;
    extern u8 BEEP_OFF_flag;
    void Beep_Configuration(void);
    void Beep_Start(void);
    void Beep_Task(void);
    void Beep_Special(void);

#ifdef __cplusplus
}
#endif

#endif
