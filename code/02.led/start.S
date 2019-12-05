
.text
.global _start

_start:
	/* 设置内存： sp栈 */
	ldr sp, = 4096 /* nand 启动 */
	//ldr sp, = 0x40000000+4096 /* nor启动 */
	
	
	/* 调用main函数 */
	bl main 
	
halt:
	b halt