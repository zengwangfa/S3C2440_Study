#include "s3c2440_soc.h"

void delay(volatile int i)
{
	while(i--);
}

int main(void)
{
	int key_value = 0;
	/* LED：GPF4/5/6设置输出模式 */
	GPFCON &= 0xC0FF; //相应位清零 	          [1100 0000 1111 1111]
	GPFCON |= 0x1500; //响应为设置为01输出模式[0001 0101 0000 0000]
	
	/* 按键：GPF0/2、GPG3设置输入模式 */
	GPFCON &= 0xFFCC; //相应位清零即为输入模式
	GPGCON &= 0xFF3F; 

	while(1){
		/* GPF0为第0位、GPF2为第1位、GPG3为第2位*/
		key_value = ((GPFDAT&0x01)) | ((GPFDAT&0x04)>>1) | ((GPGDAT&0x08)>>1);
		if(0x06 == key_value){ //GPF0被按下
			GPFDAT &= ~(1<<4);
		}
		else if(0x05 == key_value){ //GPF2被按下
			GPFDAT &= ~(1<<5);			
		}
		else if(0x03 == key_value){ //GPG3被按下
			GPFDAT &= ~(1<<6);			
		}
		else{
			GPFDAT |= (7<<4);			
		}
	}
	
	return 0;
}




