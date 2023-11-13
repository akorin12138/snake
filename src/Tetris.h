/*
 * Tetris.h
 *
 *  Created on: 2023年11月13日
 *      Author: rana
 */

#ifndef TETRIS_H_
#define TETRIS_H_

#include "sys.h"

typedef   uint64_t   u64;   ///32位
typedef   uint32_t   u32;   ///32位
typedef   uint16_t   u16;   ///16位
typedef   uint8_t     u8;   ///8位

#define ROW 29 //游戏区行数
#define COL 20 //游戏区列数

#define DOWN 80 //方向键：下
#define LEFT 75 //方向键：左
#define RIGHT 77 //方向键：右

#define SPACE 32 //空格键
#define ESC 27 //Esc键

#define WHITE 255
#define	RED	100
#define ORANGE 101
#define YELLOW 102
#define GREEN 103
#define BLUE 104
#define PURPLE 105
#define PINK 106
#define GRAY 107
typedef struct _COORD{
u16 X;//这里是短整型
u16 Y;//
}COORD;

//光标跳转
void CursorJump(int x, int y);
//初始化界面
void InitInterface();
//初始化方块信息
void InitBlockInfo();
//颜色设置
void color(int num);
//画出方块
void DrawBlock(int shape, int form, int x, int y);
//空格覆盖
void DrawSpace(int shape, int form, int x, int y);
//合法性判断
int IsLegal(int shape, int form, int x, int y);
//判断得分与结束
int JudeFunc();
//游戏主体逻辑函数
void StartGame();
void Tetris();
void TetrisDelay();
#endif /* TETRIS_H_ */
