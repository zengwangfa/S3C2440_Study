/*
 * 点亮LED：GPF4
 */ 
 
/*
 * GPFCON:0x56000050   00 = Input , 01 = Output 
 * GPFDAT:0x56000054   
 */
  
/*
 * 点亮GPF4引脚对应的LED：
 * 初始化为输出模式，即将0x100写入 GPFCON
 * 设置GPF4输出高电平，即将0x10写入GPFDAT
 */  
 
.text
.global _start


_start:

/*
 * 点亮GPF4引脚对应的LED：
 * 初始化为输出模式，即将0x100写入 GPFCON
 */  
		ldr r1, = 0x56000050
		ldr r0, = 0x100
		str r0,[r1]
/*
 * 设置GPF4输出高电平，即将0x10写入GPFDAT
 */
		ldr r1, = 0x56000054
		ldr r0, = 0x00
		str r0,[r1]

/* 死循环，防止程序乱跳 */		
halt:
		b halt
		
		
		