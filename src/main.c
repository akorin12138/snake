#include <stdint.h>
#include <stdlib.h>
#include "sys.h"

int uart_data = 0;
int delaycnt = 0;

/********************************************************************
 ** 函数名称：led_blink
 ** 函数功能：led blin测试（采用计数器的方式）
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/

void ps2_test(){
	int getps2 = *ps2ctrl_point;
	printk("getps2 = %d\n",getps2);
}


void draw_point_test(int x,int y){
	u32 addr_temp;
	u32 data_temp;
	addr_temp = 40*y + x;
	ram_address = addr_temp;
	ram_data_address = 0b00010011+(0b1<<31);
	data_temp = 0b00010011+(0b1<<31);
	printk("we_valid:%d",data_temp>>31);
}

void rgb_test(){
	u32 cut = 0;
	u32 addr = 0;
	u32 color = 0;
	u32 i;
	for(i = 0;i < 86400;i++){
		ram_address = i;
		ram_data_address = (0+(0b1<<31));
	}
	ram_address = 0;
	ram_data_address = (5+(0b1<<31));
	ram_address = 50;
	ram_data_address = (50+(0b1<<31));
	ram_address = 20000;
	ram_data_address = (150+(0b1<<31));
	hdmi_draw_point(20,50,1);
	hdmi_draw_point(20,60,2);
	hdmi_draw_point(20,70,3);
	hdmi_draw_point(20,80,4);
//	while(1){
//		cut ++;
//		if(cut == 100000){
//			cut = 0;
//			addr++;
//			color++;
//			if(color == 0xff) color = 0;
//			printk("color:%x\n",(color+1)*(0xffff+1));
//			ram_address = addr;
//			ram_data_address = (color+(0b1<<31));
//		}
//	}
}

int main(void)
{
	reg_uart_clkdiv = BAUND_9600;
	printk("Hello Risc-V Pango 2019\n");
	printk("test data = %d,%f,%s,0x = %x\n", 100,33.456,"2019",100);
	printk("simple compute : 50*10 = %d,100/3 = %f,100%3 = %d\n", 50*10,(double)100/3,(int)100%3);
	printk("test\n");

	GameStart();
//loop:
//	SnakeGameStart();
//	while(getps2 != 0b00000010){
//		getps2 = *ps2ctrl_point;
//		if(getps2 == 0b00000010){
//			for(cuty = 0;cuty<30;cuty++){
//				for(cutx = 0;cutx<40;cutx++)
//					clear_point(cutx,cuty);
//			}
//			break;
//		}
//	}//X
//	getps2 = 0;
//	goto loop;
	return 0;
}






