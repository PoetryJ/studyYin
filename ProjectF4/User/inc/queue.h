/*
 * @Description:
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-01-02 19:06:25
 * @LastEditTime: 2022-07-13 21:22:13
 * @FilePath: \Master_of_2022_C++\Project\User\inc\queue.h
 */
#ifndef __QUEUE_H
#define __QUEUE_H

#include <string.h>
#include <stdlib.h>
#include "stm32f4xx.h"
#include "includes.h"

#define CAN_1 (u8)(0x01 << 0)
#define CAN_2 (u8)(0x01 << 1)

/***********************************/
/*************** u32 Driving_Motor_ID_RX ******************/
#define ID_DMotor_All_RX 0x280
#define ID_Driving_Motor1_RX 0x281
#define ID_Driving_Motor2_RX 0x282
#define ID_Driving_Motor3_RX 0x283
#define ID_Driving_Motor4_RX 0x284

#define ID_TMotor_All_RX 0x2A0
#define ID_Turn_Motor1_RX 0x285
#define ID_Turn_Motor2_RX 0x286
#define ID_Turn_Motor3_RX 0x287
#define ID_Turn_Motor4_RX 0x288

/*************** u32 CAN_ID_RX ******************/
#define ID_GyrScope_RX 0x00020101
#define ID_DT0_RX 0x00030101
#define ID_DT1_RX 0x00040101
#define ID_Mech_RX 0x00050101
#define ID_CAMERA_RX 0x00060101
#define ID_SWITCHLASER_RX 0x00070101

/************************************************/

/*************** u32 CAN_ID_TX ******************/
#define ID_BroadCast_TX 0x00010000
#define ID_GyrScope_TX 0x00010200
#define ID_DT0_TX 0x00010300
#define ID_DT1_TX 0x00010400
#define ID_Mech_TX 0x00010500
#define ID_CAMERA_TX 0x00010600
#define ID_SWITCHLASER_TX 0x00010700

#define ID_DMotor_All_TX 0x300
#define ID_Driving_Motor1_TX 0x301
#define ID_Driving_Motor2_TX 0x302
#define ID_Driving_Motor3_TX 0x303
#define ID_Driving_Motor4_TX 0x304

#define ID_TMotor_All_TX 0x320
#define ID_Turn_Motor1_TX 0x305
#define ID_Turn_Motor2_TX 0x306
#define ID_Turn_Motor3_TX 0x307
#define ID_Turn_Motor4_TX 0x308
/************************************************/

/*************** u32 Func_ID ******************/
/************************************************/
#define CAN1_NodeNumber 8u
#define CAN2_NodeNumber 10u
//������ݣ��ǲ��ǿ���ͨ�����һ��������һ��size
#define CAN_SENDQUEUESIZE 20
#define CAN_HAVESENDQUEUESIZE 20
#define USART_SENDQUEUESIZE 500
#define USART_RECEIVESIZE 64
const int QUEUEMAXSIZE = 500; //��̬�����ڴ棬С�Ķ�ջ���
/**
 * @brief �򻯹���can����
 * @author: Dandelion
 * @Date: 2022-01-07 09:14:46
 * @return {*}
 */
typedef struct _Can_Sendstruct
{
	u32 Id;
	u8 DLC;
	u8 Data[8];
	u8 InConGrpFlag;
} CanMsgStruct;
// ѭ������ģ���࣬ʹ��ģ��ʱʵ��ҲҪ����ͷ�ļ����Ȼ����ʱ������ʵ�ֻᱨ��
template <class T>
class Queue
{
public:
	u8 queue_empty;
	u8 queue_full;
	u8 Controlist;
	Queue(int _size = QUEUEMAXSIZE)
	{ //Ĭ��ֵ�������õĻ��������ֵ
		front = rear = 0;
		size = _size;
		data = (T *)malloc(sizeof(T) * size); //����һƬ�ڴ�
	};
	void clear(void);
	bool enQueue(T ch);					   //���,����������� ���ݲ������
	bool enQueue(T *ch, int n);			   //���
	bool deQueue(T *ch);				   //����
	bool deQueue(T *ch, int n);			   //���ֽ�forѭ������
	void deQueue_all(u8 *usartDMA_tx_buf); //ֱ�Ӹ�ֵ���ӣ�memcpyЧ�ʸߣ�
	bool isFull(void);					   //�ж��Ƿ�����
	bool isEmpty(void);
	u16 getQueueLength(void); //��õ�ǰ��Ҫ���ӵĶ��г���
	int getQueueFront(void);  //��õ�ǰ����ͷ��ֵ
	int getQueueRear(void);	  //��õ�ǰ����β��ֵ
	int getQueueSize(void);	  //��õ�ǰ���д�С

private:
	vu32 front;// ����
	vu32 rear;// ��β
	u32 size; //Ԥ�趨���д�С
	// vu32 count;
	vu16 length; //��Ҫ���ӵĶ��еĳ���
	T *data;	 //������б��ľ�����Ϣ
				 //		T data[QUEUEMAXSIZE];    //������б��ľ�����Ϣ
};
/**
 * @brief �ж϶����Ƿ���
 * @author: Dandelion
 * @Date: 2022-03-24 14:33:48
 * @param {*}
 * @return {*}
 */
template <class T>
bool Queue<T>::isFull()
{
	return ((rear + 1) % size == front);
}
/**
 * @brief �ж϶����Ƿ��
 * @author: Dandelion
 * @Date: 2022-03-24 14:33:57
 * @param {*}
 * @return {*}
 */
template <class T>
bool Queue<T>::isEmpty()
{
	return (rear == front);
}
/**
 * @brief ��ӵ���Ԫ��
 * @author: Dandelion
 * @Date: 2022-03-24 14:34:05
 * @param {*}
 * @return {*}
 */
template <class T>
bool Queue<T>::enQueue(T ch)
{
	if (isFull() != true) //�����ڻ��пռ�
	{
		queue_full = false;
		data[rear] = ch;
		rear = (rear + 1) % size;
		// OS_CPU_SR cpu_sr;
		// OS_ENTER_CRITICAL();
		// count++;
		// OS_EXIT_CRITICAL();
		return true;
	}
	else
	{
		queue_full = true;
		return false;
	}
}
/**
 * @brief ��ĳ��ַ��ʼ���len����Ԫ��
 * @author: Dandelion
 * @Date: 2022-03-24 14:34:25
 * @param {*}
 * @return {*}
 */
template <class T>
bool Queue<T>::enQueue(T *ch, int len)
{
	if (((rear + len) % size) == front)
	{
		queue_full = true;
		return false;
	}
	else
	{
		queue_full = false;
		memcpy(&(data[rear]), ch, len * sizeof(T)); //���������ֽ���   ��memcpy��һ��
		rear = (rear + len) % size;
		// OS_CPU_SR cpu_sr;
		// OS_ENTER_CRITICAL();
		// count += len;
		// OS_EXIT_CRITICAL();
		return true;
	}
}
/**
 * @brief ����ͷԪ�س���
 * @author: Dandelion
 * @Date: 2022-03-24 14:34:57
 * @param {*}
 * @return {*}
 */
template <class T>
bool Queue<T>::deQueue(T *ch)
{
	if (isEmpty() != true)
	{
		*ch = data[front];
		front = (front + 1) % size;
		// OS_CPU_SR cpu_sr;
		// OS_ENTER_CRITICAL();
		// count--;
		// OS_EXIT_CRITICAL();
		queue_empty = false;
		return true;
	}
	else
	{
		queue_empty = true;
		return false;
	}
}
/**
 * @brief ��������ǰn��Ԫ�س���������
 * @author: Dandelion
 * @Date: 2022-03-24 14:36:55
 * @param {*}
 * @return {*}
 */
template <class T>
bool Queue<T>::deQueue(T *ch, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (!deQueue((ch + i)))
			return false;
	}
	return true;
}
/**
 * @brief ����ר�ó��Ӻ�����������������Ԫ��ȫ������
 * @author: Dandelion
 * @Date: 2022-03-24 14:38:12
 * @param {*}
 * @return {*}
 */
template <class T>
void Queue<T>::deQueue_all(u8 *usartDMA_tx_buf)
{
	if (isEmpty() == true)
	{
		/* code */
		queue_empty = true;
		return;
	}
	else
	{
		queue_empty = false;

		if (rear > front)
			length = rear - front;
		else if (rear < front)
			length = size - (front - rear);
		else
			length = 0;
		memcpy(usartDMA_tx_buf, &data[front], length);
		front = (front + length) % size;
		// OS_CPU_SR cpu_sr;
		// OS_ENTER_CRITICAL();
		// count -= length;
		// OS_EXIT_CRITICAL();
	}
}
/**
 * @brief ��ö���Ԫ�س���
 * @author: Dandelion
 * @Date: 2022-03-24 14:39:04
 * @param {*}
 * @return {*}
 */
template <class T>
u16 Queue<T>::getQueueLength()
{
	return length;
}
/**
 * @brief �������CLR
 * @author: Dandelion
 * @Date: 2022-03-24 14:39:16
 * @param {*}
 * @return {*}
 */
template <class T>
void Queue<T>::clear()
{
	front = 0;
	rear = 0;
}

#endif
