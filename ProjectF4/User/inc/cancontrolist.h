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

typedef struct _MesgControlGrp // ��C��ʹ�ýṹ��ʱ��Ҫ����struct�����߶Խṹ��ʹ��typedefȡ��������C++��ֱ��ʹ��
{
    s32 SendNumber;            // ���н���ڵ�ı�������
    s32 ReceiveNumber;         // �ڵ��յ��ı��ķ�������
    u32 QUEUEFullTimeout;      // ���ڶ��������޷���������Message�ļ�ʱ��
    s32 SendSem;               // Ŀǰ�ڽڵ��ڵı�����
    u16 TimeOut;               // ����û����ȥ�ļ�ʱ��
    Queue<CanMsgStruct> *Can_HaveSendqueue;// ���Ͷ��нṹ��
} MesgControlGrp;

class MesgControlListClass
{
	private:
		u8 CAN_NodeNumber;//�ڵ���
		MesgControlGrp CAN_MesgSentList[10];//�洢�����ϲ�ͬ�ڵ�����Ϣ
	public:
		void TraversalControlList(Queue<CanMsgStruct> *can_queue, u8 CAN_x);
		void InitCANControlList(Queue<CanMsgStruct> *can_queue, u8 CAN_x);
		void CANMesgControlList(CanMsgStruct can_msg_in_controlist, u8 CAN_x);
		void CanListFeedBackHandler(CanRxMsg rx_message, u8 id);
};


#endif
