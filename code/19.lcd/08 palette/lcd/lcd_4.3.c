#include "lcd.h"

#define LCD_FB_BASE 0x33c00000

/* 该款4.3寸 LCD参数结构体 */
lcd_params lcd_4_3_params = { 
	.name = "lcd_4.3",
	.pins_pol = {
		.vclk  = NORMAL,  /* normal：下降沿获取数据 */
		.hsync = INVERT, /* normal：高脉冲 */
		.vsync = INVERT, /* normal：高脉冲 */

		.rgb   = NORMAL,   /* normal：高电平表示1 */

		.de    = NORMAL,    /* normal：高电平使能 data enable */
		.pwren = NORMAL, /* normal：高电平使能power enable */
	},
	.time_seq = {
		/* 垂直方向 */
		.tvp = 10, /* Vsync脉冲宽度 */
		.tvb = 2, /* 上边黑框 Vertical Back porch */
		.tvf = 2, /* 下边黑框 Vertical Front porch */

		/* 水平方向 */
		.thp = 41, /* Hsync脉冲宽度 */
		.thb = 2, /* 左边黑框 Horizontal Back porch*/
		.thf = 2, /* 右边黑框 Horizontal Front porch */

		.vclk = 9,/* MHz */
	},
	.xres = 480,
	.yres = 272,
	.bpp  = 8,  /* 16bit or 32bit */
	.fb_base = LCD_FB_BASE,
};





/* 注册4.3寸LCD */
void lcd_4_3_add(void)
{
	register_lcd(&lcd_4_3_params);
}


