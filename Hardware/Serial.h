#ifndef __SERIAL_H
#define __SERIAL_H
#include<stdio.h>
#include "stm32f10x.h"


extern uint8_t Serial_TxPacket[4];
extern char Serial_RxPacket[100];

void Serial_Init(void);
void Serial_Send(uint8_t byte);
void Serial_Send_array(uint8_t *arrary,uint16_t Length);
void Serial_send_string(char *string);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format,...);
uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);
void Serial_SendPacket(void);
#endif
