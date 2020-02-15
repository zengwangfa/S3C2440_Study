### 工具
交叉编译freetype-2.4.10，并将其相关`include`、`lib`复制到gcc工具链中


### 编译
```
arm-linux-gcc -finput-charset=GBK -fexec-charset=GBK -o show_line show_line.c -lfreetype -lm 
```