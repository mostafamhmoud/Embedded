################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/source/croutine.c \
../FreeRTOS/source/event_groups.c \
../FreeRTOS/source/list.c \
../FreeRTOS/source/queue.c \
../FreeRTOS/source/stream_buffer.c \
../FreeRTOS/source/tasks.c \
../FreeRTOS/source/timers.c 

C_DEPS += \
./FreeRTOS/source/croutine.d \
./FreeRTOS/source/event_groups.d \
./FreeRTOS/source/list.d \
./FreeRTOS/source/queue.d \
./FreeRTOS/source/stream_buffer.d \
./FreeRTOS/source/tasks.d \
./FreeRTOS/source/timers.d 

OBJS += \
./FreeRTOS/source/croutine.o \
./FreeRTOS/source/event_groups.o \
./FreeRTOS/source/list.o \
./FreeRTOS/source/queue.o \
./FreeRTOS/source/stream_buffer.o \
./FreeRTOS/source/tasks.o \
./FreeRTOS/source/timers.o 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/source/%.o FreeRTOS/source/%.su FreeRTOS/source/%.cyclo: ../FreeRTOS/source/%.c FreeRTOS/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/anas/stm32/FreeRTOS_plus2/FreeRTOS/source/include" -I"/home/anas/stm32/FreeRTOS_plus2/FreeRTOS/source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRTOS-2f-source

clean-FreeRTOS-2f-source:
	-$(RM) ./FreeRTOS/source/croutine.cyclo ./FreeRTOS/source/croutine.d ./FreeRTOS/source/croutine.o ./FreeRTOS/source/croutine.su ./FreeRTOS/source/event_groups.cyclo ./FreeRTOS/source/event_groups.d ./FreeRTOS/source/event_groups.o ./FreeRTOS/source/event_groups.su ./FreeRTOS/source/list.cyclo ./FreeRTOS/source/list.d ./FreeRTOS/source/list.o ./FreeRTOS/source/list.su ./FreeRTOS/source/queue.cyclo ./FreeRTOS/source/queue.d ./FreeRTOS/source/queue.o ./FreeRTOS/source/queue.su ./FreeRTOS/source/stream_buffer.cyclo ./FreeRTOS/source/stream_buffer.d ./FreeRTOS/source/stream_buffer.o ./FreeRTOS/source/stream_buffer.su ./FreeRTOS/source/tasks.cyclo ./FreeRTOS/source/tasks.d ./FreeRTOS/source/tasks.o ./FreeRTOS/source/tasks.su ./FreeRTOS/source/timers.cyclo ./FreeRTOS/source/timers.d ./FreeRTOS/source/timers.o ./FreeRTOS/source/timers.su

.PHONY: clean-FreeRTOS-2f-source

