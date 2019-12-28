#ifndef __MY_PRINTF_H
#define __MY_PRINTF_H

#include "uart.h"
#include "string_utils.h"

#define __out_putchar uart0_putchar  //底层输出

#define  MAX_NUMBER_BYTES  64

int my_printf(const char *fmt, ...);

#endif
