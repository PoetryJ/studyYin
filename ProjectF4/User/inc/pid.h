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

// pid����ģʽ
enum PIDMode
{
    posi_mode = 0,// KP
    incre_mode = 1,// KI
};

class PIDClass
{
private:
    /* data */
    u8 mode; // ����ģʽ
    s8 beta; // ���ַ���ϵ��
    float threshold; //������ֵ
    float beta_thre;//���ַ�����ֵ
    /* data */
    float kp;
    float ki;
    float kd;
    /* ����ʽ */
    float err_last; //ƫ��ֵ
    float err_now;
    float err_before;
    /* λ��ʽ */
    float err_sum;
    /* ��� */
    float out;
    float P_out;
    float I_out;
    float D_out;
public:
    u8 under_threthold(void) { return (ABS(err_now) <= threshold); };
    void PidInit(const float *pid_para, u8 cal_mode, float _threshold, float _beta_thre);
    float PidOperation(float setNum, float actualNum);
    float * getErrNow(void);//������ʾ��������
};

extern float pid_para_run_point[3];
extern float pid_para_run_bezier[3];
extern float pid_para_run_bspline[3];
extern float pid_para_angle[3];// �ܵ�
extern float pid_para_lock_point_x[3];
extern float pid_para_lock_point_y[3];
extern float pid_para_lock_angle[3]; // ����


#endif
