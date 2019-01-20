/*
 * usart.c
 *
 *  Created on: 2019/01/01
 *      Author: john
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "diag/Trace.h"

#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "ethernet.h"

#include "uart.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

struct uart_data_s uart0_data = {.state = 0};

/*
 * vUartInit
 *
 *
 * init uart
 */
void vUartInit(void)
{
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
}

/*
 * vUartThread
 *
 *
 * receive data and send out via udp
 */
void vTaskInfo(void *pvParameters)
{
	char *info = NULL;

	info = (char *)malloc(512);
	if (info == NULL)
		trace_printf("falied to malloc memory\n");

	while (1) {
		vTaskList(info);
		trace_printf("---------------task list-------------------\n");
		trace_printf("%s\n", info);
		trace_printf("free heap:%u\n", xPortGetFreeHeapSize());
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
}

/*
 * vUartThread
 *
 *
 * receive data and send out via udp
 */
void vUartThread(void *pvParameters)
{
	unsigned char hello[] = "start to receive.\r\n";

	UART_Send(LPC_UART0, hello, sizeof(hello), BLOCKING);
	while(UART_CheckBusy(LPC_UART0) != SET);

	while(1) {
		UART_Receive(LPC_UART0, uart0_data.buffer, 1, BLOCKING);
		if (uart0_data.buffer[0] == 0xAA) {
			UART_Receive(LPC_UART0, uart0_data.buffer + 1, 1, BLOCKING);
			if (uart0_data.buffer[1] != 0x55)
				continue;
			UART_Receive(LPC_UART0, uart0_data.buffer + GS_HEADER_LEN, GS_DATA_LEN, BLOCKING);

			//xSemaphoreTake(xSemaphoreGS, portMAX_DELAY);
			memcpy(net_gs_data.buffer, uart0_data.buffer, GS_PACK_LEN);
			//xSemaphoreGive(xSemaphoreGS);
			UART_Send(LPC_UART0, uart0_data.buffer, GS_PACK_LEN, BLOCKING);
			while(UART_CheckBusy(LPC_UART0) != SET);
		}
	}
}


#pragma GCC diagnostic pop
