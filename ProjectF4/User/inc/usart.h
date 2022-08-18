#ifndef _USART_H
#define _USART_H
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#define USART_REC_LEN 200// �����������ֽ��� 200
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
void usart_init(u32 bound);	//USART��ʼ��
void UART1SendByte(unsigned char SendData);
#endif
