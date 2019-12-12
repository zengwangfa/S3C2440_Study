 
#include  "my_printf.h"


//==================================================================================================
typedef char *  va_list;
#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
//当sizeof(var)小于sizeof(int),则_INTSIZEOF(var)=4
#define va_start(ap,v)  ( ap = (va_list)&v + _INTSIZEOF(v) )

#define va_arg(ap,t)    ( *(t *)( ap=ap + _INTSIZEOF(t), ap- _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (va_list)0 )

//==================================================================================================
unsigned char hex_tab[]={'0','1','2','3','4','5','6','7',\
		                 '8','9','a','b','c','d','e','f'};
//输出单个字符
static int outc(int c) 
{
	__out_putchar(c);
	return 0;
}
//输出字符串
static int outs (const char *s)
{
	while (*s != '\0')	
		__out_putchar(*s++);
	return 0;
}
/*
 * 输出数字
 * n:数字, base:进制, lead:前导码, maxwidth:最大数字宽度
 */
static int out_num(long n,int base,char lead,int maxwidth)
{
	unsigned long res = 0;
	char buf[MAX_NUMBER_BYTES]; //数据缓冲区
	char *s = buf + sizeof(buf);
	int count = 0,i = 0;

	*--s = '\0';
	res = n < 0 ? -n : n; //若为负,转换正数暂存

	do{
		*--s = hex_tab[res%base]; //存储
		count++;
	}while((res/=base) != 0);

	if(maxwidth && count < maxwidth){
		for(i = maxwidth - count;i;i--){
			*--s = lead; //填充前导码,默认空格  eg:%6d,则为:   123(前面三个空格)
		}
	}
	if(n < 0){
		*--s = '-';
	}

	return outs(s);
}

   
//简易printf函数实现逻辑
/*reference :   int vprintf(const char *format, va_list ap); */
static int my_vprintf(const char *fmt, va_list ap) 
{
	char lead=' ';//前导码默认为空格
	int  maxwidth=0;
	
	 for(; *fmt != '\0'; fmt++)
	 {
			if (*fmt != '%') {//当未遇到%,直接输出字符
				outc(*fmt);
				continue;
			}
			
		//format : %08d, %8d,%d,%u,%x,%f,%c,%s 
		fmt++;
		if(*fmt == '0'){//存放前导码
			lead = '0';
			fmt++;	
		}

		lead=' ';
		maxwidth=0;
		
		while(*fmt >= '0' && *fmt <= '9'){//计算最大数字宽度 eg: %6d
			maxwidth *=10;
			maxwidth += (*fmt - '0');
			fmt++;
		}
		
		switch (*fmt) {//选择数据格式
		case 'd': out_num(va_arg(ap, int),          10,lead,maxwidth); break;
		case 'o': out_num(va_arg(ap, unsigned int),  8,lead,maxwidth); break;				
		case 'u': out_num(va_arg(ap, unsigned int), 10,lead,maxwidth); break;
		case 'x': out_num(va_arg(ap, unsigned int), 16,lead,maxwidth); break;
		case 'c': outc(va_arg(ap, int   )); break;		
		case 's': outs(va_arg(ap, char *)); break;		  		
		default:  
			outc(*fmt);break;
		}
	}
	return 0;
}


//reference :  int printf(const char *format, ...); 
int printf(const char *fmt, ...) 
{
	va_list ap;

	va_start(ap, fmt);//移动至可变参数地址
	my_vprintf(fmt, ap);	
	va_end(ap);
	return 0;
}


int my_printf_test(void)
{
	printf("This is www.100ask.org   my_printf test\n\r") ;	
	printf("test char           =%c,%c\n\r", 'A','a') ;	
	printf("test decimal number =%d\n\r",    123456) ;
	printf("test decimal number =%d\n\r",    -123456) ;	
	printf("test hex     number =0x%x\n\r",  0x55aa55aa) ;	
	printf("test string         =%s\n\r",    "www.100ask.org") ;	
	printf("num=%08d\n\r",   12345);
	printf("num=%8d\n\r",    12345);
	printf("num=0x%08x\n\r", 0x12345);
	printf("num=0x%8x\n\r",  0x12345);
	printf("num=0x%02x\n\r", 0x1);
	printf("num=0x%2x\n\r",  0x1);

	printf("num=%05d\n\r", 0x1);
	printf("num=%5d\n\r",  0x1);

	return 0;
}



