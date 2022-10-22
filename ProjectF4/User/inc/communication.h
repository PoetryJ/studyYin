/*
 * @Description: Ë«³µÍ¨ÐÅ
 * @Version: 2.0
 * @Author: Dandelion
 * @Date: 2022-06-11 16:57:38
 * @LastEditTime: 2022-06-17 23:15:59
 * @FilePath: \whurobocon2022-r1\Project\User\inc\communication.h
 */
#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#include "usart.h"
#include "mecha.h"
#include "sensor.h"
#include "Mymath.h"
#include "coordinate.h"
#include "MyDataProcess.h"

namespace Communicate
{
    void send_lagori_place(u8 num, u8 color);
    void write_lagori_place_inMech(u8 num, u8 color);
    void send_R1_posi(void);
    void self_check(void);
    void ReceiveHandler(u8 *buff);
}

#endif
