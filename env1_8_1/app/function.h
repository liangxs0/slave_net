#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "jpstm32_gpio.h"
#include "jpstm32_sysclk.h"
#include "ZigBee_usart.h"

void device_init(void);//�豸��ʼ������
//�豸�Ŀ��ƺ���
void my_equ_control(u8* ids,u8* my_control,u8 controy_type);
//���ݵ��Ϸ�����
void feedback(u8* id,u8* my_control,u8 control_len);

#endif

