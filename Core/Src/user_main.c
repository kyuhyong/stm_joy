#include "main.h"
#include "user_main.h"
#include "usb_device.h"
#include "usbd_customhid.h"

#define TX_BUFFER_SIZE 		8
#define GPIO_PORT_NUM		6
#define LED_PORT_NUM		1
#define ADC_PORT_NUM		3

uint16_t 	gpio_state_bits = 0;

GPIO_PortType gpio_ports[GPIO_PORT_NUM] = {
	{PB3_IN_GPIO_Port, PB3_IN_Pin, 1, inv_normal},
	{PB4_IN_GPIO_Port, PB4_IN_Pin, 0, inv_normal},
	{PB5_IN_GPIO_Port, PB5_IN_Pin, 2, inv_normal},
	{PB6_IN_GPIO_Port, PB6_IN_Pin, 3, inv_normal},
	{PB7_IN_GPIO_Port, PB7_IN_Pin, 4, inv_normal},
	{PB8_IN_GPIO_Port, PB8_IN_Pin, 5, inv_normal}
	//{PB0_IN_GPIO_Port, PB0_IN_Pin, 9, inverted}
};

LED_PortType led_ports[LED_PORT_NUM] = {
		{PB1_OUT_GPIO_Port, PB1_OUT_Pin, led_off, act_idle}
};

ADC_PortType adc_ports[ADC_PORT_NUM] = {
		{ 2, {0,}, 0, ADC_IDLE0, 6},
		{ 4, {0,}, 0, ADC_IDLE1, 7},
		{ 6, {0,}, 0, ADC_IDLE2, 8}
};

uint16_t 	adc_vals[8]={0,};

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim4;

uint8_t tx_buffer[TX_BUFFER_SIZE];		// Variable to store the output data
uint8_t report_buffer[64];				// Variable to receive the report buffer
uint8_t flag = 0;						// Variable to store the button flag
uint8_t flag_rx = 0;					// Variable to store the reception flag
 
// extern the USB handler
extern USBD_HandleTypeDef hUsbDeviceFS; 



uint8_t		flg_1ms = 0;
uint64_t 	timer_ms = 0;
uint64_t	timer_next_500ms = 500;
GPIO_PinState	pinState_prev = GPIO_PIN_RESET;
uint16_t	pinState_cnt = 0;

void _read_gpio(void);
uint16_t _adc_avg(uint16_t *buffer, uint16_t sample, int buffer_size);
void _update_led_ms(void);
void _update_adc(void);
void _update_action(void);

void _read_gpio(void) {
	for(int i = 0; i<GPIO_PORT_NUM; i++) {
		if(HAL_GPIO_ReadPin(gpio_ports[i].port, gpio_ports[i].pin) == GPIO_PIN_RESET) {
			if(gpio_ports[i].invState == inv_normal) {
				bitset(gpio_state_bits, gpio_ports[i].bit_order);
			} else {
				bitclear(gpio_state_bits, gpio_ports[i].bit_order);
			}
		} else {
			if(gpio_ports[i].invState == inv_normal) {
				bitclear(gpio_state_bits, gpio_ports[i].bit_order);
			} else {
				bitset(gpio_state_bits, gpio_ports[i].bit_order);
			}
		}
	}
}

void _update_led_ms(void) {
	for(int i = 0; i<LED_PORT_NUM; i++) {
		switch(led_ports[i].state) {
		case led_off:
			HAL_GPIO_WritePin(led_ports[i].port, led_ports[i].pin, GPIO_PIN_RESET);
			break;
		case led_on:
			HAL_GPIO_WritePin(led_ports[i].port, led_ports[i].pin, GPIO_PIN_SET);
			break;
		case led_blink_slow:
			if((timer_ms - led_ports[i].last_update_ms) > BLINK_SLOW_MS) {
				HAL_GPIO_TogglePin(led_ports[i].port, led_ports[i].pin);
				led_ports[i].last_update_ms = timer_ms;
			}
			break;
		case led_blink_fast:
			if((timer_ms - led_ports[i].last_update_ms) > BLINK_FAST_MS) {
				HAL_GPIO_TogglePin(led_ports[i].port, led_ports[i].pin);
				led_ports[i].last_update_ms = timer_ms;
			}
			break;
		}
	}
}

uint16_t _adc_avg(uint16_t *buffer, uint16_t sample, int buffer_size)
{
	uint32_t total = 0;
	for(int i = 0; i<buffer_size-1; i++) {
		buffer[i] = buffer[i+1];
		total+=buffer[i];
	}
	//Update new value
	buffer[buffer_size-1] = sample;
	total+=sample;
	return (uint16_t)(total/buffer_size);
}

void _update_adc(void)
{
	for(int i=0; i<ADC_PORT_NUM; i++) {
		adc_ports[i].avg_val = _adc_avg(adc_ports[i].buffer, adc_vals[i], ADC_SAMPLE_NUM);
		if(adc_ports[i].avg_val > adc_ports[i].threshold_idle) {
			bitset(gpio_state_bits, adc_ports[i].gpio_bit);
		} else {
			bitclear(gpio_state_bits, adc_ports[i].gpio_bit);
		}
	}
}
void _update_action(void)
{
	GPIO_PinState pinState = HAL_GPIO_ReadPin(PB0_IN_GPIO_Port, PB0_IN_Pin);
	if(adc_ports[0].avg_val > adc_ports[0].threshold_idle) {
		switch(led_ports[0].act) {
		case act_idle:
			led_ports[0].act = act_standby;
			led_ports[0].state = led_blink_fast;
			break;
		case act_standby:
			if(pinState_prev == GPIO_PIN_SET && pinState == GPIO_PIN_RESET) {	//On falling edge detected
				led_ports[0].act = act_activated;
				led_ports[0].state = led_on;
				bitclear(gpio_state_bits, 9);
			} else {
				if(pinState == GPIO_PIN_SET) {
					bitset(gpio_state_bits, 9);
				} else {
					bitclear(gpio_state_bits, 9);
				}
			}
			break;
		case act_activated:
			if(pinState_prev == GPIO_PIN_SET && pinState == GPIO_PIN_RESET) {	//On falling edge detected
				led_ports[0].act = act_standby;
				led_ports[0].state = led_blink_fast;
				bitclear(gpio_state_bits, 9);
			} else {
				if(pinState == GPIO_PIN_SET) {
					bitset(gpio_state_bits, 9);
				} else {
					bitclear(gpio_state_bits, 9);
				}
			}
			break;
		}
	} else {
		if(led_ports[0].act == act_standby) {
			led_ports[0].act = act_idle;
			led_ports[0].state = led_off;
			bitclear(gpio_state_bits, 9);
		}
	}
	pinState_prev = pinState;
}


void USER_Config(void)
{
	//To fill the buffer 
	for (uint8_t i=0; i<TX_BUFFER_SIZE; i++)
	{ 
		tx_buffer[i] = i; 
	}
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_vals, 8);
  	HAL_TIM_Base_Start_IT(&htim4);
	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
	led_ports[0].state = led_off;
}

void USER_Loop(void)
{
	if (flag_rx == 1) { 
		//Check if the first byte of the report buffer equals 1 
		if (report_buffer[0] == 1) { 
			//Turn the user LED on 
			//HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, SET); 
		} 
		//Check if the first byte of the report buffer equals 2 
		else if (report_buffer[0] == 2) 
		{ 
			//Turn the user LED off 
			//HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, RESET); 
		} 
		flag_rx = 0; 
	} 
	//To send the output data when the button is pressed 
	if (flg_1ms==1) 
	{
		int16_t tmp;
		_read_gpio();
		_update_adc();
		_update_action();
		tx_buffer[0] = gpio_state_bits&0xFF;
		tx_buffer[1] = (gpio_state_bits>>8)&0xFF;
		tmp = adc_ports[0].avg_val;
		tx_buffer[2] = tmp&0xFF;
		tx_buffer[3] = (tmp>>8)&0xFF;
		tmp = adc_ports[1].avg_val;
		tx_buffer[4] = tmp&0xFF;
		tx_buffer[5] = (tmp>>8)&0xFF;
		tmp = adc_ports[2].avg_val;
		tx_buffer[6] = tmp&0xFF;
		tx_buffer[7] = (tmp>>8)&0xFF;
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, tx_buffer, TX_BUFFER_SIZE); 
		_update_led_ms();
		flg_1ms = 0; 
	}
	if (timer_ms > timer_next_500ms) {
		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
		timer_next_500ms = timer_ms + 500;
	}
}

void TIM4_ISR(void)
{
	timer_ms++;
	flg_1ms = 1;
}
