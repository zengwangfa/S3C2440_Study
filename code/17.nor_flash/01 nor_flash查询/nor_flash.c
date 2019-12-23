#include "s3c2440_soc.h"
#include "uart.h"
#include "printf.h"

//Nor Flash 地址线21：即可访问2M内存，`0x1FFFFF`，其范围地址为 0~0x1FFFFF
#define NOR_FLASH_BASE 0 /* Nor Flash基地址 nor-->cs0,base_addr = 0 */

/* Nor Flash写入一个字
 * 基地址：base，偏移地址：offset，写入的值：value
 * eg: 55 98
 * 往(0 + (0x55)<<1 )写入0x98
*/
void nor_write_word(unsigned int base,unsigned int offset,unsigned short value)
{
	volatile unsigned short *p = (volatile unsigned short *) (base + offset<<1);
	*p = value;
}

void nor_cmd(unsigned int offset,unsigned short cmd)
{
	nor_write_word(NOR_FLASH_BASE, offset, cmd);
}


/* Nor Flash读取一个字
 * 基地址：base，偏移地址：offset
 * eg: 55 98
 * 往(0 + (0x55)<<1 )写入0x98
*/
unsigned int nor_read_word(unsigned int base,unsigned int offset)
{
	volatile unsigned short *p = (volatile unsigned short *) (base + offset<<1);
	return *p;
}

unsigned int nor_dat(unsigned int offset)
{
	return nor_read_word(NOR_FLASH_BASE, offset);
}


void erase_nor_flash(void)
{


}

void write_nor_flash(void)
{

	
}

void read_nor_flash(void)
{

	
}
/* 进入NOR FLASH的CFI模式
 * 读取基本信息
 */
void scan_nor_flash(void)
{
	char str[4];
	/* 1.打印 Manifacture ID、Device ID */
	nor_cmd(0x55,0x98); //进入CFI Mode

	str[0] = nor_dat(0x10);	 //读取“QRY”，即Query查询
	str[1] = nor_dat(0x11);	
	str[2] = nor_dat(0x12);	
	str[3] = '\0';	
	printf("%s\r\n",str);	
	/* 2.打印容量 */

	/* 3.打印各个扇区的起始地址 */
}





//nor_flash菜单选择
void nor_flash_menu(void)
{
	char c;
	while(1){
		printf("[s] Scan nor flash\r\n");
		printf("[e] Erase nor flash\r\n");
		printf("[w] Write nor flash\r\n");
		printf("[r] Read nor flash\r\n");
		printf("[q] Quit nor flash\r\n");
		printf("Enter selection:");

		c = uart0_getchar();
		printf("%c\r\n",c); //回显

		/* 打印菜单 */
		/* 1.识别nor flash
	   	 * 2.擦除nor flash 某个扇区
	   	 * 3.写数据至某个地址
	   	 * 4.读某个地址数据
		 */
		switch(c){
			case 'q':
			case 'Q':
				return;
				break;
			case 's':
			case 'S':
				scan_nor_flash(); //识别nor flash
				break;
			case 'e':
			case 'E':
				erase_nor_flash();//擦除nor flash 某个扇区
				break;
			case 'w':
			case 'W':
				write_nor_flash();//写数据至某个地址
				break;
			case 'r':
			case 'R':
				read_nor_flash(); //读某个地址数据
				break;
			default:
				break;
		}

	}

}


