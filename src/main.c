#include "uart.h"
#include "snake.h"

#define led_address 			(*(volatile uint32_t*)0x00008020)
#define gpio_address 			(*(volatile uint32_t*)0x00008030)
#define gpio_point   			(volatile uint32_t*)0x00008030

#define rgb_out_address				(*(volatile uint32_t*)0x00008040)
#define rgb_in_address				(*(volatile uint32_t*)0x00008050)
#define rgb_point				    (volatile uint32_t*)0x00008050
//
#define user_block_u_address		(*(volatile uint32_t*)0x00008080)
#define user_block_d_address		(*(volatile uint32_t*)0x00008090)

//
//#define rgb_r_out				(*(volatile uint32_t*)0x00008090)
//#define rgb_g_out				(*(volatile uint32_t*)0x000080A0)
//#define rgb_b_out				(*(volatile uint32_t*)0x000080B0)

//系统时钟↓
#define SYSTEM_CNT_M			50			//系统时钟单位：MHz

#define SYSTEM_CLOCK			SYSTEM_CNT_M*1000000UL
#define BAUND_9600				((SYSTEM_CLOCK)/9600)
#define BAUND_115200			(SYSTEM_CLOCK/115200)
#define GPIO_DATA				0xaa55
#define LED_DELAY				500000UL


int temp_data = 0;
int uart_data = 0;
int delaycnt = 0;
long rgb_data = 0xffcc11;//这里更改颜色，前两位r中间g后两位b
long rgb_data_get_test = 0;

void led_blink(void);
/********************************************************************
 ** 函数名称：led_blink
 ** 函数功能：led blin测试（采用计数器的方式）
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void led_blink(void)
{
//	long rgb_count = 0;
//	char c;
//	int cnt = 0;
//	int count = 0;
//	temp_data = *gpio_point;
//	if(GPIO_DATA == temp_data)
//	{
//		printk("gpio success\n");
//	}
//	else
//	{
//		printk("gpio failed\n");
//	}
//
//	led_address = 0xff;
//	while(1)
//	{
//		cnt++;
//		if(cnt == LED_DELAY / 2)
//		{
//			count++;
//
//
////			printk("%s",get_uart_data);
////			led_address = 0x00;
//			printk("half\n");
//			printk("%x,%d\n",rgb_data,count);
//		}
//		else if(cnt == LED_DELAY)
//		{
//			cnt = 0;
////			rgb_data_get_test = *rgb_point;
//			if (rgb_data_get_test == rgb_data)
//				printk("risc-v has found rgb_adress");
//			else printk("%x",rgb_data_get_test);
//		}
//		rgb_out_address = rgb_data;
//	}
}

void ps2_test(){
	int getps2 = *ps2ctrl_point;
	printk("getps2 = %d\n",getps2);
}

void gpio_test(){
	int count = 0;
	temp_data = *gpio_point;
	if(GPIO_DATA == temp_data)
	{
		printk("gpio success\n");
	}
	else
	{
		printk("gpio failed\n");
	}
	while(1){
		count++;
		if(count == 10000){
			count = 0;
			printk("test\n");
		}
	}
}


void rgb_test(){
	int addr = 0;
	int data = 0;
	int cut = 0;
	data= POINT;
	ram_address = addr;
	ram_data_address = data;
	delay(DELAY_CUT,1,1);
	delay(DELAY_CUT,2,1);
	clear_point(1,1);
	delay(DELAY_CUT,18,21);
	delay(DELAY_CUT,3,1);
	clear_point(2,1);
	delay(DELAY_CUT,4,1);
	clear_point(3,1);
	delay(DELAY_CUT,5,1);
	clear_point(4,1);
	delay(DELAY_CUT,6,1);
	clear_point(5,1);
	while(1){
		cut++;
		if(cut==1000000){
			cut = 0;
			addr++;
			printk("addr:%x",addr);
		}
		ram_address = addr;
		ram_data_address = 0b00100011;
	}
}

void block_test(){
	draw_c(8,5,2);
	draw_c(10,5,3);
	draw_c(12,5,4);
	draw_c(14,5,5);
	draw_c(16,5,6);
	draw_c(18,5,7);
	draw_c(20,5,5);
	draw_c(22,5,0);
}

int main(void)
{
	reg_uart_clkdiv = BAUND_9600;
	printk("Hello Risc-V Pango 2019\n");
	printk("test data = %d,%f,%s,0x = %x\n", 100,33.456,"2019",100);
	printk("simple compute : 50*10 = %d,100/3 = %f,100%3 = %d\n", 50*10,(double)100/3,(int)100%3);
	printk("test\n");
	int cutx = 0;int cuty = 0;
//	gpio_test();
//	rgb_test();
//	delay(10000,40,15);
//	clear_point(40,15);
	ps2_test();
//	block_test();
	u8 getps2 = *ps2ctrl_point;
loop:
	SnakeGameStart();
	while(getps2 != 0b00000010){
		getps2 = *ps2ctrl_point;
		if(getps2 == 0b00000010){
			for(cuty = 0;cuty<30;cuty++){
				for(cutx = 0;cutx<40;cutx++)
					clear_point(cutx,cuty);
			}
			break;
		}
	}//X
	getps2 = 0;
	goto loop;
	return 0;
}






