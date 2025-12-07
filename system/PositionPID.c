
void Position_PID(float Target,float Actual,float Kp,float Ki,float Kd,float *Out)
{
   static float Error0,Error1,Error2;

	Error2 = Error1;		
	Error1 = Error0;
	Error0 = Target - Actual;
	
	*Out += Kp * (Error0 - Error1) + Ki * Error0  + Kd * (Error2 - 2 * Error1 + Error2);
	if(*Out > 100){*Out=100;}
	if(*Out < -100){*Out=-100;}

}
