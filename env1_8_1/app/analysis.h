/*
filename:analysis.h
funtion:Э�������ͷ�ļ�����������
*/

#ifndef __ANALYSIS_H__
#define __ANALYSIS_H__

//��������zigbee�е������ļ�
#include "ZigBee_usart.h"  //zigbee��ͷ�ļ�
#include "function.h"
#include "config.h"

extern u8 device_ids[5][5];

u8 analysis(void);//Э�����

u8 addr_analysis(u8* buf);//��ַ����

#endif

