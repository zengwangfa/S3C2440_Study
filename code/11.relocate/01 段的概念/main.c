
#include "s3c2440_soc.h"
#include "uart.h"
#include "led.h"
#include "init.h"
#include "printf.h"

char g_Char = 'A'; //定义全局变量
const char g_Char2 = 'B'; //只读全局变量
int g_A = 0; //初值为0的全局变量
int g_B; //未定义初值的全局变量

int main(void)
{

	/* 设备初始化 */
	uart0_init(115200);

	printf("Hello, world! %d\r\n",2019);
	while(1){
		printf("%c",g_Char++);
		delay(1000000);
	}

	return 0;
}



