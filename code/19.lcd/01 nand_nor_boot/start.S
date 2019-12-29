
.text
.global _start

/*====================================异常向量表===========================================*/
_start:
	b reset   		 //vector 0x00: reset(0地址对应reset)
 	ldr pc, und_addr //vector 0x04: und  (发生未定义指令异常，则进入“处理未定义异常函数”)绝对跳转，跳转至sdram中
 	ldr pc, swi_addr //vector 0x08: swi
 	b halt           //vector 0x0c: prefetch aboot
 	b halt           //vector 0x10: data aboot
 	b halt           //vector 0x14: reserved
 	ldr pc, irq_addr //vector 0x18: IRQ
  	b halt           //vector 0x1c: FIQ	
und_addr:
	.word do_und     //存放地址,确保这一地址存放在内存的前4K中

swi_addr:
	.word do_swi

irq_addr:
	.word do_irq



 /*=================================处理未定义异常=========================================*/
 do_und:

	/*执行到这里之前：
	 *1.lr_und保存有被中断模式中的下一条即将执行的指令的地址
	 *2.SPSR_und保存被中断模式CPSR
	 *3.CPSR的[M4:M0]=[11011],进入到und模式
	 *4.跳到0x04的模式执行程序，即跳到`bl do_und`这一指令
	 */
    /* 1.sp_und 设置栈，因为后面函数需要栈 */
    ldr sp, =0x34000000

    /* 2.保存现场 */
    /* lr是异常处理完后的返回地址，也需要保存 */
    stmdb sp!, {r0-r12,lr} //在und异常处理函数总有可能需要用到r0~r12，因此先保存下来

    /* 3.处理und异常 */
	mrs r0, cpsr
	ldr r1, =und_string
	bl printException

    /* 4.恢复现场 */
    ldmia sp,{r0-r12,pc}^ //将lr的值赋给pc ,`^`会把spsr的值恢复到cpsr中
und_string:
	.string "undefined instruction exception"
.align 4  //确保4字节对齐

 /*=================================处理软中断异常=========================================*/
 do_swi:

	/*执行到这里之前：
	 *1.lr_svc保存有被中断模式中的下一条即将执行的指令的地址
	 *2.SPSR_svc保存被中断模式CPSR
	 *3.CPSR的[M4:M0]=[10011],进入到svc模式
	 *4.跳到0x08的模式执行程序，即跳到`bl do_swi`这一指令
	 */
    /* 1.sp_svc 设置栈，因为后面函数需要栈 */
    ldr sp, =0x33E00000

    /* 2.保存现场 */
    /* lr是异常处理完后的返回地址，也需要保存 */
    stmdb sp!, {r0-r12,lr} //在swi异常处理函数总有可能需要用到r0~r12，因此先保存下来

    mov r4,lr //将lr存放在r4中，调用c函数不会破坏r4
    /* 3.处理swi异常 */
	mrs r0, cpsr
	ldr r1, =swi_string
	bl printException
	
	sub r0, r4, #4
	bl printSWIVal
    /* 4.恢复现场 */
    ldmia sp,{r0-r12,pc}^ //将lr的值赋给pc ,`^`会把spsr的值恢复到cpsr中
swi_string:
	.string "swi exception"
.align 4  //确保4字节对齐

 /*=================================处理中断=========================================*/
 do_irq:

	/*执行到这里之前：
	 *1.lr_irq保存有被中断模式中的下一条即将执行的指令的地址
	 *2.SPSR_irq保存被中断模式CPSR
	 *3.CPSR的[M4:M0]=[10010],进入到irq模式
	 *4.跳到0x18的模式执行程序，即跳到`bl do_irq`这一指令
	 */
    /* 1.sp_irq 设置栈，因为后面函数需要栈 */
    ldr sp, =0x33D00000

    /* 2.保存现场 */
    /* lr-4是异常处理完后的返回地址，也需要保存 */
    sub lr,lr,#4
    stmdb sp!, {r0-r12,lr} //在und异常处理函数总有可能需要用到r0~r12，因此先保存下来

    /* 3.处理异常 */
    bl handle_irq_c

    /* 4.恢复现场 */
    ldmia sp,{r0-r12,pc}^ //将lr的值赋给pc ,`^`会把spsr的值恢复到cpsr中
/*===================================关闭看门狗============================================*/
reset:
	/* 关闭看门狗 */
	ldr r0, =0x53000000
	mov r1, #0
	str r1,[r0]
	
/*==================================设置时钟==============================================*/	

	/* 设置MPLL,使得FLCK:HCLK:PCLK = 400M : 100M : 50M */
	/* LOCKTIME(0x4C000000) = 0xFFFFFFFF*/
	ldr r0, =0x4C000000
	ldr r1, =0xFFFFFFFF
	str r1,[r0]
	
	/* CLKDIVN(0x4C000014) = 0x05,fFCLK:fHCLK:fPCLK = 8:4:1 */
	ldr r0, =0x4C000014
	mov r1, #0x05
	str r1,[r0]
	
	/* 设置CPU工作异步模式[数据手册提供] */
	mrc p15,0,r0,c1,c0,0   //c:co-process 协处理器
	orr r0,r0,#0xc0000000  //#R1_nF:OR:R1_iA
	mcr p15,0,r0,c1,c0,0  
	
	/* 设置MPLLCON(0x4C000004) = (92<<12) | (1<<4) | (1<<0)
	 * m = MDIV+8 = 92+8 =100
	 * p = PDIV+2 = 1+2 =3
	 * s = SDIV = 1
	 * FLCK = (2*m*Fin)/(p*(2^s)) = (2*100*12M)/(3*2^1) = 400M
 	 */
	ldr r0, =0x4C000004
	ldr r1, =(92<<12) | (1<<4) | (1<<0)
	str r1,[r0]
	
	//一旦设置PLL,就会锁定LOCK TIME直到PLL输出稳定,然后CPU工作
	
/*=======================================================================================*/	

	/* 
	 * 分辨是nor/nand启动
	 * 方法：写0到0地址，在读取出来，如果得到0，表示0地址上的内容被修改，即为片内RAM，则为nand启动(可修改)
	 * 否则是nor启动
	 * 原因：nor不能直接写入，写入需要发出一定格式的数据，才能写入
 	*/
	mov r0,#0 
	ldr r1,[r0]  			  //读出[0]上的值备份在r1中
	str r0,[r0]  			  //把0写入[0]
	ldr r2,[r0]  			  //从[0]读取到的值放入r2
	cmp r0, r2   			  //r2是否等于0
	ldr sp, =0x40000000+4096  //先假设nor启动
	moveq sp, #4096           //相等则为nand 启动,设置栈
	streq r1,[r0] 			  //相等则恢复[0]的值
	
/*=============================初始内存的一些操作=========================================*/
	
	bl sdram_init  //初始化sdram

	/* 重定位text、rodata、data段 */
	bl copy_to_sdram  

	/* 清零bss段 */
	bl clean_bss 


/*=======================================================================================*/
	/* 复位之后，CPU处于svc模式
	 * 在这切换至usr模式
	 */
	mrs r0,cpsr    //读出CPSR
	bic r0,r0,#0xF //低4位清零->修改CPSR的[M4:M0]=[10000]，进入usr模式,bic(bit clear)
	bic r0,r0,#(1<<7) //第7位清零(IRQ),使能中断
	msr cpsr,r0
	/*设置 sp_usr*/
	ldr sp, =0x33F00000
	ldr pc, =sdram //绝对跳转

/*=======================================================================================*/	

sdram:
	bl uart0_init

und_code:
	swi 0x123  /* 执行此命令, 触发SWI异常, 进入0x8执行 */
	ldr pc, =main //绝对跳转,跳转到SDRAM
	
halt:
	b halt





