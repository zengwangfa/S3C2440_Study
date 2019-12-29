#ifndef __LCD_CONTROLLER_H
#define __LCD_CONTROLLER_H

#include "lcd.h"

/* 抽象LCD控制器结构体
 * 向上：接收不同的LCD参数
 * 向下：使用这些参数设置对应的LCD Controller
*/
typedef struct lcd_controller{
	void (*init)(p_lcd_params plcdparams); //初始化
	void (*enable)(void);  //使
	void (*disable)(void); //禁止 

}lcd_controller,*p_lcd_controller;









#endif /* __LCD_CONTROLLER_H */


