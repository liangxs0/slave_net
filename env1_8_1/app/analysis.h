/*
filename:analysis.h
funtion:协议解析的头文件函数的声明
*/

#ifndef __ANALYSIS_H__
#define __ANALYSIS_H__

//解析来自zigbee中的数据文件
#include "ZigBee_usart.h"  //zigbee的头文集
#include "function.h"
#include "config.h"

extern u8 device_ids[5][5];

u8 analysis(void);//协议解析

u8 addr_analysis(u8* buf);//地址解析

#endif

