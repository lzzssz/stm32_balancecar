#include "stm32f10x.h"
#include "MyI2C.h"
#include "MPU6050_Reg.h"
#include <math.h>
#define MPU6050_Adress 0xD0

void MPU6050_WritingReg(uint8_t RegAddress,uint8_t Data)
{
    MyI2c_Start();
    MyI2c_SendByte(MPU6050_Adress);
    MyI2c_ReciveACK();
    MyI2c_SendByte(RegAddress);
    MyI2c_ReciveACK();
    MyI2c_SendByte(Data);
    MyI2c_ReciveACK();
    MyI2c_Stop();

}
uint8_t MPU6050_ReadingReg(uint8_t RegAddress)
{
    uint8_t Data;
    MyI2c_Start();
    MyI2c_SendByte(MPU6050_Adress);
    MyI2c_ReciveACK();
    MyI2c_SendByte(RegAddress);
    MyI2c_ReciveACK();

    MyI2c_Start();//重启
    MyI2c_SendByte(MPU6050_Adress|0x01);
    MyI2c_ReciveACK();
    Data=MyI2c_ReciveByte();
    MyI2c_SendACK(1);//1不给应答 0给应答
    MyI2c_Stop();

    return Data;



}

void MPU6050_Init(void)
{
    MyI2C_Init();
    MPU6050_WritingReg(MPU6050_PWR_MGMT_1,0x01);//电源管理寄存器1,开启内部时钟
    MPU6050_WritingReg(MPU6050_PWR_MGMT_2,0x00);//电源管理寄存器2，取消待机模式
    MPU6050_WritingReg(MPU6050_SMPLRT_DIV,0x07);//分频寄存器，值越小越快
    MPU6050_WritingReg(MPU6050_CONFIG,0x00);//配置寄存器，后3位为配置滤波器
    MPU6050_WritingReg(MPU6050_GYRO_CONFIG,0x18);//陀螺仪配置
    MPU6050_WritingReg(MPU6050_ACCEL_CONFIG,0x18);//加速度计配置
}

void MPU6050_GetData(int16_t *AccX,int16_t *AccY,int16_t *AccZ,
                    int16_t *GYROX,int16_t *GYROY,int16_t *GYROZ)
{
    int16_t DataH,DataL;
    DataH=MPU6050_ReadingReg(MPU6050_ACCEL_XOUT_H);
    DataL=MPU6050_ReadingReg(MPU6050_ACCEL_XOUT_L);
    *AccX=(DataH<<8)|DataL;

    DataH=MPU6050_ReadingReg(MPU6050_ACCEL_YOUT_H);
    DataL=MPU6050_ReadingReg(MPU6050_ACCEL_YOUT_L);
    *AccY=(DataH<<8)|DataL;

    DataH=MPU6050_ReadingReg(MPU6050_ACCEL_ZOUT_H);
    DataL=MPU6050_ReadingReg(MPU6050_ACCEL_ZOUT_L);
    *AccZ=(DataH<<8)|DataL;

    DataH=MPU6050_ReadingReg(MPU6050_GYRO_XOUT_H);
    DataL=MPU6050_ReadingReg(MPU6050_GYRO_XOUT_L);
    *GYROX=(DataH<<8)|DataL;

    DataH=MPU6050_ReadingReg(MPU6050_GYRO_YOUT_H);
    DataL=MPU6050_ReadingReg(MPU6050_GYRO_YOUT_L);
    *GYROY=(DataH<<8)|DataL;

    DataH=MPU6050_ReadingReg(MPU6050_GYRO_ZOUT_H);
    DataL=MPU6050_ReadingReg(MPU6050_GYRO_ZOUT_L);
    *GYROZ=(DataH<<8)|DataL;

}

void Angle_XoZ(float *Angle)
{
    static int16_t Ax,Ay,Az,Gx,Gy,Gz;
    static  float AccAngle;
    static  float GyocAngle;
    static  float Alpnh=0.01;
        MPU6050_GetData(&Ax,&Ay,&Az,&Gx,&Gy,&Gz);
		Gy-=25.5;
		AccAngle=-atan2(Ax,Az)/3.14159*180;
		GyocAngle=*Angle+Gy/32768.0*2000*0.05;
		*Angle=Alpnh*AccAngle+(1-Alpnh)*GyocAngle;
        

}
