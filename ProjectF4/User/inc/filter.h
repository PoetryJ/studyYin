/*
 * @Description: �˲����ṹ��
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-02-20 20:18:33
 * @LastEditTime: 2022-03-08 20:22:46
 * @FilePath: \Master_of_2022_C++\Project\User\inc\filter.h
 */
#ifndef _FILTER_H
#define _FILTER_H

#include "arm_math.h"
#include <stdio.h>
#include <stdlib.h>
#include "tim.h"
#include "float.h"

class kalmanClass
{
private:
    /* data */
    arm_matrix_instance_f32 Fk;//ϵͳ״̬ת�ƾ���
    arm_matrix_instance_f32 Fk_T;//ϵͳ״̬ת�ƾ����ת��
    arm_matrix_instance_f32 Hk;//�۲����
    arm_matrix_instance_f32 Hk_T;//�۲�����ת�þ���
    arm_matrix_instance_f32 Qk;//��������[������Ϊ0��]
    arm_matrix_instance_f32 Rk;//�۲�����
    arm_matrix_instance_f32 zk;//����ģ��
    arm_matrix_instance_f32 vk;//vk~N(0,Rk)
    arm_matrix_instance_f32 Bk;//���ƾ��󣨴洢�йؼ��ٶȵģ�
    arm_matrix_instance_f32 wk;//wk~N(0,Qk)����������

public:
    uint8_t data_updated;//�����Ƿ����
    arm_matrix_instance_f32 Pk_pre; //����Ԥ��Э�������
    arm_matrix_instance_f32 Pk;//����Ԥ��Э�������
    arm_matrix_instance_f32 Kk;//�������������
    arm_matrix_instance_f32 Xk;   //ϵͳ״̬�˲���������о���
    arm_matrix_instance_f32 X_now;//ϵͳ״̬Ԥ������о���

    arm_matrix_instance_f32 kalman_filter(int16_t x, int16_t y, uint16_t z);
    float chi_squared_test();//��������
    kalmanClass();
};

#endif
