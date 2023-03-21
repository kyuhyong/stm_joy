################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/my_workspace/my_fw/stm_joy/USB_DEVICE/App/usb_device.c \
D:/my_workspace/my_fw/stm_joy/USB_DEVICE/App/usbd_custom_hid_if.c \
D:/my_workspace/my_fw/stm_joy/USB_DEVICE/App/usbd_desc.c 

OBJS += \
./Application/User/USB_DEVICE/App/usb_device.o \
./Application/User/USB_DEVICE/App/usbd_custom_hid_if.o \
./Application/User/USB_DEVICE/App/usbd_desc.o 

C_DEPS += \
./Application/User/USB_DEVICE/App/usb_device.d \
./Application/User/USB_DEVICE/App/usbd_custom_hid_if.d \
./Application/User/USB_DEVICE/App/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/USB_DEVICE/App/usb_device.o: D:/my_workspace/my_fw/stm_joy/USB_DEVICE/App/usb_device.c Application/User/USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../USB_DEVICE/App -I../../USB_DEVICE/Target -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/USB_DEVICE/App/usbd_custom_hid_if.o: D:/my_workspace/my_fw/stm_joy/USB_DEVICE/App/usbd_custom_hid_if.c Application/User/USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../USB_DEVICE/App -I../../USB_DEVICE/Target -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/USB_DEVICE/App/usbd_desc.o: D:/my_workspace/my_fw/stm_joy/USB_DEVICE/App/usbd_desc.c Application/User/USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../USB_DEVICE/App -I../../USB_DEVICE/Target -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-User-2f-USB_DEVICE-2f-App

clean-Application-2f-User-2f-USB_DEVICE-2f-App:
	-$(RM) ./Application/User/USB_DEVICE/App/usb_device.cyclo ./Application/User/USB_DEVICE/App/usb_device.d ./Application/User/USB_DEVICE/App/usb_device.o ./Application/User/USB_DEVICE/App/usb_device.su ./Application/User/USB_DEVICE/App/usbd_custom_hid_if.cyclo ./Application/User/USB_DEVICE/App/usbd_custom_hid_if.d ./Application/User/USB_DEVICE/App/usbd_custom_hid_if.o ./Application/User/USB_DEVICE/App/usbd_custom_hid_if.su ./Application/User/USB_DEVICE/App/usbd_desc.cyclo ./Application/User/USB_DEVICE/App/usbd_desc.d ./Application/User/USB_DEVICE/App/usbd_desc.o ./Application/User/USB_DEVICE/App/usbd_desc.su

.PHONY: clean-Application-2f-User-2f-USB_DEVICE-2f-App

