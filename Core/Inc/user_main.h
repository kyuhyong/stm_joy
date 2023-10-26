#ifndef __USER_MAIN_H__
#define __USER_MAIN_H__
#include "main.h"
#include "stm32f1xx_hal.h"


#define IDR(port,pin) (((struct bitAccessStruct*)(&((port)->IDR)))->pin)
#define bitset(byte,nbit)   ((byte) |=  (1<<(nbit)))
#define bitclear(byte,nbit) ((byte) &= ~(1<<(nbit)))
#define bitflip(byte,nbit)  ((byte) ^=  (1<<(nbit)))
#define bitcheck(byte,nbit) ((byte) &   (1<<(nbit)))

#define BLINK_FAST_MS		500
#define BLINK_SLOW_MS		1000

#define ADC_SAMPLE_NUM		10
#define ADC_IDLE0			3500
#define ADC_IDLE1			3600
#define ADC_IDLE2			3500

typedef enum
{
  inv_normal = 0,
  inverted = !inv_normal
} InvertState;

typedef enum
{
	led_off = 0,
	led_on = 1,
	led_blink_slow = 2,
	led_blink_fast = 3
}LED_State;

typedef enum
{
	act_idle = 0,
	act_standby = 1,
	act_activated = 2
}ActionState;

typedef struct {
	GPIO_TypeDef* port;
	uint16_t pin;
	uint16_t bit_order;
	InvertState invState;
}GPIO_PortType;	

typedef struct {
	GPIO_TypeDef* port;
	uint16_t pin;
	LED_State state;
	uint64_t last_update_ms;
	ActionState act;
}LED_PortType;

typedef struct {
	uint16_t tx_order;
	uint16_t buffer[ADC_SAMPLE_NUM];
	uint16_t avg_val;
	uint16_t threshold_idle;
	uint16_t gpio_bit;
}ADC_PortType;



void TIM4_ISR(void);
void USER_Config(void);
void USER_Loop(void);
#endif
