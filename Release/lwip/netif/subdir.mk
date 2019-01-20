################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/netif/bridgeif.c \
../lwip/netif/bridgeif_fdb.c \
../lwip/netif/ethernet.c \
../lwip/netif/ethernetif.c \
../lwip/netif/lowpan6.c \
../lwip/netif/lowpan6_ble.c \
../lwip/netif/lowpan6_common.c \
../lwip/netif/slipif.c \
../lwip/netif/zepif.c 

OBJS += \
./lwip/netif/bridgeif.o \
./lwip/netif/bridgeif_fdb.o \
./lwip/netif/ethernet.o \
./lwip/netif/ethernetif.o \
./lwip/netif/lowpan6.o \
./lwip/netif/lowpan6_ble.o \
./lwip/netif/lowpan6_common.o \
./lwip/netif/slipif.o \
./lwip/netif/zepif.o 

C_DEPS += \
./lwip/netif/bridgeif.d \
./lwip/netif/bridgeif_fdb.d \
./lwip/netif/ethernet.d \
./lwip/netif/ethernetif.d \
./lwip/netif/lowpan6.d \
./lwip/netif/lowpan6_ble.d \
./lwip/netif/lowpan6_common.d \
./lwip/netif/slipif.d \
./lwip/netif/zepif.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/netif/%.o: ../lwip/netif/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DNDEBUG -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/lpc17xx" -I"../freertos/include" -I"../freertos/port" -I"../app/include" -I"../lwip/include" -I"../lwip/include/arch" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


