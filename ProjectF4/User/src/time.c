#include "time.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "dma.h"
#include "led.h"
#include "can.h"
#define SEND_BUF_SIZE 300

// 通过定时器3中断初始化
// arr：自动重装值。 psc：时钟预分频数
// 定时器溢出时间计算方法：Tout=((arr+1)*(psc+1))/Ft us.
// Ft=定时器工作频率，单位MHz
// 这里使用的是定时器8

void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;// 结构体定时器
	NVIC_InitTypeDef NVIC_InitStructure;// 结构体中断服务程序
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);// 使能TIM3时钟
	
	TIM_TimeBaseInitStructure.TIM_Period=arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;// 向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;// 在未分频之前 根据要求建立新的分频器，确定定时器，确定一定的延时时间
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);// 初始化定时器TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);// 允许定时器3更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;// 定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0X01;// 抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0X03;// 响应优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;// 使能中断
	NVIC_Init(&NVIC_InitStructure);// 初始化NVIC
	
	TIM_Cmd(TIM3,ENABLE);// 使能定时器3
	
};

// 定时器3中断服务函数
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)// 溢出中断
	{
//	MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);// 开启一次DMA传输
		GPIO_ToggleBits(GPIOA,GPIO_Pin_4);// 翻转电平LED，这个灯用来指示定时中断
		CAN1_Send_Msg();
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);// 清除中断标志位
}
