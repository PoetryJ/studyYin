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
//这个数据，是不是可以通过监控一波来给定一个size
#define CAN_SENDQUEUESIZE 20
#define CAN_HAVESENDQUEUESIZE 20
#define USART_SENDQUEUESIZE 500
#define USART_RECEIVESIZE 64
const int QUEUEMAXSIZE = 500; //动态分配内存，小心堆栈溢出
/**
 * @brief 简化过的can报文
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
// 循环队列模板类，使用模板时实现也要放在头文件里，不然编译时看不到实现会报错
template <class T>
class Queue
{
public:
	u8 queue_empty;
	u8 queue_full;
	u8 Controlist;
	Queue(int _size = QUEUEMAXSIZE)
	{ //默认值，不设置的话就是最大值
		front = rear = 0;
		size = _size;
		data = (T *)malloc(sizeof(T) * size); //申请一片内存
	};
	void clear(void);
	bool enQueue(T ch);					   //入队,如果队列满了 数据不会入队
	bool enQueue(T *ch, int n);			   //入队
	bool deQueue(T *ch);				   //出队
	bool deQueue(T *ch, int n);			   //单字节for循环出队
	void deQueue_all(u8 *usartDMA_tx_buf); //直接赋值出队（memcpy效率高）
	bool isFull(void);					   //判断是否满队
	bool isEmpty(void);
	u16 getQueueLength(void); //获得当前需要出队的队列长度
	int getQueueFront(void);  //获得当前队列头部值
	int getQueueRear(void);	  //获得当前队列尾部值
	int getQueueSize(void);	  //获得当前队列大小

private:
	vu32 front;// 队首
	vu32 rear;// 队尾
	u32 size; //预设定队列大小
	// vu32 count;
	vu16 length; //需要出队的队列的长度
	T *data;	 //储存队列报文具体信息
				 //		T data[QUEUEMAXSIZE];    //储存队列报文具体信息
};
/**
 * @brief 判断队列是否满
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
 * @brief 判断队列是否空
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
 * @brief 入队单个元素
 * @author: Dandelion
 * @Date: 2022-03-24 14:34:05
 * @param {*}
 * @return {*}
 */
template <class T>
bool Queue<T>::enQueue(T ch)
{
	if (isFull() != true) //队列内还有空间
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
 * @brief 从某地址开始入队len长度元素
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
		memcpy(&(data[rear]), ch, len * sizeof(T)); //拷贝的是字节数   用memcpy快一点
		rear = (rear + len) % size;
		// OS_CPU_SR cpu_sr;
		// OS_ENTER_CRITICAL();
		// count += len;
		// OS_EXIT_CRITICAL();
		return true;
	}
}
/**
 * @brief 将队头元素出掉
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
 * @brief 将队列里前n个元素出到数组中
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
 * @brief 串口专用出队函数，将队列里已有元素全部出掉
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
 * @brief 获得队列元素长度
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
 * @brief 队列清空CLR
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
