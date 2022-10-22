/*
 * @Description: 蜂鸣器
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2021-08-22 14:36:38
 * @LastEditTime: 2022-07-22 09:30:44
 * @FilePath: \Master_of_2022_C++\Project\User\src\beep.c
 */
#include "beep.h"
/**
 * @brief 蜂鸣器初始化
 * @author: Dandelion
 * @Date: 2021-08-22 21:51:57
 * @return {*}
 */
u16 beep_on_num;

void Beep_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
	BEEP_OFF();
}

/**
 * @brief 开场蜂鸣器特效
 * @author: Dandelion
 * @Date: 2021-08-22 21:53:22
 * @return {*}
 */
void Beep_Start(void)
{
	BEEP_ON();
	delay_ms(30);
	BEEP_OFF();
	delay_ms(40);
	BEEP_ON();
	delay_ms(50);
	BEEP_OFF();
	delay_ms(60);
	BEEP_ON();
	delay_ms(70);
	BEEP_OFF();
	delay_ms(50);
}

/**
 * @brief 供外部调用的beep函数
 * @author: Dandelion
 * @Date: 2021-08-22 21:54:21
 * @return {*}
 */
void Beep_Task(void)
{
	u16 num_temp = beep_on_num;
	if (0 == num_temp)
	{
		OSTimeDly(2000);
	}
	else
	{
		for (int i = 0; i < num_temp; i++)
		{
			if (BEEP_OFF_flag == false)
			{
				BEEP_ON();
				OSTimeDly(1000);
				BEEP_OFF();
				OSTimeDly(1000);
				beep_on_num--;
			}
			else
			{
				beep_on_num = 0;
				break;
			}
		}
		OSTimeDly(2000);
	}
}
/**
 * @brief 特殊报警声(只能用在任务中，不要用在其它地方，会hardfault)
 * @author: Dandelion
 * @Date: 2022-07-22 09:27:28
 * @return {*}
 */
void Beep_Special(void)
{
	BEEP_ON();
	OSTimeDly(4000);
	BEEP_OFF();
	OSTimeDly(1000);
	BEEP_ON();
	OSTimeDly(200);
	BEEP_OFF();
	OSTimeDly(1000);
	BEEP_ON();
	OSTimeDly(500);
	BEEP_OFF();
	OSTimeDly(500);
}
