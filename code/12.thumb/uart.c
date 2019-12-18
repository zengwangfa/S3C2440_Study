#include "s3c2440_soc.h"

//串口初始化
void uart0_init(void)
{
	/* 配置串口引脚 */
	/* GPH2、3复用于串口 */
	GPHCON &= ~(0xF0); //清零
	GPHCON |= (0xA0);  //写1010 
	
	/* 设置内部上拉 */
	GPHUP &= ~(0xC0);
	
	/* 设置波特率
	 * UBRDIVn = (int)( UART clock / ( buad rate x 16) ) –1
	 * UBRDIVn = 50,000,000 / (115200 x 16) -1 = 26
	 */
	UCON0 = 0x05; /* 时钟源:PCLK 模式:中断/查询*/
	UBRDIV0 = 26; 
	/* 设置数据格式 */
	ULCON0 = 0x03; /* 8N1 */
	
}


void uart0_putchar(unsigned char c)
{
	/* UTRSTAT0 */
	/* UTXH0 */
	while(!(UTRSTAT0 & (0x04))); //非空则等待
	UTXH0 = c; //写入数据
}


char uart0_getchar(void)
{
	/* read URXH0 */
	while(!(UTRSTAT0 & (0x01))); //
	return URXH0;
}

int uart0_puts(const char *s)
{
	while(*s)
	{
		uart0_putchar(*s);
		s++;
	}
}
