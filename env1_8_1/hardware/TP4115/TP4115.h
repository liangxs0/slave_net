#ifndef __TP4115_H
#define __TP4115_H

#include "stm32f10x_map.h"

void PT4115_Init(void);
/******************************************************
函数名：PT4115_Change
函数功能：通过改变PWM的占空比实现调节光线亮度
函数参数：
				L1：高亮LED光路1调节亮度值
				L2：高亮LED光路2调节亮度值
				L3：高亮LED光路3调节亮度值
				L4：高亮LED光路4调节亮度值
******************************************************/
void PT4115_Change(u8 L1,u8 L2,u8 L3,u8 L4);

#endif
