/*
 * uart.h
 *
 *  Created on: 2019/01/19
 *      Author: john
 */

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H

/* gs data */
#define GS_HEADER_I       (0xAA)
#define GS_HEADER_II      (0x55)

#define GS_HEADER_LEN     (1)
#define GS_DATA_LEN       (98)
#define GS_PACK_LEN       (GS_HEADER_LEN * 2 + GS_DATA_LEN)

/* semaphore */
#define SEMAPHORE_TIME    (10000)

/* event bit*/
#define NET_MAIN_BIT      (1 << 0)
#define TASK_BIT_ALL      NET_MAIN_BIT

/* semaphore */
extern SemaphoreHandle_t xSemaphore;

/* event group */
extern EventGroupHandle_t xEventGroup;

void vUartInit(void);
void vTaskInfo(void *pvParameters);

#endif /* INCLUDE_UART_H_ */
