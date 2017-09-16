#include "function.h"
#include "battery_check.h"
#include "led.h"

extern u8 unlock_flag;					//������־λ��Ϊ0δ������Ϊ1����	
extern vu8 led_show_mode;
extern float battery_voltage;		//��ص�ѹ
extern u8 unlock_status;//�Ƿ�ִ�н���״̬��־λ
extern u8 lock_status;//�Ƿ�ִ������״̬��־λ

//��ȡLED��״̬
void LED_State_Read(void)
{
	//�����ص�ѹС�����ޣ�����ʾ����
	if(unlock_flag == 1)//����״̬��
	{
		if((battery_voltage < BATTERY_LOW_VOLTAGE_FLYING))	led_show_mode = Low_Power_Mode;
		else led_show_mode = Normal_Fly_Mode;
	}
	else//δ����״̬��
	{
		if((battery_voltage < BATTERY_LOW_VOLTAGE_UNFLYING))	led_show_mode = Low_Power_Mode;
		else led_show_mode = Wait_Fly_Mode;
	}
	
	if(unlock_status == 1)	led_show_mode = Unlock_Mode;
	if(lock_status == 1)	led_show_mode = Lock_Mode;
}




