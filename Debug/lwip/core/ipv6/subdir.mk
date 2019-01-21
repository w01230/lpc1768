################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/core/ipv6/dhcp6.c \
../lwip/core/ipv6/ethip6.c \
../lwip/core/ipv6/icmp6.c \
../lwip/core/ipv6/inet6.c \
../lwip/core/ipv6/ip6.c \
../lwip/core/ipv6/ip6_addr.c \
../lwip/core/ipv6/ip6_frag.c \
../lwip/core/ipv6/mld6.c \
../lwip/core/ipv6/nd6.c 

OBJS += \
./lwip/core/ipv6/dhcp6.o \
./lwip/core/ipv6/ethip6.o \
./lwip/core/ipv6/icmp6.o \
./lwip/core/ipv6/inet6.o \
./lwip/core/ipv6/ip6.o \
./lwip/core/ipv6/ip6_addr.o \
./lwip/core/ipv6/ip6_frag.o \
./lwip/core/ipv6/mld6.o \
./lwip/core/ipv6/nd6.o 

C_DEPS += \
./lwip/core/ipv6/dhcp6.d \
./lwip/core/ipv6/ethip6.d \
./lwip/core/ipv6/icmp6.d \
./lwip/core/ipv6/inet6.d \
./lwip/core/ipv6/ip6.d \
./lwip/core/ipv6/ip6_addr.d \
./lwip/core/ipv6/ip6_frag.d \
./lwip/core/ipv6/mld6.d \
./lwip/core/ipv6/nd6.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/core/ipv6/%.o: ../lwip/core/ipv6/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../system/include" -I"../system/include/cmsis" -I"../system/include/lpc17xx" -I"../freertos/include" -I"../freertos/port" -I"../app/include" -I"../lwip/include" -I"../lwip/include/arch" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


