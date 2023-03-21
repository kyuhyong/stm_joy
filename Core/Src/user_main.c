#include "user_main.h"
#include "usb_device.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim4;

uint8_t tx_buffer[64];			//Variable to store the output data 
uint8_t report_buffer[64];		//Variable to receive the report buffer 
uint8_t flag = 0;				//Variable to store the button flag 
uint8_t flag_rx = 0;			//Variable to store the reception flag 
 
//extern the USB handler 
extern USBD_HandleTypeDef hUsbDeviceFS; 

uint16_t adc_vals[8]={0,};
uint64_t timer_ms = 0;

void USER_Config(void)
{
	//To fill the buffer 
	for (uint8_t i=0; i<64; i++) 
	{ 
		tx_buffer[i] = i; 
	}
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_vals, 8);
  	HAL_TIM_Base_Start_IT(&htim4);
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
	if (flag==1) 
	{ 
	//USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, tx_buffer, 64); 
	flag = 0; 
	} 
}

void TIM4_ISR(void)
{
	timer_ms++;
	//HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
	case PB0_EXTI0_Pin:
		break;
	case PB1_EXTI1_Pin:
		break;
	case PB2_EXTI2_Pin:
		break;
	case PB3_EXTI3_Pin:
		break;
	case PB4_EXTI4_Pin:
		break;
	case PB5_EXTI5_Pin:
		break;
	case PB6_EXTI6_Pin:
		break;
	case PB7_EXTI7_Pin:
		break;
	case PB8_EXTI8_Pin:
		break;
	case PB9_EXTI9_Pin:
		break;
	}
}