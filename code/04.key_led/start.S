
.text
.global _start

_start:

	// 关闭看门狗 
	ldr r0, =0x53000000
	ldr r1, =0
	str r1,[r0]

	/* 设置内存： sp栈 */
	/* 分辨是nor/nand启动 
	 * 写0到0地址，在读出来
	 * 如果得到0，便是0地址内容被修改了，它对应ram，即nand启动（因为nor不容易被写入）
	 * 否则就是nor启动
	 */
	/* nand相当于内存（读写方便），nor相当于外存（读方便，写复杂）*/
	
	mov r1, #0
	ldr r0, [r1] //暂存0地址的数据
	str r1, [r1] //0->[0]
	ldr r2, [r1] //去读0地址数据
	cmp r1, r2   //比较r1==r2? 如果等于，则0写入成功，对应nand
	ldr sp, =0x40000000+4096 /*假设是nor启动*/
	moveq sp, #4096 //若r1==r2，执行该句
	streq r0, [r1]//恢复0地址的数据
	

	bl main
halt:
	b halt