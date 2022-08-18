#include "pwm.h"
#include "stm32f4xx_gpio.h"

// TIM14 PWM部分初始化
// PWM输出初始化
// arr：自动重装值 psc：时钟预分频值
void TIM14_PWM_Init(u32 arr,u32 psc)
{
GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
	
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE); // 使能TIM14时钟
	
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // 使能GPIOA时钟
	
GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM14); // 复用为TIM14

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; // GPIOA4
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 复用功能
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 速度100
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽复用输出
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 上拉
GPIO_Init(GPIOA,&GPIO_InitStructure); // 初始化PA4
 
TIM_TimeBaseStructure.TIM_Prescaler=psc; // 设置预分频值
TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; // 向上计数模式
TIM_TimeBaseStructure.TIM_Period=arr; // 设置自动重装载值
TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; // 设置时钟分割
TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure);   // 根据指定的参数初始化TIM14

// 初始化TIM14 Channel PWM模式
TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // 调制PWM模式1
TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 比较输出使能
TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; // 输出极性低
TIM_OC1Init(TIM14, &TIM_OCInitStructure); // 初始化外设TIM14 4OC1

TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable); // 使能预装载寄存器
TIM_ARRPreloadConfig(TIM14,ENABLE);// ARPE使能

TIM_Cmd(TIM14, ENABLE); // 使能TIM14
}
