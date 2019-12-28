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

/* 函数：nand_write_data
 * 功能：往Nand Flash写一个字节的【数据】
 */
void nand_write_data(unsigned char data)
{
	volatile i;
	NFDATA = data;
	for(i=0;i<10;i++);//适当延时，保证稳定性
}



/* 函数：nand_read_data
 * 功能：从Nand Flash读一个字节的【数据】
 */
unsigned char nand_read_data(void)
{
	return NFDATA;
}

/*===============================应用函数=================================================*/	

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
		id_info[i] = nand_read_data();
	}
	nand_disable_cs();//禁止CS

	printf("\r\n===================\r\n");
	printf("Maker  Code: 0x%x\r\n",id_info[0]);
	printf("Device Code: 0x%x\r\n",id_info[1]);
	printf("3rd   cycle: 0x%x\n\r",id_info[2]);
	printf("Page   size: %d KB\n\r",1  << (id_info[3] & 0x03));       //页大小与id_info[3]最低2位有关
	printf("Block  size: %d KB\n\r",64 << ((id_info[3] >> 4) & 0x03));//块大小与id_info[3]第4、5位有关
	printf("5th   cycle: 0x%x\n\r",id_info[4]);
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
				scan_nand_flash(); //识别nor flash
				break;
			case 'e':
			case 'E':
				//erase_nor_flash();//擦除nor flash 某个扇区
				break;
			case 'w':
			case 'W':
				//write_nor_flash();//写数据至某个地址
				break;
			case 'r':
			case 'R':
				//read_nor_flash(); //读某个地址数据
				break;
			default:
				break;
		}

	}
}


















