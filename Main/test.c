#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "usart2.h"
//VCC接5V
//GND接地
//TXD接单片机RXD（我用的是usart2,PA3)
//J27接地（等价于短接M2）串口模式
//J33接地（等价于短接M4）读取8位UID
//UID依靠串口中断读取
//串口中断在usart.c中
//波特率9600	 	 
/*int main(void) //从usart1读卡
{			
	u8 t;
	//u8 len;
	u8 che;	
	u16 times = 0;
	u8 UID[9];           //能开锁的UID
	u8 success = 0;  	 //标记读到的UID是否能开锁
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化 
	uart_init(72,9600);	 //串口初始化为9600
	//uart2_init(72,19200); //串口2的时钟频率只有1的一半
	LED_Init();		  	 //初始化与LED连接的硬件接口    
	while(1)
	{
		if(USART_RX_STA&0x80)
		{					   
			printf("Card recognized\r\n");
			che = 0;
			for(t=0;t<8;t++)                    //判断读取的UID是否正确
			{
				che = che^USART_RX_BUF[t];	    //校检位为数据异或和
			}
			if(che == USART_RX_BUF[8]) 		   	//校检成功
			{
			    //for(t=0;t<9;t++)
			    //{
				//    USART1->DR=USART_RX_BUF[t];//用串口直接发送
				//    while((USART1->SR&0X40)==0);//等待发送结束
			    //}
				printf("UID is: ");
				success = 1;
				for(t=0;t<8;t++)
			    {
				    printf("%02X ",USART_RX_BUF[t]);
					if(USART_RX_BUF[t] != UID[t])  //比对，有一位不一致就失败
					{
					    success = 0;
					} 
			    }
				if(success == 1)
				{
				    printf("\r\nLock is opened.\r\n");
				}
				else
				{
				    printf("\r\nCard uncorrect.\r\n");
				}
				printf("che is %02X\n",che);
				printf("\nCheck: %02X\r\n",USART_RX_BUF[8]);
				//printf("\r\nCheck: %02X\r\n",USART_RX_BUF[8]);  
			}
			else							   //校检失败
			{
			    printf("\nIs it an ID card?\r\n");
				printf("che is %02X\n",che);
				printf("\nCheck: %02X\r\n",USART_RX_BUF[8]);
				for(t=0;t<8;t++)
			    {
				    printf("%02X ",USART_RX_BUF[t]); 
			    }
			}
			USART_RX_STA=0;
		}else									  
		{
		    if((USART_RX_STA&0x40)&&(times%30==0))	   //如果一段时间读不到9位
			{
			    printf("Not an ID card\r\n");
				//for(t=0;t<USART_RX_STA&0X3F;t++)
			    //{
				//    printf("%02X ",USART_RX_BUF[t]);
			    //}
				USART_RX_STA=0;
			}
			times++;
			if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
			delay_ms(10);   
		}
	}	 
} */
											   

int main(void)			 //从usart2读卡
{			
	u8 t;
	//u8 len;
	u8 che;	
	u16 times = 0;
	u8 UID[9];           //能开锁的UID
	u8 success = 0;  	 //标记读到的UID是否能开锁
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化 
	uart_init(72,9600);	 //串口1初始化为9600
	uart2_init(72,19200);//串口2的时钟频率只有1的一半
	LED_Init();		  	 //初始化与LED连接的硬件接口    
	while(1)
	{
		if(USART2_RX_STA&0x80)
		{					   
			printf("Card recognized\r\n");
			che = 0;
			for(t=0;t<8;t++)                    //判断读取的UID是否正确
			{
				che = che^USART2_RX_BUF[t];	    //校检位为数据异或和
			}
			if(che == USART2_RX_BUF[8]) 		   	//校检成功
			{
			    //for(t=0;t<9;t++)
			    //{
				//    USART1->DR=USART2_RX_BUF[t];//用串口直接发送
				//    while((USART2->SR&0X40)==0);//等待发送结束
			    //}
				printf("UID is: ");
				success = 1;
				for(t=0;t<8;t++)
			    {
				    printf("%02X ",USART2_RX_BUF[t]);
					if(USART2_RX_BUF[t] != UID[t])  //比对，有一位不一致就失败
					{
					    success = 0;
					} 
			    }
				if(success == 1)
				{
				    printf("\r\nLock is opened.\r\n");
				}
				else
				{
				    printf("\r\nCard uncorrect.\r\n");
				}
				//printf("che is %02X\n",che);
				//printf("\nCheck: %02X\r\n",USART2_RX_BUF[8]);
				//printf("\r\nCheck: %02X\r\n",USART2_RX_BUF[8]);  
			}
			else							   //校检失败
			{
			    printf("\nIs it an ID card?\r\n");
				printf("che is %02X\n",che);
				printf("\nCheck: %02X\r\n",USART2_RX_BUF[8]);
				for(t=0;t<8;t++)
			    {
				    printf("%02X ",USART2_RX_BUF[t]); 
			    }
			}
			USART2_RX_STA=0;
		}else									  
		{
		    if(times%30==0)
		    {
			    LED0=!LED0;//闪烁LED,提示系统正在运行.
			    if(USART2_RX_STA&0x40)	   //如果一段时间读不到9位
		    	{
			        printf("Not an ID card\r\n");
			    	//for(t=0;t<USART2_RX_STA&0X3F;t++)
			        //{
			    	//    printf("%02X ",USART2_RX_BUF[t]);
			        //}
			    	USART2_RX_STA=0;	
			    }
				times = 0;	
			}
			times++;
			delay_ms(10);   
		}
	}	 
}






















