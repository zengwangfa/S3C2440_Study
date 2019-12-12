
#include "s3c2440_soc.h"
#include "uart.h"
#include "led.h"
#include "my_printf.h"

int main(void)
{
	unsigned char c;
	/* 设备初始化 */
	led_init();
	uart0_init(115200);

	uart0_puts("Hello, world!\r\n");
	my_printf_test();
	while(1)
	{
		led_turn();
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



