/*
 * test.h
 *
 *  Created on: 2023年10月15日
 *      Author: rana
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "sys.h"
void app_demo(void);

//游戏界面行列数
#define START_X		10
#define START_Y		50

//砖块宽
#define ZK_WIDTH	25
//砖块高
#define ZK_HEIGHT	20

//板子宽
#define BZ_WIDTH	80
//板子高
#define BZ_HEIGHT	5

//横着的砖块数
#define COLS	10
//竖着的砖块数
#define ROWS	5

//窗口宽
#define WINDOW_WIDTH	250
//窗口高
#define WINDOW_HEIGHT	250

//球半径
#define RADIUS	3

//球移动像素
#define SPACE 	4

//板子移动像素
#define BZ_SPACE 	10

void app_demo(void);
#endif /* TEST_H_ */
