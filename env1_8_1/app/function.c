#include "function.h"
#include "config.h"


//�Ϸ������ݻ�����
u8 updata_buffer[20];

#if board1
#include "WS2812B.h"
#include "TP4115.h"

u8 color[3] = {0};
u8 light[1] = {0};

void device_init(void)//�豸��ʼ������h
{
  //��ʼ������LED�ƺ��Ų�led��
  PT4115_Init();
  WS2812B_Init();
}
//�豸�Ŀ��ƺ���
void my_equ_control(u8* ids,u8* my_control,u8 controy_type)
{
	u32 c_color;
	if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x0E)
	{
		if(controy_type == 0xA4)
		{
			light[0] = my_control[0];
			PT4115_Change(light[0],light[0],light[0],light[0]);
			
		}
		feedback(ids, light, 1);
	}else if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x0F)
	{
		if(controy_type == 0xA4)
		{
			color[0] = my_control[0];
			color[1] = my_control[1];
			color[2] = my_control[2];
			c_color = color[0]<<16|color[1]<<8|color[2];
			WS2812B_Clear();//���һ��ԭ�е�״̬Ȼ����λ
			WS2812B_Pixel_EN(0,0,16,&c_color,0);
		}
		feedback(ids, color, 3);
	}
}
#endif

#if board2
/*
�ڵ��2:��������������
������̼
������
����ǿ��
�¶�
ʪ��
*/

#include "SHT20.h"  //��ʪ��
#include "CO2.h"   //CO2
#include "myiic.h" 
#include "BH1750.h"//����ǿ��
#include "veml6070.h" //������

u8 t_temp[2] = {0};
u8 h_hum[2] = {0};
u8 c_co2[2] = {0};
u8 b_bh[2] = {0};
u8 v_vm[2] = {0};

void device_init(void)//�豸��ʼ������
{
  IIC_Init();//��ʼ��IIC --- >������
  BH1750_Init();//����ǿ�ȵĳ�ʼ��
  CO2_Init();//������̼��ʼ��
 
}
//�豸�Ŀ��ƺ���
void my_equ_control(u8* ids,u8* my_control,u8 controy_type)
{
  u8 updata[10] = {0};
  u8 len =  0;
  u16 Data = 0;
  float Data0,Data1;
	
	if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x01)//c02
	{
		CO2_Measure(c_co2,c_co2+1);//updata[0] updata[1]-->�����ֽڵ�����
    Data = c_co2[0]*256+c_co2[1];//���м���
    c_co2[0] = Data>>8;
    c_co2[1] = Data&0xFF;//����õ�16��������-->10������ʾ
		feedback(ids, c_co2, 2);

	}else if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x03)//temp
	{
		SHT20_Measure(&Data0,&Data1);//��ȡ�¶�Data0��ʪ��Data1
		t_temp[0] = Data0;
		t_temp[1] = (Data0-t_temp[0])*100;
		feedback(ids, t_temp, 2);
	
	}else if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x04)//hum
	{
		SHT20_Measure(&Data0,&Data1);//��ȡ�¶�Data0��ʪ��Data1
		h_hum[0] = Data1;
		h_hum[1] = (Data1-h_hum[0])*100;
		feedback(ids, h_hum, 2);
	
	}else if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x05)//����ǿ��
	{
		//����ǿ��
		BH1750_Original_Measure(&Data);
		b_bh[0] = Data>>8;
		b_bh[1] = Data&0xFF;
		feedback(ids, b_bh, 2);
		
	}else if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x0E)//������
	{
		VEML6070_Measure(&Data);
		v_vm[0] = Data>>8;
		v_vm[1] = Data&0xFF;
		feedback(ids, v_vm, 2);
	}
}

#endif

#if board3
/*��⣬���飬����,�������ļ��*/
#include "security.h"

u8 fire[1] = {0};
u8 smong[1] = {0};
u8 met[1] = {0};
u8 in[1] = {0};

void device_init(void)//�豸��ʼ������
{
  Security_GPIO_Init();
}
//�豸�Ŀ��ƺ���
void my_equ_control(u8* ids,u8* my_control,u8 controy_type)
{
	if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x06)//���
	{
		fire[0] = Fire_Measure?0:1;
		feedback(ids, fire, 1);
	}else if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x07)
	{	
		smong[0] = Smog_Measure?1:0;
		feedback(ids, smong, 1);
	}else if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x08)
	{
		in[0] = Infrared_Measure?0:1;
		feedback(ids, in, 1);
	}else if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x0D)
	{
		met[0] = Methane_Measure?0:1;
		feedback(ids, met, 1);
	}
}

#endif

#if board4

/*PM2.5*/
#include "PM2.5.h"
#include "SHT20.h"
#include "myiic.h"

u8 pm25[2] = {0};
u8 t_temp[2] = {0};
u8 h_hum[2] = {0};

void device_init(void)//�豸��ʼ������
{
  IIC_Init();
  PM2_5_Init();
}
//�豸�Ŀ��ƺ���
void my_equ_control(u8* ids,u8* my_control,u8 controy_type)
{
  float data;
  u16 Data;
  float Data0,Data1;
	if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x02)
	{
		 PM2_5_Measure(pm25,pm25+1);
		data = (pm25[0]*256+pm25[1])/10;
    Data = data;
    pm25[0] = Data>>8;
    pm25[1] = Data&0xFF;
		feedback(ids, pm25, 2);
	}else if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x0B)
	{
		 SHT20_Measure(&Data0,&Data1);//��ȡ�¶�Data0��ʪ��Data1
    t_temp[0] = Data0;
    t_temp[1] = (Data0-t_temp[0])*100;
		feedback(ids,t_temp,2);
		
	}else if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x0C)
	{
		SHT20_Measure(&Data0,&Data1);//��ȡ�¶�Data0��ʪ��Data1
   //ʪ�ȵĴ��
    h_hum[0] = Data1;
    h_hum[1] = (Data1-h_hum[0])*100;
		feedback(ids,h_hum,2);
	}
}

#endif

#if board5

/*�������������ƣ����俪�أ����俪��*/

#include "security_windows.h"

u8 warn[1] = {0};
u8 led[1] = {0};
u8 p1[1] = {0};//���俪��
u8 p2[1] = {0};//���俪��

void device_init(void)//�豸��ʼ������
{
  Security_Windows_GPIO_Init();//��ʼ��
}
//�豸�Ŀ��ƺ���
void my_equ_control(u8* ids,u8* my_control,u8 controy_type)
{
	if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x09)
	{
		//����
		p1[0] = RELATIVE_SWITCH;
		feedback(ids, p1, 1);
	
	}else if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x0A)
	{
		//����
		p2[0] = PHOTO_SWITCH;
		feedback(ids, p2, 1);
	
	}else if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x10)
	{
		//������
		if(controy_type == 0xA4)
		{
			WARN_RING = my_control[0]?1:0;
			warn[0] =  my_control[0];
		}
		feedback(ids, warn, 1);
	
	}else if(ids[0] == 0xFF && ids[1] == 0xFF && ids[2] == 0xFF	&& ids[3] == 0xFF	&& ids[4] == 0x11)
	{
		//������
		if(controy_type == 0xA4)
		{
			WARN_LED = my_control[0]?1:0;
			led[0] = my_control[0];
		}
		feedback(ids, led, 1);
	}
}

#endif

#if board6

//���
#include "servo.h"

u8 serv[1] = {0};

void device_init(void)//�豸��ʼ������
{
  Servo_Init(20000,72);

}
//�豸�Ŀ��ƺ���
void my_equ_control(u8* ids,u8* my_control,u8 controy_type)
{
  u8 updata[1] = {0};
  u8 len = 0 ;
  if(my_device_id == 0x10)
  {
    if(my_control[0] == 0x01)
    {
      Servo_ON();
      updata[0] = 0x01;
    }else if(my_control[0] == 0x02)
    {
      Servo_OFF();
      updata[0] = 0x02;
    }
    len = 1;
    feedback(my_device_id,updata,len);
  }
}

#endif

#if board7

/*������������ȣ��̵�������*/
//�������ת���Ƕ��ǿɿص�
//

#include "A4988.h"
#include "fan.h"
#include "Relay.h"

void device_init(void)//�豸��ʼ������
{
  Fan_Gpio_Init();
  Relay_Gpio_Init();
  A4988_Init();
}
//�豸�Ŀ��ƺ���
void my_equ_control(u16 my_device_id,u8 my_control[ZIGBEE_BUFFER_LEN])
{
  u8 updata[10] = {0};
  u8 len = 0;
  switch(my_device_id)
  {
    case 0x10://����
      if(my_control[0] == 0x01)
      {
        FAN_Set = 1;
        updata[0] = 0x01;
      }else if(my_control[0] == 0x02)
      {
        FAN_Set = 0;
        updata[0] = 0x02;
      }
      len = 1;
      feedback(my_device_id,updata,len);
      break;
    case 0x20://�̵���1
      if(my_control[0] == 0x01)
      {
        Relay1_Set = 1;
        updata[0] = 0x01;
      }else if(my_control[0] == 0x02)
      {
        Relay1_Set = 0;
        updata[0] = 0x02;
      }
      len = 1;
      feedback(my_device_id,updata,len);
      break;
    case 0x30://�̵���2
      if(my_control[0] == 0x01)
      {
        Relay2_Set = 1;
        updata[0] = 0x01;
      }else if(my_control[0] == 0x02)
      {
        Relay2_Set = 0;
        updata[0] = 0x02;
      }
      len = 1;
      feedback(my_device_id,updata,len);
      break;
    case 0x40://�������
      if(my_control[0] == 0x01)
      {
        A4988_DIR = 1;
        Motor_Control(2000,380);
        updata[0] = 0x01;
      }else if(my_control[0] == 0x02)
      {
        A4988_DIR = 0;
        Motor_Control(2000,380);
        updata[0] = 0x02;
      }
      len = 1;
      feedback(my_device_id,updata,len);
      break;
    default:
      break;
  }
  
}

#endif

#if board8

//mini21864
//rfid������
//�������--��IIC
//ָ��ʶ��ģ��
//�����
#include "iic_master.h"
#include "lock.h"
#include "rc522.h"
#include "JXL12864G-086.h"
#include "figure_print.h"
#include "exti.h"
#include "Debug_usart.h"

void device_init(void)//�豸��ʼ������
{
  
  figure_print_init();//ָ��ģ��ĳ�ʼ��
  Lock_Init();//������ĳ�ʼ��
  EXTIX_Init();//�ⲿ�жϳ�ʼ��
  IIC_M_Init();//IIC�ĳ�ʼ��
  InitRc522();//��Ƶnfc�ĳ�ʼ��
  Lcd_Init_IN();//mini12864�ĳ�ʼ��
  Clear_Screen_IN();//�����Ļ��ʾ
  
 
}
//�豸�Ŀ��ƺ���
void my_equ_control(u16 my_device_id,u8 my_control[ZIGBEE_BUFFER_LEN])
{
  u8 updata[1] = {0};
  u8 len = 0;
  if(my_device_id == 0x10)
  {
    if(my_control[0] == 0x01)
    {
      LOCK_CONTROL = 0x01;
      delayMs(500);
      delayMs(500);
      LOCK_CONTROL = 0x00;
    }else if(my_control[0] == 0x02)
    {
      LOCK_CONTROL = 0x00;
    }
    if(LOCK_CONTROL == 0)
      updata[0] = 0x02;
    else
      updata[0] = 0x01;
    len = 1;
    feedback(my_device_id,updata,len);
  }
}


#endif

//���ݵ��Ϸ�����
void feedback(u8* id,u8* my_control,u8 control_len)
{
	u8 i;
	u16 crcd;
	//�޸ĳ�485��ģʽ
	updata_buffer[0] = 0xED;
	updata_buffer[1] = id[0];
	updata_buffer[2] = id[1];
	updata_buffer[3] = id[2];
	updata_buffer[4] = id[3];
	updata_buffer[5] = id[4];
	updata_buffer[6] = 0xA2;
	updata_buffer[7] = control_len+10;
	for(i=0;i<control_len;i++)
	{
		updata_buffer[8+i] = my_control[i];
	}
	
	crcd = crc16_check(updata_buffer,control_len+8);
	updata_buffer[8+control_len] = crcd>>8;
	updata_buffer[9+control_len] = crcd&0xFF;
	mode_485_rt = 1;
	zigbee_send(10+control_len,updata_buffer);
	mode_485_rt = 0;
}

