/*
 * uart.h
 *
 *  Created on: 2019Äê1ÔÂ19ÈÕ
 *      Author: john
 */

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

struct uart_data_s {
	unsigned char buffer[128];
	unsigned char state:1;
};

#define GS_HEADER_LEN     (2)
#define GS_DATA_LEN       (98)
#define GS_PACK_LEN       (GS_HEADER_LEN + GS_DATA_LEN)

/* gs data struct */
struct uart_data_s uart0_data;

/* mutex for GS buffer */
extern SemaphoreHandle_t xSemaphoreGS;

void vUartInit(void);
void vTaskInfo(void *pvParameters);
void vUartThread(void *pvParameters);

#endif /* INCLUDE_UART_H_ */
