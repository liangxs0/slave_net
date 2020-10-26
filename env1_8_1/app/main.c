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
//#include "TIM1.h" //心跳包的数据

int main()
{
 
  sysclkInit(9);
  delayInit(72);
  JTAG_Set(01);//设置jatg口从下载模式转换为普通GPIO
  zigbee_usart_init(36,57600);
	max485_rd_init();//485初始化
  usart_init(72,57600);
  device_init();
  
  while(1)
  {
    if(ZigbeeR_Finish == 1)//发生数据交互
    {
      ZigbeeR_Finish = 0;//重新置位接收标记
      analysis();
    }
   
  }
  
}
