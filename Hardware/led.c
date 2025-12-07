#include "stm32f10x.h" 
#include "KEY.h"
void led_Init(void)//初始化函数
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//启动时钟
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;//推勉输出
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);//设置初始化状态
}
void LED1_ON(void)//L1亮
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}
void LED1_OFF(void)//L1灭
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}
void LED1_TURN(void)//L1取反部分
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==0)//运用函数检测状态 实现电频翻转
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	}

}
void LED2_ON(void)//L2亮
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}
void LED2_OFF(void)//L2灭
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}
void LED2_TURN(void)//L2取反
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==0)//1置0，0置1，相当于~
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}

}

