#ifndef __USER_MAIN_H__
#define __USER_MAIN_H__
#include "main.h"
#include "stm32f1xx_hal.h"


#define IDR(port,pin) (((struct bitAccessStruct*)(&((port)->IDR)))->pin)
#define bitset(byte,nbit)   ((byte) |=  (1<<(nbit)))
#define bitclear(byte,nbit) ((byte) &= ~(1<<(nbit)))
#define bitflip(byte,nbit)  ((byte) ^=  (1<<(nbit)))
#define bitcheck(byte,nbit) ((byte) &   (1<<(nbit)))

void TIM4_ISR(void);
void USER_Config(void);
void USER_Loop(void);
#endif