#ifndef __MPU6050_H
#define __MPU6050_H
void MPU6050_WritingReg(uint8_t RegAddress,uint8_t Data);
uint8_t MPU6050_ReadingReg(uint8_t RegAddress);
void MPU6050_ReadRegs(uint8_t RegAddress, uint8_t *DataArray, uint8_t Count);
void MPU6050_Init(void);
void MPU6050_GetData(int16_t *AccX,int16_t *AccY,int16_t *AccZ,
                    int16_t *GYROX,int16_t *GYROY,int16_t *GYROZ);
void Angle_XoZ(float *Angle);
#endif
