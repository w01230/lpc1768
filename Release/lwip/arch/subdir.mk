################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/arch/freertos_lwip_mac.c \
../lwip/arch/phy_smsc87x0.c \
../lwip/arch/sys_arch.c 

OBJS += \
./lwip/arch/freertos_lwip_mac.o \
./lwip/arch/phy_smsc87x0.o \
./lwip/arch/sys_arch.o 

C_DEPS += \
./lwip/arch/freertos_lwip_mac.d \
./lwip/arch/phy_smsc87x0.d \
./lwip/arch/sys_arch.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/arch/%.o: ../lwip/arch/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DNDEBUG -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/lpc17xx" -I"../freertos/include" -I"../freertos/port" -I"../app/include" -I"../lwip/include" -I"../lwip/include/arch" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


