################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/core/altcp.c \
../lwip/core/altcp_alloc.c \
../lwip/core/altcp_tcp.c \
../lwip/core/def.c \
../lwip/core/dns.c \
../lwip/core/inet_chksum.c \
../lwip/core/init.c \
../lwip/core/ip.c \
../lwip/core/mem.c \
../lwip/core/memp.c \
../lwip/core/netif.c \
../lwip/core/pbuf.c \
../lwip/core/raw.c \
../lwip/core/stats.c \
../lwip/core/sys.c \
../lwip/core/tcp.c \
../lwip/core/tcp_in.c \
../lwip/core/tcp_out.c \
../lwip/core/timeouts.c \
../lwip/core/udp.c 

OBJS += \
./lwip/core/altcp.o \
./lwip/core/altcp_alloc.o \
./lwip/core/altcp_tcp.o \
./lwip/core/def.o \
./lwip/core/dns.o \
./lwip/core/inet_chksum.o \
./lwip/core/init.o \
./lwip/core/ip.o \
./lwip/core/mem.o \
./lwip/core/memp.o \
./lwip/core/netif.o \
./lwip/core/pbuf.o \
./lwip/core/raw.o \
./lwip/core/stats.o \
./lwip/core/sys.o \
./lwip/core/tcp.o \
./lwip/core/tcp_in.o \
./lwip/core/tcp_out.o \
./lwip/core/timeouts.o \
./lwip/core/udp.o 

C_DEPS += \
./lwip/core/altcp.d \
./lwip/core/altcp_alloc.d \
./lwip/core/altcp_tcp.d \
./lwip/core/def.d \
./lwip/core/dns.d \
./lwip/core/inet_chksum.d \
./lwip/core/init.d \
./lwip/core/ip.d \
./lwip/core/mem.d \
./lwip/core/memp.d \
./lwip/core/netif.d \
./lwip/core/pbuf.d \
./lwip/core/raw.d \
./lwip/core/stats.d \
./lwip/core/sys.d \
./lwip/core/tcp.d \
./lwip/core/tcp_in.d \
./lwip/core/tcp_out.d \
./lwip/core/timeouts.d \
./lwip/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/core/%.o: ../lwip/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../system/include" -I"../system/include/cmsis" -I"../system/include/lpc17xx" -I"../freertos/include" -I"../freertos/port" -I"../app/include" -I"../lwip/include" -I"../lwip/include/arch" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


