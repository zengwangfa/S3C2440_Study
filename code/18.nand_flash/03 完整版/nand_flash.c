#include "s3c2440_soc.h"
#include "printf.h"

void nand_init(void)
{
#define TACLS   0
#define TWRPH0  1
#define TWRPH1  0 //为了方便理解，时间定义为宏

	/* 设置NAND 时序 */
	NFCONF = (TACLS<<12) | (TWRPH0<<8) | (TWRPH1<<4);
	/* 使能NAND FLASH控制器、禁止片选、初始化ECC */
	NFCONT = (1<<4) | (1<<1) | (1<<0);
}

/*===============================基本函数=================================================*/	

/* 使能片选CS */
void nand_enable_cs(void)
{
	NFCONT &= ~(1<<1);//0: Force nFCE to low (Enable chip select)
}

/* 禁止片选CS */
void nand_disable_cs(void)
{
	NFCONT |= (1<<1);
}


/* 函数：nand_write_cmd
 * 功能：往Nand Flash写一个字节的【命令】
 */
void nand_write_cmd(unsigned char cmd)
{
	volatile i;
	NFCMD = cmd;
	for(i=0;i<10;i++);//适当延时，保证稳定性
}

/* 函数：nand_write_addr
 * 功能：往Nand Flash写一个字节的【地址】
 */
void nand_write_addr(unsigned char addr)
{
	volatile i;
	NFADDR = addr;
	for(i=0;i<10;i++);//适当延时，保证稳定性
}

/* 函数：nand_write_data_byte
 * 功能：往Nand Flash写一个字节的【数据】
 */
void nand_write_data_byte(unsigned char data)
{
	volatile i;
	NFDATA = data;
	for(i=0;i<10;i++);//适当延时，保证稳定性
}



/* 函数：nand_read_data_byte
 * 功能：从Nand Flash读一个字节的【数据】
 */
unsigned char nand_read_data_byte(void)
{
	return NFDATA;
}

/* nand发出页（行）地址*/
void nand_page(unsigned int page)
{
	nand_write_addr(page & 0xFF);
	nand_write_addr((page >>  8) & 0xFF);
	nand_write_addr((page >> 16) & 0xFF);
}

/* nand发出列地址 */
void nand_col(unsigned int col)
{
	nand_write_addr(col & 0xFF);
	nand_write_addr((col >>  8) & 0xFF);
}

/*===============================应用函数=================================================*/	

/* 等待NAND就绪 */
void nand_wait_ready(void)
{
	while(!(NFSTAT & 0x01));//当NFSATA[0] = 1时，表示就绪
}

/* 检查地址所在的block与page */
void print_which_block_and_page(unsigned int addr)
{
	unsigned int whichpage = addr/2048;   //1 page  = 2K
	unsigned int whichblock= whichpage/64;//1 block = 64 page

	printf("***** This addr belongs to: page  --> %d, block --> %d\r\n",whichpage,whichblock);
}

/* 判断是否为坏块
 * ret:返回1为坏块，返回0不是
 */
int isNandBadBlock(unsigned int addr)
{
	unsigned int col = 2048;//读取OOB区第0个字节
	unsigned int page = addr / 2048;
	unsigned char val = 0;
	/* 1. 选中 */
	nand_enable_cs();
	/* 2. 发出读命令00h */
	nand_write_cmd(0x00);
	/* 3. 发出地址(分5步发出) */
	nand_col(col);
	nand_page(page);
	/* 4. 发出读命令30h */
	nand_write_cmd(0x30);
	/* 5. 判断状态,等待就绪 */
	nand_wait_ready();
	/* 6. 读数据 */
	val = nand_read_data_byte();
	/* 7. 取消选中 */	
	nand_disable_cs();

	if(val != 0xFF){
		return 1; /* 坏块 */
	}
	else{
		return 0;
	}
}
/* NAND FLASH读取数据
 * param:读取的地址、存放的地址、读取的长度
 */
void read_nand_data(unsigned int addr,unsigned char *buf,unsigned int len)
{
	int i = 0;
	/*page是定位到哪一个页，col变量定位的就是在这个
	 *页的偏移量（在这个页上的第几列0~2047）
	 */
	int col = addr % 2048;//列地址  addr &(2048-1); 

    /* 因为读取数据的时候是一次性读出一页，因此当给出
	 * 地址addr之后，每一页的数据大小是2K，因此我们可以
	 * 根据地址知道我们读取的数据是哪一个页
	 */
	int page = addr / 2048;//行地址（相当于页地址）
    /* 1.使能CS */
	nand_enable_cs();

	while(1){

		/* 2.发出0x00命令 */
		nand_write_cmd(0x00);
		/* 3.发出地址 col addr */
		nand_col(col);
		nand_page(page); /* row/page addr */
		/* 4.发出0x30命令 */
		nand_write_cmd(0x30);
        /* 5.等待就绪 */
        nand_wait_ready(); 
        /* for循环中有2个条件
         * 1.当读到页尾，但还是没有读完，说明需要读取下一页
         * 2.当已经读取指定字节数，则不再读取
         */     
        for(; (col < 2048) && (i < len); col++){
        	/* 6.读数据 */
        	buf[i++] = nand_read_data_byte();
        }
        if(i == len){
        	break;
        }
        col = 0;
        page++;//指向下一页
	}
	/* 7.禁止CS */
	nand_disable_cs(); 
}

/* NAND FLASH擦除数据
 * param:擦除的起始地址、擦除的长度(byte)
 * ret:失败-1，成功0
*/
int erase_nand_data(unsigned int addr,unsigned int len)
{
	int page = addr / 2048;//行地址

	/* 检查参数合法性 */
	if(addr & (0x1FFFF)){ //128K
		printf("Err addr! Please enter an integral multiple of 128K\r\n");
		return -1;
	}
	if(len & (0x1FFFF)){ //128K
		printf("Err len! Please enter an integral multiple of 128K\r\n");
		return -1;
	}
	/* 1.使能CS */
	nand_enable_cs();
	while(1)
	{
		page = addr / 2048;//行地址

		/* 2.发出0x60命令 */
		nand_write_cmd(0x60); 
		/* 3.发出地址row/page addr */
		nand_page(page);      
		/* 4.发出0xD0命令 */
		nand_write_cmd(0xD0); 
		/* 5.等待就绪(等待擦除完成) */
		nand_wait_ready();    

		len -= (128*1024);//长度减去一个block
		if(0 == len){
			break;
		}
		addr += (128*1024);//指向下一块
	} 
	/* 6.禁止CS */
	nand_disable_cs();
	return 0;
}

/* NAND FLASH写入数据
 * param:写入的地址、数据指针、写入的长度
 */
void write_nand_data(unsigned int addr,unsigned char *buf,unsigned int len)
{
	int i = 0;
	int page = addr / 2048;
	int col = addr & (2048 - 1);
	/* 1.使能CS */
	nand_enable_cs();
	while(1){
		/* 2.发出0x80命令 */
		nand_write_cmd(0x80);
		/* 3.发出地址 */
		nand_col(col);
		nand_page(page);
		/* 4.写入数据*/
		for(; (col < 2048) && (i < len); ){
			nand_write_data_byte(buf[i++]);			
		}
		/* 5.发出0x10命令 */
		nand_write_cmd(0x10);
		/* 6.等待就绪(等待写入完成) */
		nand_wait_ready();
		if(i == len){
			break;
		}
		else{
			col = 0;
			page++;
		}

	}
	/* 7.禁止CS */
	nand_disable_cs();
}

/*===============================应用函数封装===============================================*/	

/* 识别NAND FLASH */
void scan_nand_flash(void)
{
	int i;
	//保存读取ID信息的数组
	unsigned char id_info[5] = {0};

	nand_enable_cs();//使能CS
	nand_write_cmd(0x90);
	nand_write_addr(0x00);

	for(i = 0;i < 5;i++){
		id_info[i] = nand_read_data_byte();
	}
	nand_disable_cs();//禁止CS

	printf("\r\n========== id_info =========\r\n");
	printf("Maker  Code: 0x%x\r\n",id_info[0]);
	printf("Device Code: 0x%x\r\n",id_info[1]);
	printf("3rd   cycle: 0x%x\r\n",id_info[2]);
	printf("4th   cycle: 0x%x\r\n",id_info[3]);
	printf("5th   cycle: 0x%x\r\n\r\r",id_info[4]);
	printf("Page   size: %d KB\n\r",1  << (id_info[3] & 0x03));       //页大小与id_info[3]最低2位有关
	printf("Block  size: %d KB\n\r",64 << ((id_info[3] >> 4) & 0x03));//块大小与id_info[3]第4、5位有关
	printf("===========================\r\n");
}

/* 测试函数：读数nand上160bytes数据 
 */
void read_nand_flash(void)
{
	int i,j;
	unsigned int addr,hex_addr;
	unsigned char c,str[16],data[160];
	volatile unsigned char *p;

	/* 获得地址 */
	printf("***** Enter the address to read:");
	addr = get_uint();

	print_which_block_and_page(addr); //打印该地址所在的page与block

	read_nand_data(addr,data,160);//获取到地址上的数据
	p = (volatile unsigned char *)data;//p指向data,用于打印data数据

	hex_addr = addr;//起始地址
	printf("***** Read Data:\r\n");
	printf("            00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f\n\r");
 	/* 长度固定为160 bytes */	
	for(i = 0; i < 10; i++){
		printf("0x%08x  ",hex_addr);
		//每行打印16个16进制数
		for(j = 0; j < 16; j++){
			c = *p++;//读取16个
			str[j] = c;//保存字符
			//先打印数值
			printf("%02x ",c);
		}
		printf(" | ");
		//后打印字符
		for(j = 0; j < 16; j++){
			if(str[j] < 0x20 || str[j] > 0x7e){//不可视字符,打印‘.’
				printf(".");
			}
			else{
				printf("%c",str[j]);
			}
		}
		hex_addr+=16;//换行+16
		printf("\n\r");
	}

}

/* 擦除测试函数：固定擦除一个1block = 128K
*/
void erase_nand_flash(void)
{
	int addr;
	unsigned int whichblock;
	/* 获得第几个Block */
	printf("Enter the address of sector to erase: ");
	addr = get_uint();

	whichblock = addr / (128*1024);

	printf("***** block number : [ %d ]\r\n",whichblock);

	/* 提示擦除数据的范围 */
	printf("***** Erase range : 0x%08x - 0x%08x\n\r",addr,(addr+(128*1024)));
 	printf("***** erase ...\r\n");

 	if(erase_nand_data(addr,128*1024) == 0){//如果擦除成功
 		printf("***** Erase finished!\r\n");
 	}
 	else{
 		printf("***** Erase fail!\r\n");
 	}
}

void write_nand_flash(void)
{
	unsigned int addr;
	unsigned char str[50];
	unsigned int len;

	/* 获得第几个Block */
	printf("***** Enter addr to write: ");
	addr = get_uint();

	printf("***** Enter the string to write: ");
	gets(str);
	len = strlen(str) + 1;

	printf("***** write range : 0x%08x - 0x%08x\r\n",addr,(addr + len));
	printf("***** writing ...\r\n");

	write_nand_data(addr,str,strlen(str)+1);//strlen不包括结束符'\0'，因此需要+1
	printf("***** writing finished\r\n");
}

void nand_flash_menu(void)
{
	char c;
	while(1){
		printf("[s] Scan nand flash\r\n");
		printf("[e] Erase nand flash\r\n");
		printf("[w] Write nand flash\r\n");
		printf("[r] Read nand flash\r\n");
		printf("[q] Quit nand flash\r\n");
		printf("Enter selection:");

		c = uart0_getchar();
		printf("%c\r\n",c); //回显

		/* 打印菜单 */
		/* 1.识别nand flash
	   	 * 2.擦除nand flash 某个扇区
	   	 * 3.写数据至某个地址
	   	 * 4.读某个地址数据
		 */
		switch(c){
			case 'q':
			case 'Q':
				return;
			case 's':
			case 'S':
				scan_nand_flash(); //识别nana flash
				break;
			case 'e':
			case 'E':
				erase_nand_flash();//擦除nana flash 某个block
				break;
			case 'w':
			case 'W':
				write_nand_flash();//写数据至某个地址
				break;
			case 'r':
			case 'R':
				read_nand_flash(); //读某个地址 160个byte数据
				break;
			default:
				break;
		}

	}
}


















