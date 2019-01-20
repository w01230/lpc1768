################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/port/port.c 

OBJS += \
./freertos/port/port.o 

C_DEPS += \
./freertos/port/port.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/port/%.o: ../freertos/port/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -I"../system/include" -I"../system/include/cmsis" -I"../system/include/lpc17xx" -I"../freertos/include" -I"../freertos/port" -I"../app/include" -I"../lwip/include" -I"../lwip/include/arch" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


