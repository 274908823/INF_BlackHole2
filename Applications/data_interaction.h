#ifndef __DATE_INTERACTION_H
#define __DATE_INTERACTION_H
	
#include "stm32f10x.h"

//ȡһ�����ݵĵ�ַǿ��ת����ָ��char�͵ģ�Ȼ��ȡǰ��λ
#define BYTEL(dwTemp)       (*(char *)(&dwTemp))
#define BYTEH(dwTemp)       (*((char *)(&dwTemp) + 1))
	
#define OUT_DATA_LENGTH 24	//�������ݳ���

void Pilot_Status_USART_Data_Send(void);
void Pilot_Status_USB_Data_Send(void);
#endif



