#ifndef __INIT_H
#define __INIT_H

//SDRAM设置bank6 初始化
void sdram_init(void);
//初始化中断控制器
void interrupt_init(void);
//初始化外部中断，设置按键为中断源
void key_eint_init(void);
#endif

