#include    <stdio.h>
#include "stm32f10x.h"
#include <Pid_Serial.h>
#include <Serial.h>

uint8_t Pid_Typechoose;
uint8_t Pid_Serial_RxData;
uint8_t Pid_Serial_RxFlag;
char Pid_Serial_RxPacket[100];


void Pid_Serial_Init(void)
{
    Serial_Init();

}

uint8_t Pid_Serial_GetRxFlag(void)
{

    switch (Pid_Serial_RxFlag)//根据返回值返回返回值，兼让状态机返回初始状态
    {
        case Target:Pid_Serial_RxFlag=0;Pid_Typechoose=0;return Target;
        case Kp:Pid_Serial_RxFlag=0;Pid_Typechoose=0;return Kp;
        case Ki:Pid_Serial_RxFlag=0;Pid_Typechoose=0;return Ki;
        case Kd:Pid_Serial_RxFlag=0;Pid_Typechoose=0;return Kd;
        
        default:return 0;
    }

}

void USART1_IRQHandler(void)
{
    static uint8_t RxState=0;
    static uint8_t PRxState=0;
    if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
    {
        uint8_t Rxdata=USART_ReceiveData(USART1); 
        //状态机
        if(RxState==0)//状态机0：根据头字符判断参数种类
        {
            
           switch (Rxdata)
           {
                case '!':RxState=1;Pid_Typechoose=Target;break;
                case '@':RxState=1;Pid_Typechoose=Kp;break;
                case '#':RxState=1;Pid_Typechoose=Ki;break;
                case '$':RxState=1;Pid_Typechoose=Kd;break;
                default: RxState=0;Pid_Typechoose=0;break;
           }
            
        }
        else if(RxState==1)//状态机1：接收数据
        {
            if(Rxdata=='\r')
            {
                RxState=2;
            }
            else
            {
                Pid_Serial_RxPacket[PRxState]=Rxdata;
                PRxState++;
            }

        }
        else if(RxState==2)//状态机3：接受不同数据后传递不同的值
        {
            if(Rxdata=='\n')
            {
                RxState=0;
                Pid_Serial_RxPacket[PRxState]='\0';
                PRxState=0;

                switch (Pid_Typechoose)
                {
                    case Target:Pid_Serial_RxFlag=Target;break;
                    case Kp:Pid_Serial_RxFlag=Kp;break;
                    case Ki:Pid_Serial_RxFlag=Ki;break;
                    case Kd:Pid_Serial_RxFlag=Kd;break;
                }      
                
            }

        }

        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }

}
void Pid_Tset(float*target,float*kp,float*ki,float*kd)
{

    switch (Pid_Serial_GetRxFlag())
    {
        case Target:tranfer_5(target);break;
        case Kp:tranfer_4(kp);break;
        case Ki:tranfer_4(ki);break;
        case Kd:tranfer_4(kd);break;
    }
		
	
}

void tranfer_4(float *num)
{
    for (int i = 0; ; i++)
			{
				
				if (Pid_Serial_RxPacket[i]=='=')
				{
					
                            if(Pid_Serial_RxPacket[i+1]=='+')
                            {
                                int a=0,b=0,c=0,d=0;
                                a=Pid_Serial_RxPacket[i+2]-'0';
                                b=Pid_Serial_RxPacket[i+3]-'0';
                                c=Pid_Serial_RxPacket[i+5]-'0';
                                d=Pid_Serial_RxPacket[i+6]-'0';
                                *num=a*10+b*1+c*0.1+d*0.01;
                            }
                            else
                            {
                                int a=0,b=0,c=0,d=0;
                                a=Pid_Serial_RxPacket[i+2]-'0';
                                b=Pid_Serial_RxPacket[i+3]-'0';
                                c=Pid_Serial_RxPacket[i+5]-'0';
                                d=Pid_Serial_RxPacket[i+6]-'0';
                                *num=-(a*10+b*1+c*0.1+d*0.01);

                            }
                     break;	
				}
				
			}
}
void tranfer_5(float *num)
{
    for (int i = 0; ; i++)
			{
				
				if (Pid_Serial_RxPacket[i]=='=')
				{
					
                            if(Pid_Serial_RxPacket[i+1]=='+')
                            {
                                int a=0,b=0,c=0,d=0,e=0;
                                a=Pid_Serial_RxPacket[i+2]-'0';
                                b=Pid_Serial_RxPacket[i+3]-'0';
                                c=Pid_Serial_RxPacket[i+4]-'0';
                                d=Pid_Serial_RxPacket[i+6]-'0';
                                e=Pid_Serial_RxPacket[i+7]-'0';
                                *num=a*100+b*10+c*1+d*0.1+e*0.01;
                            }
                            else
                            {
                                int a=0,b=0,c=0,d=0,e=0;
                                a=Pid_Serial_RxPacket[i+2]-'0';
                                b=Pid_Serial_RxPacket[i+3]-'0';
                                c=Pid_Serial_RxPacket[i+4]-'0';
                                d=Pid_Serial_RxPacket[i+6]-'0';
                                e=Pid_Serial_RxPacket[i+7]-'0';
                                *num=-(a*100+b*10+c*1+d*0.1+e*0.01);

                            }
                     break;	
				}
				
			}
}
