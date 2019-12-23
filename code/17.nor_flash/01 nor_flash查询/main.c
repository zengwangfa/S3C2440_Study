
#include "s3c2440_soc.h"
#include "uart.h"
#include "led.h"
#include "init.h"

char g_char = 'A'; //定义全局变量
extern void nor_flash_menu(void);
/*
 * 按键按下翻转LED
*/
int main(void)
{
	led_init();
	key_eint_init();
	timer0_init();

	nor_flash_menu();

	return 0;
}


