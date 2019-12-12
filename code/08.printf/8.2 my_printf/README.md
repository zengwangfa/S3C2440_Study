- 由于ARM是精简指令集，对求余和除法操作基本上不支持
- 因此在链接的时候会出现以下报错
```
: undefined reference to `__umodsi3'

```

### 解决方法
- 增加编译linux内核源码linux/arch/arm/lib/lib1funcs.S（其是实现支持除法、求模操作等操作的库函数）