
#include "lcd.h"

#define RED_BPP 0xF800 //全红bpp格式
static int xres,yres,bpp;
static unsigned int fb_base;



/* 填充屏幕指定颜色*/
void fill_lcd_corlor_16bpp(unsigned int fb_base,unsigned int color)
{
	static int x,y;
	static unsigned short *p_16bpp;

	p_16bpp = (unsigned short *)fb_base;
	for (x = 0; x < xres; x++){
		for (y = 0; y < yres; y++){
			*p_16bpp++ = color;			
		}
	}
}

/* 填充屏幕指定颜色*/
void fill_lcd_corlor_32bpp(unsigned int fb_base,unsigned int color)
{
	static int x,y;
	static unsigned int *p_32bpp;

	p_32bpp = (unsigned int *)fb_base;
	for (x = 0; x < xres; x++){
		for (y = 0; y < yres; y++){
			*p_32bpp++ = color;			
		}
	}
}


void lcd_test(void)
{
	/* lcd初始化 */ 
	lcd_init();

	/* lcd使能 */
	lcd_enable();

    /* 获得LCD的参数，*/
	get_lcd_params(&fb_base,&xres,&yres,&bpp);
	fb_get_lcd_params();
	
	printf("fb_base: 0x%x,x: %d,yres: %d",fb_base,xres,yres);
	/* 往FrameBuffer中写数据 */



	if(16 == bpp){
		/* 让LCD输出正屏的红色,即RGB中的R为全为1 */
		/* 565： 0xF800 */
		fill_lcd_corlor_16bpp(fb_base,0xF800);

		/* green */
		fill_lcd_corlor_16bpp(fb_base,0x7e0);
		/* blue */
		fill_lcd_corlor_16bpp(fb_base,0x1f);

	}
	else if(32 == bpp){
		//0xRRGGBB
		/* red */
		fill_lcd_corlor_32bpp(fb_base,0xFF0000);

		/* green */
		fill_lcd_corlor_32bpp(fb_base,0x00FF00);

		/* blue */
		fill_lcd_corlor_32bpp(fb_base,0x0000FF);

		/* black */
		fill_lcd_corlor_32bpp(fb_base,0x000000);	
	}

	/* 画线 */
	draw_line(0, 0, xres - 1, 0, 0xff0000);
	draw_line(xres - 1, 0, xres - 1, yres - 1, 0xffff00);
	draw_line(0, yres - 1, xres - 1, yres - 1, 0xff00aa);
	draw_line(0, 0, 0, yres - 1, 0xff00ef);
	draw_line(0, 0, xres - 1, yres - 1, 0xff4500);
	draw_line(xres - 1, 0, 0, yres - 1, 0xff0780);

	/* 画圆 */
	draw_circle(xres/2, yres/2, yres/4, 0xff00);
	
}


