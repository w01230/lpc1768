################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/core/ipv4/autoip.c \
../lwip/core/ipv4/dhcp.c \
../lwip/core/ipv4/etharp.c \
../lwip/core/ipv4/icmp.c \
../lwip/core/ipv4/igmp.c \
../lwip/core/ipv4/ip4.c \
../lwip/core/ipv4/ip4_addr.c \
../lwip/core/ipv4/ip4_frag.c 

OBJS += \
./lwip/core/ipv4/autoip.o \
./lwip/core/ipv4/dhcp.o \
./lwip/core/ipv4/etharp.o \
./lwip/core/ipv4/icmp.o \
./lwip/core/ipv4/igmp.o \
./lwip/core/ipv4/ip4.o \
./lwip/core/ipv4/ip4_addr.o \
./lwip/core/ipv4/ip4_frag.o 

C_DEPS += \
./lwip/core/ipv4/autoip.d \
./lwip/core/ipv4/dhcp.d \
./lwip/core/ipv4/etharp.d \
./lwip/core/ipv4/icmp.d \
./lwip/core/ipv4/igmp.d \
./lwip/core/ipv4/ip4.d \
./lwip/core/ipv4/ip4_addr.d \
./lwip/core/ipv4/ip4_frag.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/core/ipv4/%.o: ../lwip/core/ipv4/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DNDEBUG -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/lpc17xx" -I"../freertos/include" -I"../freertos/port" -I"../app/include" -I"../lwip/include" -I"../lwip/include/arch" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


