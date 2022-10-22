/*
 * @Description: 双车通信
 * @Version: 2.0
 * @Author: Dandelion
 * @Date: 2022-06-11 16:56:19
 * @LastEditTime: 2022-07-22 16:22:10
 * @FilePath: \Master_of_2022_C++\Project\User\src\communication.cpp
 */
#include "communication.h"

namespace Communicate
{
    static TempData temp;
    static Coordinates lagori_place[5][2];
    /**
     * @brief 双车通信
     * @author: Dandelion
     * @Date: 2022-06-17 21:40:36
     * @param {u8} *buff
     * @return {*}
     */
    void ReceiveHandler(u8 *buff)
    {
        switch (buff[0])
        {
        case 'F':
        {
            if (buff[0] == 1)
            {
                user.headball_off = true;
            }
            else
            {
                user.headball_off = false;
            }
            break;
        }
        default:
            break;
        }
    }
    /**
     * @brief 双车通信自检
     * @author: Dandelion
     * @Date: 2022-06-12 10:07:36
     * @return {*}
     */
    void self_check(void)
    {
        u8 buff[6] = {'#', 'C', 'W', 'H', 'U', 0x0a};
        usart.addUsartSendMsg(UART4, buff, 6);
    }
    /**
     * @brief 发送积木坐标
     * @author: Dandelion
     * @Date: 2022-06-12 10:08:39
     * @param {u8} num 5号为最大，1号为最小
     * @param {u8} color 红色为‘R’， 蓝色为‘B’
     * @return {*}
     */
    void send_lagori_place(u8 num, u8 color)
    {
        u8 buff[9];
        u8 temp_color;
        temp_color = (color == 'R') ? 0 : 1;
        buff[0] = '#';
        buff[1] = 'D';
        buff[2] = num;
        buff[3] = color;

        temp.temps16 = lagori_place[num - 1][temp_color].x * 10;
        S16To2Byte(&temp.temps16, &buff[4]);
        temp.temps16 = lagori_place[num - 1][temp_color].y * 10;
        S16To2Byte(&temp.temps16, &buff[6]);
        buff[8] = 0x0a;
        usart.addUsartSendMsg(UART4, buff, 9);
    }
    /**
     * @brief 存储并计算积木坐标
     * @author: Dandelion
     * @Date: 2022-06-12 10:12:47
     * @param {u8} num 积木是几号
     * @param {u8} color 积木的颜色
     * @return {*}
     */
    void write_lagori_place_inMech(u8 num, u8 color)
    {
        u8 temp_color;
        temp_color = (color == 'R') ? 0 : 1;
        if (mech.lagoriInMechPose == normal) //如果为平躺态
        {
            mech.lagoriInMechSide = in_the_middle;
            lagori_place[num - 1][temp_color].x = position_now.x - ((mech.fetch_install[1] + (200.0 + 75.0 * (num - 1)) / 2) * arm_sin_f32(position_now.angle)) * 0.1;
            lagori_place[num - 1][temp_color].y = position_now.y + ((mech.fetch_install[1] + (200.0 + 75.0 * (num - 1)) / 2) * arm_cos_f32(position_now.angle)) * 0.1;
        }
        else if (mech.lagoriInMechPose == stand_up) //如果是侧立态
        {
            float temp_lenY, temp_lenX, theta;
            temp_lenY = mech.fetch_install[1] + 200.0f + 75.0f * num;
            temp_lenX = mech.fetch_install[0] + 200.0f + 75.0f * num - mech.fetch_install[2];
            float len = HYPOT(temp_lenX, temp_lenY);
            if (mech.lagoriInMechSide == on_your_left)
            {
                theta = RadToDeg(atan(temp_lenX / temp_lenY));
            }
            else if (mech.lagoriInMechSide == on_your_right)
            {
                theta = -RadToDeg(atan(temp_lenX / temp_lenY));
            }
            lagori_place[num - 1][temp_color].x = position_now.x - len * sin(position_now.angle + theta);
            lagori_place[num - 1][temp_color].y = position_now.y + len * cos(position_now.angle + theta);
        }
    }
    /**
     * @brief 发送R1坐标
     * @author: Dandelion
     * @Date: 2022-06-12 10:14:36
     * @return {*}
     */
    void send_R1_posi(void)
    {
        u8 buff[7];
        buff[0] = '#';
        buff[1] = 'E';
        temp.temps16 = position_now.x * 10;
        S16To2Byte(&temp.temps16, &buff[2]);
        temp.temps16 = position_now.y * 10;
        S16To2Byte(&temp.temps16, &buff[4]);
        buff[6] = 0x0a;
        usart.addUsartSendMsg(UART4, buff, 7);
    }
}
