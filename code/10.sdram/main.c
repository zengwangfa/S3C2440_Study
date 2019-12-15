
#include "s3c2440_soc.h"
#include "uart.h"
#include "led.h"
#include "init.h"
#include "printf.h"

int main(void)
{
	unsigned char c;
	/* 设备初始化 */
	led_init();
	uart0_init(115200);
	sdram_init();
	printf("Hello, world! %d\r\n",2019);

	if (sdram_test() == 0){
		while(1){
			led_loop();
		}
	}
	return 0;
}



