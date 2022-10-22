/*
 * @Description: 数据类型
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2021-08-22 14:36:38
 * @LastEditTime: 2022-05-28 20:46:48
 * @FilePath: \Master_of_2022_C++\Project\User\src\Mymath.cpp
 */

#include "Mymath.h"
/**
 * @brief 最近转角（rad）
 * @param angleNew 新角度 Deg
 * @param angleLast 旧角度 Deg
 * @param angleAdd 需要转过的角度 Deg
 * @return true 需要反向
 */
s8 ClosetTurnAngle(float angleNew, float angleLast, float &angleAdd)
{
    float angleDiff = angleNew - angleLast; // 转角（过程量）
    int temp = floor(angleDiff / PI + 0.5f); //数形结合，左移1/2个单位，每转90度需要一次最小角反向，0.5即(PI/2)/PI
    angleAdd = angleDiff - PI * temp;
    return pow(-1.f, temp);
}
/**
 * @brief 整型数据转字符串函数
 * @author: Dandelion
 * @Date: 2021-08-22 21:01:57
 * @return {*}
 * @param {int} value
 * @param {char} *string
 * @param {int} radix
 */
char *itoa(int value, char *string, int radix)
{
    u32 i;
    int d;
    int flag = 0;
    char *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)// 基数
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 100000000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;
}


