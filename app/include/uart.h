/*
 * uart.h
 *
 *  Created on: 2019/01/19
 *      Author: john
 */

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H

#define BIT(n)            (1 << n)
#define GS_EVENT          BIT(0)
#define UART0_RX_DONE     BIT(1)
#define UART0_RX_ERR      BIT(2)
#define UART0_TX_DONE     BIT(3)
#define UART0_TX_ERR      BIT(4)
#define MOTOR_EVENT       BIT(5)

#define GS_HEADER_I       (0xAA)
#define GS_HEADER_II      (0x55)

#define GS_HEADER_LEN     (1)
#define GS_DATA_LEN       (98)
#define GS_PACK_LEN       (GS_HEADER_LEN * 2 + GS_DATA_LEN)

/* event group */
extern EventGroupHandle_t xEventGroup;

void vUartInit(void);
void vTaskInfo(void *pvParameters);
void vUart0Thread(void *pvParameters);

#endif /* INCLUDE_UART_H_ */
