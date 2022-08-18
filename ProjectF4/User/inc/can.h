#ifndef _CAN_H
#define _CAN_H

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#define ID_1 0x00010200
#define ID_2 0x00010300
#define ID_3 0x00010400
#define ID_4 0x00020100

u8 CAN1_Mode_Init(u8 tsjw, u8 tbs2, u8 tbs1, u16 brp, u8 mode);
void CAN1_Send_Msg(void);
u8 CAN1_Receive_Msg(u8 *buf);
#endif

