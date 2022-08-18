#ifndef _PWM_H
#define _PWM_H
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"

// 定时器3端口定义
void TIM14_PWM_Init(u32 arr,u32 psc);
 
#endif

