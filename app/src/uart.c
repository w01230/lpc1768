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

	UARTFIFOConfig.FIFO_DMAMode = ENABLE;
	UARTFIFOConfig.FIFO_Level = UART_FIFO_TRGLEV0;
	UARTFIFOConfig.FIFO_ResetRxBuf = ENABLE;
	UARTFIFOConfig.FIFO_ResetTxBuf = ENABLE;
	UART_FIFOConfig(LPC_UART0, &UARTFIFOConfig);

	UART_TxCmd(LPC_UART0, ENABLE);

	GPDMA_Init();

	NVIC_DisableIRQ(DMA_IRQn);
	NVIC_SetPriority(DMA_IRQn, ((0x01<<3)|0x01));

	NVIC_EnableIRQ(DMA_IRQn);
}

/*
 * DMA_IRQHandler
 *
 *
 * DMA interrupt handler
 */
void DMA_IRQHandler (void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	uint32_t channel;
	// Scan interrupt pending
	for (channel = 0; channel <= 7; channel++) {
		if (GPDMA_IntGetStatus(GPDMA_STAT_INT, channel)){
			// Check counter terminal status
			if(GPDMA_IntGetStatus(GPDMA_STAT_INTTC, channel)){
				// Clear terminate counter Interrupt pending
				GPDMA_ClearIntPending (GPDMA_STATCLR_INTTC, channel);

				switch (channel){
				case 0:
					xEventGroupSetBitsFromISR(xEventGroup, UART0_RX_DONE, &xHigherPriorityTaskWoken);
					GPDMA_ChannelCmd(0, DISABLE);
					break;
				case 1:
					xEventGroupSetBitsFromISR(xEventGroup, UART0_TX_DONE, &xHigherPriorityTaskWoken);
					GPDMA_ChannelCmd(1, DISABLE);
					break;
				default:
					break;
				}

			}
			// Check error terminal status
			if (GPDMA_IntGetStatus(GPDMA_STAT_INTERR, channel)){
				// Clear error counter Interrupt pending
				GPDMA_ClearIntPending (GPDMA_STATCLR_INTERR, channel);
				switch (channel){
				case 0:
					xEventGroupSetBitsFromISR(xEventGroup, UART0_RX_ERR, &xHigherPriorityTaskWoken);
					GPDMA_ChannelCmd(0, DISABLE);
					break;
				case 1:
					xEventGroupSetBitsFromISR(xEventGroup, UART0_TX_ERR, &xHigherPriorityTaskWoken);
					GPDMA_ChannelCmd(1, DISABLE);
					break;
				default:
					break;
				}
			}
		}
	}
}

/*
 * uart0_recv_dma
 *
 *
 * uart0 receive data via dma
 */
static int uart0_recv_dma(unsigned char *buffer, unsigned int size)
{
	EventBits_t uxBits;

	GPDMA_Channel_CFG_Type GPDMACfg;

	GPDMACfg.ChannelNum = 0;
	// Source memory - don't care
	GPDMACfg.SrcMemAddr = 0;
	// Destination memory
	GPDMACfg.DstMemAddr = (uint32_t) buffer;
	// Transfer size
	GPDMACfg.TransferSize = size;
	// Transfer width - don't care
	GPDMACfg.TransferWidth = 0;
	// Transfer type
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_P2M;
	// Source connection
	GPDMACfg.SrcConn = GPDMA_CONN_UART0_Rx;
	// Destination connection - don't care
	GPDMACfg.DstConn = 0;
	// Linker List Item - unused
	GPDMACfg.DMALLI = 0;
	GPDMA_Setup(&GPDMACfg);

	// Enable GPDMA channel 0
	GPDMA_ChannelCmd(0, ENABLE);

	uxBits = xEventGroupWaitBits(xEventGroup, UART0_RX_DONE | UART0_RX_ERR, pdTRUE, pdFALSE, portMAX_DELAY);
	if ((uxBits & UART0_RX_DONE) != UART0_RX_DONE)
		return -1;

	return 0;
}

/*
 * uart0_recv_dma
 *
 *
 * uart0 receive data via dma
 */
static int uart0_send_dma(unsigned char *buffer, unsigned int size)
{
	EventBits_t uxBits;

	GPDMA_Channel_CFG_Type GPDMACfg;

	GPDMACfg.ChannelNum = 1;
	// Source memory
	GPDMACfg.SrcMemAddr = (uint32_t) buffer;
	// Destination memory - don't care
	GPDMACfg.DstMemAddr = 0;
	// Transfer size
	GPDMACfg.TransferSize = size;
	// Transfer width - don't care
	GPDMACfg.TransferWidth = 0;
	// Transfer type
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P;
	// Source connection - don't care
	GPDMACfg.SrcConn = 0;
	// Destination connection
	GPDMACfg.DstConn = GPDMA_CONN_UART0_Tx;
	// Linker List Item - unused
	GPDMACfg.DMALLI = 0;
	// Setup channel with given parameter
	GPDMA_Setup(&GPDMACfg);

	// Enable GPDMA channel 1
	GPDMA_ChannelCmd(1, ENABLE);

	uxBits = xEventGroupWaitBits(xEventGroup, UART0_TX_DONE | UART0_TX_ERR, pdTRUE, pdFALSE, portMAX_DELAY);
	if ((uxBits & UART0_TX_DONE) != UART0_TX_DONE)
		return -1;

	return 0;
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

/*
 * vUartThread
 *
 *
 * receive data and send out via udp
 */
void vUartThread(void *pvParameters)
{
	unsigned char *buffer = NULL;
	unsigned char hello[] = "ready to receive.\r\n";

	uart0_send_dma(hello, sizeof(hello));

	buffer = pvPortMalloc(GS_PACK_LEN + 16);
	if (buffer == NULL)
		return;

	while(true) {
		uart0_recv_dma(buffer, GS_HEADER_LEN);
		if (buffer[0] != GS_HEADER_I)
			continue;
		uart0_recv_dma(buffer + GS_HEADER_LEN, GS_HEADER_LEN);
		if (buffer[1] != GS_HEADER_II)
			continue;
		uart0_recv_dma(buffer + GS_HEADER_LEN * 2, GS_DATA_LEN);

		memcpy(net_gs_data.buffer, buffer, GS_PACK_LEN);
		xEventGroupSetBits(xEventGroup, GS_EVENT);

		uart0_send_dma(buffer, GS_PACK_LEN);
	}

	/* will never be here */
	vPortFree(buffer);
}


#pragma GCC diagnostic pop
