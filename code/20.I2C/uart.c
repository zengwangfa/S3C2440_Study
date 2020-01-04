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

void printHex(int val)
{
	int i;
	int arr[8];
	//先取出每一位的值
	for(i = 0;i < 8;i++){
		arr[i] = val & 0x0F;//4位跟16相与，逆序相存
		val >>= 4;
	}
	uart0_puts("0x");
	for(i = 7;i >= 0;i--){
		if (arr[i] > 0 && arr[i] <= 9){
			uart0_putchar(arr[i] + '0');
		}
		else if(arr[i] >= 0xA && arr[i] <= 0xF){
			uart0_putchar(arr[i] - 0xA + 'A');	
		}
	}
}

void printSWIVal(unsigned int *pSWI)
{
	uart0_puts("SWI val = ");
	printHex(*pSWI & ~0xff000000);
	uart0_puts("\n\r");
}

void printException(unsigned int cpsr, char *str)
{
	uart0_puts(str);
	uart0_puts("\n\r");
}
