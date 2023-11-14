/*
 * newsnake.c
 *
 *  Created on: 2023年11月12日
 *      Author: rana
 */

#include "newsnake.h"

u8 getps2 = 0;
u8 key_val = 0;
u16 score = 0;
u8 quit =0;
void snakeDelay(){
	u32 delaycnt = DELAY_CUT;
	while(delaycnt--){
		getps2 = *ps2ctrl_point;
		if(getps2 != 0) key_val = (getps2>>4);
	}
}
Snake snake;

/*
初始化蛇
*/
void snakeInit(){
	score=0;
	snake.length=3;           //初始长度为3

	snake.snakeX[0]=55;
	snake.snakeX[1]=55;
	snake.snakeX[2]=55;

	snake.snakeY[0]=55;
	snake.snakeY[1]=65;
	snake.snakeY[2]=75;

	snake.headX=snake.snakeX[0]; //记录下头部的位置
	snake.headY=snake.snakeY[0]; //记录下头部的位置
	snake.dir=1;  //设置运动方向
	snake.tpdir=1;//设置初始按键方向

	snake.life=1; //1：蛇还活着；0：蛇死亡

	generateFood();//生成食物

	refresh();    //调用函数显示出蛇和食物的位置
}
/*
每隔一秒将会执行一次，以此实现蛇的运动
*/
void snakeGo(int direct){
	u8 i;
	printk("snake.life:%d",snake.life);
	if(snake.life==1){
		if(abs(direct)!=abs(snake.dir) && direct != 0){	//如果按下的方向不是和运动的方向相同或相反
			snake.dir=direct; //将蛇运动的方向改变为按下的方向
		}else{
			direct=snake.dir;	//蛇运动的方向仍是以前运动的方向
		}
		switch(direct){
			case 1:
				snake.headY-=10;  //上：蛇的身体是有半径为5的圆组成，每运动一格的单位为10
			break;
			case -1:
				snake.headY+=10;  //下：蛇的身体是有半径为5的圆组成，每运动一格的单位为10
			break;
			case 2:
				snake.headX-=10;  //左：蛇的身体是有半径为5的圆组成，每运动一格的单位为10
			break;
			case -2:
				snake.headX+=10;  //右：蛇的身体是有半径为5的圆组成，每运动一格的单位为10
			break;
		}
		if(snake.headX==snake.foodX&&snake.headY==snake.foodY){ //如果吃到了食物
			snake.length++;  //长度加1
			score++;
			for(i=1;i<snake.length;i++){ //除头部以外的坐标前移
				snake.snakeX[snake.length-i]=snake.snakeX[snake.length-i-1];
				snake.snakeY[snake.length-i]=snake.snakeY[snake.length-i-1];
			}
			snake.snakeX[0]=snake.foodX; //头部坐标等于食物的坐标
			snake.snakeY[0]=snake.foodY;
			generateFood();  //再生成一个食物
		}else{
			for(i=1;i<snake.length;i++){
				snake.snakeX[snake.length-i]=snake.snakeX[snake.length-i-1];
				snake.snakeY[snake.length-i]=snake.snakeY[snake.length-i-1];
			}
			snake.snakeX[0]=snake.headX;
			snake.snakeY[0]=snake.headY;
		}
//		printk("snakeX=%d,snakeX=%d\n",snake.snakeX[snake.length-1],snake.snakeY[snake.length-1]);
	}
	if(snake.headY<230&&snake.headY>10&&snake.headX<230&&snake.headX>10&&isNearSelf()){
		snake.life=1;
	}
	else{ //触碰到墙壁游戏结束
		dead();
	}
}
/*
刷新屏幕上蛇和食物的位置
*/

void refresh(){
	if(snake.life==1){
		u8 i;
		hdmi_draw_fill(11,11,229,229,255);
		for(i=0;i<snake.length;i++){//画蛇
			hdmi_draw_dircle_solid(snake.snakeX[i],snake.snakeY[i],5,snakecolor);  //以算的蛇的坐标画半径为5的实心圆
		}
		hdmi_draw_dircle_solid(snake.foodX,snake.foodY,5,36);//画食物
		hdmi_draw_string(250,70,"Score:",17);
		hdmi_draw_num(260,90,score,2,23);
		hdmi_drawrectangle(10,10,230,230,25);
	}
}
/*
开始游戏
*/
/*********************************************
 ** 1000_0000:左
 ** 0100_0000:右
 ** 0010_0000:上
 ** 0001_0000:下
 *********************************************/
void GameStart(){
	hdmi_drawrectangle(10,10,230,230,25);
	hdmi_draw_string(250,70,"Score:",17);
	hdmi_draw_num(260,90,score,2,23);
	snakeInit();
	while(1){
//		getps2 = *ps2ctrl_point;//手柄键值接收
//		key_val = (getps2>>4);//取有效键值
		snakeDelay();
		switch(key_val){
			case 1:snake.tpdir = 1;break;//上
			case 2:snake.tpdir = -1;break;//下
			case 4:snake.tpdir = 2;break;//左
			case 8:snake.tpdir = -2;break;//右
		}
		snakeGo(snake.tpdir);
		if(quit){
			quit = 0;
			break;
		}
		refresh();
	}
}
/*
判断随机产生的食物是否处于蛇体内
*/
u8 isCover(u8 snakeX[],u8 snakeY[],u8 foodX,u8 foodY){
	u8 i;
	for(i=0;i<snake.length;i++){
		if(snakeX[i]==foodX&&snakeY[i]==foodY)
		{
		return 1;
		}
	}
	return 0;
}

/*
判断是否头部是否触碰到自己
*/
u8 isNearSelf(){
	u8 i;
	for(i=1;i<snake.length;i++){
		if(snake.snakeX[i]==snake.headX&&snake.snakeY[i]==snake.headY)
		{
		return 0;
		}
	}
	return 1;
}
/*
产生随机的食物坐标
*/
void generateFood(){
		unsigned int ran=rand()%22+1; //因为贪吃蛇运动区域为10<x<230，10<y<230，取得1到22的随机数
		snake.foodX=(ran*2+1)*5;  //随机数取奇数再乘以5
		ran=rand()%22+1;
		snake.foodY=(ran*2+1)*5;
	while(isCover(snake.snakeX,snake.snakeY,snake.foodX,snake.foodY)){
		ran=rand()%22+1; //因为贪吃蛇运动区域为10<x<230，10<y<230，取得1到22的随机数
		snake.foodX=(ran*2+1)*5;  //随机数取奇数再乘以5
		ran=rand()%22+1;
		snake.foodY=(ran*2+1)*5;
	}

}

/*
在头部撞到墙之后执行死亡程序
*/
void dead(){
	snake.length=0;

	snake.snakeX[0]=0;
	snake.snakeX[1]=0;
	snake.snakeX[2]=0;

	snake.snakeY[0]=0;
	snake.snakeY[1]=0;
	snake.snakeY[2]=0;

	snake.headX=snake.snakeX[0];
	snake.headY=snake.snakeY[0];
	snake.dir=0;

	snake.life=0;
	hdmi_draw_string(80,50,"You dead!!!",20);
	hdmi_draw_string(50,90,"Press any key to quit",24);
	hdmi_draw_string(250,70,"Score:",17);
	hdmi_draw_num(260,90,score,2,23);
	getps2 = 0;
	score = 0;
	while(getps2 == 0){
		getps2 = *ps2ctrl_point;
		if(getps2!=0){
			quit =1;
		}
	}
}
