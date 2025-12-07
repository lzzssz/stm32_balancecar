#include "stm32f10x.h" 
#include "PWM.h"
#ifndef __Motor_H
#define __Motor_H

//初始化Motor
void Motor_init(void);

//同时改变两个Motor的速度
void Motor_Set_OC_Speed(int16_t Speed);

//改变CH1的Motor的速度
void Motor_Set_OC1_Speed(int16_t Speed);

//改变CH2的Motor的速度
void Motor_Set_OC2_Speed(int16_t Speed);

#endif
