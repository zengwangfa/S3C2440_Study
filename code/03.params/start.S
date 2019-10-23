
.text
.global _start

_start:
	/* 设置内存： sp栈 */
	ldr sp, = 4096 /* nand 启动 */
	//ldr sp, = 0x40000000+4096 /* nor启动 */
	
	mov r0, #4
	bl led_on 
	
	mov r0, =100000
	bl delay 
	
	mov r0, #5
	bl led_on 	
halt:
	b halt