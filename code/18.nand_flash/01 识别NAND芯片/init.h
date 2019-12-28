#ifndef __INIT_H
#define __INIT_H

//定义函数指针
typedef void(*irq_func)(int);


//注册中断,输入：1.中断号，2.中断服务函数
void register_irq(int irq,irq_func fp);

//timer0 初始化
void timer0_init(void);

//SDRAM设置bank6 初始化
void sdram_init(void);

//初始化外部中断，设置按键为中断源
void key_eint_init(void);
#endif

