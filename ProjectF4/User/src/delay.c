/*
 * @Description: Ӳ����ʱ
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-01-01 22:55:28
 * @LastEditTime: 2022-01-01 22:58:13
 * @FilePath: \Master_of_2022_C++\Project\User\src\delay.c
 */
#include "delay.h"

/** 
  * @brief  ��ʱ������
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
  * @brief  ��ʱ��΢��
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
  * @brief  ��ʱ��ָ��������
  */

void delay(u16 t)
{
	while(t--);
}
