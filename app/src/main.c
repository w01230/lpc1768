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

#include <stdio.h>
#include <stdlib.h>

#include "diag/Trace.h"
#include "lpc17xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "freertos_lwip_mac.h"
#include "ethernet.h"
#include "uart.h"
#include "flash.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

/* Semaphore for sync gs data */
SemaphoreHandle_t xSemaphore = NULL;

static void prvSetupHardware(void)
{
	/* 32 group priorities */
	NVIC_SetPriorityGrouping(2);

	/* get system cock */
	SystemCoreClockUpdate();

	/* init uart */
	vUartInit();

	/* read net info */
	device_info_read(&local_net);
}

int main (int argc, char* argv[])
{
	/* Configure the hardware. */
	prvSetupHardware();

	/* create semaphore */
	xSemaphore = xSemaphoreCreateBinary();

	/* Create task. */
	xTaskCreate(vTaskInfo, "TaskList", configMINIMAL_STACK_SIZE * 2, ( void * ) NULL, tskIDLE_PRIORITY + 2, NULL);
	xTaskCreate(vEthernetDaemon, "NetDaemon", configMINIMAL_STACK_SIZE, ( void * ) NULL, tskIDLE_PRIORITY + 2, NULL);

	/* Start the scheduler. */
	vTaskStartScheduler();

	return 0;
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
