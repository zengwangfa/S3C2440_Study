
.text
.global _start

_start:
	/* 设置内存： sp栈 */
	ldr sp, = 4096 /* nand 启动 */
	//ldr sp, = 0x40000000+4096 /* nor启动 */
	
	
	mov r0, #4  //传递参数4  (r0~r3用来传参)
	bl led_on 
	
	ldr r0, =100000  //传递延时时间
	bl delay 
	
	mov r0, #5  //传递参数5
	bl led_on 
	
halt:
	b halt