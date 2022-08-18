#include "can.h"
#include "stm32f4xx_can.h"
#include "stdio.h"
#include "string.h"



//CAN ��ʼ��
//tsjw:����ͬ����Ծʱ�䵥Ԫ
//tbs2:ʱ���2��ʱ�䵥Ԫ
//tbs1:ʱ���1��ʱ�䵥Ԫ
//brp :�����ʷ�Ƶ������Χ1~1024����1~1024��tq=(brp)*tpclk1
//mode: @ref CAN_operating_mode

u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode)
{
 GPIO_InitTypeDef GPIO_InitStructure; 
 CAN_InitTypeDef CAN_InitStructure;
 CAN_FilterInitTypeDef CAN_FilterInitStructure;
 NVIC_InitTypeDef NVIC_InitStructure;

 //??????
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//?? PORTA ??
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//?? CAN1 ??
 //??? GPIO
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//????
 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//????
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//??
 GPIO_Init(GPIOA, &GPIO_InitStructure);//??? PA11,PA12
//????????
 GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_CAN1);//PA11 ??? CAN1
 GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_CAN1); //PA12 ??? CAN1
//CAN ????
 CAN_InitStructure.CAN_TTCM=DISABLE; //????????? 
 CAN_InitStructure.CAN_ABOM=DISABLE; //???????? 
 CAN_InitStructure.CAN_AWUM=DISABLE;//??????????
 CAN_InitStructure.CAN_NART=ENABLE;//????????
 CAN_InitStructure.CAN_RFLM=DISABLE; //?????,?????? 
 CAN_InitStructure.CAN_TXFP=DISABLE; //???????????
 CAN_InitStructure.CAN_Mode= mode; //????
 CAN_InitStructure.CAN_SJW=tsjw; //???????? //����ͬ����Ծ���
 CAN_InitStructure.CAN_BS1=tbs1; //Tbs1 ?? CAN_BS1_1tq ~CAN_BS1_16tq
 CAN_InitStructure.CAN_BS2=tbs2;//Tbs2 ?? CAN_BS2_1tq ~ CAN_BS2_8tq
 CAN_InitStructure.CAN_Prescaler=brp; //????(Fdiv)? brp+1
 CAN_Init(CAN1, &CAN_InitStructure); // ??? CAN1
 
 //���ù�����
 CAN_FilterInitStructure.CAN_FilterNumber=0; //�б�ģʽ
 CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList; 
 CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; 
 CAN_FilterInitStructure.CAN_FilterIdHigh=((ID_1 << 3) >> 16) & 0xffff;
 CAN_FilterInitStructure.CAN_FilterIdLow=((ID_1 << 3) & 0xffff)|CAN_ID_EXT;
 CAN_FilterInitStructure.CAN_FilterMaskIdHigh=((ID_2 << 3) >> 16) & 0xffff;
 CAN_FilterInitStructure.CAN_FilterMaskIdLow=((ID_2 << 3) & 0xffff)|CAN_ID_EXT;
 CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
 CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0
 CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
 
 CAN_FilterInitStructure.CAN_FilterNumber = 1;                                // ??????0
 CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;              // ????????g?
 CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;             // 32?
 CAN_FilterInitStructure.CAN_FilterIdHigh = ((ID_3 << 3) >> 16) & 0xffff;     // 32?ID,LED4,??16?
 CAN_FilterInitStructure.CAN_FilterIdLow = ((ID_3 << 3) & 0xffff)|CAN_ID_EXT;            // ??16?
 CAN_FilterInitStructure.CAN_FilterMaskIdHigh = ((ID_4 << 3) >> 16) & 0xffff; // 32?MASK????
 CAN_FilterInitStructure.CAN_FilterMaskIdLow = ((ID_4 << 3) & 0xffff)|CAN_ID_EXT;        // ????????IDE??1
 CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;          // ??????FIFO0
 CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;                       // ?????????FIFO0
 CAN_FilterInit(&CAN_FilterInitStructure);   
 

 CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//FIFO0��Ϣ�Һ��ж����� 
 NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // �����ȼ�Ϊ1
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // �����ȼ�Ϊ0
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 NVIC_Init(&NVIC_InitStructure);

 return 0;
} 

//�жϷ�����
void CAN1_RX0_IRQHandler(void)
{ 
 CanRxMsg RxMessage;
// if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;//û�н��յ����ݣ�ֱ���˳�
 CAN_Receive(CAN1,0,&RxMessage);//��ȡ����
 switch (RxMessage.ExtId)
        {
        case ID_1:
            GPIO_ResetBits(GPIOA, GPIO_Pin_7); //??
            break;
        case ID_2:
            GPIO_SetBits(GPIOA, GPIO_Pin_4); // ??
            break;
        case ID_3:
            GPIO_ResetBits(GPIOA, GPIO_Pin_6); //??
        case ID_4:
            GPIO_SetBits(GPIOA, GPIO_Pin_6);
            break;
// for(i=0;i<RxMessage.DLC;i++)
// buf[i]=RxMessage.Data[i]; 
// return RxMessage.DLC; //���ؽ��յ�������ֵ
}
}

//can����һ������(�̶���ʽ:IDΪ0X12,��׼֡������֡)
//len:���ݳ���(���Ϊ8) msg:����ָ��,���Ϊ8���ֽ�.
//����ֵ0���ɹ���������ʧ��
void CAN1_Send_Msg(void)
{
// u8 mbox;
// u32	i=0;
 CanTxMsg TxMessage;
// TxMessage.StdId=0x12; // ��׼��ʶ��Ϊ0
 TxMessage.ExtId=0x00010400; // ������չ��ʶ��(29λ)
 TxMessage.IDE = CAN_ID_EXT;
 TxMessage.RTR = CAN_RTR_Data; // ��Ϣ����Ϊ����֡��һ֡8λ
 TxMessage.DLC=3; // ������֡��Ϣ
// for(i=0;i<len;i++)
  TxMessage.Data[0] = 'W';         // ??h????
  TxMessage.Data[1] = 'H';
  TxMessage.Data[2] = 'U';
  CAN_Transmit(CAN1, &TxMessage);
// i=0;
// while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;
// if(i>=0XFFF)return 1;
// return 0;
}

