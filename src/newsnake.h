/*
 * newsnake.h
 *
 *  Created on: 2023年11月12日
 *      Author: rana
 */

#ifndef NEWSNAKE_H_
#define NEWSNAKE_H_

#include "sys.h"
typedef   uint64_t   u64;   ///32位
typedef   uint32_t   u32;   ///32位
typedef   uint16_t   u16;   ///16位
typedef   uint8_t     u8;   ///8位

#define snakecolor    10

typedef struct
{
	u8 life;
	u8 headX;
	u8 headY;
	u8 snakeX[300];
	u8 snakeY[300];
	u8 length;
	int dir;
	int tpdir;
	u8 foodX;
	u8 foodY;

}Snake;

void snakeDelay(void);

void snakeInit(void);
void snakeGo(int direct);
void refresh(void);
void GameStart(void);
void generateFood(void);
void dead(void);
u8 isCover(u8 snakeX[],u8 snakeY[],u8 foodX,u8 foodY);
u8 isNearSelf(void);

#endif /* NEWSNAKE_H_ */
