#include "s3c2440_soc.h"
#include "interrupt.h"
#include "init.h"

extern irq_func irq_array[32];//定义存放函数指针数组(即：数组中存放的是函数指针)
/* 注册中断
 * param：1.中断号，2.中断服务函数指针
*/
void register_irq(int irq,irq_func fp)
{
	irq_array[irq] = fp;//将fp指向的函数地址 存放在arr中

	INTMSK &= (1<<irq);
}


//timer0 初始化
void timer0_init(void)
{
	/* 1.设置timer0的时钟
	 * Timer CLK = PCLK / {prescaler value+1} / {divider value}
	 *               50000000/(99+1)/(16) = 31250
	 */
	TCFG0 = 99;    //Prescaler = 99，用于timer0,timer1
	TCFG1 &= ~0xFF;
	TCFG1 |= 3;    //MUX0=1/16(即是 divider value)

	//2.设置timer0的初值
	TCNTB0 = 15625;  //0.5s中断一次(15625/31250=0.5s)

	//3.手动加载初值至TCNT0与TCMT0，启动timer0
	TCON |= (1<<1);//Update from (TCNTB0 & TCMPB0) to (TCNT0 & TCMT0)

	//4.清除手动加载，并设置自动加载 并启动
	TCON &= ~(1<<1);
	TCON |= (1<<0) | (1<<3);//bit0：start,  bit3:auto reload

	register_irq(10, timer0_irq);
}





//初始化外部中断，设置按键为中断源
void key_eint_init(void)
{
	/* 引脚：GPF0、2   GPG3、11 */
	/* 中断：EINT0、2  EINT11、19*/
	GPFCON &= ~((3<<0) | (3<<4)); //清零
	GPFCON |=  ((2<<0) | (2<<4)); //设置[10]，配置为外部中断

	GPGCON &= ~((3<<6) | (3<<22));
	GPGCON |=  ((2<<6) | (2<<22)); //设置[10]，配置为外部中断

	/* 设置中断触发方式：下降沿触发 */
	EXTINT0 |= ((3<<0) | (3<<8)); //配置EINT0、2
	EXTINT1 |= (3<<12); //配置EINT11
	EXTINT2 |= (3<<12); //配置EINT19

	/* 设置外部MASK清零使能 */
	EINTMASK &= ~((1<<11) | (1<<19));


	register_irq(0, key_eint_irq);
	register_irq(2, key_eint_irq);
	register_irq(5, key_eint_irq);
}
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

