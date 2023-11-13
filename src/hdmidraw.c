/*
 * hdmidraw.c
 *
 *  Created on: 2023年11月12日
 *      Author: rana
 */
#include "hdmidraw.h"
#include <math.h>
/***************************************************************************
 ** 作用：显示春日影
 ** 参数：x:屏幕x坐标,y:屏幕y坐标
 ** 注:仅用作测试
****************************************************************************/
void hdmi_draw_test(u32 x,u32 y){
	u8 i;u8 j;
	u64 cursor;
	u16 x0 = x; u16 y0 = y;
	for(i = 0;i< 96; i++){
		cursor = bitmap_bytes[i];//春日影
		for(j = 0; j< 8; j++){
			if(((cursor>>(7-j))&0x01)){
				hdmi_draw_point(x0,y0,j);
			}else{
				hdmi_draw_point(x0,y0,0);
			}
			x0++;
			if(x0>319 || x0>47+x){
				x0 = x;y0++;
			}
		}
	}
}

/***************************************************************************
 ** 作用：在320X270的屏幕上画个点
 ** 参数：x:屏幕x坐标,y:屏幕y坐标,color:颜色索引值，取0~255共256位
 ** 注:使用8位索引用来表示颜色（前16位就够用了）第0位为黑色，第255位为白色，可以在windows-设
 **   置-个性化-主题色-查看颜色，后15位为15均分调色板
****************************************************************************/
//color硬件上自行设定
void hdmi_draw_point(u16 x, u16 y, u8 color){
	u64 temp_ramaddress= 0;
	temp_ramaddress = 320*y+x;
	ram_address = temp_ramaddress;
	ram_data_address = color+(0b1<<31);
}
/***************************************************************************
 ** 作用：在270X320的屏幕上画个点
 ** 参数：x:屏幕x坐标,y:屏幕y坐标,color:颜色索引值，取0~255共256位
 ** 注:用于垂直显示,此时(0,0)位于屏幕左上角
****************************************************************************/
void hdmi_draw_point_vertical(u16 x, u16 y, u8 color){
	u64 temp_ramaddress= 0;
	temp_ramaddress = 320*x+(319-y);
	ram_address = temp_ramaddress;
	ram_data_address = color+(0b1<<31);
}
/***************************************************************************
 ** 作用：显示字母，符号
 ** 参数：x:屏幕x坐标,y:屏幕y坐标,c:要显示的字母或符号,color:颜色索引
 ** 注:c仅出现ascii码里的
****************************************************************************/
void hdmi_draw_char(u16 x, u16 y, u8 c, u8 color){
	u8 i;u8 j;
	u8 ch = c - 32;
	u8 cursor;
	u16 x0 = x; u16 y0 = y;
	for(i = 0; i < 16; i++){
		cursor = F8X16[16*ch+i];
		for(j = 0; j< 8; j++){
			if(((cursor>>(7-j))&0x01)){
				hdmi_draw_point(x0,y0,color);
			}else{
				hdmi_draw_point(x0,y0,0);
			}
//			printk("x0:%d,y0:%d\n",x0,y0);
			x0++;
			if(x0>319 || x0>7+x){
				x0 = x;y0++;
			}
		}
	}
}
/***************************************************************************
 ** 作用：显示字母，符号(垂直)
 ** 参数：x:屏幕x坐标,y:屏幕y坐标,c:要显示的字母或符号,color:颜色索引,back:背景颜色索引
 ** 注:用于垂直显示
****************************************************************************/
void hdmi_draw_char_back_vertical(u16 x, u16 y, u8 c, u8 color,u8 back){
	u8 i;u8 j;
	u8 ch = c - 32;
	u8 cursor;
	u16 x0 = x; u16 y0 = y;
	for(i = 0; i < 16; i++){
		cursor = F8X16[16*ch+i];
		for(j = 0; j< 8; j++){
			if(((cursor>>(7-j))&0x01)){
				hdmi_draw_point_vertical(x0,y0,color);
			}else{
				hdmi_draw_point_vertical(x0,y0,back);
			}
			x0++;
			if(x0>269 || x0>7+x){
				x0 = x;y0++;
			}
		}
	}
}
/***************************************************************************
 ** 作用：显示字符串
 ** 参数：x:屏幕x坐标,y:屏幕y坐标,*str:要显示的字母或符号,color:颜色索引,back:背景颜色索引
 ** 注:str仅出现ascii码里的
****************************************************************************/
void hdmi_draw_string(u16 x, u16 y, u8 *str, u8 color){
	u8 i;u8 j;
	u16 x0 = x;u16 y0 = y;
	while((*str<='~')&&(*str>=' ')){
		hdmi_draw_char(x0,y0,*str,color);
		str = str + 1;
		x0 = x0 + 8;
		if(x0>319){
			x0 = x;
			y0 = y0+16;
		}
	}
}
/***************************************************************************
 ** 作用：显示字符串
 ** 参数：x:屏幕x坐标,y:屏幕y坐标,*str:要显示的字母或符号,color:颜色索引
 ** 注:用于垂直坐标
****************************************************************************/
void hdmi_draw_string_back_verticlal(u16 x, u16 y, u8 *str, u8 color,u8 back){
	u8 i;u8 j;
	u16 x0 = x;u16 y0 = y;
	while((*str<='~')&&(*str>=' ')){
		hdmi_draw_char_back_vertical(x0,y0,*str,color,back);
		str = str + 1;
		x0 = x0 + 8;
		if(x0>269){
			x0 = x;
			y0 = y0+16;
		}
	}
}
/***************************************************************************
 ** 作用：用单一颜色清屏
 ** color:颜色索引
 ** 注:
****************************************************************************/
void hdmi_draw_clear(u8 color){
	u32 x=0;
	for(x=0;x<86400;x++){
		ram_address = x;
		ram_data_address = color + (0b1<<31);
	}
}
/***************************************************************************
 ** 作用：显示数字
 ** 参数：x:x坐标,y:y坐标,num要显示的数,len:数的位数,color:颜色索引
 ** 注:
****************************************************************************/
void hdmi_draw_num(u16 x, u16 y, u16 num,u8 len ,u8 color){
	u16 x0 = x+8*(len-1);u16 y0 = y;
	u8 cnt = len;u8 numget = num%10;u16 num2 = num;
	while(cnt--){
		hdmi_draw_char(x0,y0, numget+48,color);
		x0 = x0-8;
		if(x0 < 0){
			x0 = 319;
			y0++;
		}
		num2 = num2/10;
		numget = num2%10;
	}
}
/***************************************************************************
 ** 作用：显示数字
 ** 参数：x:x坐标,y:y坐标,num要显示的数,len:数的位数,color:颜色索引
 ** 注:用于垂直垂直坐标
****************************************************************************/
void hdmi_draw_num_back_vertical(u16 x, u16 y, u16 num,u8 len ,u8 color,u8 back){
	u16 x0 = x+8*(len-1);u16 y0 = y;
	u8 cnt = len;u8 numget = num%10;u16 num2 = num;
	while(cnt--){
		hdmi_draw_char_back_vertical(x0,y0, numget+48,color,back);
		x0 = x0-8;
		if(x0 < 0){
			x0 = 269;
			y0++;
		}
		num2 = num2/10;
		numget = num2%10;
	}
}
/***************************************************************************
 ** 作用：填充颜色块
 ** 参数：sx:屏幕左上角x坐标,sy:屏幕左上角y坐标,ex:屏幕右下角x坐标,ey:屏幕右下角y坐标,
 ** 	color:颜色索引
 ** 注:
****************************************************************************/
void hdmi_draw_fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{
	u16 i,j;
	u16 x0 = sx;u16 y0 = sy;
	u16 xlen=0;
	xlen=ex-sx+1;
	for(i=sy;i<=ey;i++)
	{
		for(j=0;j<xlen;j++){
			hdmi_draw_point(x0,y0,color);
			x0++;
		}
		x0 = sx;
		y0++;
	}
}
/***************************************************************************
 ** 作用：画个矩形
 ** 参数：x:屏幕左上角x坐标,y:屏幕左上角y坐标,len:长度
 ** 	color:颜色索引
 ** 注:垂直坐标
****************************************************************************/
void hdmi_draw_square_vertical(u16 x,u16 y,u16 len,u8 color){
	u16 x0=x;u16 y0=y;
	u16 i,j;
	for(i=0;i<len;i++)
	{
		for(j=0;j<len;j++){
			hdmi_draw_point_vertical(x0,y0,color);
			x0++;
		}
		x0 = x;
		y0++;
	}
}
/***************************************************************************
 ** 作用：线
 ** 参数：x1:x起始坐标,y1:y起始坐标,color:颜色索引
 ** 注:
****************************************************************************/
void hdmi_drawLine(u16 x1, u16 y1, u16 x2, u16 y2,u8 color)
{
	u16 t;
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1;
	delta_y=y2-y1;
	uRow=x1;
	uCol=y1;
	if(delta_x>0)incx=1;
	else if(delta_x==0)incx=0;
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;
	else{incy=-1;delta_y=-delta_y;}
	if( delta_x>delta_y)distance=delta_x;
	else distance=delta_y;
	for(t=0;t<=distance+1;t++ )
	{
		hdmi_draw_point(uRow,uCol,color);
		xerr+=delta_x ;
		yerr+=delta_y ;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}
/***************************************************************************
 ** 作用：线
 ** 参数：x3:x起始坐标,y3:y起始坐标,color:颜色索引
 ** 注:用于垂直坐标的划线
****************************************************************************/
void hdmi_drawLine_vertical(u16 x1, u16 y1, u16 x2, u16 y2,u8 color){
	u16 t;
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1;
	delta_y=y2-y1;
	uRow=x1;
	uCol=y1;
	if(delta_x>0)incx=1;
	else if(delta_x==0)incx=0;
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;
	else{incy=-1;delta_y=-delta_y;}
	if( delta_x>delta_y)distance=delta_x;
	else distance=delta_y;
	for(t=0;t<=distance+1;t++ )
	{
		hdmi_draw_point_vertical(uRow,uCol,color);
		xerr+=delta_x ;
		yerr+=delta_y ;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}
/***************************************************************************
 ** 作用：画圆
 ** 参数：x0:x坐标,y0:y坐标,r:半径
 ** 注:
****************************************************************************/
void hdmi_draw_dircle_solid_vertical(u16 x0,u16 y0,u8 r,u8 color)
{
	int a,b;
	int di;
	a=0;b=r;
	di=3-(r<<1);
	while(a<=b)
	{
		hdmi_drawLine_vertical(x0+a,y0-b,x0+a,y0+b,color);             //5
		hdmi_drawLine_vertical(x0+b,y0-a,x0+b,y0+a,color);             //0
		hdmi_drawLine_vertical(x0-a,y0-b,x0-a,y0+b,color);             //4
		hdmi_drawLine_vertical(x0-b,y0-a,x0-b,y0+a,color);             //6
		a++;

		if(di<0)di +=4*a+6;
		else
		{
			di+=10+4*(a-b);
			b--;
		}
	}

}
/***************************************************************************
 ** 作用：画圆
 ** 参数：x0:x坐标,y0:y坐标,r:半径
 ** 注:
****************************************************************************/
void hdmi_draw_dircle_solid(u16 x0,u16 y0,u8 r,u8 color)
{
	int a,b;
	int di;
	a=0;b=r;
	di=3-(r<<1);
	while(a<=b)
	{
		hdmi_drawLine(x0+a,y0-b,x0+a,y0+b,color);             //5
		hdmi_drawLine(x0+b,y0-a,x0+b,y0+a,color);             //0
		hdmi_drawLine(x0-a,y0-b,x0-a,y0+b,color);             //4
		hdmi_drawLine(x0-b,y0-a,x0-b,y0+a,color);             //6
		a++;

		if(di<0)di +=4*a+6;
		else
		{
			di+=10+4*(a-b);
			b--;
		}
	}

}
/***************************************************************************
 ** 作用：画矩形
 ** 参数：x1:x坐标,y1:y坐标
 ** 注:
****************************************************************************/
void hdmi_drawrectangle(u16 x1, u16 y1, u16 x2, u16 y2,u8 color)
{
	hdmi_drawLine(x1,y1,x2,y1,color);
	hdmi_drawLine(x1,y1,x1,y2,color);
	hdmi_drawLine(x1,y2,x2,y2,color);
	hdmi_drawLine(x2,y1,x2,y2,color);
}
