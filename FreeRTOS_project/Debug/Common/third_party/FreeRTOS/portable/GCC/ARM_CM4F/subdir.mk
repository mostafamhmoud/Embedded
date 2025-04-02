################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/anas/stm32/Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F/port.o: /home/anas/stm32/Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F/port.c Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/anas/stm32/Common/third_party/FreeRTOS/include -I/home/anas/stm32/Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F -I/home/anas/stm32/Common/third_party/SEGGER/Config -I/home/anas/stm32/Common/third_party/SEGGER/OS -I/home/anas/stm32/Common/third_party/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-third_party-2f-FreeRTOS-2f-portable-2f-GCC-2f-ARM_CM4F

clean-Common-2f-third_party-2f-FreeRTOS-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F/port.cyclo ./Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F/port.d ./Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F/port.o ./Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F/port.su

.PHONY: clean-Common-2f-third_party-2f-FreeRTOS-2f-portable-2f-GCC-2f-ARM_CM4F

