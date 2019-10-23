#include "s3c2440_soc.h"

typedef unsigned char uint8;
typedef unsigned int uint32;

#define K1 (GPFDAT & 0x01)
#define K2 (GPFDAT & 0x04)
#define K3 (GPGDAT & 0x08)

uint8 key_scan(void)
{
	if(0 == K1)return 1;
	else if(0 == K2)return 2;
	else if(0 == K3)return 3;
	else return 0;
}

int main(int which)
{
	/* 配置GPFCON 4-6为输出模式 */
	GPFCON &= ~(0x3F<<8); //对应位清零
	GPFCON |=  (0x15<<8); //对应位设置 01输出模式

	/* 配置GPF0,GPF2,GPG3为输入模式 */
	GPFCON &= ~(0x33); //对应位清零 00输入模式
	GPGCON &= ~(0xC0); 

	while(1){
		switch(key_scan()){
			case 1: 
				GPFDAT = !(GPFDAT & 0x10);
				break;
			case 2: 
				GPFDAT = !(GPFDAT & 0x20);
				break;
			case 3: 
				GPFDAT = !(GPFDAT & 0x40);
				break;
			default:
				break;
		}
	}

	return 0;
}

