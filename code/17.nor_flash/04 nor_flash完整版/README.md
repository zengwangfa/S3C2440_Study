# 1.问题
## 1.1 系统异常卡死
- 执行多次的菜单选择，导致系统卡死
- [x] 该为定时器造成的异常错误，关闭定时器，则不会卡死

## 1.2 nor数据错误
- 读取设备ID时，读到的是`0x002f`,`0xea00`,该数据为反汇编中text的[0]上的数据

- [x] 编译程序加上选项：`-march=armv4`   或者指定芯片类型 `-mcpu=arm9tdmi`
否则像如下的写入操作会被分成两个strb步骤（我们需要的是strh,一次性写入两个字节），最后导致读取设备ID和厂家ID的时候出错。
```c
     volatile unsigned short *p =value;    
    *p = value;
```

# 2.记录
- Nor Flash 地址线21：即可访问2M内存，`0x1FFFFF`，其范围地址为 0~0x1FFFFF



## 2.4.2 region详细信息

> erase block region :里面含有1个或多个block，它们大小都一样，一个nor含有1个或多个region，一个region含有1个或多个block(扇区)

- Erase block region information:
    - `前2字节+1`：表示该region有多少个block
    - `后2字节*256`：表示该block的大小(bytes)

```c
	blocks = 1 + nor_dat(region_info_base) + (nor_dat(region_info_base+1)<<8);//低2字节，获取block数量
	block_size = 256 * (nor_dat(region_info_base+2) + (nor_dat(region_info_base+3)<<8));//高2字节，获取block大小
```

