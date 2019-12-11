#ifndef __UART_H
#define __UART_H

//串口初始化
void uart0_init(void);

//输出一个字符
void uart0_putchar(unsigned char c);

//获取一个字符
char uart0_getchar(void);

//输出字符串
int uart0_puts(const char *s);


#endif

