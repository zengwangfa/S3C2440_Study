
#include "s3c2440_soc.h"
#include "uart.h"
#include "led.h"
#include "init.h"

char g_char = 'A'; //定义全局变量

/*
 * NAND FLASH测试
*/
int main(void)
{
	led_init();
	key_eint_init();
	nand_init();
	//timer0_init();

	nand_flash_menu();

	return 0;
}


