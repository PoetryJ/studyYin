/*
 * @Description: can�����б�
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-01-06 21:59:25
 * @LastEditTime: 2022-07-14 23:19:12
 * @FilePath: \Master_of_2022_C++\Project\User\src\cancontrolist.cpp
 */
#include "cancontrolist.h"

void MesgControlListClass::InitCANControlList(Queue<CanMsgStruct> *can_queue, u8 CAN_x)
{
	u8 i;
	can_queue->Controlist = true;
	if (CAN_x == CAN_1)
	{
		CAN_NodeNumber = CAN1_NodeNumber;
	}
	else
	{
		CAN_NodeNumber = CAN2_NodeNumber;
	}
	for (i = 0; i < CAN_NodeNumber; i++)
	{
		CAN_MesgSentList[i].SendSem = 0;
		CAN_MesgSentList[i].TimeOut = 0;
		CAN_MesgSentList[i].QUEUEFullTimeout = 0;
		CAN_MesgSentList[i].ReceiveNumber = 0;
		CAN_MesgSentList[i].SendNumber = 0;
		CAN_MesgSentList[i].Can_HaveSendqueue = new Queue<CanMsgStruct>(10);
	}
}
/**
 * @brief ����Ҫ���ӵı��ķ����Ӧ���ӵĿ��ƿ���
 * @author: Dandelion
 * @Date: 2022-01-07 10:11:52
 * @return {*}
 * @param {MesgControlGrp} *CAN_MesgSentList
 * @param {Queue<CanMsgStruct>} *can_queue
 * @param {u8} CAN_x
 */
void MesgControlListClass::CANMesgControlList(CanMsgStruct can_msg_in_controlist, u8 CAN_x)
{
	u8 ControlListID = 0xFE; //[i]��Ӧ���Ӱ�ڵ�

	if (can_msg_in_controlist.InConGrpFlag == false)
		return;

	if (CAN_1 == CAN_x)
	{
		/* ��������ǡ�DT���������״�or����ͷ����������ID */
		ControlListID = ((0xff00 & can_msg_in_controlist.Id) >> 8) - 2;
	}
	else
	{
		/* ��ع㲥֡���ĸ�ELMO���ĸ�ת����.etc */
		if (0x320 == can_msg_in_controlist.Id)
		{
			ControlListID = 9; //��Ϊ���ֺ����ֲ���ͳһ��ֱ�Ӱ�ת�����Ĺ㲥֡�������
		}
		else if (0x300 == can_msg_in_controlist.Id)
		{
			ControlListID = 8; //ǰ����0-7��ת����������
		}
		else
		{
			ControlListID = 0xff & can_msg_in_controlist.Id - 1;
		}
	}
	if (ControlListID < CAN_NodeNumber) //��Ҫ����ĳ�����ֻ���ٴμ��� &&ControlListID ��= X
	{
		if (CAN_MesgSentList[ControlListID].Can_HaveSendqueue->isFull())
		{
			CAN_MesgSentList[ControlListID].Can_HaveSendqueue->queue_full = true;
			if (CAN_1 == CAN_x)
			{
				sprintf(user.error, "%s", "Can1ListQueueFull");
			}
			else
			{
				sprintf(user.error, "%s", "Can2ListQueueFull");
			}
		}
		else //�����ٴ�����id
		{
			CAN_MesgSentList[ControlListID].SendSem++;
			CAN_MesgSentList[ControlListID].SendNumber++;
			CAN_MesgSentList[ControlListID].Can_HaveSendqueue->enQueue(can_msg_in_controlist);
		}
	}
	else if (ControlListID > CAN_NodeNumber - 1)
	{
		beep_show(5);
		sprintf(user.error, "%d", ControlListID);
		strcat(user.error, (CAN_1 == CAN_x) ? "_List1ID Err" : "_List2ID Err");
	}
}
/**
 * @brief �����ѷ��ͱ���״̬�������������·���
 * @author: Dandelion
 * @Date: 2022-01-07 12:24:21
 * @return {*}
 * @param {MesgControlGrp} *CAN_MesgSentList
 * @param {Queue<CanMsgStruct>} *can_queue
 * @param {u8} CAN_x
 */
void MesgControlListClass::TraversalControlList(Queue<CanMsgStruct> *can_queue, u8 CAN_x)
{
	u8 i = 0;

	//����
	for (i = 0; i < CAN_NodeNumber; i++)
	{
		if (CAN_MesgSentList[i].SendSem >= 1)
		{
			CAN_MesgSentList[i].TimeOut++;
			if (CAN_MesgSentList[i].TimeOut >= 100) //���б�ڵ�100msδ�յ�����
			{
				if (can_queue->isFull())
				{
					CAN_MesgSentList[i].QUEUEFullTimeout++;
					CAN_MesgSentList[i].Can_HaveSendqueue->queue_full = true;
					// ����������100msʱ����Ϊ������Bug
					if (CAN_1 == CAN_x)
					{
						sprintf(user.error, "%s", "Can1QueueFull");
					}
					else
					{
						sprintf(user.error, "%s", "Can2QueueFull");
					}
					return;
				}
				else if (CAN_MesgSentList[i].Can_HaveSendqueue->isEmpty())
				{
					CAN_MesgSentList[i].Can_HaveSendqueue->queue_empty = true;
					CAN_MesgSentList[i].QUEUEFullTimeout = 0;//�����б�Ľڵ�û����������ոýڵ�ļ�ʱ��
					return;
				}
				else //�Ȳ��Ƕ�����Ҳ���Ƕ��пգ��Ǿ��Ƕ����ˣ��Ѷ��˵�����������������ȥ
				{
					CanMsgStruct re_send_msg;
					if (CAN_MesgSentList[i].Can_HaveSendqueue->deQueue(&re_send_msg) == true)
					{
						CAN_MesgSentList[i].SendSem--;   //��������Ʊ�������һ
						CAN_MesgSentList[i].TimeOut = 0; //����λ����
						CAN_MesgSentList[i].QUEUEFullTimeout = 0;
						can_queue->enQueue(re_send_msg);//װ���
					}
				}
				CanMsgStruct msg_not_mentioned; //������ı��ĳ���
				CAN_MesgSentList[i].Can_HaveSendqueue->deQueue(&msg_not_mentioned);
			}
			// �����ڿ����б��еı������س�����ȥ�ı���ʱ����Ϊ������Bug
			if (CAN_MesgSentList[i].QUEUEFullTimeout > 10 || CAN_MesgSentList[i].SendNumber - CAN_MesgSentList[i].ReceiveNumber > 50)
			{
				CAN_MesgSentList[i].SendSem = -10000; //���ź��ø��������˽ڵ㣬����err
				if (CAN_1 == CAN_x)
				{
					switch (i) //�����ĸ��Ӱ����
					{
					case 0:
						Led8_show(2);
						sprintf(user.error, "%s", "GyroNodeErr");
						break;
					case 1:
						Led8_show(3);
						sprintf(user.error, "%s", "DT0NodeErr");
						break;
					case 2:
						Led8_show(4);
						sprintf(user.error, "%s", "DT1NodeErr");
						break;
					case 3:
						Led8_show(5);
						sprintf(user.error, "%s", "MechNodeErr");
						break;
					case 4:
						Led8_show(6);
						sprintf(user.error, "%s", "CameraNodeErr");
						break;
					case 5:
						Led8_show(7);
						sprintf(user.error, "%s", "LaserSwitchErr");
					default:
						break;
					}
				}
				else
				{
					switch (i)
					{
					case 0:
						sprintf(user.error, "%s", "Vesc1Ero");
						break;

					case 1:
						sprintf(user.error, "%s", "Vesc2Ero");
						break;

					case 2:
						sprintf(user.error, "%s", "Vesc3Ero");
						break;

					case 3:
						sprintf(user.error, "%s", "Vesc4Ero");
						break;

					case 4:
						sprintf(user.error, "%s", "Turn1 Err");
						break;

					case 5:
						sprintf(user.error, "%s", "Turn2 Err");
						break;

					case 6:
						sprintf(user.error, "%s", "Turn3 Err");
						break;

					case 7:
#ifdef STEER_3
						sprintf(user.error, "%s", " Err");
#elif defined(STEER_4)
						sprintf(user.error, "%s", "Turn4 Err");
#endif
						break;
#ifdef STEER_4
					case 8:
					{
						sprintf(user.error, "%s", "VescAllEro Err");
						break;
					}
					case 9:
					{
						sprintf(user.error, "%s", "TurnAll Err");
						break;
					}
#endif
					default:
						break;
					}
				}
			}
		}
	}
}
/**
 * @brief ���������ģ�
 * ��Ϊ���ö��з��ͣ��������һ�����ܶ�������can��������������ÿ������֮�䶼��ʱ������
 * ��������ʱ�������յ��˱��ķ�����һ������һ������������ģ������岻����������
 * @author: Dandelion
 * @Date: 2022-01-07 12:24:08
 * @return {*}
 * @param {CanRxMsg} rx_message
 * @param {u8} id
 * @param {u8} CAN_x
 */
void MesgControlListClass::CanListFeedBackHandler(CanRxMsg rx_message, u8 id)
{
	CanMsgStruct can_meg_rec;
	if (CAN_MesgSentList[id].ReceiveNumber == CAN_MesgSentList[id].SendNumber)
	{
		CAN_MesgSentList[id].TimeOut = 0;
		CAN_MesgSentList[id].SendSem = 0;
		return;
	}
	else
	{
		CAN_MesgSentList[id].ReceiveNumber += 1;
		CAN_MesgSentList[id].TimeOut = 0;
		CAN_MesgSentList[id].SendSem--;
		CAN_MesgSentList[id].Can_HaveSendqueue->deQueue(&can_meg_rec); //���������ĳ���
	}
}
