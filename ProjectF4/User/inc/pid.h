/*
 * @Description: pid
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-01-07 21:39:45
 * @LastEditTime: 2022-05-11 14:38:37
 * @FilePath: \Master_of_2022_C++\Project\User\inc\pid.h
 */
#ifndef _PID_H
#define _PID_H
	
#include "stm32f4xx.h"
#include "Mymath.h"

#define update_pid_para(pid, para) \
    {                              \
        pid.kp = para[0];          \
        pid.ki = para[1];          \
        pid.kd = para[2];          \
    }

// pid计算模式
enum PIDMode
{
    posi_mode = 0,// KP
    incre_mode = 1,// KI
};

class PIDClass
{
private:
    /* data */
    u8 mode; // 计算模式
    s8 beta; // 积分分离系数
    float threshold; //死区阈值
    float beta_thre;//积分分离阈值
    /* data */
    float kp;
    float ki;
    float kd;
    /* 增量式 */
    float err_last; //偏差值
    float err_now;
    float err_before;
    /* 位置式 */
    float err_sum;
    /* 输出 */
    float out;
    float P_out;
    float I_out;
    float D_out;
public:
    u8 under_threthold(void) { return (ABS(err_now) <= threshold); };
    void PidInit(const float *pid_para, u8 cal_mode, float _threshold, float _beta_thre);
    float PidOperation(float setNum, float actualNum);
    float * getErrNow(void);//供虚拟示波器调用
};

extern float pid_para_run_point[3];
extern float pid_para_run_bezier[3];
extern float pid_para_run_bspline[3];
extern float pid_para_angle[3];// 跑点
extern float pid_para_lock_point_x[3];
extern float pid_para_lock_point_y[3];
extern float pid_para_lock_angle[3]; // 锁点


#endif
