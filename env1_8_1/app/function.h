#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "jpstm32_gpio.h"
#include "jpstm32_sysclk.h"
#include "ZigBee_usart.h"

void device_init(void);//设备初始化函数
//设备的控制函数
void my_equ_control(u8* ids,u8* my_control,u8 controy_type);
//数据的上发函数
void feedback(u8* id,u8* my_control,u8 control_len);

#endif

