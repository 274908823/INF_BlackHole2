#include "usart3.h"
#include <stdarg.h>
#include "string.h"

u8 send_buf_length_24[SEND_BUF_LENGTH_24]={0};
u8 send_buf_length_32[SEND_BUF_LENGTH_32]={0};

/*
 * ��������USART3_Config
 * ����  ��USART3 GPIO ����,����ģʽ���á�115200 8-N-1
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void USART3_Init(unsigned int baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* config USART3 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/* USART3 GPIO config */
	/* Configure USART3 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);    
	/* Configure USART3 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	  
	/* USART3 mode config */
	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART3, &USART_InitStructure); 
	
  USART_Cmd(USART3, ENABLE);
	
	USART3_DMA_Init();
}

/*
 * ��������DMA_Config
 * ����  ��DMA ���ڵĳ�ʼ������
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void USART3_DMA_Init(void)
{
  DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//����DMAʱ��
	
	/* Configure one bit for preemption priority */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* ����P[A|B|C|D|E]0Ϊ�ж�Դ */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
 	/*����DMAԴ���ڴ��ַ&�������ݼĴ�����ַ*/
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART3_DR_Base;    
  /*���򣺴��ڴ浽����*/		
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
	/*�ڴ��ַ(Ҫ��ŵı�����ָ��)*/
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)send_buf_length_32;
	/*�����СDMA_BufferSize=SENDBUFF_SIZE*/	
	DMA_InitStructure.DMA_BufferSize = SEND_BUF_LENGTH_32;	
	/*�����ַ����*/	    
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 	
	/*�ڴ��ַ����*/
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;		
	/*�������ݵ�λ*/	
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	
	/*�ڴ����ݵ�λ 8bit*/
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 	
	/*DMAģʽ��һ�δ��䣬ѭ��*/
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	 	
	/*���ȼ�����*/	
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  	
	/*��ֹ�ڴ浽�ڴ�Ĵ���	*/
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	
	/*����DMA1��2ͨ��*/		   
  DMA_Init(DMA1_Channel2, &DMA_InitStructure); 	   
	
	DMA_Cmd (DMA1_Channel2,ENABLE);					       //ʹ��DMA
	DMA_ITConfig(DMA1_Channel2,DMA_IT_TC,ENABLE);  //����DMA������ɺ�����ж�

}


void USART3_DMA_Init_24(void)
{
  DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//����DMAʱ��
	
	/* Configure one bit for preemption priority */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* ����P[A|B|C|D|E]0Ϊ�ж�Դ */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
 	/*����DMAԴ���ڴ��ַ&�������ݼĴ�����ַ*/
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART3_DR_Base;    
  /*���򣺴��ڴ浽����*/		
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
	/*�ڴ��ַ(Ҫ��ŵı�����ָ��)*/
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)send_buf_length_24;
	/*�����СDMA_BufferSize=SENDBUFF_SIZE*/	
	DMA_InitStructure.DMA_BufferSize = SEND_BUF_LENGTH_24;	
	/*�����ַ����*/	    
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 	
	/*�ڴ��ַ����*/
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;		
	/*�������ݵ�λ*/	
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	
	/*�ڴ����ݵ�λ 8bit*/
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 	
	/*DMAģʽ��һ�δ��䣬ѭ��*/
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	 	
	/*���ȼ�����*/	
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  	
	/*��ֹ�ڴ浽�ڴ�Ĵ���	*/
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	
	/*����DMA1��2ͨ��*/		   
  DMA_Init(DMA1_Channel2, &DMA_InitStructure); 	   
	
	DMA_Cmd (DMA1_Channel2,ENABLE);					       //ʹ��DMA
	DMA_ITConfig(DMA1_Channel2,DMA_IT_TC,ENABLE);  //����DMA������ɺ�����ж�

}

DMA_InitTypeDef DMA_InitStructure;

u8 send_buf_length;
int SEND_BUF_LENGTH;
/*
 * ��������USART3_Data_Send
 * ����  ��
 * ����  ��
 * ���  ����
 */  
void USART3_Data_Send(unsigned char *send_buf,int length)
{
	//�����Ҫ�����Ż�������֮�����³�ʼ����DMA_Init���Ż������ѿ�����
	//������̳��������Ŷ  www.infcre.com/forum.php
	if(length == SEND_BUF_LENGTH_24)
	{
		memcpy(&send_buf_length_24,send_buf,length);
		
		DMA_Cmd(DMA1_Channel2, DISABLE);   //ֹͣDMA
		//DMA_InitStructure.DMA_MemoryBaseAddr = (u32)send_buf_length_24;
		//DMA_InitStructure.DMA_BufferSize = SEND_BUF_LENGTH_24;
		USART3_DMA_Init_24();
	}		
	else if(length == SEND_BUF_LENGTH_32)
	{
		memcpy(&send_buf_length_32,send_buf,length);
		
		DMA_Cmd(DMA1_Channel2, DISABLE);   //ֹͣDMA
		//DMA_InitStructure.DMA_MemoryBaseAddr = (u32)send_buf_length_32;
		//DMA_InitStructure.DMA_BufferSize = SEND_BUF_LENGTH_32;
		USART3_DMA_Init();
	}		
			
	DMA_Cmd(DMA1_Channel2, ENABLE);    //Enable DMA
	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
}

void DMA1_Channel2_IRQHandler(void)
{	
	//�ж��Ƿ�ΪDMA��������ж�   
	if(DMA_GetFlagStatus(DMA1_FLAG_TC2) == SET)    
	{
		DMA_ClearFlag(DMA1_FLAG_TC2);
	}
}

u8 receive_data = 0x00;
void USART3_IRQHandler(void)                	//����3�жϷ������
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
		receive_data = USART_ReceiveData(USART3);//(USART1->DR);	//��ȡ���յ�������			 
  } 

} 

/*
 * ��������fputc
 * ����  ���ض���c�⺯��printf��USART1
 * ����  ����
 * ���  ����
 * ����  ����printf����
 */
int fputc(int ch, FILE *f)
{
	/* ��Printf���ݷ������� */
  	USART_SendData(USART3, (unsigned char) ch);
  	while (!(USART3->SR & USART_FLAG_TXE));
  	
  	return (ch);
}

/*
 * ��������itoa
 * ����  ������������ת�����ַ���
 * ����  ��-radix =10 ��ʾ10���ƣ��������Ϊ0
 *         -value Ҫת����������
 *         -buf ת������ַ���
 *         -radix = 10
 * ���  ����
 * ����  ����
 * ����  ����USART1_printf()����
 */
static char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */

/*
 * ��������USART1_printf
 * ����  ����ʽ�������������C���е�printf��������û���õ�C��
 * ����  ��-USARTx ����ͨ��������ֻ�õ��˴���1����USART1
 *		     -Data   Ҫ���͵����ڵ����ݵ�ָ��
 *			   -...    ��������
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ����
 *         ����Ӧ��USART1_printf( USART1, "\r\n this is a demo \r\n" );
 *            		 USART1_printf( USART1, "\r\n %d \r\n", i );
 *            		 USART1_printf( USART1, "\r\n %s \r\n", j );
 */
void USART3_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
{
	const char *s;
  	int d;   
  	char buf[16];
  	
  	va_list ap;
  	va_start(ap, Data);

	while ( *Data != 0)     // �ж��Ƿ񵽴��ַ���������
	{				                          
		if ( *Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //�س���
					USART_SendData(USARTx, 0x0d);
					Data ++;
					break;

				case 'n':							          //���з�
					USART_SendData(USARTx, 0x0a);	
					Data ++;
					break;
				
				default:
					Data ++;
				    break;
			}			 
		}
		else if ( *Data == '%')
		{									  //
			switch ( *++Data )
			{				
				case 's':										  //�ַ���
					s = va_arg(ap, const char *);
          for ( ; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
          }
					Data++;
          break;

        case 'd':										//ʮ����
          d = va_arg(ap, int);
          itoa(d, buf, 10);
          for (s = buf; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
          }
					Data++;
          break;
				 default:
						Data++;
				    break;
			}		 
		} /* end of else if */
		else USART_SendData(USARTx, *Data++);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
}
/******************* (C) COPYRIGHT 2013 CEPARK�๦�ܿ���ѧϰ��*****END OF FILE****/

