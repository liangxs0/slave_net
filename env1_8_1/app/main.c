#include <stdio.h>
#include "function.h"
#include "sys.h"
#include "jpstm32_sysclk.h"
#include "analysis.h"
#include "config.h"

#include "iic_master.h"
#include "lock.h"
#include "rc522.h"
#include "JXL12864G-086.h"
#include "figure_print.h"
#include "exti.h"
#include "Debug_usart.h"
#include "rgb_led.h"
//#include "TIM1.h" //������������

int main()
{
 
  sysclkInit(9);
  delayInit(72);
  JTAG_Set(01);//����jatg�ڴ�����ģʽת��Ϊ��ͨGPIO
  zigbee_usart_init(36,57600);
	max485_rd_init();//485��ʼ��
  usart_init(72,57600);
  device_init();
  
  while(1)
  {
    if(ZigbeeR_Finish == 1)//�������ݽ���
    {
      ZigbeeR_Finish = 0;//������λ���ձ��
      analysis();
    }
   
  }
  
}
