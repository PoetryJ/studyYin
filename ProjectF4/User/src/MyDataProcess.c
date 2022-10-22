/*
 * @Description: 数据的类型转换，直接从学长处继承
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2021-08-22 14:36:36
 * @LastEditTime: 2022-06-12 14:49:30
 * @FilePath: \Master_of_2022_C++\Project\User\src\MyDataProcess.c
 */

#include "MyDataProcess.h"

/**
 * @brief 将float型数据f转化为4byte存放在buff中
 * @author: Dandelion
 * @Date: 2021-08-23 17:34:17
 * @return {*}
 * @param {float} *f
 * @param {u8} *buff
 */
void FloatTo4Byte(float *f, u8 *buff)
{
    u8 *p_float;
    p_float = (unsigned char *)f; //得到float的地址

    *buff = p_float[0];
    *(++buff) = p_float[1];
    *(++buff) = p_float[2];
    *(++buff) = p_float[3];
}

/**
 * @brief 将4byte数据buff解算成float型数据存放在f中
 * @author: Dandelion
 * @Date: 2021-08-23 17:35:00
 * @return {*}
 * @param {float} *f
 * @param {u8} *buff
 */
void Byte4ToFloat(float *f, u8 *buff)
{
    u8 *p_float;
    p_float = (unsigned char *)f; //得到float的地址

    p_float[0] = *buff;
    p_float[1] = *(++buff);
    p_float[2] = *(++buff);
    p_float[3] = *(++buff);
}

/**
 * @brief 将s16型数据f转化为2byte数据存放在buff中
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
 * @brief 将2byte数据buff拼接成s16型数据存放在f中
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
 * @brief 将u16型数据f转化为2byte数据存放在buff中
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
 * @brief 将2byte数据buff拼接成u16型数据存放在f中
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
 * @brief 将s32型数据f转化为4byte型存放在buff中
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
 * @brief 将4byte数据buff拼接成s32型数据存放在f中
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
 * @brief 将u32型数据f转化成4byte数据存放在buff中
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
 * @brief 将4byte数据拼接成u32型数据存放在f中
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
