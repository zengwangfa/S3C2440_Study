# 1.记录
- 把每一个中断的处理函数放置在指针数组中，当发生中断时，通过判断**中断号**，调用对应的函数即可

---

- 定义函数指针,指针的变量名为irq_func
```c
typedef void (*irq_func)(int);

irq_func irq_array[32];//定义存放函数指针数组(即：数组中存放的是函数指针)
```


- `typedef void(*Func)(void)`的用途,先来看下其基本用法

```c
	typedef void (*func)(void);  
	void myfunc(void);  
	func pfun = myfunc;/*赋值*/  
	pfun();/*调用*/  
```

## 1.1 由来
`typedef void(*Func)(void);`的由来
其实这样的形式声明函数指针是有"问题"的。如果仿照变量类型声明，声明函数指针似乎应该这样：
`typedef void(*)()  variable;`

但是c标准的创建者没有这样做，不知道为什么，而选择了这样的声明：

`typedef void(*variable)();`

C编译器非常清楚，这就是在声明一个void(*)() 类型的函数指针variable。
