#ifndef __LED_H
#define __LED_H


void delay(volatile int i);
//LED初始化
void led_init(void);
//LED流水灯
int led_loop(void);
//LED翻转
void led_turn(void);

#endif


