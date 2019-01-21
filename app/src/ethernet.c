/*
 * ethernet.c
 *
 *  Created on: 2018/12/30
 *	  Author: john
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"

#include "lwip/sys.h"
#include "lwip/tcpip.h"
#include "lwip/api.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"

#include "phy_smsc87x0.h"
#include "freertos_lwip_mac.h"

#include "diag/Trace.h"
#include "ethernet.h"
#include "uart.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

struct net_gs_data_s net_gs_data = {.state = 0};

/*
 * get_dev_info
 *
 * @device: device data point
 * @type: header type
 *
 * get_device info
 *
 * RETURN VALUE:
 * 0  if net is not NULL
 * -1 if net is NULL
 */
static int get_dev_info(struct device_s *device, char *type)
{
	if ((device->header == NULL) || (type == NULL)) {
		trace_printf("strcpy:invalid point address!\n");
		return -1;
	}

	if (strlen(device->header) < strlen(type)) {
		trace_printf("strcpy:memspace is not enough!\n");
		return -1;
	}

	device->dev.type = HD_IPC;
	strcpy(device->header, type);
	memcpy(device->dev.vendor, "HDIPC", 6);
	memcpy(device->dev.name, "LPC1768", 8);
	memcpy(device->dev.serial_number, "1000001", 9);
	memcpy(device->dev.software, "1.0.0", 4);
	memcpy(device->dev.hardware, "1.0.0", 4);
	memcpy(&device->net, &local_net, sizeof(local_net));
	memcpy(device->net.port, "80", 3);

	return 0;
}

/*
 * set_hd_dev_net
 *
 * @net:device net data point
 *
 * set_device net
 *
 * RETURN VALUE:
 * 0  if this device
 * -1 if not this device
 */
static int set_dev_net(struct net_info_s *net)
{
	struct net_info_s local_net;

	if (strcmp(net->mac_addr, local_net.mac_addr) != 0)
		return -1;

	return 0;
}

/*
 * vDeviceInfo
 *
 *
 * device search client
 */
static void vDeviceInfo(void *pvParameters)
{
	int socketfd, on = 1;
	unsigned int socklen = 0;
	struct sockaddr_in local, multi;
	struct device_s device;
	struct ip_mreq mreq;

	do {
		if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
			trace_printf("socket error\n");
			return;
		}

		if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
			trace_printf("setsockopt error\n");
			break;
		}

		memset(&local, 0, sizeof(struct sockaddr_in));
		local.sin_family = AF_INET;
		local.sin_port = htons(MULTICAST_RCV_PORT);
		local.sin_addr.s_addr = INADDR_ANY;

		if (bind(socketfd, (struct sockaddr *)&local, sizeof(struct sockaddr_in)) == -1) {
			trace_printf("bind error\n");
			break;
		}

		memset(&mreq, 0, sizeof(struct ip_mreq));
		mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_ADDR);
		mreq.imr_interface.s_addr = htonl(INADDR_ANY);

		if (setsockopt(socketfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(struct ip_mreq)) == -1) {
			trace_printf("setsockopt error\n");
			break;
		}

		socklen = sizeof(struct sockaddr_in);
		memset(&multi, 0, socklen);
		multi.sin_family = AF_INET;
		if (inet_pton(AF_INET, MULTICAST_ADDR, &multi.sin_addr) <= 0) {
			trace_printf("inet_pton error\n");
			break;
		}
		multi.sin_port = htons(MULTICAST_SEND_PORT);

		memset(&device, 0, sizeof(struct device_s));

		while (true) {
			if ((recvfrom(socketfd, (void *)&device, sizeof(struct device_s), 0, (struct sockaddr *)&local, (socklen_t *)&socklen)) < 0) {
				trace_printf("recvfrom error");
			} else {
				trace_printf("message:%s\n", device.header);
				if ((strcmp(device.header, REQUEST_DEV_INFO)) == 0) {
					if (get_dev_info(&device, (char *)RESPOND_DEV_INFO) < 0)
						trace_printf("hd_dev_info return illegal\n");
					if (sendto(socketfd, &device, sizeof(struct device_s), 0,
						(struct sockaddr *)&multi, sizeof(struct sockaddr_in)) < 0)
						trace_printf("sendto error\n");
				} else if ((strcmp(device.header, REQUEST_DEV_SET)) == 0) {
					if (set_dev_net(&device.net) == 0) {
						strcpy(device.header, RESPOND_DEV_SET);
						if (sendto(socketfd, &device, sizeof(struct device_s), 0,
							(struct sockaddr *)&multi, sizeof(struct sockaddr_in)) < 0)
							trace_printf("sendto error\n");
					}
				} else {
					trace_printf("invalid request.\n");
				}
			}
		}
	} while(false);
	close(socketfd);
}

/*
 * udp_client
 *
 *
 * UDP client function
 */
static void vUDPServer(void *pvParameters)
{
	int socketfd;
	struct sockaddr_in servaddr, cliaddr;
	unsigned char buffer[20] = {0};
	int len, n;

	// Creating socket file descriptor
	if ( (socketfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		trace_printf("socket creation failed");
		return;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	// Filling server information
	servaddr.sin_family	= AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(UDP_SERVER_PORT);

	// Bind the socket with the server address
	if (bind(socketfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		trace_printf("bind failed");
		return;
	}

	while(true) {
		/* send and receive motor control data here */
		n = recvfrom(socketfd, (char *)buffer, sizeof(buffer), 0, ( struct sockaddr *) &cliaddr, (socklen_t *)&len);
		if (n < 0)
			continue;
		sendto(socketfd, (const char *)buffer, sizeof(buffer), 0, (const struct sockaddr *) &cliaddr, len);
		/* one operation done send event to rs485 thread */
		xEventGroupSetBits(xEventGroup, MOTOR_EVENT);
	}

	closesocket(socketfd);
}

/*
 * udp_client
 *
 *
 * UDP client function
 */
static void vUDPClient(void *pvParameters)
{
	EventBits_t uxBits;
	struct sockaddr_in server_addr;
	int socketfd, status = 0;

	socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketfd == -1) {
		trace_printf("failed to create socket \n");
		return;
	}

	server_addr.sin_port = htons(UDP_REMOTE_SERVER_PORT);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(UDP_REMOTE_SERVER_IP);

	while (true) {
		uxBits = xEventGroupWaitBits(xEventGroup, GS_EVENT, pdTRUE, pdFALSE, portMAX_DELAY);
		if ((uxBits & GS_EVENT) != GS_EVENT)
			continue;
		status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
		if (status != 0)
			continue;
		status = send(socketfd, (char *)net_gs_data.buffer, GS_PACK_LEN, 0);
		if (status < 0)
			continue;
	}

	closesocket(socketfd);
}

/*
 * vEthernetDeamon
 *
 *
 * Daemon task for Ethernet
 */
void vEthernetDaemon(void *pvParameters)
{
	ip4_addr_t ipaddr, netmask, gw;
	struct netif lpc17xx_netif;
	uint32_t physts;

#if LWIP_DHCP
	ip4_addr_set_zero(&ipaddr);
	ip4_addr_set_zero(&netmask);
	ip4_addr_set_zero(&gw);
#else
	inet_pton(AF_INET, local_net.ip_addr, &ipaddr);
	inet_pton(AF_INET, local_net.netmask, &netmask);
	inet_pton(AF_INET, local_net.gateway, &gw);
#endif

	tcpip_init(NULL, NULL);				/* Initialize TCP/IP Stack. */
	netif_add(&lpc17xx_netif, &ipaddr, &netmask, &gw, NULL, lpc_enetif_init, tcpip_input);
	netif_set_default(&lpc17xx_netif);	/* Setting this interface default. */

#if !LWIP_DHCP
	netif_set_up(&lpc17xx_netif);
#else
	dhcp_start(&lpc17xx_netif);
#endif

	/* udp client */
	sys_thread_new("udpclient", vUDPClient, NULL, configMINIMAL_STACK_SIZE , DEFAULT_THREAD_PRIO);

	/* udp server */
	sys_thread_new("udpserver", vUDPServer, NULL, configMINIMAL_STACK_SIZE , DEFAULT_THREAD_PRIO);

	/* device info */
	sys_thread_new("deviceinfo", vDeviceInfo, NULL, configMINIMAL_STACK_SIZE * 2, DEFAULT_THREAD_PRIO);

	/* This loop monitors the PHY link and will handle cable events via the PHY driver. */
	while (true) {
		physts = lpcPHYStsPoll();

		/* Only check for connection state when the PHY status has changed */
		if (physts & PHY_LINK_CHANGED) {
			if (physts & PHY_LINK_CONNECTED) {
				if (physts & PHY_LINK_SPEED100)
					lpc_emac_set_speed(1);
				else
					lpc_emac_set_speed(0);

				if (physts & PHY_LINK_FULLDUPLX)
					lpc_emac_set_duplex(1);
				else
					lpc_emac_set_duplex(0);

				tcpip_callback_with_block((tcpip_callback_fn) netif_set_link_up, (void *) &lpc17xx_netif, 1);
			} else {
				tcpip_callback_with_block((tcpip_callback_fn) netif_set_link_down, (void *) &lpc17xx_netif, 1);
			}
			vTaskDelay(configTICK_RATE_HZ / 4);		/* Delay for link detection (250mS) */
		}
	}
}

#pragma GCC diagnostic pop
