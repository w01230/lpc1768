/*
 * wdt.c
 *
 *  Created on: 2019/02/15
 *      Author: jun
 */
#include <stdbool.h>
#include "lpc17xx_wdt.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"

#include "uart.h"
#include "wdt.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

/*
 * vWDTInit
 *
 *
 * init wdt
 */
void vWDTInit(void)
{
	if (WDT_ReadTimeOutFlag())
		WDT_ClrTimeOutFlag();

	WDT_Init(WDT_CLKSRC_IRC, WDT_MODE_RESET);

	WDT_Start(WDT_TIMEOUT);
}

/*
 * vWDTFeed
 *
 *
 * a task used to check main thread and clear WDT
 */
void vWDTFeed(void *pvParameters)
{
	EventBits_t uxBits;
	const TickType_t xTicksToWait = WDT_TICKS / portTICK_PERIOD_MS;

	while (true) {
		uxBits = xEventGroupWaitBits(xEventGroup, TASK_BIT_ALL, pdTRUE, pdTRUE, xTicksToWait);
		if ((uxBits & TASK_BIT_ALL) == TASK_BIT_ALL)
			WDT_UpdateTimeOut(WDT_TIMEOUT);
	}
}

#pragma GCC diagnostic pop
