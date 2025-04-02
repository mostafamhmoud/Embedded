################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/anas/stm32/Common/third_party/FreeRTOS/croutine.c \
/home/anas/stm32/Common/third_party/FreeRTOS/event_groups.c \
/home/anas/stm32/Common/third_party/FreeRTOS/list.c \
/home/anas/stm32/Common/third_party/FreeRTOS/queue.c \
/home/anas/stm32/Common/third_party/FreeRTOS/stream_buffer.c \
/home/anas/stm32/Common/third_party/FreeRTOS/tasks.c \
/home/anas/stm32/Common/third_party/FreeRTOS/timers.c 

OBJS += \
./Common/third_party/FreeRTOS/croutine.o \
./Common/third_party/FreeRTOS/event_groups.o \
./Common/third_party/FreeRTOS/list.o \
./Common/third_party/FreeRTOS/queue.o \
./Common/third_party/FreeRTOS/stream_buffer.o \
./Common/third_party/FreeRTOS/tasks.o \
./Common/third_party/FreeRTOS/timers.o 

C_DEPS += \
./Common/third_party/FreeRTOS/croutine.d \
./Common/third_party/FreeRTOS/event_groups.d \
./Common/third_party/FreeRTOS/list.d \
./Common/third_party/FreeRTOS/queue.d \
./Common/third_party/FreeRTOS/stream_buffer.d \
./Common/third_party/FreeRTOS/tasks.d \
./Common/third_party/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Common/third_party/FreeRTOS/croutine.o: /home/anas/stm32/Common/third_party/FreeRTOS/croutine.c Common/third_party/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/anas/stm32/Common/third_party/FreeRTOS/include -I/home/anas/stm32/Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F -I/home/anas/stm32/Common/third_party/SEGGER/Config -I/home/anas/stm32/Common/third_party/SEGGER/OS -I/home/anas/stm32/Common/third_party/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/third_party/FreeRTOS/event_groups.o: /home/anas/stm32/Common/third_party/FreeRTOS/event_groups.c Common/third_party/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/anas/stm32/Common/third_party/FreeRTOS/include -I/home/anas/stm32/Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F -I/home/anas/stm32/Common/third_party/SEGGER/Config -I/home/anas/stm32/Common/third_party/SEGGER/OS -I/home/anas/stm32/Common/third_party/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/third_party/FreeRTOS/list.o: /home/anas/stm32/Common/third_party/FreeRTOS/list.c Common/third_party/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/anas/stm32/Common/third_party/FreeRTOS/include -I/home/anas/stm32/Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F -I/home/anas/stm32/Common/third_party/SEGGER/Config -I/home/anas/stm32/Common/third_party/SEGGER/OS -I/home/anas/stm32/Common/third_party/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/third_party/FreeRTOS/queue.o: /home/anas/stm32/Common/third_party/FreeRTOS/queue.c Common/third_party/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/anas/stm32/Common/third_party/FreeRTOS/include -I/home/anas/stm32/Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F -I/home/anas/stm32/Common/third_party/SEGGER/Config -I/home/anas/stm32/Common/third_party/SEGGER/OS -I/home/anas/stm32/Common/third_party/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/third_party/FreeRTOS/stream_buffer.o: /home/anas/stm32/Common/third_party/FreeRTOS/stream_buffer.c Common/third_party/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/anas/stm32/Common/third_party/FreeRTOS/include -I/home/anas/stm32/Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F -I/home/anas/stm32/Common/third_party/SEGGER/Config -I/home/anas/stm32/Common/third_party/SEGGER/OS -I/home/anas/stm32/Common/third_party/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/third_party/FreeRTOS/tasks.o: /home/anas/stm32/Common/third_party/FreeRTOS/tasks.c Common/third_party/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/anas/stm32/Common/third_party/FreeRTOS/include -I/home/anas/stm32/Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F -I/home/anas/stm32/Common/third_party/SEGGER/Config -I/home/anas/stm32/Common/third_party/SEGGER/OS -I/home/anas/stm32/Common/third_party/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/third_party/FreeRTOS/timers.o: /home/anas/stm32/Common/third_party/FreeRTOS/timers.c Common/third_party/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/anas/stm32/Common/third_party/FreeRTOS/include -I/home/anas/stm32/Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F -I/home/anas/stm32/Common/third_party/SEGGER/Config -I/home/anas/stm32/Common/third_party/SEGGER/OS -I/home/anas/stm32/Common/third_party/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-third_party-2f-FreeRTOS

clean-Common-2f-third_party-2f-FreeRTOS:
	-$(RM) ./Common/third_party/FreeRTOS/croutine.cyclo ./Common/third_party/FreeRTOS/croutine.d ./Common/third_party/FreeRTOS/croutine.o ./Common/third_party/FreeRTOS/croutine.su ./Common/third_party/FreeRTOS/event_groups.cyclo ./Common/third_party/FreeRTOS/event_groups.d ./Common/third_party/FreeRTOS/event_groups.o ./Common/third_party/FreeRTOS/event_groups.su ./Common/third_party/FreeRTOS/list.cyclo ./Common/third_party/FreeRTOS/list.d ./Common/third_party/FreeRTOS/list.o ./Common/third_party/FreeRTOS/list.su ./Common/third_party/FreeRTOS/queue.cyclo ./Common/third_party/FreeRTOS/queue.d ./Common/third_party/FreeRTOS/queue.o ./Common/third_party/FreeRTOS/queue.su ./Common/third_party/FreeRTOS/stream_buffer.cyclo ./Common/third_party/FreeRTOS/stream_buffer.d ./Common/third_party/FreeRTOS/stream_buffer.o ./Common/third_party/FreeRTOS/stream_buffer.su ./Common/third_party/FreeRTOS/tasks.cyclo ./Common/third_party/FreeRTOS/tasks.d ./Common/third_party/FreeRTOS/tasks.o ./Common/third_party/FreeRTOS/tasks.su ./Common/third_party/FreeRTOS/timers.cyclo ./Common/third_party/FreeRTOS/timers.d ./Common/third_party/FreeRTOS/timers.o ./Common/third_party/FreeRTOS/timers.su

.PHONY: clean-Common-2f-third_party-2f-FreeRTOS

