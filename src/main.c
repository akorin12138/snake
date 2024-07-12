#include <stdint.h>
#include <stdlib.h>
#include "sys.h"

int uart_data = 0;
int delaycnt = 0;
void delay(){
	u16 cnt=1000;
	while(cnt--){
		led_address=0;
	}
}
int main(void)
{
	reg_uart_clkdiv = BAUND_9600;
	printk("Hello Risc-V Pango 2019\n");
	printk("test data = %d,%f,%s,0x = %x\n", 100,33.456,"2019",100);
	printk("simple compute : 50*10 = %d,100/3 = %f,100%3 = %d\n", 50*10,(double)100/3,(int)100%3);
	printk("test\n");
	hdmi_draw_clear(255);
	hdmi_drawziguang(120,20,PURPLE,255);
	u8 temp;
	temp = sound_address;
	printk("%d",temp);
	hdmi_draw_string_back(60,180,"Snake Go!",ORANGE,255);
	hdmi_draw_string_back(60,196,"Tetris Go!",ORANGE,255);
	hdmi_draw_string_back(60,212,"Board Go!",ORANGE,255);
	hdmi_drawtriangle(49,180,PURPLE,255);
	hdmi_drawquwei(100,100,PINK,255);
	u8 Oldkey,Newkey =0;
	u16 Oldy,Newy =180;
	u8 choose_val=0;
	sound_address = 0b1111111;
	while(1){
		Oldkey=Newkey;
		Newkey = *ps2ctrl_point;
		if(Newkey != Oldkey){
			if(Newkey == 0b00010000){//上
				if(choose_val!=0){
					Oldy = Newy;
					Newy = Newy-16;
					choose_val--;
					}
				}
				else if(Newkey == 0b00100000){
					if(choose_val<2){//修改1来增加选择项
						Oldy = Newy;
						Newy = Newy+16;
						choose_val++;
					}
				}
				hdmi_drawtriangle(49,Newy,PURPLE,255);
				hdmi_drawtriangle(49,Oldy,255,255);
			}
		if(choose_val == 0) rgb_address = 0b0000010;
		else if(choose_val == 1)  rgb_address = 0b0000001;
		else if(choose_val == 2)  rgb_address = 0b0000000;

		if(Newkey == 0b00000010){
			if(choose_val == 0){
				GameStart();
				hdmi_draw_clear(255);
				hdmi_draw_string_back(60,180,"Snake Go!",ORANGE,255);
				hdmi_draw_string_back(60,196,"Tetris Go!",ORANGE,255);
				hdmi_draw_string_back(60,212,"Board Go!",ORANGE,255);
				hdmi_drawtriangle(49,180,PURPLE,255);
				hdmi_drawziguang(120,20,PURPLE,255);
				hdmi_drawquwei(100,100,PINK,255);
			}else if(choose_val == 1){
				Tetris();
				hdmi_draw_clear(255);
				hdmi_draw_string_back(60,180,"Snake Go!",ORANGE,255);
				hdmi_draw_string_back(60,196,"Tetris Go!",ORANGE,255);
				hdmi_draw_string_back(60,212,"Board Go!",ORANGE,255);
				hdmi_drawtriangle(49,196,PURPLE,255);
				hdmi_drawziguang(120,20,PURPLE,255);
				hdmi_drawquwei(100,100,PINK,255);
			}
			else if(choose_val == 2){
				app_demo();
				hdmi_draw_clear(255);
				hdmi_draw_string_back(60,180,"Snake Go!",ORANGE,255);
				hdmi_draw_string_back(60,196,"Tetris Go!",ORANGE,255);
				hdmi_draw_string_back(60,212,"Board Go!",ORANGE,255);
				hdmi_drawtriangle(49,212,PURPLE,255);
				hdmi_drawziguang(120,20,PURPLE,255);
				hdmi_drawquwei(100,100,PINK,255);
			}
		}
	}
	return 0;
}
