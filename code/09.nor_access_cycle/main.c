
#include "s3c2440_soc.h"
#include "uart.h"
#include "led.h"
#include "init.h"
#include "my_printf.h"


/* 设置nor flash的访问时间 
 * 当Tacc数值变化，CPU读取nor上的数据与代码时的效率会不同
 */
int main(void)
{
	unsigned char c;
	/* 设备初始化 */
	led_init();
	uart0_init(115200);

	my_printf("Enter the Nor Tacc value:\r\n");

	while(1)
	{
		c = uart0_getchar();
		uart0_putchar(c);//回显
		
		if(c >= '0' && c <= '7'){
			bank0_tacc_set(c -'0');
			while(1){
				led_loop();	
			}		
		}
		else{
			my_printf("Error:Input must range from 0 to 7\r\n");
			my_printf("Enter the Nor Tacc value again:\r\n");
		}
	}
	return 0;
}



