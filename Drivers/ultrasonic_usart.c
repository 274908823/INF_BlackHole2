#include "ultrasonic_usart.h"	  
#include "stm32f10x.h"

/*
 * Function Name: Ultrasonic_Module_Init
 * Description  : Ultrasonic ranging module initialize.
 * Input  	    : none
 * Output       : none
 */
void Ultrasonic_Module_Init(void)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
//����1�ܽų�ʼ�� PA9 TX PA10 RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;																
	GPIO_Init(GPIOA, &GPIO_InitStructure); 	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;       
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;																
//	GPIO_Init(GPIOA, &GPIO_InitStructure); 																				
  
	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = 80000;																		 //������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;										 //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;											   //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;														 //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode =  USART_Mode_Tx | USART_Mode_Rx;							 //�շ�ģʽ
	
	//Usart1 NVIC ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;                              //
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;                       //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		                         //�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			                           //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	                                               //����ָ���Ĳ�����ʼ��VIC�Ĵ���
   
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//���������ж�
//	USART_ITConfig(USART1, USART_IT_TXE, ENABLE); //���������ж�

  USART_Init(USART1, &USART_InitStructure); 																		 //��ʼ������

  USART_Cmd(USART1, ENABLE);                																		 //ʹ�ܴ��� 
}


