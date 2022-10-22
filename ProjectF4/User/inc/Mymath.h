/*
 * @Description:     ? ?
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2021-08-22 14:36:38
 * @LastEditTime: 2022-08-07 00:19:41
 * @FilePath: \Master_of_2022_C++\Project\User\inc\Mymath.h
 */
#ifndef _MYMATH_H
#define _MYMATH_H

#include <math.h>
#include <arm_math.h>
#include "stm32f4xx.h"

/* some const */
//       ?   ?  1e-6 η 
//#define PI 3.1415926
#define PI_half PI / 2
#define g 9.8f
#define cos_30 0.8660254f
#define cos_60 0.500000
#define cos_45 0.7071067f
#define sin_30 0.500000
#define sin_60 0.8660254f
#define sin_45 0.7071067f

/* some simple math function */
#define ABS(x) ((x) > 0 ? (x) : -(x))                                                         //     ?      x     ?  ? 
#define SIGN(x) ((x) > 0 ? 1 : ((x) < 0 ? -1 : 0))                                            //   ?          
#define SQUARE(x) ((x) * (x))                                                                 // ?  
#define HYPOT(x, y) (sqrt((x) * (x) + (y) * (y)))                                             //б  
#define BELONG(x, min, max) ((x) >= (MIN(min, max)) && (x) <= (MAX(min, max)) ? true : false) // if x in [min, max] return True
#define MAX(x, y) (((x) >= (y)) ? (x) : (y))                                                  //            ?
#define MIN(x, y) (((x) >= (y)) ? (y) : (x))                                                  //           С?
#define DegToRad(x) (x * 0.017453f)                                                           // ? ?    
#define RadToDeg(x) (x * 57.295780f)                                                          //    ? ? 

/* 两点间距离 */
#define CountDistance(x_from, y_from, x_to, y_to) \
    (float)(sqrt((x_to - x_from) * (x_to - x_from) + (y_to - y_from) * (y_to - y_from)))
/* 点积 */
#define InnerProduct(vector1, vector2) \
    (float)(vector1.x * vector2.x + vector1.y * vector2.y)
/* 上下限制 */
#define Limit(x, _max, _min) ((x) > _max ? _max : ((x) < _min ? _min : (x)))

s8 ClosetTurnAngle(float angleNew, float angleLast, float &angleAdd);

#endif
