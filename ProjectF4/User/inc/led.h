/*
 * @Description:
 * @Version: 1.0
 * @Author: Dandelion
 * @Date: 2022-01-01 09:09:14
 * @LastEditTime: 2022-08-10 02:16:01
 * @FilePath: \Master_of_2022_C++\Project\User\inc\led.h
 */
#ifndef _LED_H
#define _LED_H

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#ifdef __cplusplus
extern "C"
{
#endif

// #define LED_BLUE_OFF GPIOA->BSRRL = GPIO_Pin_6
// #define LED_GREEN_OFF GPIOA->BSRRL = GPIO_Pin_7
// #define LED_YELLOW_OFF GPIOA->BSRRL = GPIO_Pin_5
// #define LED_RED_OFF GPIOA->BSRRL = GPIO_Pin_4
#define LED_BLUE_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define LED_GREEN_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_6)
#define LED_YELLOW_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define LED_RED_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_4)

#define LED_BLUE_ON GPIO_SetBits(GPIOA, GPIO_Pin_7)
#define LED_GREEN_ON GPIO_SetBits(GPIOA, GPIO_Pin_6)
#define LED_YELLOW_ON GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define LED_RED_ON GPIO_SetBits(GPIOA, GPIO_Pin_4)

//#define LED_POWER_TOGGLE		GPIOA->ODR ^= GPIO_Pin_15
#define LED_RED_TOGGLE GPIOA->ODR ^= GPIO_Pin_4
#define LED_YELLOW_TOGGLE GPIOA->ODR ^= GPIO_Pin_5
#define LED_BLUE_TOGGLE GPIOA->ODR ^= GPIO_Pin_6
#define LED_GREEN_TOGGLE GPIOA->ODR ^= GPIO_Pin_7

    void LED_Configuration(void);
#ifdef __cplusplus
}
#endif

#endif
