#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
#include "Serial.h"


uint8_t Serial_RxData;
uint8_t Serial_RxFlag;
uint8_t Serial_TxPacket[4];
char Serial_RxPacket[100];



void Serial_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

    GPIO_InitTypeDef a;
    a.GPIO_Mode=GPIO_Mode_AF_PP;
    a.GPIO_Pin=GPIO_Pin_9;
    a.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&a);

     a.GPIO_Mode=GPIO_Mode_IPU;
    a.GPIO_Pin=GPIO_Pin_10;
    a.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&a);

    USART_InitTypeDef b;
    b.USART_BaudRate=9600;//波特率
    b.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//硬件流控制
    b.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;//接收模式or发送模式or接收|发送模式
    b.USART_Parity=USART_Parity_No;//校验 ODD基校验
    b.USART_StopBits=USART_StopBits_1;//停止字节长
    b.USART_WordLength=USART_WordLength_8b;//字长
    USART_Init(USART1,&b);

    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef c;
    c.NVIC_IRQChannel=USART1_IRQn;
    c.NVIC_IRQChannelCmd=ENABLE;
    c.NVIC_IRQChannelPreemptionPriority=1;
    c.NVIC_IRQChannelSubPriority=2;
    NVIC_Init(&c);


    USART_Cmd(USART1,ENABLE);

}





void Serial_Send(uint8_t byte)
{
    USART_SendData(USART1,byte);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);

}
void Serial_Send_array(uint8_t *Arrary,uint16_t Length)//发送数组
{
    int16_t i;
    for (i=0;i<Length;i++)
    {
        Serial_Send(Arrary[i]);
    }
}
void Serial_send_string(char *string)
{
    int16_t i;
    for(i=0;string[i]!=0;i++)
    {
        Serial_Send(string[i]);
    }

}
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_Send(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch,FILE*F)//printf代码底层
{
    Serial_Send(ch);
    return ch;
}

void Serial_Printf(char *format,...)//封装sprintf
{
    char String[100];
    va_list arg;
    va_start(arg,format);
    vsprintf(String,format,arg);
    va_end(arg);
    Serial_send_string(String);
}

uint8_t Serial_GetRxFlag(void)
{
    if(Serial_RxFlag==1)
    {
        Serial_RxFlag=0;
        return 1;
    }
    return 0;

}

uint8_t Serial_GetRxData(void)
{
    return Serial_RxData;

}

void Serial_SendPacket(void)
{
    Serial_Send(0xff);
    Serial_Send_array(Serial_TxPacket,4);
    Serial_Send(0xfe);

}


/*void USART1_IRQHandler(void)
{
    static uint8_t RxState=0;
    static uint8_t PRxState=0;
    if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
    {
        uint8_t Rxdata=USART_ReceiveData(USART1); 
        if(RxState==0)
        {
            if(Rxdata=='*')
            {
                RxState=1;
            }
            
        }
        else if(RxState==1)
        {
            if(Rxdata=='\r')
            {
                RxState=2;
            }
            else
            {
                Serial_RxPacket[PRxState]=Rxdata;
                PRxState++;
            }

        }
        else if(RxState==2)
        {
            if(Rxdata=='\n')
            {
                RxState=0;
                Serial_RxPacket[PRxState]='\0';
                Serial_RxFlag=1;
                
            }

        }

        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }

}*/






