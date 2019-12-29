
#include "lcd_controller.h"

#define HCLK 100  //HCLK -> 100M

/* 具体的lcd控制器初始化
*/
void s3c2240_lcd_controller_init(p_lcd_params plcdparams);
{
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
	 *  [23:14] ：LINEVAL = line - 1 
	 *  [13:6]  ：VFPD    = Tvf - 1 
	 *  [5:0]	：VSPW 	  = Tvp -1
	 */
	LCDCON2 = ((plcdparams->time_seq.tvb -1) << 24) | \
			  ((plcdparams->yres -1) << 14) 		| \
			  ((plcdparams->time_seq.tvf -1) << 6 ) | \
		  	  ((plcdparams->time_seq.tvp -1) << 0 );

	/*  水平	  	  
	 *  [31:19] ：HBPD    = THb - 1
	 *  [18:8] ：HOZVAL  = 列 - 1
	 *  [7:0]  ：HFPD    = Thf - 1 
	 */
	LCDCON2 = ((plcdparams->time_seq.thb -1) << 19) | \
			  ((plcdparams->xres -1) << 8) 			| \
			  ((plcdparams->time_seq.tvf -1) << 0 );
	/*   	  
	 *  [23:14] ：HSPW = thp - 1
	 */
	LCDCON2 = ((plcdparams->time_seq.thb -1) << 19) | \
			  ((plcdparams->xres -1) << 8) 			| \
			  ((plcdparams->time_seq.tvf -1) << 0 );


}












/* 
*/
lcd_controller s3c2240_lcd_controller{
	.init = s3c2240_lcd_controller_init,
	.enable = s3c2240_lcd_controller_init_enable,
	.disable = s3c2240_lcd_controller_init_disable,
};
