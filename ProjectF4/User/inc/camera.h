/*
 * @Description: 摄像头头文件
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-02-15 20:49:52
 * @LastEditTime: 2022-03-30 14:59:46
 * @FilePath: \Master_of_2022_C++\Project\User\inc\camera.h
 */
#ifndef _CAMERA_H
#define _CAMERA_H

#include "stm32f4xx.h"
#include "usart.h"
#include "MyDataProcess.h"
#include "filter.h"
#include "can.h"

typedef struct _BALLPOSI
{
    u8 color;//1红色，2蓝色
    float x;//单位mm
    float y;//单位mm 在这里的y坐标方向朝上为正，和摄像头设定的坐标系相反，在接收函数那里取负号
    float z;//单位mm
    float angle;//单位 度
    float vx;//x方向速度 mm/s
    float vy;//y方向速度 mm/s
    float vz;//z方向速度 mm/s
}BallPosi;

typedef struct  _LAGORIPOSI
{
  u8 color;
  u8 hierarchy;
  float x;
  float y;
  float z;
}LagoriPosi;

class CameraClass
{
private:
    float x_in;//摄像头的摄像口在小车内部的坐标
    float y_in;
    float h_in;
		float install[3];
		CanClass *can_class;
		CanMsgStruct can_msg;

public:
    u8 on_off;//小电脑是否开机
    u8 if_use_camera;//是否调用摄像头
    u8 feedback_ok;//视野中是否有球
    u8 ball_target_lockon;//球坐标是否锁定，如果锁定了就可以发射
    int messageNum_get;//摄像头识别到了多少次球
    int messageNum_lost;//摄像头丢帧了多少次
    BallPosi ball;
    LagoriPosi lagori;
    kalmanClass kalman;
    void self_check();
    void self_check(u8 InConGrpFlag);
    void check_ball(void);
		void check_ball(u8 area_side, u8 InConGrpFlag);
    void shutdown_stream(void);
		void shutdown_stream(u8 InConGrpFlag);
    void begin_stream(void);
		void begin_stream(u8 area_side, u8 InConGrpFlag);
    float *get_camera_install(void) {
        return install;
    };
    CameraClass(float x, float y, float h, CanClass *_can_class) : x_in(x), y_in(y), h_in(h), can_class(_can_class){
			install[0] = x;
			install[1] = y;
			install[2] = h;
		};
};

extern CameraClass camera;

void CameraReceiveHandler(u8 *buff);
void CameraReceiveHandler(CanRxMsg rx_message);

#endif
