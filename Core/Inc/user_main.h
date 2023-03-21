#ifndef __USER_MAIN_H__
#define __USER_MAIN_H__
#include "main.h"
#include "stm32f1xx_hal.h"

void TIM4_ISR(void);
void USER_Config(void);
void USER_Loop(void);
#endif