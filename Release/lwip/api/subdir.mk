################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/api/api_lib.c \
../lwip/api/api_msg.c \
../lwip/api/err.c \
../lwip/api/if_api.c \
../lwip/api/netbuf.c \
../lwip/api/netdb.c \
../lwip/api/netifapi.c \
../lwip/api/sockets.c \
../lwip/api/tcpip.c 

OBJS += \
./lwip/api/api_lib.o \
./lwip/api/api_msg.o \
./lwip/api/err.o \
./lwip/api/if_api.o \
./lwip/api/netbuf.o \
./lwip/api/netdb.o \
./lwip/api/netifapi.o \
./lwip/api/sockets.o \
./lwip/api/tcpip.o 

C_DEPS += \
./lwip/api/api_lib.d \
./lwip/api/api_msg.d \
./lwip/api/err.d \
./lwip/api/if_api.d \
./lwip/api/netbuf.d \
./lwip/api/netdb.d \
./lwip/api/netifapi.d \
./lwip/api/sockets.d \
./lwip/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/api/%.o: ../lwip/api/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DNDEBUG -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/lpc17xx" -I"../freertos/include" -I"../freertos/port" -I"../app/include" -I"../lwip/include" -I"../lwip/include/arch" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


