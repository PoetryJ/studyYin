/*
 * @Description: 底盘运动学pid
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-01-07 21:39:35
 * @LastEditTime: 2022-08-27 16:20:59
 * @FilePath: \机构ldce:\2022ROBOCON\Master_of_2022_C++\Project\User\src\pid.cpp
 */
#include "pid.h"

/***************pid各组参数**************/
// pid para
float pid_para_run_point[3] = {6.0f, 0.01, 0.05}; //{5.0f, 0.01, 0.03f};
float pid_para_run_bezier[3] = {5.7f, 0.01f, 0.056f};
float pid_para_run_bspline[3] = {6.0f, 0.01f, 0.05f}; //新轮系未测试
float pid_para_angle[3] = {6.4f, 0.02f, 0.05f};

/* 锁点pid */
float pid_para_lock_point_x[3] = {6.8f, 0.02f, 0.02f}; // 5,0.01,0.02
float pid_para_lock_point_y[3] = {6.8f, 0.02f, 0.02f};
float pid_para_lock_angle[3] = {6.8f, 0.02f, 0.05f}; // 锁点
/**
 * @brief pid参数初始化（及后续更改）
 * @author: Dandelion
 * @Date: 2022-01-07 21:56:27
 * @param pid_para PID基本参数
 * @param cal_mode 计算模式
 * @param _threshold 死区阈值
 * @param _beta_thre 积分分离阈值
 */
void PIDClass::PidInit(const float *pid_para, u8 cal_mode, float _threshold, float _beta_thre)
{
	err_sum = 0;
	err_before = 0;
	err_last = 0;
	err_now = 0;
	out = 0;
	beta = 1;

	kp = pid_para[0];
	ki = pid_para[1];
	kd = pid_para[2];
	mode = cal_mode;

	threshold = _threshold;
	beta_thre = _beta_thre;
}

/**
 * @brief pid核心计算部分
 * @author: Dandelion
 * @Date: 2022-01-07 21:58:32
 * @param {volatile PidStruct} *pid
 */
float PIDClass::PidOperation(float setPara, float actualPara)
{
	err_now = setPara - actualPara;
	if (ABS(err_now) <= threshold)
	{
		err_now = 0.0f;
	}


 
	if (ABS(err_now) <= beta_thre)
	{
		beta = 1;
	}
	else
	{
		beta = 0; //积分分离
	}

	if (mode == posi_mode)
	{
		P_out = kp * err_now;
		I_out = ki * beta * err_sum;
		D_out = kd * (err_now - err_last);
		out = P_out + I_out + D_out;
	}
	else
	{
		P_out = kp * (err_now - err_last);
		I_out = ki * beta * (err_now + err_last) * 0.5f;
		D_out = kd * (err_now - 2 * err_last + err_before);
		out += P_out + I_out + D_out;
	}
	err_sum += beta * (err_now + err_last) * 0.5f; // 用梯形面积求和积分代替矩形求和积分，梯形积分精度高
	err_before = err_last;
	err_last = err_now;
	return out;
}

float *PIDClass::getErrNow(void)
{
	return &(err_now);
}
