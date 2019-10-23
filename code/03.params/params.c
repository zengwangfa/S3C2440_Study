
void delay(volatile int us)
{
	while(us--);
}

int led_on(int which)
{
	volatile unsigned int *pGPFCON = 0x56000050;
	volatile unsigned int *pGPFDAT = 0x56000054;
	if(which == 4){
		*pGPFCON = 0x100;
	}
	else if(which == 5){
		*pGPFCON = 0x400;
	}
	*pGPFDAT = 0;
	return 0;
}

