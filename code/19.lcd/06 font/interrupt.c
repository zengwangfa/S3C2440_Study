#include "s3c2440_soc.h"
#include "init.h"
#include "interrupt.h"
#include "led.h"

irq_func irq_array[32];//定义存放函数指针数组(即：数组中存放的是函数指针)


/* SRCPND 用来显示哪一个中断产生，需要清除对应位
 * bit0-eint0
 * bit2-eint2
 * bit5-eint8~23 
*/
/* INTMSK 用来屏蔽中断(1-mask) 
 * bit0-eint0
 * bit2-eint2
 * bit5-eint8~23 
*/
/* INTPND 用来显示当前优先级最高、正在发生的中断，需要清除对应位
 * bit0-eint0
 * bit2-eint2
 * bit5-eint8~23 
*/
/* INTOFFSE 用来显示INPND哪一位被设置为1
 *
 */

//宏定义中断源OFFEST value
#define INT_TIMER0_OFFEST 10
#define EINT8_23_OFFEST    5
#define EINT4_7_OFFEST     4
#define EINT3_OFFEST       3
#define EINT2_OFFEST       2
#define EINT1_OFFEST       1
#define EINT0_OFFEST       0




/* 注册中断
 * param：1.中断号，2.中断服务函数
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
/* ===================================================== */

void timer0_irq(int irq)
{
	static int i = 4;

	GPFDAT |=  (7<<4);    //3个位都置1
	GPFDAT &= ~(1<<(i++));//相应位清零

	i = i > 7 ? 4:i;//i在[4,7]之间
}



/* 
 * 读EINTPEND 分辨哪一个EINT产生(eint4~23) 
 * 清除中断时，写EINTPEND的相应位
 */
void key_eint_irq(int irq)
{
	unsigned int val = EINTPEND;//可以用来用具体判断哪一个中断
	switch (irq)
	{
		case EINT0_OFFEST:
				led_turn(1);//翻转第1个LED
				break;							
		case EINT2_OFFEST:
				led_turn(2);//翻转第2个LED
				break;	
		case EINT8_23_OFFEST:
			if(val & (1<<11)){//用来判断eint11
				led_turn(4);//翻转第3个LED
			}
			else if(val & (1<<19)){//用来判断eint11
				led_turn(7);//翻转所有的LED	
			}
			break;		
		default:break;
	}
	EINTPEND = val;
}


/* 中断处理函数
 *
*/
void handle_irq_c(void)
{
	/* 1.分辨中断源 */
	int bit = INTOFFSET;//判断谁在请求中断

	/* 2.调用对应的处理函数 */
	irq_array[bit](bit); //irq_array存放的是函数指针，加一个()即表示调用该函数

	/* 3.清中断 ：从源头开始清 */
	SRCPND = (1<<bit);
	INTPND = (1<<bit);
}






