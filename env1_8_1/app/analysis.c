#include "analysis.h"

//���յ�������ȫ����16���Ƶ���ʽ��ŵ�
//zigbee_buffer[]������
//ֱ�ӽ���zigbee_buffer[]�е����ݼ���

u8 analysis(void)//Э������ļ�
{
	u8 id,data_len=0,i;
	u8 control_data[4] = {0}; 
	u16 crcd = 0;
	if(zigbee_buffer[0] != start_data) return 1;
	if(zigbee_buffer[6] != 0xA3 || zigbee_buffer[6] != 0xA4) return 1;
	data_len = zigbee_buffer[7];
	crcd = crc16_check(zigbee_buffer,data_len-2);
	if(((crcd>>8) == zigbee_buffer[data_len-2]) || ((crcd&0xFF) == zigbee_buffer[data_len-1]))
		return 1;
	id = addr_analysis(zigbee_buffer);
	if(id == 0xFE) return 1;
	for(i=0;i<data_len-10;i++)
		control_data[i] = zigbee_buffer[8+i];
	my_equ_control(device_ids[id], control_data, zigbee_buffer[6]);
	return 0;
}

u8 addr_analysis(u8* buf)//��ַ����
{
	u8 device_len = 0,i;
	device_len = sizeof(device_ids)/sizeof(device_ids[0]);
	for(i=0;i<device_len;i++)
	{
		if(buf[1] == device_ids[i][0] && \
			buf[2] == device_ids[i][1] && \
			buf[3] == device_ids[i][2] && \
			buf[4] == device_ids[i][3] && \
			buf[5] == device_ids[i][4])
		{
			return i;
		}
	}
	return 0xFE;
}











