################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/anas/stm32/Common/third_party/SEGGER/SEGGER/SEGGER_RTT.c \
/home/anas/stm32/Common/third_party/SEGGER/SEGGER/SEGGER_RTT_printf.c \
/home/anas/stm32/Common/third_party/SEGGER/SEGGER/SEGGER_SYSVIEW.c 

S_UPPER_SRCS += \
/home/anas/stm32/Common/third_party/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./Common/third_party/SEGGER/SEGGER/SEGGER_RTT.o \
./Common/third_party/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o \
./Common/third_party/SEGGER/SEGGER/SEGGER_RTT_printf.o \
./Common/third_party/SEGGER/SEGGER/SEGGER_SYSVIEW.o 

S_UPPER_DEPS += \
./Common/third_party/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./Common/third_party/SEGGER/SEGGER/SEGGER_RTT.d \
./Common/third_party/SEGGER/SEGGER/SEGGER_RTT_printf.d \
./Common/third_party/SEGGER/SEGGER/SEGGER_SYSVIEW.d 


# Each subdirectory must supply rules for building sources it contributes
Common/third_party/SEGGER/SEGGER/SEGGER_RTT.o: /home/anas/stm32/Common/third_party/SEGGER/SEGGER/SEGGER_RTT.c Common/third_party/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/anas/stm32/Common/third_party/FreeRTOS/include -I/home/anas/stm32/Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F -I/home/anas/stm32/Common/third_party/SEGGER/Config -I/home/anas/stm32/Common/third_party/SEGGER/OS -I/home/anas/stm32/Common/third_party/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/third_party/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o: /home/anas/stm32/Common/third_party/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.S Common/third_party/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I/home/anas/stm32/Common/third_party/SEGGER/Config -I/home/anas/stm32/Common/third_party/SEGGER/SEGGER -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
Common/third_party/SEGGER/SEGGER/SEGGER_RTT_printf.o: /home/anas/stm32/Common/third_party/SEGGER/SEGGER/SEGGER_RTT_printf.c Common/third_party/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/anas/stm32/Common/third_party/FreeRTOS/include -I/home/anas/stm32/Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F -I/home/anas/stm32/Common/third_party/SEGGER/Config -I/home/anas/stm32/Common/third_party/SEGGER/OS -I/home/anas/stm32/Common/third_party/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/third_party/SEGGER/SEGGER/SEGGER_SYSVIEW.o: /home/anas/stm32/Common/third_party/SEGGER/SEGGER/SEGGER_SYSVIEW.c Common/third_party/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/anas/stm32/Common/third_party/FreeRTOS/include -I/home/anas/stm32/Common/third_party/FreeRTOS/portable/GCC/ARM_CM4F -I/home/anas/stm32/Common/third_party/SEGGER/Config -I/home/anas/stm32/Common/third_party/SEGGER/OS -I/home/anas/stm32/Common/third_party/SEGGER/SEGGER -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-third_party-2f-SEGGER-2f-SEGGER

clean-Common-2f-third_party-2f-SEGGER-2f-SEGGER:
	-$(RM) ./Common/third_party/SEGGER/SEGGER/SEGGER_RTT.cyclo ./Common/third_party/SEGGER/SEGGER/SEGGER_RTT.d ./Common/third_party/SEGGER/SEGGER/SEGGER_RTT.o ./Common/third_party/SEGGER/SEGGER/SEGGER_RTT.su ./Common/third_party/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d ./Common/third_party/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o ./Common/third_party/SEGGER/SEGGER/SEGGER_RTT_printf.cyclo ./Common/third_party/SEGGER/SEGGER/SEGGER_RTT_printf.d ./Common/third_party/SEGGER/SEGGER/SEGGER_RTT_printf.o ./Common/third_party/SEGGER/SEGGER/SEGGER_RTT_printf.su ./Common/third_party/SEGGER/SEGGER/SEGGER_SYSVIEW.cyclo ./Common/third_party/SEGGER/SEGGER/SEGGER_SYSVIEW.d ./Common/third_party/SEGGER/SEGGER/SEGGER_SYSVIEW.o ./Common/third_party/SEGGER/SEGGER/SEGGER_SYSVIEW.su

.PHONY: clean-Common-2f-third_party-2f-SEGGER-2f-SEGGER

