/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.4.0
  * @date    10/15/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x_it.h"
#include "systick.h"
#include "task.h"

extern TASK_TIME Task_Time;
u32 system_time = 0;//��λ��ms

/*
 * ��������SysTick_Handler
 * ����  ���δ��жϺ���
 * ����  ����
 * ���  ����
 */  
void SysTick_Handler(void)
{	
	system_time++;
	
	Task_Time.Cnt_1Ms++;
	Task_Time.Cnt_2Ms++;
	Task_Time.Cnt_5Ms++;
	Task_Time.Cnt_10Ms++;
	Task_Time.Cnt_20Ms++;
	Task_Time.Cnt_40Ms++;
	Task_Time.Cnt_50Ms++;
	Task_Time.Cnt_150Ms++;
}


extern  void USB_Istr(void);

void USB_LP_CAN1_RX0_IRQHandler(void) 
{
	USB_Istr();
} 


u8 	Rc_Capture_Sta[13] = {0};//13��ͨ���Ĳ���״̬
u16 Rc_Channel_Val[13] = {0};//13��ͨ���Ĳ���ֵ

/*
 * ��������TIM2_IRQHandler
 * ����  ����ʱ��2���벶���жϺ���
 * ����  ����
 * ���  ����
 */ 
void TIM2_IRQHandler(void)
{
//**************************����1���������¼�**************************
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1)	!= RESET)
		{
			if(Rc_Capture_Sta[3])																				//�����½��� 		
			{
				Rc_Channel_Val[3]	=	TIM_GetCapture1(TIM2);								//��ȡ����ֵ������ΪPWM�ߵ�ƽʱ��
			 	Rc_Capture_Sta[3]	=	0;																		//��ǲ���������
				TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising); 				//����Ϊ�����ز���
			}
			else  																											//����������
			{
				TIM_SetCounter(TIM2,0);																		//�����������������
				Rc_Capture_Sta[3]	=	1;																		//��ǲ�����������
				TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling);				//����Ϊ�½��ز���
			}
      TIM_ClearITPendingBit(TIM2, TIM_IT_CC1); 	//���ͨ��1�жϱ�־λ
		}			     	   
	
//**************************����2���������¼�**************************
	if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
	{	
		if(Rc_Capture_Sta[2])																					//�����½��� 		
		{	  			
			Rc_Channel_Val[2]	=	TIM_GetCapture2(TIM2);									//��ȡ����ֵ������ΪPWM�ߵ�ƽʱ��	
			Rc_Capture_Sta[2]	=	0;																			//��ǲ��������� 		
			TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising); 					//����Ϊ�����ز��� 
		}
		else																													//����������
		{
			Rc_Capture_Sta[2]	=	1;																			//�����������������
			TIM_SetCounter(TIM2,0);																			//��ǲ�����������
			TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Falling);					//����Ϊ�½��ز���
		}		 
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2); 			 							//���ͨ��2�жϱ�־λ	
	}			 	
		
//**************************����3���������¼�**************************			
	if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)
	{
		if(Rc_Capture_Sta[1])																					//�����½��� 				 		
		{	  			
			Rc_Channel_Val[1]=TIM_GetCapture3(TIM2);										//��ȡ����ֵ������ΪPWM�ߵ�ƽʱ��
			Rc_Capture_Sta[1]=0;																				//��ǲ���������
		  TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Rising); 					//����Ϊ�����ز���  
		}
		else  																												//����������
		{
			Rc_Capture_Sta[1]=1;																				//�����������������
	 		TIM_SetCounter(TIM2,0);																			//��ǲ�����������
			TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Falling);					//����Ϊ�½��ز���
		}		 
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC3); 			 							//���ͨ��3�жϱ�־λ	
	}			 

	
//**************************����4���������¼�**************************	
	if (TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET)
	{
		if(Rc_Capture_Sta[0])																					//�����½��� 		
		{	  			
			Rc_Channel_Val[0]=TIM_GetCapture4(TIM2);										//��ȡ����ֵ������ΪPWM�ߵ�ƽʱ��
			Rc_Capture_Sta[0]=0;																				//��ǲ���������
			TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Rising);  				//����Ϊ�����ز���
		}
		else  																												//����������
		{
			Rc_Capture_Sta[0]=1;																				//�����������������
	 		TIM_SetCounter(TIM2,0);																			//��ǲ�����������
	 		TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Falling);					//����Ϊ�½��ز���
		}	
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC4); 		//���ͨ��4�жϱ�־λ	
	}			 
}

/*
 * ��������TIM3_IRQHandler
 * ����  ����ʱ��3���벶���жϺ���
 * ����  ����
 * ���  ����
 */ 
void TIM3_IRQHandler(void)
{
	//**************************����1���������¼�**************************	
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1)	!= RESET)
		{	
			if(Rc_Capture_Sta[5])																				//�����½��� 		
			{	  
				Rc_Channel_Val[5]	=	TIM_GetCapture1(TIM3);								//��ȡ����ֵ������ΪPWM�ߵ�ƽʱ��
			 	Rc_Capture_Sta[5]	=	0;																		//��ǲ���������
				TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising); 				//����Ϊ�����ز���
			}
			else  																											//����������
			{
				TIM_SetCounter(TIM3,0);																		//�����������������
				Rc_Capture_Sta[5]	=	1;																		//��ǲ�����������
				TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling);				//����Ϊ�½��ز���
			}	
      TIM_ClearITPendingBit(TIM3, TIM_IT_CC1); 	//���ͨ��1�жϱ�־λ			
		}			     	   
	
//**************************����2���������¼�**************************			
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
	{	
		if(Rc_Capture_Sta[4])																					//�����½��� 		
		{	  			
			Rc_Channel_Val[4]	=	TIM_GetCapture2(TIM3);									//��ȡ����ֵ������ΪPWM�ߵ�ƽʱ��	
			Rc_Capture_Sta[4]	=	0;																			//��ǲ��������� 		
			TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Rising); 					//����Ϊ�����ز��� 
		}
		else																													//����������
		{
			Rc_Capture_Sta[4]	=	1;																			//�����������������
			TIM_SetCounter(TIM3,0);																			//��ǲ�����������
			TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Falling);					//����Ϊ�½��ز���
		}		 
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2); 		//���ͨ��2�жϱ�־λ
	}
}



