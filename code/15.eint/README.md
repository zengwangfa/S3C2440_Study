# 1.记录
- 设置中断源（让它能发出中断信号）
- 设置中断控制器（让它能发出中断信号给CPU）
- 设置CPU总开关（CPSR有I位，设置总开关，使能中断）

>处理时要分辨中断源
>处理完要清中断	

## 1.1 中断源
- 设置按键为中断源引脚
    - 配置引脚为外部中断模式
    - 配置中断为下降沿触发
    - 配置外部中断MASK使能

## 1.2 中断控制器

- 设置INTMASK（INTERRUPT MASK (INTMSK) REGISTER）中断屏蔽寄存器
    - 0 = Interrupt service is available.
    - 1 = Interrupt service is masked.


```c
//初始化中断控制器
void interrupt_init(void)
{
	INTMASK &= ~((1<<0) | (1<<2) | (1<<5));//使能中断
}
```


## 1.3 CPU使能中断

- 设置CPSR的I位
- 当设置为0时enable，设置为1时disable

```
mrs r0,cpsr    //读出CPSR
bic r0,r0,#(1<<7) //第7位清零(IRQ)
msr cpsr,r0
```
# 2.中断服务函数
## 2.1 分辨中断源
- 中断偏移寄存器 （INTERRUPT OFFSET (INTOFFSET) REGISTER）
- 可通过判断`INTOFFEST`的中的可知当前中断源



## 2.2 调用处理函数
- 该为触发外部中断，因此需要清除外部中断
- `EINTPEND` (External Interrupt Pending Register)
- 清除该中断，只需要对应写1即可，因此产生什么中断，只需要把该中断的`EINTPEND`的值写入`EINTPEND`


```c
	/* 2.调用对应的处理函数 ，清除对应的中断*/
	key_eint_irq(bit); 
```

## 2.3 清中断
- 从源头开始清：即先清除`SRCPND`，再清除`INTPND`

- 它只清除`SRCPND`与`INTPND`寄存器对应于数据中设置为1的位的位置，因此清除哪一个中断，只需要对应为写1即可