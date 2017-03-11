#include <stm32f10x_lib.h>
#include "key.h"
#include "delay.h"
//按键初始化函数
//特别注意：在该函数之后，JTAG将无法使用（SWD也无法使用）
//如果想JTAG仿真，可以屏蔽该函数。
//PA0.13.15 设置成输入
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<2;     //使能PORTA时钟
	GPIOA->CRL&=0XFFFFFFF0;//PA0设置成输入	  
	GPIOA->CRL|=0X00000008;   
	GPIOA->CRH&=0X0F0FFFFF;//PA13,15设置成输入	  
	GPIOA->CRH|=0X80800000; 				   
	GPIOA->ODR|=1<<13;	   //PA13上拉,PA0默认下拉
	GPIOA->ODR|=1<<15;	   //PA15上拉
} 
//按键处理函数
//返回按键值
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2!!
u8 KEY_Scan(void)
{	 
	static u8 key_up=1;//按键按松开标志	
	JTAG_Set(JTAG_SWD_DISABLE);
	if(key_up&&(KEY0==0||KEY1==0||KEY2==1))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)
		{
			JTAG_Set(SWD_ENABLE);
			return 1;
		}
		else if(KEY1==0)
		{
			JTAG_Set(SWD_ENABLE);
			return 2;
		}
		else if(KEY2==1)
		{
			JTAG_Set(SWD_ENABLE);
			return 3;
		}
	}else if(KEY0==1&&KEY1==1&&KEY2==0)key_up=1; 	    
	JTAG_Set(SWD_ENABLE);
	return 0;// 无按键按下
}




















