#include "stm32f10x.h" 
#include "PWM.h"
void Motor_init(void)
{
    PWM_init();
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    //——————————————GPIO————————————————

    GPIO_InitTypeDef GPIO_A;
    GPIO_A.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_A.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
    GPIO_A.GPIO_Speed=GPIO_Speed_50MHz;
    

    GPIO_InitTypeDef GPIO_B;
    GPIO_B.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_B.GPIO_Pin=GPIO_Pin_14|GPIO_Pin_15;
    GPIO_B.GPIO_Speed=GPIO_Speed_50MHz;
    

    //—————————————INIT—————————————————
    GPIO_Init(GPIOA,&GPIO_A);
    GPIO_Init(GPIOB,&GPIO_B);

}

void Motor_Set_OC_Speed(int16_t Speed)
{
    if (Speed>=0)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_4);
        GPIO_SetBits(GPIOB,GPIO_Pin_14);

        GPIO_ResetBits(GPIOA,GPIO_Pin_5);
        GPIO_ResetBits(GPIOB,GPIO_Pin_15);

        PWM_Set_OC_CCR(Speed);
    }
    else
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_5);
        GPIO_SetBits(GPIOB,GPIO_Pin_15);

        GPIO_ResetBits(GPIOA,GPIO_Pin_4);
        GPIO_ResetBits(GPIOB,GPIO_Pin_14);

        PWM_Set_OC_CCR(-Speed);

    }

}

void Motor_Set_OC1_Speed(int16_t Speed)
{
    if (Speed>=0)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_4);

        GPIO_ResetBits(GPIOA,GPIO_Pin_5);

        PWM_Set_OC1_CCR(Speed);
    }
    else
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_5);
        
        GPIO_ResetBits(GPIOA,GPIO_Pin_4);
        
        PWM_Set_OC1_CCR(-Speed);
    }
}

void Motor_Set_OC2_Speed(int16_t Speed)
{
    if (Speed>=0)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_14);

        GPIO_ResetBits(GPIOB,GPIO_Pin_15);

        PWM_Set_OC2_CCR(Speed);
    }
    else
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_15);
        
        GPIO_ResetBits(GPIOB,GPIO_Pin_14);
        
        PWM_Set_OC2_CCR(-Speed);
    }
}
