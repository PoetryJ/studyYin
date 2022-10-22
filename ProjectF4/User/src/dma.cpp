/*
 * @Description: DMA
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-01-03 17:51:49
 * @LastEditTime: 2022-06-19 21:28:17
 * @FilePath: \Master_of_2022_C++\Project\User\src\dma.cpp
 */
#include "dma.h"
/**
 * @brief DMA��ʼ��
 * @author: Dandelion
 * @Date: 2022-01-03 20:25:33
 * @return {*}
 * @param {DMA_Stream_TypeDef} *DMA_Streamx
 * @param {uint32_t} chx ͨ��ѡ��
 * @param {uint32_t} par DMA�����ַ
 * @param {uint32_t} mar DMA�洢�� 0 ��ַ
 * @param {uint32_t} dir �洢��������ģʽѡ��
 * @param {u16} ndtr    ���ݴ�����
 */
void DMA_Config(DMA_Stream_TypeDef *DMA_Streamx, uint32_t chx, uint32_t par, uint32_t mar, uint32_t dir, u16 ndtr)
{

    DMA_InitTypeDef DMA_InitStructure;

    if ((u32)DMA_Streamx >= (u32)DMA2) //�õ���ǰstream������DMA2����DMA1
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); // DMA2ʱ��ʹ��
    }
    else
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE); // DMA1ʱ��ʹ��
    }
    DMA_DeInit(DMA_Streamx);

    while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE)
    {
    } //�ȴ�DMA������

    /* ���� DMA Stream */
    DMA_InitStructure.DMA_Channel = chx;                                    //ͨ��ѡ��
    DMA_InitStructure.DMA_PeripheralBaseAddr = par;                         // DMA�����ַ
    DMA_InitStructure.DMA_Memory0BaseAddr = mar;                            // DMA �洢��0��ַ
    DMA_InitStructure.DMA_DIR = dir;                                        // direction of transmit.
    DMA_InitStructure.DMA_BufferSize = ndtr;                                //���ݴ�����
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        //���������ģʽ
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 //�洢������ģʽ
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //�������ݳ���:8λ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         //�洢�����ݳ���:8λ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           // ʹ����ͨģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                   //�е����ȼ�
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         //�洢��ͻ�����δ���
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; //����ͻ�����δ���
    DMA_Init(DMA_Streamx, &DMA_InitStructure);
}

/**
 * @brief �ⲿ���ÿ���DMA����
 * @author: Dandelion
 * @Date: 2022-01-03 20:25:20
 * @return {*}
 * @param {DMA_Stream_TypeDef} *DMA_Streamx
 * @param {u16} ndtr
 */
void DMA_ENABLE(DMA_Stream_TypeDef *DMA_Streamx, u16 ndtr)
{
    DMA_Cmd(DMA_Streamx, DISABLE);
    while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE)
    {
    } //�ȴ�dma������
    DMA_SetCurrDataCounter(DMA_Streamx, ndtr);
    DMA_Cmd(DMA_Streamx, ENABLE);
}
