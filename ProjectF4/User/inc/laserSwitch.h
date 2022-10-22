/*
 * @Description:光电开关
 * @Version: 2.0
 * @Author: Dandelion
 * @Date: 2022-07-07 16:48:45
 * @LastEditTime: 2022-07-15 16:06:42
 * @FilePath: \Master_of_2022_C++\Project\User\inc\laserSwitch.h
 */
#ifndef _LASERSWITCH_H
#define _LASERSWITCH_H

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "beep.h"
#include "can.h"
#include "Master_para.h"
#include "queue.h"
#include "MyDataProcess.h"
#include "mecha.h"

class laserSwitchClass
{
private:
    /* data */
    CanClass *can_class;
    CanMsgStruct can_msg;

public:
    u8 condition_check;      //是否采用光电检测
    u8 checked_in_threshold; //光电检测范围内是否有东西
    u16 cnt;
    u16 distance;
    void start_check(u8 InConGrpFlag);
    void stop_check(u8 InConGrpFlag);
    void self_check(u8 InConGrpFlag);
    laserSwitchClass(CanClass *_can) { can_class = _can; }
};

void laserSwitchHandler(CanRxMsg rx_message);
extern laserSwitchClass laserSwitch;
void LaserSwitchInit();
#endif
