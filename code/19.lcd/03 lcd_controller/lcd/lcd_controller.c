#include "lcd.h"

/* 最大LCD CONTROLLER数量 */
#define LCD_CON_MAX_NUM  5


static p_lcd_controller p_array_lcd_controller[LCD_CON_MAX_NUM];//保存注册的LCD控制器
static p_lcd_controller g_p_lcd_controller_selected;//被选中的LCD控制器

/* 注册LCD 控制器 
 * ret: -1表示失败
*/
int register_lcd_controller(p_lcd_controller plcdcon)
{
	int i;
	for(i = 0; i < LCD_CON_MAX_NUM; i++){
		if(!p_array_lcd_controller[i]){
			p_array_lcd_controller[i] = plcdcon;
			return i;
		}
	}
	return -1;
}

/* 通过名字选择LCD控制器 
 * ret: -1表示失败
*/
int select_lcd_controller(char *name)
{
	int i;
	for(i = 0; i < LCD_CON_MAX_NUM; i++){
		if(p_array_lcd_controller[i] && !strcmp(p_array_lcd_controller[i]->name,name)){
			g_p_lcd_controller_selected = p_array_lcd_controller[i];
			return i;
		}
	}
	return -1;
}




/* LCD控制器初始化
 * 向上：接收不同的LCD参数
 * 向下：使用这些参数设置对应的LCD Controller
 * 
 * ret: -1表示失败
*/
void lcd_controller_init(p_lcd_params plcdparams)
{
	/* 调用2440的LCD初始化函数 */
	if(g_p_lcd_controller_selected){//被选中的LCD控制器非空才进行初始化
		g_p_lcd_controller_selected->init(plcdparams);
		return 0;
	}
	return -1;
}

void lcd_controller_register(void)
{
	s3c2440_lcd_controller_register();
}

