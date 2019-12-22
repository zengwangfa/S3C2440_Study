
#include "s3c2440_soc.h"
#include "uart.h"
#include "led.h"
#include "init.h"

char g_char = 'A'; //定义全局变量
/*
 * 按键按下翻转LED
*/
int main(void)
{
	led_init();
	interrupt_init();
	key_eint_init();
	timer_init();

	while(1){
		uart0_putchar(g_char++);
		delay(500000);
	}

	return 0;
}


