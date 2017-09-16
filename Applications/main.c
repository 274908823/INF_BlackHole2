/********* BlackHole2 **************
 *	File					:					 main.c
 *	Description		: 	�����򣬳�ʼ���Ĵ���
 *  IDE						:			  	 MDK5.14
 *	Version				:    	BlackHole2_V1.0
 *	Author				:	 		  		 INF
 *	Copyright			:	  	��INF�������
 *	Last Time			:			     20160806								
 *	Support				:		 	 www.infcre.com
 *	QQ Group			:   	    168590475
 *  State					:        	 	 open
 *			For infinite creativity
 */

#include "main.h"

/*
 * Function Name:System_Init
 * Description	:System init function
 * Input  			:None
 * Output  			:None
 */
void System_Init(void)
{
	FLASH_Unlock();											//����flash,�Ƿ�ȫ���࿼��
	EE_Init();													//��ʼ��ģ��eeprom����	
	Param_Init();												//������ʼ��                
	LED_Init();													//LED״̬�Ƴ�ʼ��
	PWM_In_Init(0xffff,72	-	1);       	//�������벶�񣬶�ʱ����Ϊ1us
	PWM_Out_Init(3999,35,0,0,0,0);			//PWM�����ʼ�������PWMƵ��500Hz
	WIFI_Module_Init();   							//Wifi Module initialize	
 	Ultrasonic_Module_Init();           //Ultrasonic module initialization
	ADC_Battery_Init();									//��ص�ѹADC����ʼ��
	while(!MPU6500_Init());							//�ȴ�MPU6500��ʼ���ɹ�
	//MS5611_Init();											//MS5611 initialize
	LED_StartShow();										//Polit start state display
  USB_Hardware_Init(); 								//USBͨ�ų�ʼ��
  Systick_Init();											//Enable system 1ms interrupt	
}

/*
 * Function Name:main
 * Description	:main function
 * Input  			:None
 * Output  			:None
 */
int main(void)
{			
	System_Init();											//system initialize
	while(1)													
	{			
		System_Task_Loop();								//system task loop
  }	 			  
}
		
		








#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
		/* User can add his own implementation to report the file name and line number,
			 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

		/* Infinite loop */
		while (1)
		{
		}
}

#endif

