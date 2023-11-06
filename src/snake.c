/*
 * snake.c
 *
 *  Created on: 2023年11月1日
 *      Author: rana
 */
#include "snake.h"

void HDMI_DrawPoint(u8 x,u8 y,u8 c)
{
	if(c)
		delay(DELAY_CUT,x,y);
  else
	  clear_point(x,y);
}

void draw_point(int x,int y){
	int addr_temp;
	addr_temp = 40*y + x;
	ram_address = addr_temp;
	ram_data_address = POINT;
}

void clear_point(int x,int y){
	int addr_temp;
	int cut_temp = 20;
	addr_temp = 40*y + x;
	while(cut_temp--){
		ram_address = addr_temp;
		ram_data_address = 0;
	}
}
void delay(long d,char x,char y){
	int addr_temp;
	addr_temp = 40*y + x;
	long count = d;
	while(count--){
		ram_address = addr_temp;
		ram_data_address = POINT;
	}
}
//0:R,2:G,3:A,4:M,5:E,6:O,7:V
void draw_c(int x,int y,char c){
	int addr_temp;
	int data_temp;
	addr_temp = 40*y + x;
	data_temp = (c<<4) | (c<<1)+1;
	ram_address = addr_temp;
	ram_data_address = data_temp;
}
void draw_gameover(){
	draw_c(12,15,2);
	draw_c(14,15,3);
	draw_c(16,15,4);
	draw_c(18,15,5);
	draw_c(20,15,6);
	draw_c(22,15,7);
	draw_c(24,15,5);
	draw_c(26,15,0);
}
//保存节点坐标结果体

struct SNAKE
{
  u8 x;//节点x坐标
  u8 y;//节点y坐标
};

struct SNAKE snake_info[50];//蛇节点最多50个
static u8 node_cnt=0;//蛇身长度

static void HDMI_DrawSnakebody(struct SNAKE *buff,u8 cnt,u8 c)
{
    u8 i=0;
    for(i=0;i<cnt;i++)
    {
    	HDMI_DrawPoint(buff[i].x,buff[i].y,c);
    }
}
/**************判断实物位置***************
**
**判断新生成的实物x坐标是否落在蛇身上
**形参:u8 x --实物光标位置
**      cnt  --蛇身节点个数
**返回值：1 --落在蛇身上，0 -- 没有
*******************************************/
static u8 HDMI_GetSnakeFoodX(u8 x,u8 cnt)
{
  u8 i=0;
  for(i=0;i<cnt;i++)
  {
    if(x==snake_info[i].x)break;
  }
  if(i==cnt)return 0;
  else return 1;
}
/**************判断实物位置***************
**
**判断新生成的实物y坐标是否落在蛇身上
**形参:u8 y --实物光标位置
**      cnt  --蛇身节点个数
**返回值：1 --落在蛇身上，0 -- 没有
*******************************************/
static u8 HDMI_GetSnakeFoodY(u8 y,u8 cnt)
{
  u8 i=0;
  for(i=0;i<cnt;i++)
  {
    if(y==snake_info[i].y)break;
  }
  if(i==cnt)return 0;
  else return 1;
}
/*******************动态移动蛇身********************************/
static void Snake_Move(u8 x,u8 y)
{
  u8 i=0;
  draw_point(snake_info[node_cnt-1].x,snake_info[node_cnt-1].y);//显示蛇头节点
  HDMI_DrawPoint(snake_info[0].x,snake_info[0].y,0);//清除蛇尾
  for(i=0;i<node_cnt-1;i++)//节点往前偏移
  {
    snake_info[i].x= snake_info[i+1].x;
    snake_info[i].y=snake_info[i+1].y;

  }
  /*蛇头节点坐标*/
  snake_info[node_cnt-1].x=x;
  snake_info[node_cnt-1].y=y;
  draw_point(snake_info[0].x,snake_info[0].y);//显示蛇头节点
  HDMI_DrawPoint(snake_info[node_cnt-1].x,snake_info[node_cnt-1].y,1);//显示蛇头节点
  printk("x0:%d,y0:%d",snake_info[0].x,snake_info[0].y);
//  HDMI_DrawSnakebody(snake_info,node_cnt,1);
}
/*******************控制方向,判断游戏是否结束********************/
u8 SnakeGameStart(void)
{
  u8 i=0;
  u8 x=15;
  u8 y=15;
  u8 food_x,food_y;
  u8 stat=8;
  char buff[20];
  //创建蛇身1
  snake_info[node_cnt].x=x;
  snake_info[node_cnt].y=y;
  node_cnt++;
  //创建蛇身2
  snake_info[node_cnt].x=x+1;
  snake_info[node_cnt].y=y;
  //保存蛇头坐标
  x=snake_info[node_cnt].x;
  y=snake_info[node_cnt].y;
  node_cnt++;
  snake_info[node_cnt].y = y;
  snake_info[node_cnt].x = x;
  HDMI_DrawSnakebody(snake_info,node_cnt,1);//绘制蛇身
  //生成实物坐标
  food_x=(rand()%40)+1;
  food_y=(rand()%30)+1;
  printk("foodx:%d,foody:%d\n",food_x,food_y);
  food_x = 23;
  food_y = 15;
  HDMI_DrawPoint(food_x,food_y,1);//绘制实物
  int getps2 = *ps2ctrl_point;//手柄键值接收
  u8 key_val = (getps2>>4);//取有效键值
  while(1)
  {
	  snake_info[node_cnt].x=snake_info[node_cnt-1].x;
	  snake_info[node_cnt].y=snake_info[node_cnt-1].y;
	  if(stat&1<<0)
		  snake_info[node_cnt].y=snake_info[node_cnt-1].y-1;
	  else if(stat&1<<1)
		  snake_info[node_cnt].y=snake_info[node_cnt-1].y+1;
	  else if(stat&1<<2)
		  snake_info[node_cnt].x=snake_info[node_cnt-1].x-1;
	  else if(stat&1<<3)
		  snake_info[node_cnt].x=snake_info[node_cnt-1].x+1;
    if(snake_info[node_cnt].x>39 || snake_info[node_cnt-1].y>=29 || snake_info[node_cnt-1].x<1 || snake_info[node_cnt-1].y<1)//判断是否撞墙
    {
//      snprintf(buff,sizeof(buff),"Mark:%d",node_cnt-2);
//      HDMI_DisplayStr(36,8,8,16,buff);//字符串显示
//      HDMI_DisplayStr(10,28,12,24,"Game over");//字符串显示
    	draw_gameover();
    	printk("game over");
      node_cnt=0;//清空节点
      break;//游戏结束
    }
    if(snake_info[node_cnt].x==food_x && snake_info[node_cnt].y==food_y)//判断是否吃到食物
    {
//      if((stat&1<<0) || (stat&1<<1))//向上或向下时y+5
//      {
//        snake_info[node_cnt].x=food_x;
//        snake_info[node_cnt].y=food_y+1;
        if(stat&1<<0) y--;if(stat&1<<1) y++;
//      }
//      else //向左或向右时x+5
//      {
//        snake_info[node_cnt].x=food_x+1;
//        snake_info[node_cnt].y=food_y;
        if(stat&1<<3) x++;if(stat&1<<2) x--;
//      }
      node_cnt++;
//      HDMI_DrawSnakebody(snake_info,node_cnt,1);
      draw_point(snake_info[node_cnt-1].x,snake_info[node_cnt-1].y);//显示蛇头节点
      printk("node_cnt:%d",node_cnt);
      while(1)//保证重新生成的实物不再蛇身上
      {
    	food_x=(rand()%39)+1;
        if(HDMI_GetSnakeFoodX(food_x,node_cnt)==0)break;
      }
      while(1)
      {
    	food_y=(rand()%29)+1;
        if(HDMI_GetSnakeFoodY(food_y,node_cnt)==0)break;
      }
      HDMI_DrawPoint(food_x,food_y,1);//绘制实物
//      printk("foodx:%d,foody:%d\n",food_x,food_y);
    }
    getps2 = *ps2ctrl_point;
    if((getps2>>4)!=0)
    	key_val = (getps2>>4);
//    printk("x:%d,y:%d\n",snake_info[node_cnt-1].x,snake_info[node_cnt-1].y);
    printk("key_val:%x\n",key_val);
    switch(key_val)
    {
      case 0b0001://上
      stat&=~(0x3<<2);//清除左右标志
      if(stat&1<<1){}//向下时不能直接向上
      else
      {
        stat|=1<<0;//向上
        y-=1;
        Snake_Move(x,y);
      }
      break;
      case 0b0010://下
      stat&=~(0x3<<2);//清除左右标志
      if(stat&1<<0){}//在向上时不能直接向下
      else
      {
        stat|=1<<1;//向下标志位
        y+=1;
        Snake_Move(x,y);
      }
      break;
      case 0b0100://左
      stat&=~(0x3<<0);//清除上下标志
      if(stat&1<<3){}//向右时不能直接向左
      else
      {
        stat|=1<<2;//向左
        x-=1;
        Snake_Move(x,y);
      }
      break;
      case 0b1000://右
      stat&=~(0x3<<0);//清除上下标志
      if(stat&1<<2){}//向左时不能直接向右
      else
      {
        stat|=1<<3;
        x+=1;
        Snake_Move(x,y);
      }
      break;
    }
//    Delay_Ms(300);
  }
  return 0;
}
