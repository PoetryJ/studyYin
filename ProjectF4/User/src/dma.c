#include "dma.h"
//DMAx 的各通道配置
//这里的传输形式是固定的,这点要根据不同的情况来修改
//从存储器->外设模式/8位数据宽度/存储器增量模式
//DMA_Streamx:DMA数据流,DMA1_Stream0~7/DMA2_Stream0~7
//chx:DMA通道选择, @ref DMA_channel DMA_Channel_0~DMA_Channel_7
//par:外设地址 mar:存储器地址 ndtr:数据传输量 
void MYDMA_Config(DMA_Stream_TypeDef *DMA_Streamx,u32 chx,u32 par,u32 mar,u16 ndtr)
{ 
	DMA_InitTypeDef DMA_InitStructure;// 结构体
	NVIC_InitTypeDef NVIC_InitStructure;
	
	if((u32)DMA_Streamx>(u32)DMA2)// 得到当前 stream 是属于 DMA2 还是 DMA1
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);// DMA2 时钟使能
	}
	else 
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);// DMA1 时钟使能
	}
	DMA_DeInit(DMA_Streamx);// 复位
	while(DMA_GetCmdStatus(DMA_Streamx)!=DISABLE){}// 等待 DMA 可配置
	
	/* 配置 DMA Stream */
	DMA_InitStructure.DMA_Channel = chx; // 通道选择DMA_Channel_7
	DMA_InitStructure.DMA_PeripheralBaseAddr = par;// DMA 外设地址&USART1->DR
	DMA_InitStructure.DMA_Memory0BaseAddr = mar;// DMA存储器0地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;// 数据传输方向：存储器到外设模式
	DMA_InitStructure.DMA_BufferSize = ndtr;// 数据传输量
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;// 外设非增量模式，串口地址不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;// 存储器增量模式
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;// 外设数据长度:8 位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;// 存储器数据长度:8 位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// 使用普通模式，不循环
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;// 中等优先级
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;// FIFO 模式禁止 
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;// FIFO 阈值，不管
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;// 存储器突发单次传输
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;// 外设突发单次传输
	
	DMA_Init(DMA_Streamx, &DMA_InitStructure);// 初始化 DMA Stream
		
	// 中断配置
	NVIC_InitStructure.NVIC_IRQChannel=DMA2_Stream7_IRQn;// 串口1发送中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;// IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
} 

//开启一次 DMA 传输
//DMA_Streamx:DMA 数据流,DMA1_Stream0~7/DMA2_Stream0~7 
//ndtr:数据传输量 
void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr)// 发送应用函数
{
	DMA_Cmd(DMA_Streamx, DISABLE); // 关闭 DMA 传输
	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){} // 确保 DMA 可以被设置 
	DMA_SetCurrDataCounter(DMA_Streamx,ndtr); // 数据传输量 
	DMA_Cmd(DMA_Streamx, ENABLE); // 开启 DMA 传输，打开DMA数据流
}


