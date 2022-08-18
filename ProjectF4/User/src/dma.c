#include "dma.h"
//DMAx �ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//DMA_Streamx:DMA������,DMA1_Stream0~7/DMA2_Stream0~7
//chx:DMAͨ��ѡ��, @ref DMA_channel DMA_Channel_0~DMA_Channel_7
//par:�����ַ mar:�洢����ַ ndtr:���ݴ����� 
void MYDMA_Config(DMA_Stream_TypeDef *DMA_Streamx,u32 chx,u32 par,u32 mar,u16 ndtr)
{ 
	DMA_InitTypeDef DMA_InitStructure;// �ṹ��
	NVIC_InitTypeDef NVIC_InitStructure;
	
	if((u32)DMA_Streamx>(u32)DMA2)// �õ���ǰ stream ������ DMA2 ���� DMA1
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);// DMA2 ʱ��ʹ��
	}
	else 
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);// DMA1 ʱ��ʹ��
	}
	DMA_DeInit(DMA_Streamx);// ��λ
	while(DMA_GetCmdStatus(DMA_Streamx)!=DISABLE){}// �ȴ� DMA ������
	
	/* ���� DMA Stream */
	DMA_InitStructure.DMA_Channel = chx; // ͨ��ѡ��DMA_Channel_7
	DMA_InitStructure.DMA_PeripheralBaseAddr = par;// DMA �����ַ&USART1->DR
	DMA_InitStructure.DMA_Memory0BaseAddr = mar;// DMA�洢��0��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;// ���ݴ��䷽�򣺴洢��������ģʽ
	DMA_InitStructure.DMA_BufferSize = ndtr;// ���ݴ�����
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;// ���������ģʽ�����ڵ�ַ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;// �洢������ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;// �������ݳ���:8 λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;// �洢�����ݳ���:8 λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ����ͨģʽ����ѭ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;// �е����ȼ�
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;// FIFO ģʽ��ֹ 
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;// FIFO ��ֵ������
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;// �洢��ͻ�����δ���
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;// ����ͻ�����δ���
	
	DMA_Init(DMA_Streamx, &DMA_InitStructure);// ��ʼ�� DMA Stream
		
	// �ж�����
	NVIC_InitStructure.NVIC_IRQChannel=DMA2_Stream7_IRQn;// ����1�����ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;// IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
	
} 

//����һ�� DMA ����
//DMA_Streamx:DMA ������,DMA1_Stream0~7/DMA2_Stream0~7 
//ndtr:���ݴ����� 
void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr)// ����Ӧ�ú���
{
	DMA_Cmd(DMA_Streamx, DISABLE); // �ر� DMA ����
	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){} // ȷ�� DMA ���Ա����� 
	DMA_SetCurrDataCounter(DMA_Streamx,ndtr); // ���ݴ����� 
	DMA_Cmd(DMA_Streamx, ENABLE); // ���� DMA ���䣬��DMA������
}


