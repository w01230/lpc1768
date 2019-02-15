/*
 * wdt.h
 *
 *  Created on: 2019/02/15
 *      Author: jun
 */

#ifndef INCLUDE_WDT_H_
#define INCLUDE_WDT_H_

/* wdt 2s */
#define WDT_SECOND     (2)
#define WDT_TIMEOUT    (WDT_SECOND * 1000000)
#define WDT_TICKS      (WDT_SECOND * 1000 + 500)

void vWDTInit(void);
void vWDTFeed(void *pvParameters);

#endif /* INCLUDE_WDT_H_ */
