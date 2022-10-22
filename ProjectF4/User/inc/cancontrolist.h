/*
 * @Description: 
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-01-06 21:59:46
 * @LastEditTime: 2022-02-15 19:59:00
 * @FilePath: \Master_of_2022_C++\Project\User\inc\cancontrolist.h
 */
#ifndef _CANCONTROLIST_H
#define _CANCONTROLIST_H

#include "queue.h"
#include "includes.h"
#include "beep.h"
#include "led8.h"

typedef struct _MesgControlGrp // 在C中使用结构体时需要加上struct，或者对结构体使用typedef取别名，而C++可直接使用
{
    s32 SendNumber;            // 所有进入节点的报文总数
    s32 ReceiveNumber;         // 节点收到的报文反馈总数
    u32 QUEUEFullTimeout;      // 由于队列满而无法往里面塞Message的计时数
    s32 SendSem;               // 目前在节点内的报文数
    u16 TimeOut;               // 报文没发出去的计时数
    Queue<CanMsgStruct> *Can_HaveSendqueue;// 发送队列结构体
} MesgControlGrp;

class MesgControlListClass
{
	private:
		u8 CAN_NodeNumber;//节点数
		MesgControlGrp CAN_MesgSentList[10];//存储总线上不同节点板的信息
	public:
		void TraversalControlList(Queue<CanMsgStruct> *can_queue, u8 CAN_x);
		void InitCANControlList(Queue<CanMsgStruct> *can_queue, u8 CAN_x);
		void CANMesgControlList(CanMsgStruct can_msg_in_controlist, u8 CAN_x);
		void CanListFeedBackHandler(CanRxMsg rx_message, u8 id);
};


#endif
