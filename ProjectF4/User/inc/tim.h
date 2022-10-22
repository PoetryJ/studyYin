#ifndef __TIM_H
#define __TIM_H

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"

#ifdef __cplusplus
extern "C" {
#endif
	
struct TimeStruct
{
  float time_ms;   
	float deltaTime;  
};

extern struct TimeStruct time;
	
	
void TIM2_Configuration(void);
	
void TIM3_Configuration(void);

#ifdef __cplusplus
}
#endif
#endif
