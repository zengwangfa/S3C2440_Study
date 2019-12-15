#ifndef __INIT_H
#define __INIT_H

//SDRAM设置bank6 初始化
void sdram_init(void);

/*
	sdram读写测试
	返回写入数组的首地址
*/
int sdram_test(void);


#endif

