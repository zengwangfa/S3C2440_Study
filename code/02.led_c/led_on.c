
void main(void)
{
	volatile unsigned int *pGPFCON = 0x56000050;
	volatile unsigned int *pGPFDAT = 0x56000054;
	
	*pGPFCON | = 0xFDFF;
	*pGPFDAT & = (~(1<<4));
}

