/*
 * @Description: ��������ϵ
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-01-06 17:39:45
 * @LastEditTime: 2022-06-01 21:38:32
 * @FilePath: \Master_of_2022_C++\Project\User\inc\coordinate.h
 */
#ifndef _COORDINATE_H
#define _COORDINATE_H

#include "stm32f4xx.h"

//����������Ƕ�
typedef struct _POSITION
{
    /* data */
    volatile float x; //x axis
    volatile float y; //y axis
    volatile float angle; //�Ƕ���Ϣ
} Position;

//ͨ�õѿ�������ϵXY����
typedef struct _COORDINATES
{
    /* data */
    volatile float x; //x axis
    volatile float y; //y axis
} Coordinates;

//�����ٶ�ʸ��
typedef struct _VELOCITY
{
    /* data */
    volatile float v;
    volatile float vx;
    volatile float vy;
    volatile float vw;//��ÿ��
} Velocity;

extern Position position_now;
extern Position Radar;
extern Velocity velocity_now;
extern Velocity velocity_abs;

#endif
