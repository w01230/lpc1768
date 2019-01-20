################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/apps/altcp_tls/altcp_tls_mbedtls.c \
../lwip/apps/altcp_tls/altcp_tls_mbedtls_mem.c 

OBJS += \
./lwip/apps/altcp_tls/altcp_tls_mbedtls.o \
./lwip/apps/altcp_tls/altcp_tls_mbedtls_mem.o 

C_DEPS += \
./lwip/apps/altcp_tls/altcp_tls_mbedtls.d \
./lwip/apps/altcp_tls/altcp_tls_mbedtls_mem.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/apps/altcp_tls/%.o: ../lwip/apps/altcp_tls/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DNDEBUG -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/lpc17xx" -I"../freertos/include" -I"../freertos/port" -I"../app/include" -I"../lwip/include" -I"../lwip/include/arch" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


