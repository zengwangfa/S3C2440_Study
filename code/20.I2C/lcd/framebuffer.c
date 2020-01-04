
#include "lcd.h"

static int xres,yres,bpp;
static unsigned int fb_base;


void fb_get_lcd_params(void)
{
	get_lcd_params(&fb_base,&xres,&yres,&bpp);
}

/* rgb:0xRRGGBB 
 * ret: rgb565
*/
unsigned short convert32bppto16bpp(unsigned int rgb)
{
	int r = (rgb >> 16) & 0xFF;
	int g = (rgb >> 8 ) & 0xFF;
	int b = rgb & 0xFF;

    /* RGB 565 */
	r = r >> 3;
	g = g >> 2;
	b = b >> 3;
	return (unsigned short)((r<<11) | (g<<5) | (b));
}

/* 画点
 * color为32bit，即0xRRGGBB
 * 
*/
void fb_draw_dot(int x,int y,unsigned int color)
{
	unsigned char *pc;  /* 8bpp  */
	unsigned short *pw; /* 16bpp */
	unsigned int *pdw;  /* 32bpp */

	/* 获取(x,y)像素起始地址*/
	unsigned int dot_base = fb_base + (xres * bpp / 8) *y + x * bpp / 8;

	switch(bpp){
		case 8:
			pc = (unsigned char *)dot_base;
			*pc = color;
			break;
		case 16:
			pw = (unsigned short *)dot_base;
			*pw = convert32bppto16bpp(color);
			break;
		case 32:
			pdw = (unsigned int *)dot_base;
			*pdw = color;
			break;		


	}

}

