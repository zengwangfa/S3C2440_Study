# 1.SWI中软处理过程
- 执行异常处理函数之前，硬件会处理的事情：
* [x] 1.lr_svc保存有被中断模式中的下一条即将执行的指令的地址
* [x] 2.SPSR_svc保存被中断模式CPSR
* [x] 3.CPSR的[M4:M0]=[11011],进入到svc模式
* [x] 4.跳到`0x08`的模式执行程序，即跳到`b do_svc`这一指令


## 1.1设置栈
- sp_svc 设置栈，因为后面有函数需要用到栈 
- `ldr sp, =0x33E00000`
## 1.2 保存现场
- `stmdb`：stm（m为many），即写多个内存，db预先减少(Decrement Before)，即**先减后写**
- r是异常处理完后的返回地址，也需要保存 
- `stmdb sp!, {r0-r12,lr}` //在swi异常处理函数总有可能需要用到r0~r12，因此先保存下来


## 1.3 处理swi异常
- 打印提示发生未定义异常，并调用打印函数显示CPSR的值
- `mrs r0,cpsr //把cpsr的值放入r0`

、预先增加(Increment Before)、过后减少(Decrement After)、。 
## 1.4 恢复现场

- `ldmia`：ldm（m为many）即读多个内存，ia(Increment After)过后增加，即**先读后加**
- 将lr的值赋给pc ,`^`会把spsr的值恢复到cpsr中

- `ldmia sp,{r0-r12,pc}^ `


