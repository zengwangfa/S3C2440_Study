
#include "s3c2440_soc.h"
#include "uart.h"
#include "led.h"

int main(void)
{
	unsigned char c;
	/* 设备初始化 */
	led_init();
	uart0_init();

	uart0_puts("Hello, world!\r\n");
	
	while(1)
	{
		led_loop();
		c = uart0_getchar();
		if ('\r' == c){
			uart0_putchar('\n');
		}
		else if ('\n' == c){
			uart0_putchar('\r');
		}
		uart0_putchar(c);
	}
	return 0;
}



