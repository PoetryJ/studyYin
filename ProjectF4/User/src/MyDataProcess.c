/*
 * @Description: ���ݵ�����ת����ֱ�Ӵ�ѧ�����̳�
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2021-08-22 14:36:36
 * @LastEditTime: 2022-06-12 14:49:30
 * @FilePath: \Master_of_2022_C++\Project\User\src\MyDataProcess.c
 */

#include "MyDataProcess.h"

/**
 * @brief ��float������fת��Ϊ4byte�����buff��
 * @author: Dandelion
 * @Date: 2021-08-23 17:34:17
 * @return {*}
 * @param {float} *f
 * @param {u8} *buff
 */
void FloatTo4Byte(float *f, u8 *buff)
{
    u8 *p_float;
    p_float = (unsigned char *)f; //�õ�float�ĵ�ַ

    *buff = p_float[0];
    *(++buff) = p_float[1];
    *(++buff) = p_float[2];
    *(++buff) = p_float[3];
}

/**
 * @brief ��4byte����buff�����float�����ݴ����f��
 * @author: Dandelion
 * @Date: 2021-08-23 17:35:00
 * @return {*}
 * @param {float} *f
 * @param {u8} *buff
 */
void Byte4ToFloat(float *f, u8 *buff)
{
    u8 *p_float;
    p_float = (unsigned char *)f; //�õ�float�ĵ�ַ

    p_float[0] = *buff;
    p_float[1] = *(++buff);
    p_float[2] = *(++buff);
    p_float[3] = *(++buff);
}

/**
 * @brief ��s16������fת��Ϊ2byte���ݴ����buff��
 * @author: Dandelion
 * @Date: 2021-08-23 17:39:00
 * @return {*}
 * @param {s16} *f
 * @param {u8} *buff
 */
void S16To2Byte(s16 *f, u8 *buff)
{
    *(s16 *)(buff) = *(f);
}

/**
 * @brief ��2byte����buffƴ�ӳ�s16�����ݴ����f��
 * @author: Dandelion
 * @Date: 2021-08-23 17:41:07
 * @return {*}
 * @param {s16} *f
 * @param {u8} *buff
 */
void Byte2ToS16(s16 *f, u8 *buff)
{
    *(f) = *(s16 *)(buff);
}
/**
 * @brief ��u16������fת��Ϊ2byte���ݴ����buff��
 * @author: Dandelion
 * @Date: 2021-08-23 17:42:51
 * @return {*}
 * @param {u16} *f
 * @param {u8} *buff
 */
void U16To2Byte(u16 *f, u8 *buff)
{
    *(u16 *)(buff) = *(f);
}

/**
 * @brief ��2byte����buffƴ�ӳ�u16�����ݴ����f��
 * @author: Dandelion
 * @Date: 2021-08-23 17:43:32
 * @return {*}
 * @param {u16} *f
 * @param {u8} *buff
 */
void Byte2ToU16(u16 *f, u8 *buff)
{
    *(f) = *(u16 *)(buff);
}

/**
 * @brief ��s32������fת��Ϊ4byte�ʹ����buff��
 * @author: Dandelion
 * @Date: 2021-08-23 17:44:08
 * @return {*}
 * @param {s32} *f
 * @param {u8} *buff
 */
void S32To4Byte(s32 *f, u8 *buff)
{
    *(s32 *)(buff) = *(f);
}

/**
 * @brief ��4byte����buffƴ�ӳ�s32�����ݴ����f��
 * @author: Dandelion
 * @Date: 2021-08-23 17:44:52
 * @return {*}
 * @param {s32} *f
 * @param {u8} *buff
 */
void Byte4ToS32(s32 *f, u8 *buff)
{
    *(f) = *(s32 *)(buff);
}

/**
 * @brief ��u32������fת����4byte���ݴ����buff��
 * @author: Dandelion
 * @Date: 2021-08-23 17:45:48
 * @return {*}
 * @param {u32} *f
 * @param {u8} *buff
 */
void U32To4Byte(u32 *f, u8 *buff)
{
    *(u32 *)(buff) = *(f);
}

/**
 * @brief ��4byte����ƴ�ӳ�u32�����ݴ����f��
 * @author: Dandelion
 * @Date: 2021-08-23 17:46:29
 * @return {*}
 * @param {u32} *f
 * @param {u8} *buff
 */
void Byte4ToU32(u32 *f, u8 *buff)
{
    *(f) = *(u32 *)(buff);
}

void DecodeFloatData(float *f, unsigned char *buff)
{
    short int f_c[2];
    f_c[0] = *(short int *)buff;
    f_c[1] = *(short int *)(buff + 2);
    *f = *(float *)f_c;
}
