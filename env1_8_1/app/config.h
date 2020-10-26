//这是条件编译的控制文件
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "sys.h"

#define board1 0
#define board2 0
#define board3 0
#define board4 0
#define board5 1
#define board6 0
#define board7 0
#define board8 0

#define start_data 0xEE


//CRC16检验
u16 crc16_check(u8 *buf, u8 len);//进行crc校验

#endif



