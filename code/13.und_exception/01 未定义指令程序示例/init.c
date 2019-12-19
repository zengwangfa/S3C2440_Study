#include "s3c2440_soc.h"
#include "printf.h"


//SDRAM设置bank6 初始化
void sdram_init(void)
{
    //带宽&等待控制寄存器
	BWSCON   = 0x22000000;

/*  > BANK控制寄存器
	- 内存类型设置为SDRAM
	- 设置发出行地址与列地址之间的时间间隔）20ns，即设置为00=2 clock（以为HCLK=100M，clock=10ns）
	- 设置列地址为9位  */
	BANKCON6 = 0x18001;
	BANKCON7 = 0x18001;
	//刷新控制寄存器（由于SDRAM如果长时间不刷新，里面的数据会丢失，因此要时常刷新）
	REFRESH = 0x8404F5;

	BANKSIZE = 0xB1;

    //SDRAM 模式设置寄存器
	MRSRB6 = 0x20;
	MRSRB7 = 0x20;
}

/*
 * 将除bss段的全部数据拷贝到sdram中
 * 传递形参，原地址src:_start  目标地址dest:__bss_start  长度len:__bss_start-_star
 */
void copy_to_sdram(void)
{
	/* 要从lds文件中获取__code_start、__bss_start
	 * 然后从0地址把数据复制到__code_start
	 */
	extern int __code_start,__bss_start; //声明外部变量

	volatile unsigned int *src  = (volatile unsigned int *)0; //flash中0地址 
	volatile unsigned int *dest = (volatile unsigned int *)&__code_start; //目标地址：sdram中的0x30000000地址
	volatile unsigned int *end  = (volatile unsigned int *)&__bss_start;  //结束地址：bss的起始地址

	while(dest < end){
		*dest++ = *src++; //拷贝
	}
}

/* 清除bss段数据 */
void clean_bss(void)
{
	extern int __bss_start,__bss_end;//声明外部变量

	volatile unsigned int *start = (volatile unsigned int *)&__bss_start;
	volatile unsigned int *end  = (volatile unsigned int *)&__bss_end;

	while(start <= end)
	{
		*start++ = 0;
	}
}