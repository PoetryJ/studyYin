#ifndef _PWM_H
#define _PWM_H
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"

// ��ʱ��3�˿ڶ���
void TIM14_PWM_Init(u32 arr,u32 psc);
 
#endif

