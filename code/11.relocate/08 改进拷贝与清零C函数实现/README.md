### 记录
- lds中的变量保存在符号表（symbol table）里面，直接存放变量的值，而不是地址。因此想要获取lds中的变量数值，直接进行取地址即可。
```
	volatile unsigned int *start = (volatile unsigned int *)&__bss_start;
```
- 在符号表（symbol table），一般变量存放的是变量的地址（addr）