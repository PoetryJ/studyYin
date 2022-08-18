#include "time.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "dma.h"
#include "led.h"
#include "can.h"
#define SEND_BUF_SIZE 300

// ͨ����ʱ��3�жϳ�ʼ��
// arr���Զ���װֵ�� psc��ʱ��Ԥ��Ƶ��
// ��ʱ�����ʱ����㷽����Tout=((arr+1)*(psc+1))/Ft us.
// Ft=��ʱ������Ƶ�ʣ���λMHz
// ����ʹ�õ��Ƕ�ʱ��8

void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;// �ṹ�嶨ʱ��
	NVIC_InitTypeDef NVIC_InitStructure;// �ṹ���жϷ������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);// ʹ��TIM3ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period=arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;// ���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;// ��δ��Ƶ֮ǰ ����Ҫ�����µķ�Ƶ����ȷ����ʱ����ȷ��һ������ʱʱ��
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);// ��ʼ����ʱ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);// ����ʱ��3�����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;// ��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0X01;// ��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0X03;// ��Ӧ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;// ʹ���ж�
	NVIC_Init(&NVIC_InitStructure);// ��ʼ��NVIC
	
	TIM_Cmd(TIM3,ENABLE);// ʹ�ܶ�ʱ��3
	
};

// ��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)// ����ж�
	{
//	MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);// ����һ��DMA����
		GPIO_ToggleBits(GPIOA,GPIO_Pin_4);// ��ת��ƽLED�����������ָʾ��ʱ�ж�
		CAN1_Send_Msg();
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);// ����жϱ�־λ
}
