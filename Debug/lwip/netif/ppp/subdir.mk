################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/netif/ppp/auth.c \
../lwip/netif/ppp/ccp.c \
../lwip/netif/ppp/chap-md5.c \
../lwip/netif/ppp/chap-new.c \
../lwip/netif/ppp/chap_ms.c \
../lwip/netif/ppp/demand.c \
../lwip/netif/ppp/eap.c \
../lwip/netif/ppp/ecp.c \
../lwip/netif/ppp/eui64.c \
../lwip/netif/ppp/fsm.c \
../lwip/netif/ppp/ipcp.c \
../lwip/netif/ppp/ipv6cp.c \
../lwip/netif/ppp/lcp.c \
../lwip/netif/ppp/magic.c \
../lwip/netif/ppp/mppe.c \
../lwip/netif/ppp/multilink.c \
../lwip/netif/ppp/ppp.c \
../lwip/netif/ppp/pppapi.c \
../lwip/netif/ppp/pppcrypt.c \
../lwip/netif/ppp/pppoe.c \
../lwip/netif/ppp/pppol2tp.c \
../lwip/netif/ppp/pppos.c \
../lwip/netif/ppp/upap.c \
../lwip/netif/ppp/utils.c \
../lwip/netif/ppp/vj.c 

OBJS += \
./lwip/netif/ppp/auth.o \
./lwip/netif/ppp/ccp.o \
./lwip/netif/ppp/chap-md5.o \
./lwip/netif/ppp/chap-new.o \
./lwip/netif/ppp/chap_ms.o \
./lwip/netif/ppp/demand.o \
./lwip/netif/ppp/eap.o \
./lwip/netif/ppp/ecp.o \
./lwip/netif/ppp/eui64.o \
./lwip/netif/ppp/fsm.o \
./lwip/netif/ppp/ipcp.o \
./lwip/netif/ppp/ipv6cp.o \
./lwip/netif/ppp/lcp.o \
./lwip/netif/ppp/magic.o \
./lwip/netif/ppp/mppe.o \
./lwip/netif/ppp/multilink.o \
./lwip/netif/ppp/ppp.o \
./lwip/netif/ppp/pppapi.o \
./lwip/netif/ppp/pppcrypt.o \
./lwip/netif/ppp/pppoe.o \
./lwip/netif/ppp/pppol2tp.o \
./lwip/netif/ppp/pppos.o \
./lwip/netif/ppp/upap.o \
./lwip/netif/ppp/utils.o \
./lwip/netif/ppp/vj.o 

C_DEPS += \
./lwip/netif/ppp/auth.d \
./lwip/netif/ppp/ccp.d \
./lwip/netif/ppp/chap-md5.d \
./lwip/netif/ppp/chap-new.d \
./lwip/netif/ppp/chap_ms.d \
./lwip/netif/ppp/demand.d \
./lwip/netif/ppp/eap.d \
./lwip/netif/ppp/ecp.d \
./lwip/netif/ppp/eui64.d \
./lwip/netif/ppp/fsm.d \
./lwip/netif/ppp/ipcp.d \
./lwip/netif/ppp/ipv6cp.d \
./lwip/netif/ppp/lcp.d \
./lwip/netif/ppp/magic.d \
./lwip/netif/ppp/mppe.d \
./lwip/netif/ppp/multilink.d \
./lwip/netif/ppp/ppp.d \
./lwip/netif/ppp/pppapi.d \
./lwip/netif/ppp/pppcrypt.d \
./lwip/netif/ppp/pppoe.d \
./lwip/netif/ppp/pppol2tp.d \
./lwip/netif/ppp/pppos.d \
./lwip/netif/ppp/upap.d \
./lwip/netif/ppp/utils.d \
./lwip/netif/ppp/vj.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/netif/ppp/%.o: ../lwip/netif/ppp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -I"../system/include" -I"../system/include/cmsis" -I"../system/include/lpc17xx" -I"../freertos/include" -I"../freertos/port" -I"../app/include" -I"../lwip/include" -I"../lwip/include/arch" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


