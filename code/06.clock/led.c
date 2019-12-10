void delay(volatile int i)
{
	while(i--);
}

int main(int which)
{
	volatile unsigned int *pGPFCON = (volatile unsigned int *)0x56000050;
	volatile unsigned int *pGPFDAT = (volatile unsigned int *)0x56000054;
	
	/* GPF4/5/6设置输出模式 */
	*pGPFCON &= 0xC0FF; //相应位清零 	        [1100 0000 1111 1111]
	*pGPFCON |= 0x1500; //响应为设置为01输出模式[0001 0101 0000 0000]
	
	/* 循环点亮 */
	while(1){
		for(int i = 4;i < 7;i++)
		{
			*pGPFDAT |=  (7<<4);//3个位都置1
			*pGPFDAT &= ~(1<<i);//相应位清零

			delay(100000);
		}
	}
	
	return 0;
}




