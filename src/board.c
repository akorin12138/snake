#include "board.h"
#include "newsnake.h"
/***************************************************************************
 ** 作用：画圆
 ** 参数：x0:x坐标,y0:y坐标,r:半径
 ** 注:
****************************************************************************/

u8 ps2key = 0;
u8 boardps2 = 0;

//砖块类型
struct ZK
{
	//左上角点坐标
	int x,y;
	//砖块宽高
	int w,h;
	u16 color;

	u8 isLive;//是否存在
};

struct BZ
{
	//左上角点坐标
	int x,y;
	//板子宽高
	int w,h;
	u16 color;
};

//球类型
struct Ball
{
	//圆心坐标
	int x,y;
	//半径
	int radius;
	u16 color;
	int xfx,yfx;//移动数据
	//xfx为正往右  为负往左
	//yfx为正往下  为负往上
};

//描述砖块的数组
struct ZK zk[ROWS][COLS];
struct BZ bz;
struct Ball ball;
u8 isContinue=1;

//游戏参数
u8 glevel=1;//游戏关卡
u32 gscore=0;//游戏得分

u32 gtime_cnt=0;

u16 gcolor[7]={RED,ORANGE,YELLOW,GREEN,BLUE,PURPLE,PINK};

//初始化球
void initBall()
{
	ball.radius=RADIUS;
	ball.x=WINDOW_WIDTH/2+START_X;
	ball.y=WINDOW_HEIGHT-BZ_HEIGHT-RADIUS+START_Y;
	ball.color=BLUE;

	ball.xfx=SPACE;
	ball.yfx=-SPACE;

}

void initBz()
{
	bz.w=BZ_WIDTH;
	bz.h=BZ_HEIGHT;
	bz.color=RED;
	bz.x=(WINDOW_WIDTH-BZ_WIDTH)/2+START_X;
	bz.y=WINDOW_HEIGHT-BZ_HEIGHT+START_Y;
}

void initZk()
{
	int i,j;
	for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLS;j++)
		{
			zk[i][j].x=j*ZK_WIDTH+START_X;
			zk[i][j].y=i*ZK_HEIGHT+START_Y;

			zk[i][j].w=ZK_WIDTH;
			zk[i][j].h=ZK_HEIGHT;

			zk[i][j].color=gcolor[rand()%7];
			zk[i][j].isLive=1;//砖块存活
		}
	}
}
void delayBall(){

}
void drawBall()
{
	hdmi_draw_dircle_solid_vertical(ball.x,ball.y,ball.radius,ball.color);
	//delay_ms(100);记得加延时
	u32 delaycnt = 50000;
			while(delaycnt--){
				boardps2 = *ps2ctrl_point;
				if(boardps2 != 0) ps2key = (boardps2>>4);
			}
}

void drawBz()
{
	hdmi_draw_fill_vertical(bz.x,bz.y,bz.x+BZ_WIDTH,bz.y+BZ_HEIGHT,bz.color);
	hdmi_drawrectangle_vertical(bz.x,bz.y,bz.x+BZ_WIDTH,bz.y+BZ_HEIGHT,WHITE);
}

void drawZK(int i,int j)
{
	hdmi_draw_fill_vertical(zk[i][j].x,zk[i][j].y,zk[i][j].x+ZK_WIDTH,zk[i][j].y+ZK_HEIGHT,zk[i][j].color);
	hdmi_drawrectangle_vertical(zk[i][j].x,zk[i][j].y,zk[i][j].x+ZK_WIDTH,zk[i][j].y+ZK_HEIGHT,WHITE);
}

void drawAllZk()
{
	int i,j;
	for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLS;j++)
		{
			if(zk[i][j].isLive)
				drawZK(i,j);
		}
	}
}

void ball_move()
{
	hdmi_draw_dircle_solid_vertical(ball.x,ball.y,ball.radius,GRAY);

	ball.x+=ball.xfx;
	ball.y+=ball.yfx;
}

void check()
{
	int i,j;
	//撞上右边墙壁
	if(ball.x>=(WINDOW_WIDTH-RADIUS+START_X))
	{
		sound_address = 0b1111011;
		ball.xfx=-SPACE;
	}
	//撞上左边墙壁
	if(ball.x<=RADIUS+START_X)
	{
		sound_address = 0b1111011;
		ball.xfx=SPACE;
	}
	//撞上上边墙壁
	if(ball.y<=RADIUS+START_Y)
	{
		sound_address = 0b1111011;
		ball.yfx=SPACE;
	}
	//撞上下边墙壁
	if(ball.y>=(WINDOW_HEIGHT-RADIUS+START_Y))
	{
		isContinue=0;
	}

	//撞上板子
	if(ball.y>=(WINDOW_HEIGHT-RADIUS-BZ_HEIGHT+START_Y)&&
		ball.x>=bz.x+START_X &&
		ball.x<=(bz.x+BZ_WIDTH+START_X))
	{
		sound_address = 0b1111011;
		ball.yfx=-SPACE;
	}

	for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLS;j++)
		{
			if(zk[i][j].isLive&&
				ball.y<=(zk[i][j].y+ZK_HEIGHT+RADIUS)&&
				ball.x>=zk[i][j].x &&
				ball.x<=(zk[i][j].x+ZK_WIDTH))
			{
				zk[i][j].isLive=0;//砖块变为不存活
				ball.yfx=SPACE;//球方向改变
				hdmi_draw_fill_vertical(zk[i][j].x,zk[i][j].y,zk[i][j].x+ZK_WIDTH,zk[i][j].y+ZK_HEIGHT,GRAY);
				gscore+=10;//得分
			}
		}
	}
}

void bz_moveLeft()
{
	hdmi_draw_fill_vertical(bz.x,bz.y,bz.x+BZ_WIDTH,bz.y+BZ_HEIGHT,GRAY);
	if(bz.x>=BZ_SPACE+START_X-5)
		bz.x-=BZ_SPACE;
}

void bz_moveRight()
{
	hdmi_draw_fill_vertical(bz.x,bz.y,bz.x+BZ_WIDTH,bz.y+BZ_HEIGHT,GRAY);
	if(bz.x<=WINDOW_WIDTH-BZ_WIDTH-BZ_SPACE+START_X+5)
		bz.x+=BZ_SPACE;
}

void keyCtol()
{
	switch(ps2key)
	{
		case 4:
			bz_moveLeft();
			break;
		case 8:
			bz_moveRight();
			break;
	}
}

void initGame()
{
	srand(gtime_cnt);//设置随机算子
	//1、做窗口
	hdmi_drawrectangle_vertical(START_X,START_Y,START_X+WINDOW_WIDTH,START_Y+WINDOW_HEIGHT,WHITE);
	initZk();
	initBz();
	initBall();
	isContinue=1;

	drawAllZk();
	drawBz();
	drawBall();
}

void showGame()
{
	hdmi_drawrectangle_vertical(START_X,START_Y,START_X+WINDOW_WIDTH,START_Y+WINDOW_HEIGHT,WHITE);
	drawBz();
	drawBall();
	hdmi_draw_num_back_vertical(START_X+32*3,WINDOW_HEIGHT+START_Y+20,gscore,5,WHITE,GRAY);
}

void ctolGame()
{
	ball_move();
	check();
	keyCtol();
}

void app_demo(void)
{
	rgb_address = 0b0000000;
	gscore=0;
	hdmi_draw_clear(GRAY);
	initGame();
	while(isContinue)
	{
		showGame();
		sound_address = 0b1111111;
		ctolGame();
	}
	if(!isContinue){
		rgb_address = 0b0000110;
		sound_address = 0b1011111;
		drawBz();
		hdmi_draw_string_back_verticlal(50,100,"GAME OVER",RED,WHITE);
		hdmi_draw_string_back_verticlal(50,120,"PRESS ANY KEY TO QUIT",RED,WHITE);
		boardps2 = 0;
		while(boardps2 == 0){
			boardps2 = *ps2ctrl_point;
			if(boardps2 == 0B00000010){
				sound_address = 0b1111111;
				break;
			}
		}
	}
}

