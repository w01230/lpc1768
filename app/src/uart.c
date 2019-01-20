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
#include "lpc17xx_gpdma.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "ethernet.h"

#include "uart.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

struct uart_data_s uart0_data = {.channel0_rx_tc = 0, .channel1_tx_tc = 0, .state = 0};

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
	uint32_t tmp;
		// Scan interrupt pending
	for (tmp = 0; tmp <= 7; tmp++) {
		if (GPDMA_IntGetStatus(GPDMA_STAT_INT, tmp)){
			// Check counter terminal status
			if(GPDMA_IntGetStatus(GPDMA_STAT_INTTC, tmp)){
				// Clear terminate counter Interrupt pending
				GPDMA_ClearIntPending (GPDMA_STATCLR_INTTC, tmp);

				switch (tmp){
					case 0:
						uart0_data.channel0_rx_tc++;
						GPDMA_ChannelCmd(0, DISABLE);
						break;
					case 1:
						uart0_data.channel1_tx_tc++;
						GPDMA_ChannelCmd(1, DISABLE);
						break;
					default:
						break;
				}

			}
				// Check error terminal status
			if (GPDMA_IntGetStatus(GPDMA_STAT_INTERR, tmp)){
				// Clear error counter Interrupt pending
				GPDMA_ClearIntPending (GPDMA_STATCLR_INTERR, tmp);
				switch (tmp){
					case 0:
						uart0_data.channel0_rx_err++;
						GPDMA_ChannelCmd(0, DISABLE);
						break;
					case 1:
						uart0_data.channel1_tx_err++;
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
	unsigned int timeout = UART_BLOCKING_TIMEOUT;

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

	/* Reset terminal counter */
	uart0_data.channel0_rx_tc = 0;
	/* Reset Error counter */
	uart0_data.channel0_rx_err = 0;

	// Enable GPDMA channel 0
	GPDMA_ChannelCmd(0, ENABLE);

	while ((uart0_data.channel0_rx_tc == 0) && (uart0_data.channel0_rx_err == 0)){
		if (timeout == 0)
			return -1;
		timeout--;

	};

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
	unsigned int timeout = UART_BLOCKING_TIMEOUT;

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

	/* Reset terminal counter */
	uart0_data.channel0_rx_tc = 0;
	/* Reset Error counter */
	uart0_data.channel0_rx_err = 0;

	// Enable GPDMA channel 1
	GPDMA_ChannelCmd(1, ENABLE);

	/* wait for time out */
	while ((uart0_data.channel1_tx_tc == 0) && (uart0_data.channel1_tx_err == 0)) {
		if (timeout == 0)
			return -1;
		timeout--;

	};

	return 0;
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
	unsigned char hello[] = "ready to receive.\r\n";

	uart0_send_dma(hello, sizeof(hello));

	while(1) {
		uart0_recv_dma(uart0_data.buffer, GS_HEADER_LEN);
		if (uart0_data.buffer[0] != GS_HEADER_I)
			continue;
		uart0_recv_dma(uart0_data.buffer + GS_HEADER_LEN, GS_HEADER_LEN);
		if (uart0_data.buffer[1] != GS_HEADER_II)
			continue;
		uart0_recv_dma(uart0_data.buffer + GS_HEADER_LEN * 2, GS_DATA_LEN);

		//xSemaphoreTake( xSemaphoreGS, portMAX_DELAY);
		memcpy(net_gs_data.buffer, uart0_data.buffer, GS_PACK_LEN);
		uart0_send_dma(uart0_data.buffer, GS_PACK_LEN);
		//xSemaphoreGive(xSemaphoreGS);
	}
}


#pragma GCC diagnostic pop
