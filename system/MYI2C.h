#ifndef __MYI2C_H
#define __MYI2C_H

void MyI2C_Init(void);
void MYI2C_W_SCL(uint8_t t);
void MYI2C_W_SDA(uint8_t t);
uint8_t MYI2C_R_SDA(void);
void MyI2c_Start(void);
void MyI2c_Stop(void);
void MyI2c_SendByte(uint8_t Byte);
uint8_t MyI2c_ReciveByte(void);
void MyI2c_SendACK(uint8_t ACK);
uint8_t MyI2c_ReciveACK(void);

#endif
