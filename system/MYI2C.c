#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void MYI2C_W_SCL(uint8_t t)
{
    GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)t);
    
}
void MYI2C_W_SDA(uint8_t t)
{
    GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)t);
    
}
uint8_t MYI2C_R_SDA()
{
    uint8_t Value;
    Value=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
    
    return Value;
}

void MyI2C_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef a;
    a.GPIO_Mode=GPIO_Mode_Out_OD;//开漏输出
    a.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
    a.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&a);  

    GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);

}

void MyI2c_Start(void)
{
     MYI2C_W_SDA(1);
     MYI2C_W_SCL(1);
     MYI2C_W_SDA(0);
     MYI2C_W_SCL(0);
}

void MyI2c_Stop(void)
{
     MYI2C_W_SDA(0);
     MYI2C_W_SCL(1);
     MYI2C_W_SDA(1);
}

void MyI2c_SendByte(uint8_t Byte)
{
    uint8_t i;
    for ( i = 0; i < 8; i++)
    {
        MYI2C_W_SDA(Byte & (0x80 >> i));
        MYI2C_W_SCL(1);
        MYI2C_W_SCL(0);
    }
}

uint8_t MyI2c_ReciveByte(void)
{
    uint8_t i,Byte=0x00;
    MYI2C_W_SDA(1);
    for ( i = 0; i < 8; i++)
    {
        MYI2C_W_SCL(1);
        if(MYI2C_R_SDA()==1)
        {
            
            Byte|=(0x80>>i);
            
        }
        MYI2C_W_SCL(0);    
    }   
        
    
    return Byte;
}

void MyI2c_SendACK(uint8_t ACK)
{
    
        MYI2C_W_SDA(ACK);
        MYI2C_W_SCL(1);
        MYI2C_W_SCL(0);

}

uint8_t MyI2c_ReciveACK(void)
{
    uint8_t ACK;  
     MYI2C_W_SDA(1);
     MYI2C_W_SCL(1);
     ACK=MYI2C_R_SDA();        
     MYI2C_W_SCL(0);                   
    return ACK;
}
