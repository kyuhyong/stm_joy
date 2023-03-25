#ifndef __USER_MAIN_H__
#define __USER_MAIN_H__
#include "main.h"
#include "stm32f1xx_hal.h"


#define IDR(port,pin) (((struct bitAccessStruct*)(&((port)->IDR)))->pin)
#define bitset(byte,nbit)   ((byte) |=  (1<<(nbit)))
#define bitclear(byte,nbit) ((byte) &= ~(1<<(nbit)))
#define bitflip(byte,nbit)  ((byte) ^=  (1<<(nbit)))
#define bitcheck(byte,nbit) ((byte) &   (1<<(nbit)))

typedef struct {
	GPIO_TypeDef* port;
	uint16_t pin;
	uint16_t bit_order;
}GPIO_PortType;	

void TIM4_ISR(void);
void USER_Config(void);
void USER_Loop(void);
#endif