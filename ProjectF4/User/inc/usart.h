#ifndef _USART_H
#define _USART_H
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#define USART_REC_LEN 200// 定义最大接收字节数 200
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
void usart_init(u32 bound);	//USART初始化
void UART1SendByte(unsigned char SendData);
#endif
