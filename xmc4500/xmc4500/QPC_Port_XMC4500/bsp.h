
#ifndef BSP_H
#define BSP_H

#include "Serial.h"
#include "LED.h"
//#include "ADC.h"

void bsp_Init(void);
void bsp_ButtonInit(void);
unsigned int bps_checkButton(unsigned int num);

void _sys_exit(int rtc); 

#endif

