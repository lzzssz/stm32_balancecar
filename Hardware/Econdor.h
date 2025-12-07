#ifndef __ECONDOR_H
#define __ECONDOR_H
void Econdor1_init(void);
int16_t Econdor1_CNT(void);
void Econdor2_init(void);
int16_t Econdor2_CNT(void);

void Econdor1_Catch_Speed( float T ,float *speed);

void Econdor2_Catch_Speed( float T ,float *speed);

#endif
