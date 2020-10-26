#include "heart.h"
#include "config.h"
#include "jpstm32_sysclk.h"
u8 data[10] = {0};

#if board1

void heart_up()
{
  u8 i;
  data[0] = 0xEF;
  data[1] = 0xEF;
  data[2] = 0x00;
  data[3] = 0xFF;
  data[4] = 0xFF;
  data[5] = 0x0A;
  data[6] = device_id;//节点id
  for(i=0;i<4;i++)
  {
    //设备id
    data[7] = 0x10*(i+1);
    data[8] = 0xCC;
    data[9] = 0xFF;
    zigbee_send(10,data);
    delayMs(30);
  }
 
}

#endif

#if board2

void heart_up()
{
  data[0] = 0xEF;
  data[1] = 0xEF;
  data[2] = 0x00;
  data[3] = 0xFF;
  data[4] = 0xFF;
  data[5] = 0x0A;
  data[6] = device_id;//节点id
  data[7] = 0x00;
  data[8] = 0xCC;
  data[9] = 0xFF;
  zigbee_send(10,data);
}

#endif


#if board3

void heart_up()
{
  data[0] = 0xEF;
  data[1] = 0xEF;
  data[2] = 0x00;
  data[3] = 0xFF;
  data[4] = 0xFF;
  data[5] = 0x0A;
  data[6] = device_id;//节点id
  data[7] = 0x00;
  data[8] = 0xCC;
  data[9] = 0xFF;
  zigbee_send(10,data);
}

#endif

#if board4

void heart_up()
{
  data[0] = 0xEF;
  data[1] = 0xEF;
  data[2] = 0x00;
  data[3] = 0xFF;
  data[4] = 0xFF;
  data[5] = 0x0A;
  data[6] = device_id;//节点id
  //设备id
  data[7] = 0x00;
  data[8] = 0xCC;
  data[9] = 0xFF;
  zigbee_send(10,data);

}

#endif

#if board5

void heart_up()
{
  u8 i;
  data[0] = 0xEF;
  data[1] = 0xEF;
  data[2] = 0x00;
  data[3] = 0xFF;
  data[4] = 0xFF;
  data[5] = 0x0A;
  data[6] = device_id;//节点id
  data[8] = 0xCC;
  data[9] = 0xFF;
  for(i=0;i<3;i++)
  {
    data[7] = 0x01*i;//0x00 0x10 0x20
    zigbee_send(10,data);
    delayMs(35);
  }
  
}

#endif


#if board6

void heart_up()
{
  u8 i;
  data[0] = 0xEF;
  data[1] = 0xEF;
  data[2] = 0x00;
  data[3] = 0xFF;
  data[4] = 0xFF;
  data[5] = 0x0A;
  data[6] = device_id;//节点id
  //设备id
  data[7] = 0x10;
  data[8] = 0xCC;
  data[9] = 0xFF;
  zigbee_send(10,data);
}

#endif

#if board7

void heart_up()
{
  u8 i;
  data[0] = 0xEF;
  data[1] = 0xEF;
  data[2] = 0x00;
  data[3] = 0xFF;
  data[4] = 0xFF;
  data[5] = 0x0A;
  data[6] = device_id;//节点id
  //设备id
  data[8] = 0xCC;
  data[9] = 0xFF;
  for(i=0;i<4;i++)
  {
    data[7] = 0x10*(i+1);
    zigbee_send(10,data);
    delayMs(25);
  }
  
}

#endif

#if board8

void heart_up()
{
  data[0] = 0xEF;
  data[1] = 0xEF;
  data[2] = 0x00;
  data[3] = 0xFF;
  data[4] = 0xFF;
  data[5] = 0x0A;
  data[6] = device_id;//节点id
  //设备id
  data[7] = 0x10;
  data[8] = 0xCC;
  data[9] = 0xFF;
  zigbee_send(10,data);
}

#endif
