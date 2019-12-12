#include "s3c2440_soc.h"

void delay(volatile int i)
{
	while(i--);
}

void led_init(void)
{
		/* GPF4/5/6设置输出模式 */
	GPFCON &= 0xC0FF; //相应位清零 	        [1100 0000 1111 1111]
	GPFCON |= 0x1500; //响应为设置为01输出模式[0001 0101 0000 0000]
	GPFDAT &= ~(7<<4);
}

int led_loop(void)
{
	int i;
	/* 循环点亮 */
	for(i = 4;i < 7;i++)
	{
		GPFDAT |=  (7<<4);//3个位都置1
		GPFDAT &= ~(1<<i);//相应位清零

		delay(100000);
	}
	
	return 0;
}




