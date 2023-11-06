/*
 * snake.h
 *
 *  Created on: 2023年11月1日
 *      Author: rana
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include <stdint.h>
#include <stdlib.h>
#include "uart.h"

typedef   uint32_t   u32;   ///32位
typedef   uint16_t   u16;   ///16位
typedef   uint8_t     u8;   ///8位

#define	POINT				    0b00010011
#define	DELAY_CUT				1000000
#define ram_address					(*(volatile uint32_t*)0x00008060)
#define ram_data_address			(*(volatile uint32_t*)0x00008070)
//#define ps2ctrl_address					(*(volatile uint32_t*)0x000080A0)
//#define ps2ctrl_point				    (volatile uint32_t*)0x000080A0
#define ps2ctrl_address					(*(volatile uint32_t*)0x00008100)
#define ps2ctrl_point				    (volatile uint32_t*)0x00008100

void draw_c(int x,int y,char c);
void draw_point(int x,int y);
void clear_point(int x,int y);
void delay(long d,char x,char y);
u8 SnakeGameStart(void);

#endif /* SNAKE_H_ */
