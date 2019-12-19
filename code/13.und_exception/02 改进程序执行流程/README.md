### 记录

- 执行异常处理函数之前，硬件会处理的事情：
* [x] 1.lr_und保存有被中断模式中的下一条即将执行的指令的地址
* [x] 2.SPSR_und保存被中断模式CPSR
* [x] 3.CPSR的[M4:M0]=[11011],进入到und模式
* [x] 4.跳到0x04的模式执行程序，即跳到`b do_und`这一指令
	 


#### 1.1 在汇编中加入string
- [官方文档](http://web.mit.edu/gnu/doc/html/as_7.html)
- `.string "str"` Copy the characters in str to the object file. You may specify more than one string to copy, separated by commas. Unless otherwise specified for a particular machine, the assembler marks the end of each string with a 0 byte. You can use any of the escape sequences described in section Strings.


#### 1.2 MRS & MSR

> ARM中有两条指令用于在状态寄存器和通用寄存器之间传送数据

- MRS: 状态寄存器到通用寄存器的传送指令
    - `mrs r0,cpsr`   //将CPSR的值读出放在r0
- MSR: 通用寄存器到状态寄存器的传送指令
    - `msr cpsr, r0`  //将r0的值写入CPSR

#### 1.3 设置und的栈
- 由于后面需要保存寄存器数数据、以及发生函数调用并且需要传递参数，需要用到栈，因此需要先设置栈
- `ldr sp, =0x34000000`（随便指向一块未使用的内存）

#### 1.4 保存现场
- 根据未定义指令异常寄存器资源，在und异常处理函数总有可能需要用到r0~r12，因此先保存下来（保存在栈中）
- 以及lr寄存器，后面还需要返回
- `stmdb sp!, {r0-r12,lr}`
![937cca192d1ffb78675c5e61b2dcbaf4.png](en-resource://database/11053:1)


#### 1.5 处理异常
- 打印提示发生未定义异常，并打印CPSR的值
- `mrs r0,cpsr //把cpsr的值放入r0`

#### 1.6 恢复现场
- 依次恢复r0~r12的值，恢复cpsr的值，并把lr的值赋给PC
- ` ldmia sp,{r0-r12,pc}^` 
