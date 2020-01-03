#include "lcd.h"
#include "lcd_controller.h"
#include "../string_utils.h"

#define LCD_MAX_NUM 5

static p_lcd_params p_array_lcd[LCD_MAX_NUM];//保存注册的LCD
static p_lcd_params g_p_lcd_selected;  //被选中的LCD


/* 注册LCD 
 * ret: -1表示失败
*/
int register_lcd(p_lcd_params plcd)
{
	int i;
	for(i = 0; i < LCD_MAX_NUM; i++){
		if(!p_array_lcd[i]){
			p_array_lcd[i] = plcd;
			return i;
		}
	}
	return -1;
}

/* 通过名字选择LCD
 * ret: -1表示失败
*/
int select_lcd(char *name)
{
	int i;
	for(i = 0; i < LCD_MAX_NUM; i++){
		if(p_array_lcd[i] && !strcmp(p_array_lcd[i]->name,name)){
			g_p_lcd_selected = p_array_lcd[i];
			return i;
		}
	}
	return -1;
}

/* 获取LCD参数 */
void get_lcd_params(unsigned int *fb_base,int *xres,int *yres,int *bpp)
{
	*fb_base = g_p_lcd_selected->fb_base;
	*xres = g_p_lcd_selected->xres;
	*yres = g_p_lcd_selected->yres;
	*bpp = g_p_lcd_selected->bpp;
}


int lcd_init(void)
{

	/* 注册LCD */
	lcd_4_3_add();

	/* 注册LCD控制器 */
	lcd_controller_add();

	/* 选择LCD */
	select_lcd("lcd_4.3");
	
	/* 选择LCD控制器 */
	select_lcd_controller("s3c2440");

	/* 使用LCD的参数，初始化LCD控制器 */
	lcd_controller_init(g_p_lcd_selected);

}

void lcd_enable(void)
{
	lcd_controller_enable();
}

void lcd_disable(void)
{
	lcd_controller_disable();
}
