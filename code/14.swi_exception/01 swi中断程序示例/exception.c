#include "printf.h"
#include "uart.h"

//提示异常信息，打印CPSR的值
void printException(unsigned int cpsr,char *str)
{
	printf("\r\n==============================\r\n");
	printf("Exception CPSR = %x\r\n",cpsr);
	printf("%s\r\n",str);
}


void printf_test1(void)
{
	printf("123\r\n");
}

void printf_test2(void)
{
	printf("456\r\n");
}

