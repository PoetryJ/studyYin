/*
 * @Description: Ö÷¿Ø°åledµÆ
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-01-01 09:06:26
 * @LastEditTime: 2022-08-10 03:22:56
 * @FilePath: \Master_of_2022_C++\Project\User\src\led.c
 */
#include "led.h"
/**
 * @brief µÆ³õÊ¼»¯
 * @author: Dandelion
 * @Date: 2022-01-01 09:15:30
 * @return {*}
 */
void LED_Configuration()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	LED_BLUE_ON;
	LED_GREEN_ON;
	LED_YELLOW_ON;
	LED_RED_ON;
}
