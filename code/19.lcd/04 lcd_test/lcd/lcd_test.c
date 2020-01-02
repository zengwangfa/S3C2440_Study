
#include "lcd.h"

#define RED_BPP 0xF800 //全红bpp格式

void lcd_test(void)
{
	unsigned int fb_base;
	unsigned short *p;
	int xres,yres,bpp;
	int x,y;
	printf("test2");
	/* lcd初始化 */ 
	lcd_init();

	/* lcd使能 */
	lcd_enable();

    /* 获得LCD的参数，*/
	get_lcd_params(&fb_base,&xres,&yres,&bpp);
	printf("fb_base: 0x%x,x: %d,yres: %d",fb_base,xres,yres);
	/* 往FrameBuffer中写数据 */

		/* 让LCD输出正屏的红色,即RGB中的R为全为1 */
		/* 565： 0xF800 */

	if(16 == bpp){
		p = (unsigned short *)fb_base;
		for (x = 0; x < xres; x++)
			for (y = 0; y < yres; y++)
				*p++ = 0xf800;

		/* green */
		p = (unsigned short *)fb_base;
		for (x = 0; x < xres; x++)
			for (y = 0; y < yres; y++)
				*p++ = 0x7e0;

		/* blue */
		p = (unsigned short *)fb_base;
		for (x = 0; x < xres; x++)
			for (y = 0; y < yres; y++)
				*p++ = 0x1f;
	}
	
}