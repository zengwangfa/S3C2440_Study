void delay(volatile int i)
{
	while(i--);
}



int led_on(int which)
{
	volatile unsigned int *pGPFCON = (volatile unsigned int *)0x56000050;
	volatile unsigned int *pGPFDAT = (volatile unsigned int *)0x56000054;
	
	if(4 == which){
		*pGPFCON = 0x100; //GPF4输出模式
	}
	else if(5 == which){
		*pGPFCON = 0x400; //GPF5输出模式	
	}
	*pGPFDAT = 0;
	return 0;
}




