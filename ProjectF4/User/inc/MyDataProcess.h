/*
 * @Description: 
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2021-08-22 14:36:36
 * @LastEditTime: 2022-06-12 15:02:46
 * @FilePath: \Master_of_2022_C++\Project\User\inc\MyDataProcess.h
 */
#ifndef _MYDATAPROCESS_H
#define _MYDATAPROCESS_H

#ifdef __cplusplus
extern "C"{
#endif

#include "stm32f4xx.h"

typedef struct _TEMPDATA
{
  s8 temps8;
  u8 tempu8;
  u16 tempu16;
  s16 temps16;
  u32 tempu32;
  s32 temps32;
} TempData;
/** 
  * @brief  ��float�������о��ȶ�ʧ�ؽس�2���ֽڣ�����buff��
  */
#define EncodeFloatDataLost(f,buff)				{buff[0] = (u8)(((s16)*f)&0x00ff);buff[1] = (u8)((((s16)*f)>>8)&0x00ff);}
	
/** 
  * @brief  ��float�������о��ȶ�ʧ�ؽس�4���ֽڣ�����buff��
	*/
#define DecodeFloatDataLost(f,buff)				{*f=(double)((s16)((u16)(buff[1]&0x00ff)<<8)|buff[0]);}

/** 
  * @brief   ����buff��ʼ��4���ֽ�λƴ��ת����float
	*/
//#define EncodeFloatData(f,buff)						{*(float*)buff = *f;}



/** 
  * @brief   ��16λ�з�������ת����2���ֽڷ���buff��
*/
#define EncodeS16Data(f,buff)							{*(s16*)buff = *f;}
/** 
  * @brief   ��buff�е�2���ֽ�ƴ��Ϊs16
*/
#define DecodeS16Data(f,buff)							{*f = *(s16*)buff;}
/** 
  * @brief   ��16λ�޷�������ת����2���ֽڷ���buff��
	*/
#define EncodeU16Data(f,buff)							{*(u16*)buff = *f;}
/** 
  * @brief   ��buff�е�2���ֽ�ƴ��Ϊu16
	*/
#define DecodeU16Data(f,buff)							{*f = *(u16*)buff;}

/** 
  * @brief        ��32λ�з�������ת����4���ֽڷ���buff��
	*/
#define EncodeS32Data(f,buff)							{*(s32*)buff = *f;}

/** 
  * @brief        ��buff�е�4���ֽ�ƴ��Ϊs32 
	*/
#define DecodeS32Data(f,buff)							{*f = *(s32 *)buff;}
#define sba(x) ((x)>0? (x):(-(x)))

void FloatTo4Byte(float *f, u8 *buff);
void Byte4ToFloat(float *f, u8 *buff);
void S16To2Byte(s16 *f, u8 *buff);
void Byte2ToS16(s16 *f, u8 *buff);
void U16To2Byte(u16 *f, u8 *buff);
void Byte2ToU16(u16 *f, u8 *buff);
void S32To4Byte(s32 *f, u8 *buff);
void Byte4ToS32(s32 *f, u8 *buff);
void U32To4Byte(u32 *f, u8 *buff);
void Byte4ToU32(u32 *f, u8 *buff);
void DecodeFloatData(float *f, unsigned char *buff);

#ifdef __cplusplus
}
#endif

#endif
