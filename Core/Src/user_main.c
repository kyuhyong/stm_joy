#include "main.h"
#include "user_main.h"
#include "usb_device.h"
#include "usbd_customhid.h"

#define TX_BUFFER_SIZE 		7			// Exact number of bytes to be reported
#define GPIO_PORT_NUM		18			// Number of GPIO ports to be used

uint16_t 	gpio_state_bits[2] = {0,};	// Stores gpio state bits as 16bit data

const GPIO_PortType gpio_ports[GPIO_PORT_NUM] = {	// { Port Address, Pin #, Bit assignment }
	{S1_GPIO_Port, 	S1_Pin, 	0},
	{S2_GPIO_Port, 	S2_Pin, 	1},
	{S3_GPIO_Port, 	S3_Pin, 	2},
	{S4_GPIO_Port, 	S4_Pin, 	3},
	{S5_GPIO_Port, 	S5_Pin, 	4},
	{S6_GPIO_Port, 	S6_Pin, 	5},
	{S7_GPIO_Port, 	S7_Pin, 	6},
	{S8_GPIO_Port, 	S8_Pin, 	7},
	{S9_GPIO_Port, 	S9_Pin, 	8},
	{S10_GPIO_Port, S10_Pin, 	9},
	{S11_GPIO_Port, S11_Pin, 	10},
	{S12_GPIO_Port, S12_Pin, 	11},
	{S13_GPIO_Port, S13_Pin, 	12},
	{S14_GPIO_Port, S14_Pin, 	13},
	{S15_GPIO_Port, S15_Pin, 	14},
	{S16_GPIO_Port, S16_Pin, 	15},
	{S17_GPIO_Port, S17_Pin, 	16},
	{S18_GPIO_Port, S18_Pin, 	17}
};

#define ADC_CHANNEL_NUM		2			// Number of ADC channels to be reported
#define ADC_SAMPLE_NUM		10			//
#define ADC_IDLE0			3500
#define ADC_IDLE1			3600
#define ADC_IDLE2			3500

uint16_t 	adc_vals[8]={0,};
uint16_t	adc_buffer[ADC_CHANNEL_NUM][ADC_SAMPLE_NUM] = {{0,},};
uint16_t	adc_avgs[ADC_CHANNEL_NUM]={0,};

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim4;

uint8_t tx_buffer[TX_BUFFER_SIZE];		//Variable to store the output data
uint8_t report_buffer[64];				//Variable to receive the report buffer
uint8_t flag = 0;						//Variable to store the button flag
uint8_t flag_rx = 0;					//Variable to store the reception flag
 
//extern the USB handler 
extern USBD_HandleTypeDef hUsbDeviceFS; 



uint8_t		flg_1ms = 0;
uint64_t 	timer_ms = 0;
uint64_t	timer_next_500ms = 500;

void _read_gpio(void);
uint16_t _adc_avg(uint16_t *buffer, uint16_t sample, int buffer_size);

void _read_gpio(void) {
	for(int i = 0; i<GPIO_PORT_NUM; i++) {
		if(HAL_GPIO_ReadPin(gpio_ports[i].port, gpio_ports[i].pin) == GPIO_PIN_RESET) {
			if(gpio_ports[i].bit_order < 16) {
				bitset(gpio_state_bits[0], gpio_ports[i].bit_order);
			} else {
				bitset(gpio_state_bits[1], gpio_ports[i].bit_order - 16);
			}
		} else {
			if(gpio_ports[i].bit_order < 16) {
				bitclear(gpio_state_bits[0], gpio_ports[i].bit_order);
			} else {
				bitclear(gpio_state_bits[1], gpio_ports[i].bit_order - 16);
			}
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
		// Update gpio state
		_read_gpio();
		//Update adc channels
		adc_avgs[0] = _adc_avg(adc_buffer[0], adc_vals[0], ADC_SAMPLE_NUM);
		adc_avgs[1] = _adc_avg(adc_buffer[1], adc_vals[1], ADC_SAMPLE_NUM);
		//adc_avgs[2] = _adc_avg(adc_buffer[2], adc_vals[2], ADC_SAMPLE_NUM);
		//if(adc_avgs[0] > ADC_IDLE0) bitset(gpio_state_bits, 6); else bitclear(gpio_state_bits, 6);
		//if(adc_avgs[1] > ADC_IDLE1) bitset(gpio_state_bits, 7); else bitclear(gpio_state_bits, 7);
		//if(adc_avgs[2] > ADC_IDLE2) bitset(gpio_state_bits, 8); else bitclear(gpio_state_bits, 8);
		
		tx_buffer[0] = gpio_state_bits[0]&0xFF;
		tx_buffer[1] = (gpio_state_bits[0]>>8)&0xFF;
		tx_buffer[2] = gpio_state_bits[1]&0xFF;
		tmp = adc_avgs[0];
		tx_buffer[3] = tmp&0xFF;
		tx_buffer[4] = (tmp>>8)&0xFF;
		tmp = adc_avgs[1];
		tx_buffer[5] = tmp&0xFF;
		tx_buffer[6] = (tmp>>8)&0xFF;
		//tmp = adc_avgs[2];
		//tx_buffer[6] = tmp&0xFF;
		//tx_buffer[7] = (tmp>>8)&0xFF;
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, tx_buffer, TX_BUFFER_SIZE); 
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
/* EXTI Interrupt callback NOT USED
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
	case PB0_EXTI0_Pin:
		//if(HAL_GPIO_ReadPin(PB0_EXTI0_GPIO_Port, PB0_EXTI0_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, 0); 
		//else bitclear(gpio_state_bits,0);
		break;
	case PB1_EXTI1_Pin:
		//if(HAL_GPIO_ReadPin(PB1_EXTI1_GPIO_Port, PB1_EXTI1_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, 1); 
		//else bitclear(gpio_state_bits,1);
		break;
	case PB2_EXTI2_Pin:
		//if(HAL_GPIO_ReadPin(PB2_EXTI2_GPIO_Port, PB2_EXTI2_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, 2); 
		//else bitclear(gpio_state_bits,2);
		break;
	case PB3_EXTI3_Pin:
		if(HAL_GPIO_ReadPin(PB3_EXTI3_GPIO_Port, PB3_EXTI3_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, gpio_ports[0].bit_order); 
		else bitclear(gpio_state_bits,gpio_ports[0].bit_order);
		break;
	case PB4_EXTI4_Pin:
		if(HAL_GPIO_ReadPin(PB4_EXTI4_GPIO_Port, PB4_EXTI4_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, gpio_ports[1].bit_order); 
		else bitclear(gpio_state_bits,gpio_ports[1].bit_order);
		break;
	case PB5_EXTI5_Pin:
		if(HAL_GPIO_ReadPin(PB5_EXTI5_GPIO_Port, PB5_EXTI5_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, gpio_ports[2].bit_order); 
		else bitclear(gpio_state_bits,gpio_ports[2].bit_order);
		break;
	case PB6_EXTI6_Pin:
		if(HAL_GPIO_ReadPin(PB6_EXTI6_GPIO_Port, PB6_EXTI6_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, gpio_ports[3].bit_order); 
		else bitclear(gpio_state_bits,gpio_ports[3].bit_order);
		break;
	case PB7_EXTI7_Pin:
		if(HAL_GPIO_ReadPin(PB7_EXTI7_GPIO_Port, PB7_EXTI7_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, gpio_ports[4].bit_order); 
		else bitclear(gpio_state_bits,gpio_ports[4].bit_order);
		break;
	case PB8_EXTI8_Pin:
		if(HAL_GPIO_ReadPin(PB8_EXTI8_GPIO_Port, PB8_EXTI8_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, gpio_ports[5].bit_order); 
		else bitclear(gpio_state_bits,gpio_ports[5].bit_order);
		break;
	case PB9_EXTI9_Pin:
		//if(HAL_GPIO_ReadPin(PB0_EXTI0_GPIO_Port, PB0_EXTI0_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, 6); 
		//else bitclear(gpio_state_bits,6);
		break;
	}
}
*/
