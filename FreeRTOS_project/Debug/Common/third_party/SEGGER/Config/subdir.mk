################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/anas/stm32/Common/third_party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c 

OBJS += \
./Common/third_party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o 

C_DEPS += \
./Common/third_party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
Common/third_party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o: /home/anas/stm32/Common/third_party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c Common/third_party/SEGGER/Config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/anas/stm32/Common/third_party/FreeRTOS/include -I/home/anas/stm32/Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F -I/home/anas/stm32/Common/third_party/SEGGER/Config -I/home/anas/stm32/Common/third_party/SEGGER/OS -I/home/anas/stm32/Common/third_party/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-third_party-2f-SEGGER-2f-Config

clean-Common-2f-third_party-2f-SEGGER-2f-Config:
	-$(RM) ./Common/third_party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.cyclo ./Common/third_party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d ./Common/third_party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o ./Common/third_party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.su

.PHONY: clean-Common-2f-third_party-2f-SEGGER-2f-Config

