#include "s3c2440_soc.h"

//设置bank0 Tacc
/* 参数如下,传递参数转换为十进制,即0~7
000 = 1  clock    001 = 2 clocks
010 = 3  clocks   011 = 4 clocks
100 = 6  clocks   101 = 8 clocks
110 = 10 clocks   111 = 14 clocks
*/
void bank0_tacc_set(int val)
{
	BANKCON0 = (val << 8);
}
