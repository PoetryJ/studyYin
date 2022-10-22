/*
 * @Description:
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-01-02 09:56:46
 * @LastEditTime: 2022-07-13 10:22:30
 * @FilePath: \Master_of_2022_C++\Project\User\inc\can.h
 */
#ifndef __CAN_H
#define __CAN_H

#include "stm32f4xx.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "queue.h"
#include "cancontrolist.h"

class CanClass
{
public:
  void CAN1_Configuration(u8 prep_prio, u8 sub_prio);
  void CAN2_Configuration(u8 prep_prio, u8 sub_prio);
  void CAN_Self_Check(CAN_TypeDef *CANx);
  bool addCanSendMsg(CAN_TypeDef *CANx, CanMsgStruct can_send_msg); //添加can路要发送的消息
  void sendCanSendList(CAN_TypeDef *CANx);                          //发送消息，清空队列
  Queue<CanMsgStruct> *can1_send_list, *can2_send_list;             //发送队列
  void canSendMsg(CanMsgStruct can_msg, CAN_TypeDef *CANx);
  MesgControlListClass MesgControlListCAN1;
  MesgControlListClass MesgControlListCAN2;

private:
  void canSendMsg(u8 *msg, u8 len, int id, CAN_TypeDef *CANx);
};
extern void SensorsReceiveHandler(CanRxMsg rx_message);
//extern void laserSwitchHandler(CanRxMsg rx_message);
extern void MechaReceiveHandler(CanRxMsg rx_message);
extern void ChassisReceiveHandler(CanRxMsg rx_message);
//extern void CameraReceiveHandler(CanRxMsg rx_message);

extern CanClass can_class;
#endif
