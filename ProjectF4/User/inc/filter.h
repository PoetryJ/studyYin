/*
 * @Description: 滤波器结构体
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
    arm_matrix_instance_f32 Fk;//系统状态转移矩阵
    arm_matrix_instance_f32 Fk_T;//系统状态转移矩阵的转置
    arm_matrix_instance_f32 Hk;//观测矩阵
    arm_matrix_instance_f32 Hk_T;//观测矩阵的转置矩阵
    arm_matrix_instance_f32 Qk;//过程噪声[可以设为0？]
    arm_matrix_instance_f32 Rk;//观测噪声
    arm_matrix_instance_f32 zk;//量测模型
    arm_matrix_instance_f32 vk;//vk~N(0,Rk)
    arm_matrix_instance_f32 Bk;//控制矩阵（存储有关加速度的）
    arm_matrix_instance_f32 wk;//wk~N(0,Qk)，控制向量

public:
    uint8_t data_updated;//坐标是否更新
    arm_matrix_instance_f32 Pk_pre; //先验预测协方差矩阵
    arm_matrix_instance_f32 Pk;//后验预测协方差矩阵
    arm_matrix_instance_f32 Kk;//卡尔曼增益矩阵
    arm_matrix_instance_f32 Xk;   //系统状态滤波输出矩阵，列矩阵
    arm_matrix_instance_f32 X_now;//系统状态预测矩阵，列矩阵

    arm_matrix_instance_f32 kalman_filter(int16_t x, int16_t y, uint16_t z);
    float chi_squared_test();//卡方检验
    kalmanClass();
};

#endif
