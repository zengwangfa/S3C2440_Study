#ifndef __INTERTUPT_H
#define __INTERTUPT_H

//定义函数指针
typedef void(*irq_func)(int);
void key_eint_irq(int irq);

void timer0_irq(int irq);

#endif

