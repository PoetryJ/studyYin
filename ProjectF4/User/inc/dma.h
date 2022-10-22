/*
 * @Description: DMAÍ·ÎÄ¼þ
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-01-03 17:51:58
 * @LastEditTime: 2022-06-18 22:44:23
 * @FilePath: \Master_of_2022_C++\Project\User\inc\dma.h
 */
#ifndef _DMA_H
#define _DMA_H

#include "stm32f4xx.h"
#include "stm32f4xx_dma.h"

#define DMA_Tx_Mode 0
#define DMA_Rx_Mode 1
#define DMA_TxRx_Mode 2
#define DMA_Close_Mode 3

void DMA_Config(DMA_Stream_TypeDef *DMA_Streamx, uint32_t chx, uint32_t par, uint32_t mar, uint32_t dir, u16 ndtr);
void DMA_ENABLE(DMA_Stream_TypeDef *DMA_Streamx, u16 ndtr);

#endif
