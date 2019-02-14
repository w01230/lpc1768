/*
 * flash.c
 *
 *  Created on: 2019/02/14
 *      Author: jun
 */

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#include "lpc17xx_iap.h"
#include "freertos_lwip_mac.h"
#include "flash.h"

/*
 * device_info_read
 *
 *
 * read device info from flash
 */

int device_info_read(struct local_net_s *net)
{
	struct local_net_s flash_net;

	memcpy(&flash_net, (void *)DEVICE_INFO_START, sizeof(struct local_net_s));

	if ((unsigned char)flash_net.mac_addr[0] == 0xFF)
		return -1;

	memcpy(net, &flash_net, sizeof(struct local_net_s));

	return 0;
}

/*
 * device_info_save
 *
 *
 * write device info to flash
 */
int device_info_save(struct local_net_s *net)
{
	IAP_STATUS_CODE status = CMD_SUCCESS;
	uint32_t uid[4] = {0};
	uint32_t sector = 0;
	uint8_t *buffer = NULL;

	status = ReadDeviceSerialNum(uid);
	if (status != CMD_SUCCESS)
		return -1;

	/* using uid to generate mac address */
	net->mac_addr[15] = uid[0] % 10  + 0x30;
	net->mac_addr[16] = uid[3] % 10  + 0x30;

	buffer = malloc(IAP_WRITE_256);

	memset(buffer, 0xFF, IAP_WRITE_256);
	memcpy(buffer, net, sizeof(struct local_net_s));

	do {
		sector = GetSecNum(DEVICE_INFO_START);
		status = EraseSector(sector, sector);
		if (status != CMD_SUCCESS)
			break;

		status =  CopyRAM2Flash((uint8_t *)DEVICE_INFO_START, (uint8_t *)buffer, IAP_WRITE_256);
		if (status != CMD_SUCCESS)
			break;

		status =  Compare((uint8_t *)DEVICE_INFO_START, (uint8_t *)buffer, IAP_WRITE_256);
		if (status != CMD_SUCCESS)
			break;
	} while (false);

	free(buffer);
	if (status != CMD_SUCCESS)
		return -1;

	NVIC_SystemReset();

	return 0;
}
