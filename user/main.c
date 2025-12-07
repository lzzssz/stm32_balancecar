#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Econdor.h"
#include "Pid_Serial.h"
#include "Serial.h"
#include "Timer.h"
#include "PositionPID.h"
#include "Key.h"
#include "MPU6050.h"
#include <math.h>

float Avi_target;
float kp1=0,ki1=0,kd1=0;

float LeftPwm1,RightPwm2;
float LeftSpeed,RightSpeed;
float Avi_L_speed,Avi_R_speed;
float Dvi_L_speed=0,Dvi_R_speed=0;
float Avi_out,Avi_Speed;

float Angle;

int16_t ax,ay,az,gx,gy,gz;


uint8_t KeyNum;

int main(void)
{
	Timer_Init();
	OLED_Init();
	Pid_Serial_Init();
	Motor_init();
	Econdor1_init();
	Econdor2_init();
	MPU6050_Init();

	while(1)
	{
		MPU6050_GetData(&ax,&ay,&az,&gx,&gy,&gz);
		Serial_Printf("%d,%d,%d,%d,%d,%d\r\n",ax,ay,az,gx,gy,gz);
		
		/*
		Pid_Tset(&Avi_target,&kp1,&ki1,&kd1);
		Serial_Printf("\r\n%f\r\n",Angle);
		Serial_Printf("%f %f %f %f\r\n",Avi_target,kp1,ki1,kd1);
		*/
	}
}
void TIM1_UP_IRQHandler(void) 
{
	static uint16_t count;

	static float Avi_actual;
	if(TIM_GetITStatus(TIM1,TIM_IT_Update) == SET)
	{

		

		//Key_Tick();
		count++;
		if (count >= 50)
		{
			count = 0;



			/*
			Econdor1_Catch_Speed(0.05,&RightSpeed);
			Econdor2_Catch_Speed(0.05,&LeftSpeed);
 
			
			Avi_actual=LeftSpeed/2+RightSpeed/2;
			
		//均速环——avi_speed
			Position_PID(0,Avi_actual,kp1,ki1,kd1,&Avi_out);
		

			//     姿态环
			Angle_XoZ(&Angle);//提取姿态角
				//姿态环作用于左轮
			Position_PID(Avi_out,Angle,3,0,-1,&Avi_Speed);
			
			
			LeftPwm1=Avi_Speed;
			RightPwm2=Avi_Speed;
		
			if(LeftPwm1>=100){LeftPwm1=100;}else if (LeftPwm1<=-100){LeftPwm1=-100;}
			if(RightPwm2>=100){RightPwm2=100;}else if (RightPwm2<=-100){RightPwm2=-100;}

			
			Motor_Set_OC1_Speed(-LeftPwm1);
			Motor_Set_OC2_Speed(-RightPwm2);
			*/
			
		}
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
	}
}
