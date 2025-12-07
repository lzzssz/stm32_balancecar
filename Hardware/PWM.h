#include "stm32f10x.h"
#ifndef __PWM_H
#define __PWM_H

void PWM_init(void);

void PWM_Set_OC1_CCR(uint16_t CCR);

void PWM_Set_OC2_CCR(uint16_t CCR);

void PWM_Set_OC_CCR(uint16_t CCR);


#endif
