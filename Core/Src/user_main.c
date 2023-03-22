#include "main.h"
#include "user_main.h"
#include "usb_device.h"
#include "usbd_customhid.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim4;

uint8_t tx_buffer[5];			//Variable to store the output data 
uint8_t report_buffer[64];		//Variable to receive the report buffer 
uint8_t flag = 0;				//Variable to store the button flag 
uint8_t flag_rx = 0;			//Variable to store the reception flag 
 
//extern the USB handler 
extern USBD_HandleTypeDef hUsbDeviceFS; 

uint16_t 	adc_vals[8]={0,};
uint16_t 	gpio_state_bits;
uint8_t		flg_1ms = 0;
uint64_t 	timer_ms = 0;
uint64_t	timer_next_500ms = 500;

void USER_Config(void)
{
	//To fill the buffer 
	for (uint8_t i=0; i<64; i++) 
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
		tx_buffer[0] = gpio_state_bits&0xFF;
		tmp = (int16_t)adc_vals[0] - 2047;
		tx_buffer[1] = tmp&0xFF;
		tx_buffer[2] = (tmp>>8)&0xFF;
		tmp = (int16_t)adc_vals[1] - 2047;
		tx_buffer[3] = tmp&0xFF;
		tx_buffer[4] = (tmp>>8)&0xFF;
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, tx_buffer, 5); 
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

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
	case PB0_EXTI0_Pin:
		if(HAL_GPIO_ReadPin(PB0_EXTI0_GPIO_Port, PB0_EXTI0_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, 0); 
		else bitclear(gpio_state_bits,0);
		break;
	case PB1_EXTI1_Pin:
		if(HAL_GPIO_ReadPin(PB1_EXTI1_GPIO_Port, PB1_EXTI1_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, 1); 
		else bitclear(gpio_state_bits,1);
		break;
	case PB2_EXTI2_Pin:
		if(HAL_GPIO_ReadPin(PB2_EXTI2_GPIO_Port, PB2_EXTI2_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, 2); 
		else bitclear(gpio_state_bits,2);
		break;
	case PB3_EXTI3_Pin:
		if(HAL_GPIO_ReadPin(PB3_EXTI3_GPIO_Port, PB3_EXTI3_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, 3); 
		else bitclear(gpio_state_bits,3);
		break;
	case PB4_EXTI4_Pin:
		if(HAL_GPIO_ReadPin(PB4_EXTI4_GPIO_Port, PB4_EXTI4_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, 4); 
		else bitclear(gpio_state_bits,4);
		break;
	case PB5_EXTI5_Pin:
		if(HAL_GPIO_ReadPin(PB5_EXTI5_GPIO_Port, PB5_EXTI5_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, 5); 
		else bitclear(gpio_state_bits,5);
		break;
	case PB6_EXTI6_Pin:
		if(HAL_GPIO_ReadPin(PB6_EXTI6_GPIO_Port, PB6_EXTI6_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, 6); 
		else bitclear(gpio_state_bits,6);
		break;
	case PB7_EXTI7_Pin:
		if(HAL_GPIO_ReadPin(PB7_EXTI7_GPIO_Port, PB7_EXTI7_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, 7); 
		else bitclear(gpio_state_bits,7);
		break;
	case PB8_EXTI8_Pin:
		if(HAL_GPIO_ReadPin(PB8_EXTI8_GPIO_Port, PB8_EXTI8_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, 8); 
		else bitclear(gpio_state_bits,8);
		break;
	case PB9_EXTI9_Pin:
		if(HAL_GPIO_ReadPin(PB0_EXTI0_GPIO_Port, PB0_EXTI0_Pin) == GPIO_PIN_RESET) bitset(gpio_state_bits, 9); 
		else bitclear(gpio_state_bits,9);
		break;
	}
}