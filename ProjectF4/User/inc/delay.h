/*
 * @Description: delay???
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2021-08-22 14:36:38
 * @LastEditTime: 2022-01-01 23:00:49
 * @FilePath: \Master_of_2022_C++\Project\User\inc\delay.h
 */
#ifndef _DELAY_H
#define _DELAY_H

#ifdef __cplusplus
extern "C"{
#endif
	
#include "stm32f4xx.h"

void delay_ms(unsigned int t);
void delay_us(unsigned int t);
void delay(u16 t);
	
#ifdef __cplusplus
}
#endif

#endif
