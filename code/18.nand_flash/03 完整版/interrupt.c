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






