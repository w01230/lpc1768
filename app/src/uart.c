/*
 * usart.c
 *
 *  Created on: 2019/01/01
 *      Author: john
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "diag/Trace.h"

#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_gpdma.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"

#include "ethernet.h"

#include "uart.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

/*
 * vUartInit
 *
 *
 * init uart
 */
void vUartInit(void)
{
	const uint8_t hello[] = "ready to receive data\n";

	UART_CFG_Type UARTConfig;
	UART_FIFO_CFG_Type UARTFIFOConfig;
	PINSEL_CFG_Type PinConfig;

	PinConfig.Funcnum = 1;
	PinConfig.OpenDrain = 0;
	PinConfig.Pinmode = 0;
	PinConfig.Pinnum = 2;
	PinConfig.Portnum = 0;
	PINSEL_ConfigPin(&PinConfig);

	PinConfig.Pinnum = 3;
	PINSEL_ConfigPin(&PinConfig);

	UARTConfig.Baud_rate = 230400;
	UARTConfig.Databits = UART_DATABIT_8;
	UARTConfig.Parity = UART_PARITY_NONE;
	UARTConfig.Stopbits = UART_STOPBIT_1;
	UART_Init(LPC_UART0, &UARTConfig);

	UARTFIFOConfig.FIFO_DMAMode = DISABLE;
	UARTFIFOConfig.FIFO_Level = UART_FIFO_TRGLEV0;
	UARTFIFOConfig.FIFO_ResetRxBuf = ENABLE;
	UARTFIFOConfig.FIFO_ResetTxBuf = ENABLE;
	UART_FIFOConfig(LPC_UART0, &UARTFIFOConfig);

	UART_TxCmd(LPC_UART0, ENABLE);

	/* Enable UART Rx interrupt */
	UART_IntConfig(LPC_UART0, UART_INTCFG_RBR, ENABLE);
	/* Enable UART line status interrupt */
	UART_IntConfig(LPC_UART0, UART_INTCFG_RLS, ENABLE);

	NVIC_SetPriority(UART0_IRQn, 5);

	NVIC_EnableIRQ(UART0_IRQn);

	/* Send hello */
	UART_Send(LPC_UART0, (uint8_t *)hello, sizeof(hello), BLOCKING);
}

/*
 * uart_receive_int
 *
 *
 * uart receive data via interrupt
 */
void uart_receive_int(void)
{
	uint32_t len = 0;
	uint8_t data = 0;
	static uint8_t prev = 0;
	static bool frame_flag = false;
	static uint8_t gs_data = 0;
	BaseType_t xHigherPriorityTaskWoken;

	len = UART_Receive(LPC_UART0, &data, 1, NONE_BLOCKING);
	if (len > 0) {
		if (data == GS_HEADER_II) {
			if (prev == GS_HEADER_I) {
				net_gs_data.buffer[0] = prev;
				net_gs_data.buffer[1] = data;
				frame_flag = true;
				gs_data = 0;
				return;
			}
		} else {
			prev = data;
		}

		if (frame_flag == true) {
			net_gs_data.buffer[2 + gs_data++] = data;
			if (gs_data >= GS_DATA_LEN) {
				gs_data = 0;
				frame_flag = false;
				xSemaphoreGiveFromISR(xSemaphore, &xHigherPriorityTaskWoken);
				portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
			}
		}
	}
}

/*
 * UART0_IRQHandler
 *
 *
 * UART0 handler
 */
void UART0_IRQHandler(void)
{
	uint32_t intsrc, tmp, tmp1;

	/* Determine the interrupt source */
	intsrc = UART_GetIntId(LPC_UART0);
	tmp = intsrc & UART_IIR_INTID_MASK;

	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS){
		// Check line status
		tmp1 = UART_GetLineStatus(LPC_UART0);
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE | UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1)
			return;
	}

	// Receive Data Available or Character time-out
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI))
		uart_receive_int();
}

/*
 * vTaskInfo
 *
 *
 * printf task info
 */
void vTaskInfo(void *pvParameters)
{
	char *info = NULL;

	info = (char *)pvPortMalloc(1024);
	if (info == NULL)
		trace_printf("failed to malloc memory\n");

	while (1) {
		vTaskList(info);
		trace_printf("task          state  priority  stack  number\n");
		trace_printf("%s", info);
		trace_printf("free heap:%u\n", xPortGetFreeHeapSize());
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
}


#pragma GCC diagnostic pop
