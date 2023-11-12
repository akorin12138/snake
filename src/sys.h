/*
 * sys.h
 *
 *  Created on: 2023年11月12日
 *      Author: rana
 */

#ifndef SYS_H_
#define SYS_H_
#include <stdint.h>
#include <stdlib.h>

#include "uart.h"
#include "bitmap.h"
#include "hdmidraw.h"
#include "newsnake.h"

typedef   uint64_t   u64;   ///32位
typedef   uint32_t   u32;   ///32位
typedef   uint16_t   u16;   ///16位
typedef   uint8_t     u8;   ///8位

#define led_address 			(*(volatile uint32_t*)0x00008020)
#define gpio_address 			(*(volatile uint32_t*)0x00008030)
#define gpio_point   			(volatile uint32_t*)0x00008030

#define rgb_out_address				(*(volatile uint32_t*)0x00008040)
#define rgb_in_address				(*(volatile uint32_t*)0x00008050)
#define rgb_point				    (volatile uint32_t*)0x00008050
//
#define user_block_u_address		(*(volatile uint32_t*)0x00008080)
#define user_block_d_address		(*(volatile uint32_t*)0x00008090)
#define ps2ctrl_address				(*(volatile uint32_t*)0x00008100)
#define ps2ctrl_point				(volatile uint32_t*)0x00008100
#define ram_address					(*(volatile uint32_t*)0x00008060)
#define ram_data_address			(*(volatile uint32_t*)0x00008070)
//
//#define rgb_r_out				(*(volatile uint32_t*)0x00008090)
//#define rgb_g_out				(*(volatile uint32_t*)0x000080A0)
//#define rgb_b_out				(*(volatile uint32_t*)0x000080B0)

//系统时钟↓
#define SYSTEM_CNT_M			50			//系统时钟单位：MHz

#define SYSTEM_CLOCK			SYSTEM_CNT_M*1000000UL
#define BAUND_9600				((SYSTEM_CLOCK)/9600)
#define BAUND_115200			(SYSTEM_CLOCK/115200)
#define GPIO_DATA				0xaa55
#define LED_DELAY				500000UL
#define color_test				0x7E2B43
#define	POINT				    (0b00010011+(0b1<<31))
#define	DELAY_CUT				5000000


#endif /* SYS_H_ */
