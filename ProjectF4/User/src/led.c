#include "led.h"
#include "sys.h"


void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  // '??GPIOA???
	  
	  // GPIOA4,A5??A6,A7??'??????
    GPIO_InitStructure.GPIO_Pin     =   GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;  // LED???IO??
    GPIO_InitStructure.GPIO_Mode    =   GPIO_Mode_OUT;  // ??????g?
    GPIO_InitStructure.GPIO_OType   =   GPIO_OType_PP;  //???????
    GPIO_InitStructure.GPIO_Speed   =   GPIO_Speed_100MHz;  //???100
    GPIO_InitStructure.GPIO_PuPd    =   GPIO_PuPd_UP;  //????

    GPIO_Init(GPIOA, &GPIO_InitStructure);  // ??'??GPIO
    GPIO_SetBits(GPIOA,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);  //???ø??????
}
