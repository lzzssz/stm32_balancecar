#ifndef __PID_SERIAL_H
#define __PID_SERIAL_H
#include    <stdio.h>
#include "stm32f10x.h"
extern char Pid_Serial_RxPacket[100];
typedef enum
{
    Target=1,
    Kp=2,
    Ki=3,
    Kd=4,

}
pid;
void Pid_Serial_Init(void);
uint8_t Pid_Serial_GetRxFlag(void);
void Pid_Tset(float*target,float*kp,float*ki,float*kd);
void tranfer_4(float *num);
void tranfer_5(float *num);

/*

name:shi山+简单粗暴分别调串口调Pid4个参

前置文件：
project目录内需含有江协的串口代码，仅需Init,如其内部有串口中断请注释

附文档使用说明：

    1.本代码仅适用于调整target、Kp、Ki、Kd四个值；
    2.本代码使用Usart1,连接方式为  Tx——>PA10 Rx——>PA9
    3.对串口调参程序有一定规则限制
    (1)对于调整Target,对应格式为：！=+(符号，务必有)xxx.xx(后按回车)
    (2)对于调整pid三项来说，对应格式为：@/#/￥(三选一，分别对应p、i、d)=+(符号，务必有)xx.xx(后按回车，简易按回车)
    (3)对于x来说，无用时写0，不要不写！！！！！！！！！
    (4)在调用函数时放入地址即可取数
    4.务必按照规则调整，在特殊符号和=间可添加任意英文字母，注意发送时输入的字应均为英文输入法否则将调参失败
    5.发送时选用文本模式

*/
#endif
