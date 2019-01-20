/*
 * ethernet.h
 *
 *  Created on: 2018骞�/12/30
 *      Author: john
 */

#ifndef ETHERNET_H
#define ETHERNET_H

/* defines used for udp client */
#define UDP_SERVER_PORT         (1025)
#define UDP_SERVER_IP           "10.0.0.201"

/*mulicast defines*/
#define MULTICAST_ADDR          "239.0.0.1"
#define MULTICAST_RCV_PORT      9980
#define MULTICAST_SEND_PORT     9988

/*Request type*/
#define REQUEST_DEV_INFO        "request:device info"
#define RESPOND_DEV_INFO        "respone:device info"
#define REQUEST_DEV_SET         "request:device config"
#define RESPOND_DEV_SET         "respone:device config"

/* define data len of device struct */
#define VENDOR_LEN              0x10
#define NAME_LEN                0x10
#define SN_LEN                  0x21
#define VERSION_LEN             0x08

/* net defines */
#define MAC_LEN                 0x12
#define NET_LEN                 0x10
#define PORT_LEN                0x06


/* define device type */
#define HD_IPC                  0x01
#define HD_PTZ                  0x02
#define HD_OTHER                0x03

/* struct of device */
struct dev_info_s {
	unsigned char type;
	char vendor[VENDOR_LEN];
	char name[NAME_LEN];
	char serial_number[SN_LEN];
	char software[VERSION_LEN];
	char hardware[VERSION_LEN];
};

/*struct of net*/
struct net_info_s {
	char ip_addr[NET_LEN];
	char gateway[NET_LEN];
	char netmask[NET_LEN];
	char dns1[NET_LEN];
	char dns2[NET_LEN];
	char mac_addr[MAC_LEN];
	char port[PORT_LEN];
};

/* udp data struct */
struct device_s {
	char header[32];
	struct dev_info_s dev;
	struct net_info_s net;
};

struct net_gs_data_s {
	unsigned char buffer[128];
	unsigned char state:1;
};

struct net_gs_data_s net_gs_data;

/* Ethernet Daemon */
void vEthernetDaemon(void *pvParameters);

#endif /* SRC_ETHERNET_H_ */
