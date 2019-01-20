/*
 * uart.h
 *
 *  Created on: 2019��1��19��
 *      Author: john
 */

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H

struct uart_data_s {
	unsigned int channel0_rx_tc;
	unsigned int channel1_tx_tc;
	unsigned int channel0_rx_err;
	unsigned int channel1_tx_err;
	unsigned char buffer[128];
	unsigned char state:1;
};


#define GS_HEADER_I       (0xAA)
#define GS_HEADER_II      (0x55)

#define GS_HEADER_LEN     (1)
#define GS_DATA_LEN       (98)
#define GS_PACK_LEN       (GS_HEADER_LEN * 2 + GS_DATA_LEN)

/* gs data struct */
struct uart_data_s uart0_data;

/* mutex for GS buffer */
extern SemaphoreHandle_t xSemaphoreGS;

void vUartInit(void);
void vTaskInfo(void *pvParameters);
void vUartThread(void *pvParameters);

#endif /* INCLUDE_UART_H_ */
