#include "s3c2440_soc.h"
#include "interrupt.h"
#include "init.h"
#include "nand_flash.h"



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

/* 检查是否从NorFlash中启动
 * 方法：写0x12345678到0地址，在读取出来，如果得到0x12345678，表示0地址上的内容被修改，即为片内RAM，则为nand启动
 * 原因：原因：nor不能直接写入，写入需要发出一定格式的数据，才能写入
 * 返回0为nand启动，返回1为nor启动
*/
int isBootFromNorFlash(void)
{
	volatile int *p = (volatile int *)0;
	int val;

	val = *p;
	*p = 0x12345678;
	if (*p == 0x12345678)
	{
		*p = val;
		return 0;
	}
	else
	{
		return 1;
	}
}

/*
 * 将除bss段的全部数据拷贝到sdram中
 * 传递形参，原地址src:_start  目标地址dest:__bss_start  长度len:__bss_start-_star
 */
void copy2sdram(void)
{
	/* 要从lds文件中获取__code_start、__bss_start
	 * 然后从0地址把数据复制到__code_start
	 */
	extern int __code_start,__bss_start; //声明外部变量

	volatile unsigned int *src  = (volatile unsigned int *)0; //flash中0地址 
	volatile unsigned int *dest = (volatile unsigned int *)&__code_start; //目标地址：sdram中的0x30000000地址
	volatile unsigned int *end  = (volatile unsigned int *)&__bss_start;  //结束地址：bss的起始地址

	int len = (unsigned int)&__bss_start - (unsigned int)&__code_start;//获取数据总长度

	if(isBootFromNorFlash()){//如果从Nor中启动
		while(dest < end){
			*dest++ = *src++; //拷贝
		}
	}
	else{//从Nand中启动,需要先初始化nand，然后重定位代码
		nand_init();
		//从 src 复制到 des ,总共复制len字节，也就是重定位的代码
		nand_read((unsigned int)src,dest,len);
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

