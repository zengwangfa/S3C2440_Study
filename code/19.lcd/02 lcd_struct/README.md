## 1.记录
### 1.1 NAND地址转换
```c
void read_nand_flash(unsigned int addr,unsigned char *buf,unsigned int len)
{
	int i = 0;

    /* 因为读取数据的时候是一次性读出一页，因此当给出
	 * 地址addr之后，每一页的数据大小是2K，因此我们可以
	 * 根据地址知道我们读取的数据是哪一个页
	 */
	int page = addr / 2048;

	/*page是定位到哪一个页，col变量定位的就是在这个
	 *页的偏移量
	 */
	int col  = addr % 2048;//列地址  addr &(2048-1); 
}
```

### 1.2 判断从nor/nand启动
- nor不能直接写入，写入需要发出一定格式的数据，才能写入，利用这个特性，来判断是否从Nor中启动
```c
/* 检查是否从NorFlash中启动
 * 方法：写0x12345678到0地址，在读取出来，如果得到0x12345678，表示0地址上的内容被修改，即为片内RAM，则为nand启动
 * 原因：nor不能直接写入，写入需要发出一定格式的数据，才能写入
 * 返回0为nand启动，返回1为nor启动
*/
int isBootFromNorFlash(void)
{
	volatile unsigned int *p = (volatile unsigned int *)0;
	unsigned int val = *p;//暂存[0]上的数据
	*p = 0x12345678;
	if(0x12345678 == *p){
		/* 写成功，对应nand启动 */
		*p = val;//恢复原来的值
		return 0;
	}
	else{
		return 1;
	}

}
```

### 1.3 擦除输入参数合法性
```c
	/* 检查参数合法性 */
	if(addr & (0x1FFFF)){ //128K
		printf("Err addr! Please enter an integral multiple of 128K\r\n");
		return -1;
	}
	if(len & (0x1FFFF)){ //128K
		printf("Err len! Please enter an integral multiple of 128K\r\n");
		return -1;
	}
```

## 2.注意
### 2.1 Makefile编译顺序
> 这里还需要注意一点，需要修改Makefile使编译生成的bin文件，使代码重定位的代码放在前4K，如果在后面的话，nand Flash拷贝到SRAM数据丢失会导致程序重定位失败。

```makefile
all: start.o init.o interrupt.o nand_flash.o main.o led.o uart.o printf.o string_utils.o lib1funcs.o
	arm-linux-ld -T sdram.lds $^ -o project.elf
	arm-linux-objcopy -O binary -S project.elf project.bin
	arm-linux-objdump -D project.elf > project.dis
	rm *.o *.elf
```	