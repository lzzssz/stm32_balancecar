#include "stm32f10x.h"                  // Device header
void Econdor1_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//1.使能时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

  GPIO_InitTypeDef b;//2.开启GPIO
  b.GPIO_Mode=GPIO_Mode_IPU;
  b.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
  b.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&b);

  TIM_TimeBaseInitTypeDef a;//3.配置时基单元
  a.TIM_ClockDivision=TIM_CKD_DIV1;//预分频选择
  a.TIM_CounterMode=TIM_CounterMode_Up ;//计数模式选择 向上计数
  a.TIM_Period=65535-1;
  a.TIM_Prescaler=1-1;//两个参数配置计数时间
  TIM_TimeBaseInit(TIM3,&a);

  TIM_ICInitTypeDef c;//4.配置IC输入
  TIM_ICStructInit(&c);//赋初始值
  c.TIM_Channel=TIM_Channel_1;
  c.TIM_ICFilter=0xF;
  TIM_ICStructInit(&c);
  c.TIM_Channel=TIM_Channel_2;
  c.TIM_ICFilter=0xF;

  TIM_ICInit(TIM3,&c);
  //配置定时器编码器模式
  TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//Rasing为正向，Falling为反向

  TIM_Cmd(TIM3,ENABLE);//开启时钟

}

int16_t Econdor1_CNT(void)
{
  int16_t t=0;//定参为了方便给CNT清零
  t=TIM_GetCounter(TIM3);
  TIM_SetCounter(TIM3,0);//给CNT置0
  return t;

}

void Econdor2_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//1.使能时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

  GPIO_InitTypeDef b;//2.开启GPIO
  b.GPIO_Mode=GPIO_Mode_IPU;
  b.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
  b.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&b);

  TIM_TimeBaseInitTypeDef a;//3.配置时基单元
  a.TIM_ClockDivision=TIM_CKD_DIV1;//预分频选择
  a.TIM_CounterMode=TIM_CounterMode_Up ;//计数模式选择 向上计数
  a.TIM_Period=65535-1;
  a.TIM_Prescaler=1-1;//两个参数配置计数时间
  TIM_TimeBaseInit(TIM4,&a);

  TIM_ICInitTypeDef c;//4.配置IC输入
  TIM_ICStructInit(&c);//赋初始值
  c.TIM_Channel=TIM_Channel_1;
  c.TIM_ICFilter=0xF;
  TIM_ICStructInit(&c);
  c.TIM_Channel=TIM_Channel_2;
  c.TIM_ICFilter=0xF;

  TIM_ICInit(TIM4,&c);
  //配置定时器编码器模式
  TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//Rasing为正向，Falling为反向

  TIM_Cmd(TIM4,ENABLE);//开启时钟

}

int16_t Econdor2_CNT(void)
{
  int16_t t=0;//定参为了方便给CNT清零
  t=TIM_GetCounter(TIM4);
  TIM_SetCounter(TIM4,0);//给CNT置0
  return t;
}

void Econdor1_Catch_Speed( float T ,float *speed)
{
 static float rpm;
  rpm=60*Econdor1_CNT()/(400*T);//圈每秒
  *speed=rpm*3.1415926/30;
}
void Econdor2_Catch_Speed( float T ,float *speed)
{
  static float rpm;
  rpm=60*Econdor2_CNT()/(400*T);//圈每秒
  *speed=rpm*3.1415926/30;
}
