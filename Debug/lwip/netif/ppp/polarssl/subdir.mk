################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/netif/ppp/polarssl/arc4.c \
../lwip/netif/ppp/polarssl/des.c \
../lwip/netif/ppp/polarssl/md4.c \
../lwip/netif/ppp/polarssl/md5.c \
../lwip/netif/ppp/polarssl/sha1.c 

OBJS += \
./lwip/netif/ppp/polarssl/arc4.o \
./lwip/netif/ppp/polarssl/des.o \
./lwip/netif/ppp/polarssl/md4.o \
./lwip/netif/ppp/polarssl/md5.o \
./lwip/netif/ppp/polarssl/sha1.o 

C_DEPS += \
./lwip/netif/ppp/polarssl/arc4.d \
./lwip/netif/ppp/polarssl/des.d \
./lwip/netif/ppp/polarssl/md4.d \
./lwip/netif/ppp/polarssl/md5.d \
./lwip/netif/ppp/polarssl/sha1.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/netif/ppp/polarssl/%.o: ../lwip/netif/ppp/polarssl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../system/include" -I"../system/include/cmsis" -I"../system/include/lpc17xx" -I"../freertos/include" -I"../freertos/port" -I"../app/include" -I"../lwip/include" -I"../lwip/include/arch" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


