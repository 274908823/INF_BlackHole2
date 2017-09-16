#ifndef __WIFI_MODULE_H
#define __WIFI_MODULE_H

#include "stm32f10x.h"

#define WIFI_RST(X)  (X==0)?GPIO_ResetBits(GPIOA,GPIO_Pin_4):GPIO_SetBits(GPIOA,GPIO_Pin_4)//WifiоƬ��λ���ţ��͵�ƽ��λ
#define WIFI_CH_PD(X)  (X==0)?GPIO_ResetBits(GPIOC,GPIO_Pin_14):GPIO_SetBits(GPIOC,GPIO_Pin_14)//WifiоƬʹ�ܶˣ��ߵ�ƽ��Ч

void WIFI_Module_Enable(void);
void WIFI_Module_Init(void);

#endif


