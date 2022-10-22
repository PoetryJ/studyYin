/*
 * @Description: ��������
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2021-08-22 14:36:38
 * @LastEditTime: 2022-05-28 20:46:48
 * @FilePath: \Master_of_2022_C++\Project\User\src\Mymath.cpp
 */

#include "Mymath.h"
/**
 * @brief ���ת�ǣ�rad��
 * @param angleNew �½Ƕ� Deg
 * @param angleLast �ɽǶ� Deg
 * @param angleAdd ��Ҫת���ĽǶ� Deg
 * @return true ��Ҫ����
 */
s8 ClosetTurnAngle(float angleNew, float angleLast, float &angleAdd)
{
    float angleDiff = angleNew - angleLast; // ת�ǣ���������
    int temp = floor(angleDiff / PI + 0.5f); //���ν�ϣ�����1/2����λ��ÿת90����Ҫһ����С�Ƿ���0.5��(PI/2)/PI
    angleAdd = angleDiff - PI * temp;
    return pow(-1.f, temp);
}
/**
 * @brief ��������ת�ַ�������
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
    if (radix != 10)// ����
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


