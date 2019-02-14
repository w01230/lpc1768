/*
 * flash.h
 *
 *  Created on: 2019/02/14
 *      Author: jun
 */

#ifndef INCLUDE_FLASH_H_
#define INCLUDE_FLASH_H_

#define DEIVCE_SIZE             (512 * 1024)
#define DEVICE_INFO_START       (DEIVCE_SIZE - 0x200)

/* read device net info from flash */
int device_info_read(struct local_net_s *net);

/* write device net info to flash */
int device_info_save(struct local_net_s *net);

#endif /* INCLUDE_FLASH_H_ */
