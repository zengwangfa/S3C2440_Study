#ifndef _FRAME_BUFFER_H
#define _FRAME_BUFFER_H


void fb_get_lcd_params(void);
void fb_draw_dot(int x,int y,unsigned int color);

unsigned short convert32bppto16bpp(unsigned int rgb);
#endif /*_FRAME_BUFFER_H  */

