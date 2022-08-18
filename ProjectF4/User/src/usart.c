#include "usart.h"

#if 1
#include <stdio.h>
/* 告知连接器不从C库链接使用半主机的函数 */
#pragma import(__use_no_semihosting)
/* 定义 _sys_exit() 以避免使用半主机模式 */
void _sys_exit(int x)
{
    x = x;
}
/* 标准库需要的支持类型 */
struct __FILE
{
    int handle;
};
FILE __stdout;
/*  */
int fputc(int ch, FILE *stream)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);// 检测发送数据寄存器中的数据有没有取走
	USART_SendData(USART1,(uint8_t)ch);// 发送完成，将该字符发送
	return ch;
}
int fgetc(FILE *f)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);// 检测发送数据寄存器中的数据有没有取走,没取走就在循环里
	return (int)USART_ReceiveData(USART1);
}
#endif


u8 USART_RX_BUF[USART_REC_LEN];  //串口接收缓冲数组
u16 USART_RX_STA; //接收状态控制标记
u8 END_Receiving=0;// 接收标志位，为1时完成接收
void usart_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);// 使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);// 使能串口1时钟
	
	//
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	//USART1_TX
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;// 对应IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;// 复用模式
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;// 推挽复用输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;// 50MHz
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;// 上拉,初始灯灭
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIO
	
	//USART初始化
	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure);
	
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);// 开启串口接受中断
//	//USART1 NVIC配置
//	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
}


void USART1_IRQHandler(void)
{
u8 Res;

if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
//????(????????? 0x0d 0x0a ??) {
Res =USART_ReceiveData(USART1);//(USART1->DR); //????????
if((USART_RX_STA&0x8000)==0)//?????
{
if(USART_RX_STA&0x4000)//???? 0x0d
{
if(Res!=0x0a)USART_RX_STA=0;//????,????
else USART_RX_STA|=0x8000; //?????
}
else //???? 0X0D
{
if(Res==0x0d)USART_RX_STA|=0x4000;
else
{
USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
USART_RX_STA++;
if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;
//??????,?????? 
} }
} 
}

void UART1SendByte(unsigned char SendData)
{	   
        USART_SendData(USART1,SendData);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	   
}
