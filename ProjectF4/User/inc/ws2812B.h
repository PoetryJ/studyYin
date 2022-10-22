/*
 * @Description:
 * @Version: 2.0
 * @Author: Dandelion
 * @Date: 2022-06-18 20:28:54
 * @LastEditTime: 2022-07-10 17:17:27
 * @FilePath: \Master_of_2022_C++\Project\User\inc\ws2812B.h
 */
#ifndef _WS2812B_H
#define _WS2812B_H

#include "stm32f4xx.h"
#include "dma.h"
#include "includes.h"

#define WS_HIGH 144 // 0.69
#define WS_LOW 67   // 0.32

enum Status_of_LED
{
    RED_ON = 0,
    GREEN_ON,
    BLUE_ON,
    ALL_CLOSE,
    rainbow,               //�ʺ�ģʽ����֪����cycleģʽ������ʲô��ͬ�������ԣ�
    rainbow_cycle,         //�òʺ���ȷֲ�����������
    theater_chase,         //��Ժģʽ����������һ����һ����ɫ��
    theater_chase_rainbow, //��Ժ�ʺ�ģʽ����������һ����RGB�ʺ�ģʽ��
    color_wipe,            //���ε���
};

class ws2812BClass
{
private:
    u8 pixel_num;
    u8 GRB;
    u16 pixelBuffer[170][24];

    void WS281x_Show(void);
    u32 WS281x_Color(u8 red, u8 green, u8 blue);
    void WS281x_SetPixelColor(u16 n, u32 GRBColor);
    void WS281x_SetPixelRGB(u16 n, u8 red, u8 green, u8 blue);
    void CloseAll(void);
    u32 WS281x_Wheel(u8 wheelPos);
    void WS281x_ColorWipe(u32 c, u32 wait);
    void WS281x_Rainbow(u32 wait);
    void WS281x_RainbowCycle(u32 wait);
    void WS281x_TheaterChase(u32 c, u32 wait);
    void WS281x_TheaterChaseRainbow(u32 wait);

public:
    vu8 status;
    ws2812BClass(u8 pixel_num, u8 GRB, vu8 status);
    void Init(void);
    void mode_choose(u8 status);
};

extern ws2812BClass ledLine;

#endif
