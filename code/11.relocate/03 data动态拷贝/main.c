
#include "s3c2440_soc.h"
#include "uart.h"
#include "led.h"
#include "init.h"
#include "printf.h"

char g_Char = 'A'; //定义全局变量
char g_Char1 = 'a'; //定义全局变量
const char g_Char2 = 'B'; //只读全局变量
int g_A = 0; //初值为0的全局变量
int g_B; //未定义初值的全局变量

//GUN链接手册 http://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_mono/ld.html#SEC6
int main(void)
{

	/* 设备初始化 */
	sdram_init();
	uart0_init(115200);

	printf("Hello, world! %d\r\n",2019);
	while(1){
		printf("%c",g_Char++);
		delay(500000);
		
		printf("%c",g_Char1++);
		delay(500000);
	}

	return 0;
}



