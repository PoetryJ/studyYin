/*
 * @Description:����
 * @Version: 2.0
 * @Author: Dandelion
 * @Date: 2022-06-18 20:28:45
 * @LastEditTime: 2022-07-10 17:29:04
 * @FilePath: \Master_of_2022_C++\Project\User\src\ws2812B.cpp
 */
#include "ws2812B.h"
/**
 * @brief ������ʼ����������ʱ����IO��ʼ����
 * @author: Dandelion
 * @Date: 2022-06-18 21:37:11
 * @param {u8} pixel_num
 * @param {u8} GRB
 * @return {*}
 */
ws2812BClass::ws2812BClass(u8 pixel_num, u8 GRB, vu8 status)
{ // PC8��ͨ��0��������2��TIM8-CH3��NΪ����ͨ�����������Ϊ��
    this->pixel_num = pixel_num;
    this->GRB = GRB;
    this->status = status;
}
/**
 * @brief IO/TIM/PWM/DMA��ʼ��
 * @author: Dandelion
 * @Date: 2022-06-19 18:51:47
 * @return {*}
 */
void ws2812BClass::Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8); //...corrected err
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_ResetBits(GPIOC, GPIO_Pin_8);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);         // 168mhz//168M / 210 = 800k
    TIM_TimeBaseInitStruct.TIM_Prescaler = 1 - 1;                //����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseInitStruct.TIM_Period = 210 - 1;                 //�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;     //����ʱ�ӷָ�
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // TIM ���ϼ���
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;            //�߼���ʱ��1���ö�ʱ��������������ſ����������ļ���Ƶ�� ֵ��ע��ĵط�
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStruct);

    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; //ʹ�ܸ�ͨ�����
    TIM_OCInitStruct.TIM_Pulse = 0;                            //����ռ�ձ�ʱ��
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;     //�����������
    //���漸�������Ǹ߼���ʱ���Ż��õ��ģ�ͨ�ö�ʱ����������
    TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable; //ʧ�ܻ��������
    TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;      //���û������������
    TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;       //���������״̬
    TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;   //�����󻥲������״̬
    TIM_OC3Init(TIM8, &TIM_OCInitStruct);

    //������ɲ���������ã��߼���ʱ�����еģ�ͨ�ö�ʱ����������
    TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;             //����ģʽ�����ѡ��
    TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;             //����ģʽ�����ѡ��
    TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;                 //��������
    TIM_BDTRInitStructure.TIM_DeadTime = 0x10;                               //����ʱ������
    TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;                     //ɲ������ʹʧ��
    TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;        //ɲ�����뼫��
    TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable; //�Զ����ʹ��
    TIM_BDTRConfig(TIM8, &TIM_BDTRInitStructure);
    //ʹ�ܶ˵Ĵ�
    TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM8, ENABLE);
    TIM_Cmd(TIM8, ENABLE);

    TIM_CtrlPWMOutputs(TIM8, ENABLE); // MOE �����ʹ��

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); // DMA2ʱ��ʹ��

    DMA_DeInit(DMA2_Stream2);
    while (DMA_GetCmdStatus(DMA2_Stream2) != DISABLE)
    {
    } //�ȴ�DMA������

    DMA_InitStructure.DMA_Channel = DMA_Channel_0; //ͨ��ѡ��
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32) & (TIM8->CCR3);
    DMA_InitStructure.DMA_Memory0BaseAddr = (u32)this->pixelBuffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructure.DMA_BufferSize = this->pixel_num * this->GRB;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         //�洢��ͻ�����δ���
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; //����ͻ�����δ���

    DMA_Init(DMA2_Stream2, &DMA_InitStructure);

    DMA_Cmd(DMA2_Stream2, DISABLE);
    TIM_DMACmd(TIM8, TIM_DMA_CC3, ENABLE);

    CloseAll();
}
/**
 * @briefDMA��Ԥ����ַ�е����ݴ������ݵ��洢����ַ����ʱ��ͨ���Ƚ�ֵ
 * @author: Dandelion
 * @Date: 2022-06-18 23:09:00
 * @return {*}
 */
void ws2812BClass::WS281x_Show()
{
    TIM_Cmd(TIM8, ENABLE);
    DMA_SetCurrDataCounter(DMA2_Stream2, this->pixel_num * this->GRB);
    DMA_Cmd(DMA2_Stream2, ENABLE);
    while (!DMA_GetFlagStatus(DMA2_Stream2, DMA_FLAG_TCIF2)) //�ȴ�DMA2_Stream6�������
    {
    }
    DMA_Cmd(DMA2_Stream2, DISABLE);
    DMA_ClearFlag(DMA2_Stream2, DMA_FLAG_TCIF2);
    TIM_Cmd(TIM8, DISABLE); //��DMA���ݴ�����ɺ�Ӧ�ȹر�DMAͨ�����ٹرն�ʱ������ֹDMA������ɣ���PWM���һ���ź�δ������Ӱ�����һ���Ƶ���ʾ
}
/**
 * @brief ������������е���
 * @author: Dandelion
 * @Date: 2022-06-18 22:54:53
 * @return {*}
 */
void ws2812BClass::CloseAll()
{
    for (int i = 0; i < pixel_num; i++)
    {
        for (int j = 0; j < 24; j++)
        {
            pixelBuffer[i][j] = WS_LOW;
        }
    }
    WS281x_Show();
}
/**
 * @brief ����GRB��˳�������Ų���ɫ
 * @author: Dandelion
 * @Date: 2022-06-18 22:56:53
 * @param {u8} red
 * @param {u8} green
 * @param {u8} blue
 * @return {*}
 */
u32 ws2812BClass::WS281x_Color(u8 red, u8 green, u8 blue)
{
    return green << 16 | red << 8 | blue;
}
/**
 * @brief ���õ������ص���ɫ
 * @author: Dandelion
 * @Date: 2022-06-18 22:58:22
 * @param {u16} n
 * @param {u32} GRBColor
 * @return {*}
 */
void ws2812BClass::WS281x_SetPixelColor(u16 n, u32 GRBColor)
{
    if (n < pixel_num)
    {
        for (int i = 0; i < GRB; i++)
        {
            pixelBuffer[n][i] = ((GRBColor << i) & 0x00800000) ? WS_HIGH : WS_LOW;
        }
    }
}
/**
 * @brief ���õ������ص�RGBֵ���������飩
 * @author: Dandelion
 * @Date: 2022-06-18 22:59:45
 * @param {uint16_t} n
 * @param {u8} red
 * @param {u8} green
 * @param {u8} blue
 * @param {WS2812LED} *led_line
 * @return {*}
 */
void ws2812BClass::WS281x_SetPixelRGB(u16 n, u8 red, u8 green, u8 blue)
{
    if (n < pixel_num)
    {
        for (int i = 0; i < GRB; ++i)
        {
            pixelBuffer[n][i] = (((WS281x_Color(red, green, blue) << i) & 0X800000) ? WS_HIGH : WS_LOW);
        }
    }
}
/**
 * @brief Input a value 0 to 255 to get a color value.
The colours are a transition r - g - b - back to r.
 * @author: Dandelion
 * @Date: 2022-06-19 09:19:05
 * @param {uint8_t} wheelPos
 * @return {*}
 */
u32 ws2812BClass::WS281x_Wheel(uint8_t wheelPos)
{
    wheelPos = 255 - wheelPos;
    if (wheelPos < 85)
    {
        return WS281x_Color((255 - wheelPos * 3) * 0.1, 0, (wheelPos * 3) * 0.1);
    }
    if (wheelPos < 170)
    {
        wheelPos -= 85;
        return WS281x_Color(0, (wheelPos * 3) * 0.1, (255 - wheelPos * 3) * 0.1);
    }
    wheelPos -= 170;
    return WS281x_Color((wheelPos * 3) * 0.1, (255 - wheelPos * 3) * 0.1, 0);
}
/**
 * @brief Fill the dots one after the other with a color
 * @author: Dandelion
 * @Date: 2022-06-19 09:25:01
 * @param {uint32_t} c
 * @param {uint8_t} wait
 * @param {WS2812LED} *led_line
 * @return {*}
 */
void ws2812BClass::WS281x_ColorWipe(u32 c, u32 wait)
{
    for (int i = 0; i < pixel_num; i++)
    {
        WS281x_SetPixelColor(i, c);
        WS281x_Show();
        OSTimeDly(wait);
    }
    OSTimeDly(wait);
    status = rainbow_cycle;
}
/**
 * @brief �ʺ�ģʽ
 * @author: Dandelion
 * @Date: 2022-06-19 09:27:13
 * @param {u8} wait
 * @return {*}
 */
void ws2812BClass::WS281x_Rainbow(u32 wait)
{
    for (int j = 0; j < 256; j++)
    {
        for (int i = 0; i < pixel_num; i++)
        {
            WS281x_SetPixelColor(i, WS281x_Wheel((i + j) & 255));
        }
        WS281x_Show();
        OSTimeDly(wait);
        if (status != rainbow)
        {
            break;
        }
    }
}
/**
 * @brief Slightly different, this makes the rainbow equally distributed throughout
 * ���в�ͬ����ʹ�òʺ���ȷֲ�
 * @author: Dandelion
 * @Date: 2022-06-19 10:11:24
 * @param {u8} wait
 * @return {*}
 */
void ws2812BClass::WS281x_RainbowCycle(u32 wait)
{
    for (int j = 0; j < 256 * 5; j++)
    { // 5 cycles of all colors on wheel
        for (int i = 0; i < pixel_num; i++)
        {
            WS281x_SetPixelColor(i, WS281x_Wheel(((i * 256 / pixel_num) + j) & 255));
        }
        WS281x_Show();
        OSTimeDly(wait);
        if (status != rainbow_cycle)
        {
            break;
        }
    }
}
/**
 * @brief Theatre-style crawling lights.
 * @author: Dandelion
 * @Date: 2022-06-19 09:41:13
 * @param {u32} c
 * @param {u8} wait
 * @return {*}
 */
void ws2812BClass::WS281x_TheaterChase(u32 c, u32 wait)
{
    for (int j = 0; j < 10; j++)
    { // do 10 cycles of chasing
        for (int q = 0; q < 3; q++)
        {
            for (int i = 0; i < pixel_num; i = i + 3)
            {
                WS281x_SetPixelColor(i + q, c); // turn every third pixel on
            }
            WS281x_Show();

            OSTimeDly(wait);

            for (int i = 0; i < pixel_num; i = i + 3)
            {
                WS281x_SetPixelColor(i + q, 0); // turn every third pixel off
            }
            WS281x_Show();

            OSTimeDly(wait);
        }
        if (status != theater_chase)
        {
            break;
        }
    }
}
/**
 * @brief Theatre-style crawling lights with rainbow effect
 * @author: Dandelion
 * @Date: 2022-06-19 09:43:14
 * @param {u8} wait
 * @return {*}
 */
void ws2812BClass::WS281x_TheaterChaseRainbow(u32 wait)
{
    for (int j = 0; j < 256; j++)
    { // cycle all 256 colors in the wheel
        for (int q = 0; q < 3; q++)
        {
            for (int i = 0; i < pixel_num; i = i + 3)
            {
                WS281x_SetPixelColor(i + q, WS281x_Wheel((i + j) % 255)); // turn every third pixel on
            }
            WS281x_Show();

            OSTimeDly(wait);

            for (int i = 0; i < pixel_num; i = i + 3)
            {
                WS281x_SetPixelColor(i + q, 0); // turn every third pixel off
            }
            WS281x_Show();

            OSTimeDly(wait);
        }
        if (status != theater_chase_rainbow)
        {
            break;
        }
    }
}
/**
 * @brief ѡ�����ģʽ
 * @author: Dandelion
 * @Date: 2022-06-19 09:46:11
 * @param {u8} status
 * @return {*}
 */
void ws2812BClass::mode_choose(u8 status)
{
    switch (status)
    {
    case RED_ON:
    {
        for (int i = 0; i < pixel_num; i++)
        {
            WS281x_SetPixelRGB(i, 30, 0, 0); // TODO ,�����һƪ����
            OSTimeDly(20);
        }
        WS281x_Show();
    }
    break;
    case GREEN_ON:
    {
        for (int i = 0; i < pixel_num; i++)
        {
            WS281x_SetPixelRGB(i, 0, 30, 0); // TODO ,�����һƪ����
            OSTimeDly(20);
        }
        WS281x_Show();
    }
    break;
    case BLUE_ON:
    {
        for (int i = 0; i < pixel_num; i++)
        {
            WS281x_SetPixelRGB(i, 0, 0, 30); // TODO ,�����һƪ����
            OSTimeDly(20);
        }
        WS281x_Show();
        break;
    }
    case ALL_CLOSE:
    {
        CloseAll();
        OSTimeDly(20);
        break;
    }
    case rainbow:
    {
        WS281x_Rainbow(200);
        break;
    }
    case rainbow_cycle:
    {
        WS281x_RainbowCycle(200);
        break;
    }
    case theater_chase:
    {
        WS281x_TheaterChase(WS281x_Color(40, 40, 40), 700);
        break;
    }
    case color_wipe:
    {
        WS281x_ColorWipe(WS281x_Color(30, 30, 30), 80);
        break;
    }
    case theater_chase_rainbow:
    {
        WS281x_TheaterChaseRainbow(1000);
        break;
    }
    default:
        break;
    }
}
