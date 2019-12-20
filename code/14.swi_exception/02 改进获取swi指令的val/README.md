# 1.问题
- 未解决，程序超过4K时，data数据会丢失


# 2.取出SWI指令中的值
- 在swi异常处理函数中，先将lr的值保存在r4中，因为执行完swi指令后，发生异常，`lr`会保存下一条指令的地址，因此lr-4即是swi指令的地址
- 用r0 = r4-4
- 传给打印函数 
```c
    sub r0,r4,#4
    bl printSWIVal
```
- 由下表可知，swi中断指令高8位可以忽略，即取后24位即可
```c
void printSWIVal(unsigned int *pSWI)
{
	unsigned int val = *pSWI & (~0xff000000);
	printf("SWI val = %x\r\n",val);
}
```