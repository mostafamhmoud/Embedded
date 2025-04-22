################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/source/portable/MemMang/heap_4.c 

C_DEPS += \
./FreeRTOS/source/portable/MemMang/heap_4.d 

OBJS += \
./FreeRTOS/source/portable/MemMang/heap_4.o 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/source/portable/MemMang/%.o FreeRTOS/source/portable/MemMang/%.su FreeRTOS/source/portable/MemMang/%.cyclo: ../FreeRTOS/source/portable/MemMang/%.c FreeRTOS/source/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/anas/stm32/FreeRTOS_plus2/FreeRTOS/source/include" -I"/home/anas/stm32/FreeRTOS_plus2/FreeRTOS/source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRTOS-2f-source-2f-portable-2f-MemMang

clean-FreeRTOS-2f-source-2f-portable-2f-MemMang:
	-$(RM) ./FreeRTOS/source/portable/MemMang/heap_4.cyclo ./FreeRTOS/source/portable/MemMang/heap_4.d ./FreeRTOS/source/portable/MemMang/heap_4.o ./FreeRTOS/source/portable/MemMang/heap_4.su

.PHONY: clean-FreeRTOS-2f-source-2f-portable-2f-MemMang

