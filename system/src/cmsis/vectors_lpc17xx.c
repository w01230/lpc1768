/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include "cortexm/ExceptionHandlers.h"

// ----------------------------------------------------------------------------

void __attribute__((weak))
Default_Handler(void);

// Forward declaration of the specific IRQ handlers. These are aliased
// to the Default_Handler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//
// TODO: Rename this and add the actual routines here.

void __attribute__ ((weak, alias ("Default_Handler")))
WDT_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIMER0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIMER1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIMER2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIMER3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
UART0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
UART1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
UART2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
UART3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
PWM1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
I2C0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
I2C1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
I2C2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
SPI_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
SSP0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
SSP1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
PLL0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
RTC_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EINT0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EINT1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EINT2_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
EINT3_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
ADC_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
BOD_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
USB_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
CAN_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
I2S_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
ENET_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
RIT_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
MCPWM_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
QEI_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
PLL1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
USBActivity_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
CANActivity_IRQHandler(void);

extern unsigned int _estack;

extern void vPortSVCHandler(void);
extern void xPortPendSVHandler(void);
extern void xPortSysTickHandler(void);

typedef void
(* const pHandler)(void);

// ----------------------------------------------------------------------------

// The vector table.
// This relies on the linker script to place at correct location in memory.

__attribute__ ((section(".isr_vector"),used))
pHandler __isr_vectors[] =
{ //
    (pHandler) &_estack,                          // The initial stack pointer
    Reset_Handler,                            // The reset handler
    
    NMI_Handler,                              // The NMI handler
    HardFault_Handler,                        // The hard fault handler
    
#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
    MemManage_Handler,                        // The MPU fault handler
    BusFault_Handler,// The bus fault handler
    UsageFault_Handler,// The usage fault handler
#else
    0, 0, 0,                  // Reserved
#endif
    0,                                        // Reserved
    0,                                        // Reserved
    0,                                        // Reserved
    0,                                        // Reserved
    vPortSVCHandler,                              // SVCall handler
#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
    DebugMon_Handler,                         // Debug monitor handler
#else
    0,                      // Reserved
#endif
    0,                                        // Reserved
    xPortPendSVHandler,                       // The PendSV handler
    xPortSysTickHandler,                      // The SysTick handler
    
    // Chip Level - LPC17
    WDT_IRQHandler,                           // 16, 0x40 - WDT
    TIMER0_IRQHandler,                        // 17, 0x44 - TIMER0
    TIMER1_IRQHandler,                        // 18, 0x48 - TIMER1
    TIMER2_IRQHandler,                        // 19, 0x4c - TIMER2
    TIMER3_IRQHandler,                        // 20, 0x50 - TIMER3
    UART0_IRQHandler,                         // 21, 0x54 - UART0
    UART1_IRQHandler,                         // 22, 0x58 - UART1
    UART2_IRQHandler,                         // 23, 0x5c - UART2
    UART3_IRQHandler,                         // 24, 0x60 - UART3
    PWM1_IRQHandler,                          // 25, 0x64 - PWM1
    I2C0_IRQHandler,                          // 26, 0x68 - I2C0
    I2C1_IRQHandler,                          // 27, 0x6c - I2C1
    I2C2_IRQHandler,                          // 28, 0x70 - I2C2
    SPI_IRQHandler,                           // 29, 0x74 - SPI
    SSP0_IRQHandler,                          // 30, 0x78 - SSP0
    SSP1_IRQHandler,                          // 31, 0x7c - SSP1
    PLL0_IRQHandler,                          // 32, 0x80 - PLL0 (Main PLL)
    RTC_IRQHandler,                           // 33, 0x84 - RTC
    EINT0_IRQHandler,                         // 34, 0x88 - EINT0
    EINT1_IRQHandler,                         // 35, 0x8c - EINT1
    EINT2_IRQHandler,                         // 36, 0x90 - EINT2
    EINT3_IRQHandler,                         // 37, 0x94 - EINT3
    ADC_IRQHandler,                           // 38, 0x98 - ADC
    BOD_IRQHandler,                           // 39, 0x9c - BOD
    USB_IRQHandler,                           // 40, 0xA0 - USB
    CAN_IRQHandler,                           // 41, 0xa4 - CAN
    DMA_IRQHandler,                           // 42, 0xa8 - GP DMA
    I2S_IRQHandler,                           // 43, 0xac - I2S
    ENET_IRQHandler,                          // Ethernet.
    RIT_IRQHandler,                           // 45, 0xb4 - RITINT
    MCPWM_IRQHandler,                         // 46, 0xb8 - Motor Control PWM
    QEI_IRQHandler,                           // 47, 0xbc - Quadrature Encoder
    PLL1_IRQHandler,                          // 48, 0xc0 - PLL1 (USB PLL)
    USBActivity_IRQHandler,                   // 49, 0xc4 - USB Activity interrupt to wakeup
    CANActivity_IRQHandler,                   // 50, 0xc8 - CAN Activity interrupt to wakeup
};

// ----------------------------------------------------------------------------

// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.

void __attribute__ ((section(".after_vectors")))
Default_Handler(void)
{
    while (1)
    {
    }
}

// ----------------------------------------------------------------------------
