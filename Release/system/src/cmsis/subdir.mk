################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/cmsis/system_lpc17xx.c \
../system/src/cmsis/vectors_lpc17xx.c 

OBJS += \
./system/src/cmsis/system_lpc17xx.o \
./system/src/cmsis/vectors_lpc17xx.o 

C_DEPS += \
./system/src/cmsis/system_lpc17xx.d \
./system/src/cmsis/vectors_lpc17xx.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/cmsis/%.o: ../system/src/cmsis/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DNDEBUG -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/lpc17xx" -I"../freertos/include" -I"../freertos/port" -I"../app/include" -I"../lwip/include" -I"../lwip/include/arch" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


