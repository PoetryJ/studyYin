/*
 * @Description: ����ͷͷ�ļ�
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
    u8 color;//1��ɫ��2��ɫ
    float x;//��λmm
    float y;//��λmm �������y���귽����Ϊ����������ͷ�趨������ϵ�෴���ڽ��պ�������ȡ����
    float z;//��λmm
    float angle;//��λ ��
    float vx;//x�����ٶ� mm/s
    float vy;//y�����ٶ� mm/s
    float vz;//z�����ٶ� mm/s
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
    float x_in;//����ͷ���������С���ڲ�������
    float y_in;
    float h_in;
		float install[3];
		CanClass *can_class;
		CanMsgStruct can_msg;

public:
    u8 on_off;//С�����Ƿ񿪻�
    u8 if_use_camera;//�Ƿ��������ͷ
    u8 feedback_ok;//��Ұ���Ƿ�����
    u8 ball_target_lockon;//�������Ƿ���������������˾Ϳ��Է���
    int messageNum_get;//����ͷʶ���˶��ٴ���
    int messageNum_lost;//����ͷ��֡�˶��ٴ�
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
