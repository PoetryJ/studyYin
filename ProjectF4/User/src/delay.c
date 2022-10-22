/*
 * @Description: 硬性延时
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-01-01 22:55:28
 * @LastEditTime: 2022-01-01 22:58:13
 * @FilePath: \Master_of_2022_C++\Project\User\src\delay.c
 */
#include "delay.h"

/** 
  * @brief  延时、毫秒
  */
	 
void delay_ms(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=42000;
		while(a--);
	}
}

/** 
  * @brief  延时、微秒
  */
void delay_us(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=40;
		while(a--);
	}
}

/** 
  * @brief  延时、指令周期数
  */

void delay(u16 t)
{
	while(t--);
}
