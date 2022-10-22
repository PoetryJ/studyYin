/*
 * @Description: 串口
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-01-03 17:12:59
 * @LastEditTime: 2022-03-15 09:23:00
 * @FilePath: \Master_of_2022_C++\Project\User\inc\usart.h
 */
#ifndef _USART_H
#define _USART_H

#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "includes.h"
#include "queue.h"
#include "dma.h"
#include "Mymath.h"
#include "beep.h"

// 串口具体私有变量
typedef struct _USARTDATASTRUCT
{
    /* data */
    volatile u8 dma_finish;
    u8 dma_rx_buf[USART_RECEIVESIZE];
    u8 data_buf[USART_RECEIVESIZE];
    u8 rx_sta;
    u8 rx_len;
    u8 dma_tx_buf[USART_SENDQUEUESIZE];

    Queue<u8> send_queue;
} UsartDataStruct;

class UsartClass
{
    public:
        UsartDataStruct u1; // 串口1
        UsartDataStruct u2;
        UsartDataStruct u3;
        UsartDataStruct u4;
        UsartDataStruct u5;
        u8 open_num[6]; // DMA队列发送开哪几个串口，“12”->开u1u2
        bool addUsartSendMsg(USART_TypeDef *USARTx, uint8_t *msg, int len);  //添加消息队列
        void sendUsartSendList(USART_TypeDef *USARTx);                  //发送消息 清空队列
        void USARTx_DMAInit(USART_TypeDef *USARTx,
                        uint32_t BaudRate,
                        u16 USART_IT_WAY,
                        u8 DMA_WAY,
                        u8 preprio,
                        u8 subprio);
        void usart_DMA_send(const u8 *usart_x, ...);
};

extern UsartClass usart;
#endif
