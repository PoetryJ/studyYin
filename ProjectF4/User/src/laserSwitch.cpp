/*
 * @Description:��磨����IOû�й�������ã�
 * @Version: 2.0
 * @Author: Dandelion
 * @Date: 2022-07-07 16:48:12
 * @LastEditTime: 2022-07-16 04:05:28
 * @FilePath: \Master_of_2022_C++\Project\User\src\laserSwitch.cpp
 */
#include "laserSwitch.h"
/**
 * @brief �������жϴ���
 * @author: Dandelion
 * @Date: 2022-07-13 09:28:02
 * @param {CanRxMsg} rx_message
 * @return {*}
 */
void laserSwitchHandler(CanRxMsg rx_message)
{
    static TempData temp;
    if (rx_message.ExtId == ID_SWITCHLASER_RX)
    {
        if (rx_message.Data[0] == 'R' && rx_message.Data[1] == 'E')
        {
            reset_flag.switchLaser_reset++;
        }
        else if (rx_message.Data[0] == 0x41)
        {
            if (rx_message.Data[1] == 'C')
            {
                OSFlagPost(FlagCan1Check, 0x04, OS_FLAG_SET, ErrorCan1);
            }
            can_class.MesgControlListCAN1.CanListFeedBackHandler(rx_message, (u8)(rx_message.ExtId >> 16) - 2);
        }
        else if (rx_message.Data[0] == 'D' && rx_message.Data[1] == 'S')
        {
            Byte2ToU16(&temp.tempu16, &rx_message.Data[2]);
            laserSwitch.distance = temp.tempu16;
            if (laserSwitch.condition_check == true)
            {
                if (laserSwitch.distance <= 11 && laserSwitch.distance > 0)
                {
                    laserSwitch.cnt++;
                    laserSwitch.checked_in_threshold = true;
                    if (laserSwitch.cnt > 20)
                    {
                        OSSemPost(PickSem);
                        laserSwitch.cnt = 0;
                    }
                }
                else
                {
                    laserSwitch.cnt = 0;
                    laserSwitch.checked_in_threshold = false;
                }
            }
        }
    }
}
/**
 * @brief ��ʼ�����
 * @author: Dandelion
 * @Date: 2022-07-13 09:53:15
 * @param {u8} InConGrpFlag
 * @return {*}
 */
void laserSwitchClass::start_check(u8 InConGrpFlag)
{
    condition_check = true;
    can_msg.Id = ID_SWITCHLASER_TX;
    can_msg.DLC = 3;
    can_msg.Data[0] = 0x01;
    can_msg.Data[1] = 'B';
    can_msg.Data[2] = 'G';
    can_msg.InConGrpFlag = InConGrpFlag;

    can_class->addCanSendMsg(CAN1, can_msg);
}
/**
 * @brief ֹͣ�����
 * @author: Dandelion
 * @Date: 2022-07-13 09:55:51
 * @param {u8} InConGrpFlag
 * @return {*}
 */
void laserSwitchClass::stop_check(u8 InConGrpFlag)
{
    condition_check = false;
    can_msg.Id = ID_SWITCHLASER_TX;
    can_msg.DLC = 3;
    can_msg.Data[0] = 0x01;
    can_msg.Data[1] = 'S';
    can_msg.Data[2] = 'T';
    can_msg.InConGrpFlag = InConGrpFlag;

    can_class->addCanSendMsg(CAN1, can_msg);
}

void laserSwitchClass::self_check(u8 InConGrpFlag)
{
    can_msg.Id = ID_BroadCast_TX;
    can_msg.DLC = 5;
    can_msg.Data[0] = 0x00;
    can_msg.Data[1] = 'C';
    can_msg.Data[2] = 'W';
    can_msg.Data[3] = 'H';
    can_msg.Data[4] = 'U';
    can_msg.InConGrpFlag = InConGrpFlag;

    can_class->addCanSendMsg(CAN1, can_msg);
}
/**
 * @brief �����翪�س�ʼ����PB15��
 * @author: Dandelion
 * @Date: 2022-07-07 17:17:23
 * @return {*}
 */
void LaserSwitchInit()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    // IO�ڳ�ʼ��
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //ʹ��GPIOBʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;      //��ͨ����ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50M
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      //����
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //��ʼ��GPIOA5

    //�ⲿ�жϳ�ʼ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); //ʹ��SYSCFGʱ��

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource15);

    EXTI_InitStructure.EXTI_Line = EXTI_Line15;             // LINE12,13��ҡ��L1,R1
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     //�ж��¼�
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش�������֤ÿ�ΰ���ʱ���ܷ�Ӧ�����������������Ҫ�ȵ�����ʱ�Ż�����Ӧ��
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;               //ʹ��LINE
    EXTI_Init(&EXTI_InitStructure);                         //����

    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;      //�ⲿ�ж�1
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //�����ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);                           //����
}

#ifdef __cplusplus
extern "C"
{
#endif
    void EXTI15_10_IRQHandler(void)
    {
        if (EXTI_GetITStatus(EXTI_Line15) != RESET)
        {
            if (laserSwitch.condition_check)
            {
                beep_show(1);
                laserSwitch.checked_in_threshold = true;
                OSSemPost(PickSem);
            }
            EXTI_ClearITPendingBit(EXTI_Line15);
        }
    }

#ifdef __cplusplus
}
#endif
