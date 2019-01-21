################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/lpc17xx/debug_frmwrk.c \
../system/src/lpc17xx/lpc17xx_adc.c \
../system/src/lpc17xx/lpc17xx_can.c \
../system/src/lpc17xx/lpc17xx_clkpwr.c \
../system/src/lpc17xx/lpc17xx_dac.c \
../system/src/lpc17xx/lpc17xx_emac.c \
../system/src/lpc17xx/lpc17xx_exti.c \
../system/src/lpc17xx/lpc17xx_gpdma.c \
../system/src/lpc17xx/lpc17xx_gpio.c \
../system/src/lpc17xx/lpc17xx_i2c.c \
../system/src/lpc17xx/lpc17xx_i2s.c \
../system/src/lpc17xx/lpc17xx_iap.c \
../system/src/lpc17xx/lpc17xx_libcfg_default.c \
../system/src/lpc17xx/lpc17xx_mcpwm.c \
../system/src/lpc17xx/lpc17xx_nvic.c \
../system/src/lpc17xx/lpc17xx_pinsel.c \
../system/src/lpc17xx/lpc17xx_pwm.c \
../system/src/lpc17xx/lpc17xx_qei.c \
../system/src/lpc17xx/lpc17xx_rit.c \
../system/src/lpc17xx/lpc17xx_rtc.c \
../system/src/lpc17xx/lpc17xx_spi.c \
../system/src/lpc17xx/lpc17xx_ssp.c \
../system/src/lpc17xx/lpc17xx_systick.c \
../system/src/lpc17xx/lpc17xx_timer.c \
../system/src/lpc17xx/lpc17xx_uart.c \
../system/src/lpc17xx/lpc17xx_wdt.c 

OBJS += \
./system/src/lpc17xx/debug_frmwrk.o \
./system/src/lpc17xx/lpc17xx_adc.o \
./system/src/lpc17xx/lpc17xx_can.o \
./system/src/lpc17xx/lpc17xx_clkpwr.o \
./system/src/lpc17xx/lpc17xx_dac.o \
./system/src/lpc17xx/lpc17xx_emac.o \
./system/src/lpc17xx/lpc17xx_exti.o \
./system/src/lpc17xx/lpc17xx_gpdma.o \
./system/src/lpc17xx/lpc17xx_gpio.o \
./system/src/lpc17xx/lpc17xx_i2c.o \
./system/src/lpc17xx/lpc17xx_i2s.o \
./system/src/lpc17xx/lpc17xx_iap.o \
./system/src/lpc17xx/lpc17xx_libcfg_default.o \
./system/src/lpc17xx/lpc17xx_mcpwm.o \
./system/src/lpc17xx/lpc17xx_nvic.o \
./system/src/lpc17xx/lpc17xx_pinsel.o \
./system/src/lpc17xx/lpc17xx_pwm.o \
./system/src/lpc17xx/lpc17xx_qei.o \
./system/src/lpc17xx/lpc17xx_rit.o \
./system/src/lpc17xx/lpc17xx_rtc.o \
./system/src/lpc17xx/lpc17xx_spi.o \
./system/src/lpc17xx/lpc17xx_ssp.o \
./system/src/lpc17xx/lpc17xx_systick.o \
./system/src/lpc17xx/lpc17xx_timer.o \
./system/src/lpc17xx/lpc17xx_uart.o \
./system/src/lpc17xx/lpc17xx_wdt.o 

C_DEPS += \
./system/src/lpc17xx/debug_frmwrk.d \
./system/src/lpc17xx/lpc17xx_adc.d \
./system/src/lpc17xx/lpc17xx_can.d \
./system/src/lpc17xx/lpc17xx_clkpwr.d \
./system/src/lpc17xx/lpc17xx_dac.d \
./system/src/lpc17xx/lpc17xx_emac.d \
./system/src/lpc17xx/lpc17xx_exti.d \
./system/src/lpc17xx/lpc17xx_gpdma.d \
./system/src/lpc17xx/lpc17xx_gpio.d \
./system/src/lpc17xx/lpc17xx_i2c.d \
./system/src/lpc17xx/lpc17xx_i2s.d \
./system/src/lpc17xx/lpc17xx_iap.d \
./system/src/lpc17xx/lpc17xx_libcfg_default.d \
./system/src/lpc17xx/lpc17xx_mcpwm.d \
./system/src/lpc17xx/lpc17xx_nvic.d \
./system/src/lpc17xx/lpc17xx_pinsel.d \
./system/src/lpc17xx/lpc17xx_pwm.d \
./system/src/lpc17xx/lpc17xx_qei.d \
./system/src/lpc17xx/lpc17xx_rit.d \
./system/src/lpc17xx/lpc17xx_rtc.d \
./system/src/lpc17xx/lpc17xx_spi.d \
./system/src/lpc17xx/lpc17xx_ssp.d \
./system/src/lpc17xx/lpc17xx_systick.d \
./system/src/lpc17xx/lpc17xx_timer.d \
./system/src/lpc17xx/lpc17xx_uart.d \
./system/src/lpc17xx/lpc17xx_wdt.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/lpc17xx/%.o: ../system/src/lpc17xx/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../system/include" -I"../system/include/cmsis" -I"../system/include/lpc17xx" -I"../freertos/include" -I"../freertos/port" -I"../app/include" -I"../lwip/include" -I"../lwip/include/arch" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


