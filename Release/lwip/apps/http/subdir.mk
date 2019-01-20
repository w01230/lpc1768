################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/apps/http/altcp_proxyconnect.c \
../lwip/apps/http/fs.c \
../lwip/apps/http/http_client.c \
../lwip/apps/http/httpd.c 

OBJS += \
./lwip/apps/http/altcp_proxyconnect.o \
./lwip/apps/http/fs.o \
./lwip/apps/http/http_client.o \
./lwip/apps/http/httpd.o 

C_DEPS += \
./lwip/apps/http/altcp_proxyconnect.d \
./lwip/apps/http/fs.d \
./lwip/apps/http/http_client.d \
./lwip/apps/http/httpd.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/apps/http/%.o: ../lwip/apps/http/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DNDEBUG -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/lpc17xx" -I"../freertos/include" -I"../freertos/port" -I"../app/include" -I"../lwip/include" -I"../lwip/include/arch" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


