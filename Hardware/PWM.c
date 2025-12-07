#include "stm32f10x.h" 

void PWM_init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    GPIO_InitTypeDef GPIO_A;
    TIM_TimeBaseInitTypeDef TIM_2;
    TIM_OCInitTypeDef TIM_OC;

    //——————————————GPIO————————————————
    GPIO_A.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_A.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
    GPIO_A.GPIO_Speed=GPIO_Speed_50MHz;
    

    TIM_InternalClockConfig(TIM2);
    
    //—————————————TIMBase——————————————
    TIM_2.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_2.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_2.TIM_Period=100-1;         //ARR
    TIM_2.TIM_Prescaler=720-1;       //PSC
    

    //—————————————TIMOC————————————————
    TIM_OCStructInit(&TIM_OC);
    TIM_OC.TIM_OCMode=TIM_OCMode_PWM1;
    TIM_OC.TIM_OCPolarity=TIM_OCPolarity_High;
    TIM_OC.TIM_OutputState=TIM_OutputState_Enable;
    TIM_OC.TIM_Pulse=0;             //CCR


    //—————————————INIT—————————————————
    GPIO_Init(GPIOA,&GPIO_A);
    TIM_TimeBaseInit(TIM2,&TIM_2);
    TIM_OC1Init(TIM2,&TIM_OC);
    TIM_OC2Init(TIM2,&TIM_OC);

    
    //—————————————CMD——————————————————
    TIM_Cmd(TIM2,ENABLE);

}

void PWM_Set_OC1_CCR(uint16_t CCR)
{
    TIM_SetCompare1(TIM2,CCR);

}

void PWM_Set_OC2_CCR(uint16_t CCR)
{
    TIM_SetCompare2(TIM2,CCR);

}

void PWM_Set_OC_CCR(uint16_t CCR)
{
    TIM_SetCompare1(TIM2,CCR);
    TIM_SetCompare2(TIM2,CCR);

}
