
#include "lcd_controller.h"

#define HCLK 100  //HCLK -> 100M

/* 初始化LCD引脚 */
void jz2440_pin_init(void)
{
	/* 初始化 背光引脚： GPB0 */
	GPBCON &= ~0x03;
	GPBCON |= 0x01;  //输出模式

	/* 初始化LCD专用引脚  */
	GPCCON = 0xAAAAAAAA;
	GPDCON = 0xAAAAAAAA;

	/* 电源引脚 LCD_PWRDN */
	GPGCON |= (3<<8);
}


/* 具体的lcd控制器初始化
*/
void s3c2240_lcd_controller_init(p_lcd_params plcdparams);
{
	int pixelformat;//像素存储格式
	unsigned int fb_addr;//fb地址

	jz2440_pin_init();

	/* LCDCON1[17:8] : CLKVAL, vclk = HCLK/[(CLKVAL+1)*2] 
	 *                              = 100M/[(CLKVAL+1)*2]
	 *						   CLKVAL = 100/vclk/2 - 1 , vclk
 	 * [6:5]：0b11，TFT LCD
 	 * [4:1]：bpp mode
 	 * [0]  ：LCD video output and the logic enable(1)/disable(0)
	*/
	int clkval  = (double)100/plcdparams->time_seq.vclk/2 - 1 + 0.5;
	int bppmode = (plcdparams ==  8) ? 0x0B :\ //8bpp
				  (plcdparams == 16) ? 0x0C :\ //16bpp
				  0x0D; //24bpp 

	LCDCON1 = (clkval << 8) | (3 << 5) | (bppmode << 1);

	/*  垂直
	 *  [31:24] ：VBPD    = Tvb - 1
	 *  [23:14] ：LINEVAL = line - 1  纵向像素点
	 *  [13:6]  ：VFPD    = Tvf - 1 
	 *  [5:0]	：VSPW 	  = Tvp -1 帧脉冲宽度
	 */
	LCDCON2 = ((plcdparams->time_seq.tvb -1) << 24) | \
			  ((plcdparams->yres -1) << 14) 		| \
			  ((plcdparams->time_seq.tvf -1) << 6 ) | \
		  	  ((plcdparams->time_seq.tvp -1) << 0 );

	/*  水平	  	  
	 *  [31:19] ：HBPD    = Thb - 1
	 *  [18:8]  ：HOZVAL  = 列 - 1  横向像素点
	 *  [7:0]   ：HFPD    = Thf - 1 
	 */
	LCDCON3 = ((plcdparams->time_seq.thb -1) << 19) | \
			  ((plcdparams->xres -1) << 8) 			| \
			  ((plcdparams->time_seq.thf -1) << 0 );
   	  
	/*  [23:14] ：HSPW = thp - 1  行脉冲宽度
	 */
	LCDCON4 = ((plcdparams->time_seq.thp -1) << 0 );



	/* 用来设置引脚极性, 设置16bpp数据格式, 设置内存中象素存放的格式
     * [12] : BPP24BL,This bit determines the order of 24 bpp video memory.
	 * [11] : FRM565, 1-565
	 * [10] : INVVCLK, 0 = The video data is fetched at VCLK falling edge
	 * [9]  : HSYNC是否反转
	 * [8]  : VSYNC是否反转
	 * [7]  : INVVD, rgb是否反转
	 * [6]  : INVVDEN
	 * [5]  : INVPWREN
	 * [4]  : INVLEND
	 * [3]  : PWREN, LCD_PWREN output signal enable/disable
	 * [2]  : ENLEND  
	 * [1]  : BSWP
	 * [0]  : HWSWP
	 */

	pixelformat = plcdparams->pins_pol.bpp == 24 ? (0) : \//24bpp
				  plcdparams->pins_pol.bpp == 16 ? (1) : \ //16bpp
				  (1<<1);//8ppp
	LCDCON5 = (plcdparams->pins_pol.vclk<<10) |\
			  (plcdparams->pins_pol.hsync<<9) |\
			  (plcdparams->pins_pol.vsync<<8) |\
			  (plcdparams->pins_pol.rgb<<7)   |\
			  (plcdparams->pins_pol.de<<6)    |\
			  (plcdparams->pins_pol.pwren<<5) |\
			  (1<<11) | pixelformat;

	/* framebuffer 起始地址
	 * [29:21] : LCDBANK, A[30:22] of fb_start
	 * [20:0]  : LCDBASEU, A[21:1] of fb_start
	 */	  
	fb_addr = plcdparams->fb_base & (~(1<<31)); //清除最高位
	LCDSADDR1 = fb_addr>>1;//清除最低位

	/* framebuffer 结束地址
	 * [20:0]  : LCDBASEU, [21:1] of fb_end
	 */	  
	fb_addr = plcdparams->fb_base + plcdparams->xres*plcdparams->yres*plcdparams->bpp/8;//结束地址 = 起始地址+一帧所占空间大小
	LCDSADDR2 = (fb_addr & 0x3FFFFF) >> 1;
}


void s3c2240_lcd_controller_enable(void)
{
	/* 背光引脚： GPB0 */
	GPBDAT |= (1<<0); //背光开启

	/* LCDCON5 [3]  : PWREN, LCD_PWREN output signal enable/disable */
	/* pwren : 给LCD提供AVDD */
	LCDCON5 |= (1<<3);

	/* LCDCON1'BIT 0 : 设置LCD控制器是否输出信号 */
	LCDCON1 |= (1<<0);
}


void s3c2240_lcd_controller_disable(void)
{
	/* 背光引脚： GPB0 */
	GPBDAT |= ~(1<<0); //背光关闭

	/* LCDCON5 [3]  : PWREN, LCD_PWREN output signal enable/disable */
	/* pwren : 给LCD提供AVDD */

	LCDCON5 |= ~(1<<3);
	/* LCDCON1'BIT 0 : 设置LCD控制器是否输出信号 */
	LCDCON1 |= ~(1<<0);
}



/* LCD 控制器具体实现函数 
*/
lcd_controller s3c2240_lcd_controller{
	.name    = "s3c2440";
	.init    = s3c2240_lcd_controller_init,
	.enable  = s3c2240_lcd_controller_enable,
	.disable = s3c2240_lcd_controller_disable,
};


/* s3c2440 lcd控制器注册 */
void s3c2440_lcd_controller_register(void)
{
	register_lcd_controller(&s3c2240_lcd_controller);
}
