#include <stdio.h>
#include <stdlib.h>
#include "Tetris.h"

u8 tetriskey = 0;
u8 end = 0;
COORD pos;
struct Face
{
	u8 data[ROW][COL + 10]; //用于标记指定位置是否有方块（1为有，0为无）
	u8 color[ROW][COL + 10]; //用于记录指定位置的方块颜色编码
}face;

struct Block
{
	u8 space[4][4];
}block[7][4]; //用于存储7种基本形状方块的各自的4种形态的信息，共28种

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

int max, grade; //全局变量
void Tetris()
{
	max = 0, grade = 0; //初始化变量
	InitInterface(); //初始化界面
	InitBlockInfo(); //初始化方块信息
	srand(1); //设置随机数生成的起点
	StartGame(); //开始游戏
}

//光标跳转
void CursorJump(int x, int y)
{
	 //定义光标位置的结构体变量
	pos.X = x; //横坐标设置
	pos.Y = y; //纵坐标设置
}
//初始化界面
void InitInterface()
{
	hdmi_draw_clear(255);
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL + 10; j++)
		{
			if (j == 0 || j == COL - 1 || j == COL + 9)
			{
				face.data[i][j] = 1; //标记该位置有方块
			}
			else if (i == ROW - 1)
			{
				face.data[i][j] = 1; //标记该位置有方块
			}
			else
				face.data[i][j] = 0; //标记该位置无方块
		}
	}
	for (int i = COL; i < COL + 10; i++)
	{
		face.data[8][i] = 1; //标记该位置有方块
	}
	//上色
	for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL + 10; j++){
				if(face.data[i][j] == 1){
					hdmi_draw_square_vertical(j*8,i*8,8,255);
					hdmi_draw_square_vertical(j*8+1,i*8+1,6,0);
				}
				else{
					hdmi_draw_square_vertical(j*8,i*8,8,255);
				}
			}
		}
	hdmi_draw_string_back_verticlal((COL + 1)*8,160,"SCORE:",0,255);
	hdmi_draw_num_back_vertical((COL + 1)*8,180,grade,3,0,255);
//功能区打印东西
}

void InitBlockInfo()
{
	//“T”形
	for (int i = 0; i <= 2; i++)
		block[0][0].space[1][i] = 1;
	block[0][0].space[2][1] = 1;

	//“L”形
	for (int i = 1; i <= 3; i++)
		block[1][0].space[i][1] = 1;
	block[1][0].space[3][2] = 1;

	//“J”形
	for (int i = 1; i <= 3; i++)
		block[2][0].space[i][2] = 1;
	block[2][0].space[3][1] = 1;

	for (int i = 0; i <= 1; i++)
	{
		//“Z”形
		block[3][0].space[1][i] = 1;
		block[3][0].space[2][i + 1] = 1;
		//“S”形
		block[4][0].space[1][i + 1] = 1;
		block[4][0].space[2][i] = 1;
		//“O”形
		block[5][0].space[1][i + 1] = 1;
		block[5][0].space[2][i + 1] = 1;
	}

	//“I”形
	for (int i = 0; i <= 3; i++)
		block[6][0].space[i][1] = 1;

	int temp[4][4];
	for (int shape = 0; shape < 7; shape++) //7种形状
	{
		for (int form = 0; form < 3; form++) //4种形态（已经有了一种，这里每个还需增加3种）
		{
			//获取第form种形态
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					temp[i][j] = block[shape][form].space[i][j];
				}
			}
			//将第form种形态顺时针旋转，得到第form+1种形态
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					block[shape][form + 1].space[i][j] = temp[3 - j][i];
				}
			}
		}
	}
}

void color(int c)
{
	switch (c)
	{
	case 0:
		c = 13; //“T”形方块设置为紫色
		break;
	case 1:
	case 2:
		c = 12; //“L”形和“J”形方块设置为红色
		break;
	case 3:
	case 4:
		c = 10; //“Z”形和“S”形方块设置为绿色
		break;
	case 5:
		c = 14; //“O”形方块设置为黄色
		break;
	case 6:
		c = 11; //“I”形方块设置为浅蓝色
		break;
	default:
		c = 7; //其他默认设置为白色
		break;
	}
//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //颜色设置
		//注：SetConsoleTextAttribute是一个API（应用程序编程接口）
}
void DrawBlock(int shape, int form, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[shape][form].space[i][j] == 1) //如果该位置有方块
			{
				CursorJump((x + j), y + i); //光标跳转到指定位置
				hdmi_draw_square_vertical(8*pos.X,8*pos.Y,8,0);
				hdmi_draw_square_vertical(8*pos.X+1,8*pos.Y+1,6,ORANGE);
//				printf("■"); //输出方块
			}
		}
	}
}
void DrawSpace(int shape, int form, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[shape][form].space[i][j] == 1) //如果该位置有方块
			{
				hdmi_draw_square_vertical(8*(x +j),8*(y+i),8,255);
			}
		}
	}
}
int IsLegal(int shape, int form, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//如果方块落下的位置本来就已经有方块了，则不合法
			if ((block[shape][form].space[i][j] == 1) && (face.data[y + i][x + j] == 1))
				return 0; //不合法
		}
	}
	return 1; //合法
}
int JudeFunc()
{
	//判断是否得分
	for (int i = ROW - 2; i > 4; i--)//>4?
	{
		int sum = 0; //记录第i行的方块个数
		for (int j = 1; j < COL - 1; j++)
		{
			sum += face.data[i][j]; //统计第i行的方块个数
		}
		if (sum == 0) //该行没有方块，无需再判断其上的层次（无需再继续判断是否得分）
			break; //跳出循环
		if (sum == COL - 2) //该行全是方块，可得分
		{
			grade += 10; //满一行加10分
			for (int j = 1; j < COL - 1; j++) //清除得分行的方块信息
			{
				face.data[i][j] = 0; //该位置得分后被清除，标记为无方块
				CursorJump(j, i); //光标跳转到该位置
				hdmi_draw_square_vertical(8*(pos.X +j),8*(pos.Y+i),8,255);
			}
			//把被清除行上面的行整体向下挪一格
			for (int m = i; m >1; m--)
			{
				sum = 0; //记录上一行的方块个数
				for (int n = 1; n < COL - 1; n++)
				{
					sum += face.data[m - 1][n]; //统计上一行的方块个数
					face.data[m][n] = face.data[m - 1][n]; //将上一行方块的标识移到下一行
					face.color[m][n] = face.color[m - 1][n]; //将上一行方块的颜色编号移到下一行
				}
				if (sum == 0){ //上一行移下来的全是空格，无需再将上层的方块向下移动（移动结束）
					//移动完毕整体上色
					for (int i = 0; i < ROW - 1; i++)
						{
							for (int j = 1; j < COL - 1; j++){
								if(face.data[i][j] == 1){
									hdmi_draw_square_vertical(j*8,i*8,8,0);
									hdmi_draw_square_vertical(j*8+1,i*8+1,6,ORANGE);
								}
								else
									hdmi_draw_square_vertical(j*8,i*8,8,255);
							}
						}
					return 1; //返回1，表示还需调用该函数进行判断（移动下来的可能还有满行）
				}
			}
		}
	}//循环找得分结束
	//判断游戏是否结束
	for (int j = 1; j < COL - 1; j++)
	{
		if (face.data[1][j] == 1) //顶层有方块存在（以第1行为顶层，不是第0行）
		{
			hdmi_draw_string_back_verticlal(20,120,"GAME OVER",RED,255);
			while (1)
			{//游戏结束等待键值返回
				hdmi_draw_string_back_verticlal(20,160,"PRESS'X'TO QUIT",PURPLE,255);
				u8 overkey = 0;
				tetriskey = *ps2ctrl_point;
				if(tetriskey!=0)
					switch(tetriskey){
					case 0b00000010:overkey = SPACE;break;//空格  B
					case 0b00000100:overkey = ESC;break;//退出     X
					}
				if(overkey == SPACE){
					end = 2;
					return 0;
				}else if(overkey == ESC){
					end = 1;
					return 0;
				}
			}
		}
	}
	return 0; //判断结束，无需再调用该函数进行判断
}
void TetrisDelay(){
	u32 cnt = 500;
	while(cnt--)
		led_address = 0;
}
void StartGame()
{
	int shape = rand() % 7, form = rand() % 4; //随机获取方块的形状和形态
	while (1)
	{
		hdmi_draw_num_back_vertical((COL + 1)*8,180,grade,3,0,255);
		u8 key;u8 tetriskeyval;u32 cnt;u8 key_d;u8 flag = 0;
		u32 nextShape = rand() % 7, nextForm = rand() % 4; //随机获取下一个方块的形状和形态
		u32 x = COL / 2 - 2, y = 0; //方块初始下落位置的横纵坐标
		DrawBlock(nextShape, nextForm, COL + 3, 3); //将下一个方块显示在右上角
		while (1)
		{
			tetriskeyval = 0;
			cnt = 700000;
			DrawBlock(shape, form, x, y); //将该方块显示在初始下落位置
			while(--cnt){
				tetriskey = *ps2ctrl_point;
				if(tetriskey!=0)
					tetriskeyval = tetriskey;
			}
			switch(tetriskeyval){
				case 0:key = 0;break;
				case 0b00100000:key = DOWN;break;//下
				case 0b01000000:key = LEFT;break;//左
				case 0b10000000:key = RIGHT;break;//右
				case 0b00000010:key = SPACE;break;//空格  B
				case 0b00000100:key = ESC;break;//退出     X
			}
			if (key == 0) //键盘未被敲击
			{
				if (IsLegal(shape, form, x, y + 1) == 0) //方块再下落就不合法了（已经到达底部）
				{
					//将当前方块的信息录入face当中
					//face:记录界面的每个位置是否有方块，若有方块还需记录该位置方块的颜色。
					for (u8 i = 0; i < 4; i++)
					{
						for (u8 j = 0; j < 4; j++)
						{
							if (block[shape][form].space[i][j] == 1)
							{
								face.data[y + i][x + j] = 1; //将该位置标记为有方块
								face.color[y + i][x + j] = shape; //记录该方块的颜色数值
							}
						}
					}
					while (JudeFunc()); //判断此次方块下落是否得分以及游戏是否结束
					break; //跳出当前死循环，准备进行下一个方块的下落
				}
				else //未到底部
				{
					DrawSpace(shape, form, x, y); //用空格覆盖当前方块所在位置
					y++; //纵坐标自增（下一次显示方块时就相当于下落了一格了）
				}
			}
			else //键盘被敲击
			{
				switch (key)
				{
				case DOWN: //方向键：下
					if (IsLegal(shape, form, x, y + 1) == 1) //判断方块向下移动一位后是否合法
					{
						//方块下落后合法才进行以下操作
						DrawSpace(shape, form, x, y); //用空格覆盖当前方块所在位置
						y=y++; //纵坐标自增（下一次显示方块时就相当于下落了一格了）
					}
					break;
				case LEFT: //方向键：左
					if (IsLegal(shape, form, x - 1, y) == 1) //判断方块向左移动一位后是否合法
					{
						//方块左移后合法才进行以下操作
						DrawSpace(shape, form, x, y); //用空格覆盖当前方块所在位置
						x--; //横坐标自减（下一次显示方块时就相当于左移了一格了）
					}
					break;
				case RIGHT: //方向键：右
					if (IsLegal(shape, form, x + 1, y) == 1) //判断方块向右移动一位后是否合法
					{
						//方块右移后合法才进行以下操作
						DrawSpace(shape, form, x, y); //用空格覆盖当前方块所在位置
						x++; //横坐标自增（下一次显示方块时就相当于右移了一格了）
					}
					break;
				case SPACE: //空格键
					if (IsLegal(shape, (form + 1) % 4, x, y + 1) == 1) //判断方块旋转后是否合法
					{
						//方块旋转后合法才进行以下操作
						DrawSpace(shape, form, x, y); //用空格覆盖当前方块所在位置
						y++; //纵坐标自增（总不能原地旋转吧）
						form = (form + 1) % 4; //方块的形态自增（下一次显示方块时就相当于旋转了）
					}
					break;
				case ESC: //Esc键
					hdmi_draw_string_back_verticlal(pos.X,pos.Y,"GAME END",255,0);
					CursorJump(COL, ROW / 2 + 2);break;
				}
			}
			DrawBlock(shape, form, x, y);
		}
		if(end == 1){
					end = 0;
					break;
				}
		else if(end == 2){
			end = 0;
			for (int i = 0; i < ROW - 1; i++){
				for (int j = 1; j < COL - 1; j++){
					face.data[i][j] = 0;
					}
				}
				grade = 0;
				InitInterface();
				hdmi_draw_string_back_verticlal((COL + 1)*8,160,"SCORE:",0,255);
			}
		shape = nextShape, form = nextForm; //获取下一个方块的信息
		DrawSpace(nextShape, nextForm, COL + 3, 3); //将右上角的方块信息用空格覆盖
	}
}
