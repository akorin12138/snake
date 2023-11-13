/*
 * hdmidraw.h
 *
 *  Created on: 2023年11月12日
 *      Author: rana
 */

#ifndef HDMIDRAW_H_
#define HDMIDRAW_H_
#include <math.h>
#include "sys.h"
typedef   uint64_t   u64;   ///32位
typedef   uint32_t   u32;   ///32位
typedef   uint16_t   u16;   ///16位
typedef   uint8_t     u8;   ///8位

void hdmi_draw_clear(u8 color);
void hdmi_draw_point(u16 x, u16 y, u8 color);
void hdmi_draw_test(u32 x,u32 y);
void hdmi_draw_char(u16 x, u16 y, u8 c, u8 color);
void hdmi_draw_string(u16 x, u16 y, u8 *str, u8 color);
void hdmi_draw_fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
void hdmi_drawLine(u16 x1, u16 y1, u16 x2, u16 y2,u8 color);
void hdmi_draw_dircle_solid(u16 x0,u16 y0,u8 r,u8 color);
void hdmi_drawrectangle(u16 x1, u16 y1, u16 x2, u16 y2,u8 color);
void hdmi_draw_num(u16 x, u16 y, u16 num,u8 len ,u8 color);
/******************下面函数用于垂直坐标*****************************************/
void hdmi_draw_point_vertical(u16 x, u16 y, u8 color);
void hdmi_draw_char_back_vertical(u16 x, u16 y, u8 c, u8 color,u8 back);
void hdmi_drawLine_vertical(u16 x3, u16 y3, u16 x4, u16 y4,u8 color);
void hdmi_draw_string_back_verticlal(u16 x, u16 y, u8 *str, u8 color,u8 back);
void hdmi_draw_num_back_vertical(u16 x, u16 y, u16 num,u8 len ,u8 color,u8 back);
void hdmi_draw_square_vertical(u16 x,u16 y,u16 len,u8 color);
#endif /* HDMIDRAW_H_ */
