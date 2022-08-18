#include "main.h"
//#include "usart.h"
#include "led.h"
//#include "stdio.h"
#include "time.h"
//#include "string.h"
//#include "dma.h"
#include "delay.h"
//#include "can.h"

//#define SEND_BUF_SIZE 300
//char SendBuff[SEND_BUF_SIZE];// 
//char TEXT_TO_SEND[]={'W','H','U'};// ???????WHU
//char times[3]={0};
//u8 t=0;
//u8 j=0;

int main()
{
	SystemInit();
//	u8 i;
//	u8 k;
//	u8 p;
//	u8 mode=1;// CAN工作模式，0：普通模式，1：环回模式
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
//	usart_init(115200);								
	TIM3_Int_Init(5000-1,8400-1);
	LED_Init();
//	MYDMA_Config(DMA2_Stream7,DMA_Channel_4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);
//  CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_4tq,CAN_BS1_9tq,3,CAN_Mode_Normal); //CAN ???????,??? 500Kbps
//	// 填充字符
//  j=sizeof(TEXT_TO_SEND);
//  //SendBuff[0]='#';
//	//strcat(SendBuff,TEXT_TO_SEND);
//	for(i=0;i<60;i++)
//	{
//		if(t>=j)
//		{
//			 t=0;
//			 i--;
//		}
//		else
//		{
//			 SendBuff[i]=TEXT_TO_SEND[t];
//			 t++;
//		}
//	}
//	SendBuff[64]=0x0a;
//	i='1';
//	k='0';
//	p='0';
	
	
	while (1)
	{
//	  // 确定计数位置
//		times[0]=p;
//		times[1]=k;
//		times[2]=i;
//		SendBuff[61]=times[0];
//		SendBuff[62]=times[1];
//		SendBuff[63]=times[2];
		
//		USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); 
  

//		while(1)
//		{
//			if(DMA_GetFlagStatus(DMA2_Stream7,DMA_FLAG_TCIF7)!=RESET)// ???????,TCIF?1?
//			{
//				DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7);// ????????
//				DMA_ClearITPendingBit(DMA2_Stream7,DMA_FLAG_TCIF7);
//				break;
//			}
		    // LED
	      GPIO_ResetBits(GPIOA,GPIO_Pin_5); 
        Delay_ms(100); 	
        GPIO_SetBits(GPIOA,GPIO_Pin_5);
        Delay_ms(100); 	
//		}
//		i++;// i?????????
//		if(i>'9')
//		{
//			i='0';
//			k++;
//		}
//		if(k>'9')
//		{
//			k='0';
//			p++;
//		}
//		if(p>'9')
//		{
//			p='0';
//		}
//		Delay_ms(200);
  
}
}
