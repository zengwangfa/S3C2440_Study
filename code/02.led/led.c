
int main(void)
{
	volatile unsigned int *pGPFCON = (volatile unsigned int *)0x56000050;
	volatile unsigned int *pGPFDAT = (volatile unsigned int *)0x56000054;
	
	*pGPFCON = 0x100;
	*pGPFDAT = 0;
	return 0;
}

